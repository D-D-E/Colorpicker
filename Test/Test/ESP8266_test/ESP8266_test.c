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
    SetReceiveData("OK", 2);
    assert_int_equal(ESP_SetModeStation(), 1);
}

static void test_esp_corrupted_start_ap(void **state)
{
    SetReceiveData("OK", 2);
    ESP_StopTCPServer(80);

    SetReceiveData("ERROR", 5);
    assert_int_equal(ESP_SetModeSoftAP(), 0);
    SetReceiveData("OK", 2);
    assert_int_equal(ESP_SetParamsSoftAP("ssid", "passwd"), 1);
    SetReceiveData("OK", 2);
    assert_int_equal(ESP_StartTCPServer(80), 1);
}

static void test_esp_corrupted_set_params_ap(void **state)
{
    SetReceiveData("OK", 2);
    ESP_StopTCPServer(80);

    SetReceiveData("OK", 2);
    assert_int_equal(ESP_SetModeSoftAP(), 1);
    SetReceiveData("ERROR", 5);
    assert_int_equal(ESP_SetParamsSoftAP("ssid", "passwd"), 0);
    SetReceiveData("OK", 2);
    assert_int_equal(ESP_StartTCPServer(80), 1);
}

static void test_esp_corrupted_start_server(void **state)
{
    SetReceiveData("OK", 2);
    ESP_StopTCPServer(80);

    SetReceiveData("OK", 2);
    assert_int_equal(ESP_SetModeSoftAP(), 1);
    SetReceiveData("OK", 2);
    assert_int_equal(ESP_SetParamsSoftAP("ssid", "passwd"), 1);
    SetReceiveData("ERROR", 5);
    assert_int_equal(ESP_StartTCPServer(80), 0);
}

static void test_esp_start(void **state)
{
    SetReceiveData("OK", 2);
    ESP_StopTCPServer(80);

    SetReceiveData("OK", 2);
    assert_int_equal(ESP_SetModeSoftAP(), 1);
    SetReceiveData("OK", 2);
    assert_int_equal(ESP_SetParamsSoftAP("ssid", "passwd"), 1);
    SetReceiveData("OK", 2);
    assert_int_equal(ESP_StartTCPServer(80), 1);
}

static void test_esp_stop(void **state)
{
    SetReceiveData("OK", 2);
    assert_int_equal(ESP_StopTCPServer(80), 1);
}

static void test_esp_send_data(void **state)
{
    ClearSendData();
    SetReceiveData(">", 1);
    char test[] = "send test data";
    char answer[] = "AT+CIPSEND=0,14\r\nsend test data";
    ESP_SendConstData(test, strlen(test), 0);
    for(int i = 0; i < 14; i++)
    {
        assert_int_equal(GetSendData()[i], answer[i]);
    }
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
           ,cmocka_unit_test(test_esp_send_data)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}


