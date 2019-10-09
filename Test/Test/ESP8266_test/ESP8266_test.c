#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"
#include <string.h>
#include "ESP8266.h"
#include "ring_buffer.h"
#include "request.h"
#include "uart.h"


static void test_esp_init(void **state)
{
    ESPInit();
}

static void test_esp_reset(void **state)
{
    ESP_Resset();
}

static void test_esp_mode_station(void **state)
{
    SetReceiveData("OK");
    assert_int_equal(ESP_SetModeStation(), 1);
}

static void test_esp_corrupted_start_ap(void **state)
{
    SetReceiveData("OK");
    ESP_StopTCPServer(80);

    SetReceiveData("ERROR");
    assert_int_equal(ESP_SetModeSoftAP(), 0);
    SetReceiveData("OK");
    assert_int_equal(ESP_SetParamsSoftAP("ssid", "passwd"), 1);
    SetReceiveData("OK");
    assert_int_equal(ESP_StartTCPServer(80), 1);
}

static void test_esp_corrupted_set_params_ap(void **state)
{
    SetReceiveData("OK");
    ESP_StopTCPServer(80);

    SetReceiveData("OK");
    assert_int_equal(ESP_SetModeSoftAP(), 1);
    SetReceiveData("ERROR");
    assert_int_equal(ESP_SetParamsSoftAP("ssid", "passwd"), 0);
    SetReceiveData("OK");
    assert_int_equal(ESP_StartTCPServer(80), 1);
}

static void test_esp_corrupted_start_server(void **state)
{
    SetReceiveData("OK");
    ESP_StopTCPServer(80);

    SetReceiveData("OK");
    assert_int_equal(ESP_SetModeSoftAP(), 1);
    SetReceiveData("OK");
    assert_int_equal(ESP_SetParamsSoftAP("ssid", "passwd"), 1);
    SetReceiveData("ERROR");
    assert_int_equal(ESP_StartTCPServer(80), 0);
}

static void test_esp_start(void **state)
{
    SetReceiveData("OK");
    ESP_StopTCPServer(80);

    SetReceiveData("OK");
    assert_int_equal(ESP_SetModeSoftAP(), 1);
    SetReceiveData("OK");
    assert_int_equal(ESP_SetParamsSoftAP("ssid", "passwd"), 1);
    SetReceiveData("OK");
    assert_int_equal(ESP_StartTCPServer(80), 1);
}

static void test_esp_stop(void **state)
{
    SetReceiveData("OK");
    assert_int_equal(ESP_StopTCPServer(80), 1);
}

static void test_esp_request_not_found(void **state)
{
    SetReceiveData(">");
    ESP_Request(NULL, NULL, 0);
}

static void test_esp_request_not_found_page(void **state)
{
    SetReceiveData("+IPD,1,112  GET /NOT_EXIST  >");
    ESP_Request(PAGES, FUNCTIONS, 2);
}

static void test_esp_request_id_found(void **state)
{
    SetReceiveData("+IPD,8,112  >");
    ESP_Request(PAGES, FUNCTIONS, 2);
}

static void test_esp_request_page_found(void **state)
{
    SetReceiveData("+IPD,1,122, GET /PICKER     >");
    ESP_Request(PAGES, FUNCTIONS, 2);
}

static void test_esp_request_page_set(void **state)
{
    SetReceiveData("+IPD,1,122, GET /PICKER?picker=%23ffffff    >");
    ESP_Request(PAGES, FUNCTIONS, 2);
}

static void test_esp_request_page_null(void **state)
{
    SetReceiveData("+IPD,1,122, GET /PICKER   >");
    ESP_Request(NULL, NULL, 2);
}

static void test_esp_send_data(void **state)
{
    SetReceiveData(">");
    char test[] = "send test data";
    ESP_SendData(test, strlen(test), 0);

    assert_int_equal(GetSendData()[0], 'a');
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
            cmocka_unit_test(test_esp_init)
           ,cmocka_unit_test(test_esp_reset)
           ,cmocka_unit_test(test_esp_corrupted_start_ap)
           ,cmocka_unit_test(test_esp_corrupted_set_params_ap)
           ,cmocka_unit_test(test_esp_corrupted_start_server)
           ,cmocka_unit_test(test_esp_mode_station)
           ,cmocka_unit_test(test_esp_start)
           ,cmocka_unit_test(test_esp_stop)
           ,cmocka_unit_test(test_esp_request_not_found)
           ,cmocka_unit_test(test_esp_request_not_found_page)
           ,cmocka_unit_test(test_esp_request_id_found)
           ,cmocka_unit_test(test_esp_request_page_found)
           ,cmocka_unit_test(test_esp_request_page_set)
           ,cmocka_unit_test(test_esp_request_page_null)
           ,cmocka_unit_test(test_esp_send_data)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}


