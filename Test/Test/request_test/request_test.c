#include <mock_obj/esp_mock/ESP8266.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"
#include <string.h>
#include "led.h"
#include "request.h"

char test[] = "HTTP/1.1 404 Not Found\r\n";
char NOT_FOUND[] = "+IPD,0,498:GET /NEXIST HTTP/1.1\r\nHost: 192.168.4.1\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36<\r><\n>Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\nReferer: http://192.168.4.1/PICKER\r\nAccept-Encoding: gzip, deflate\r\nAccept-Language: en-US,en;q=0.9,ru;q=0.8,uk;q=0.7\r\n\r\n  >";
char INCORRECTID[] = "+IPD,8,498:GET /PICKER HTTP/1.1\r\nHost: 192.168.4.1\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36<\r><\n>Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\nReferer: http://192.168.4.1/PICKER\r\nAccept-Encoding: gzip, deflate\r\nAccept-Language: en-US,en;q=0.9,ru;q=0.8,uk;q=0.7\r\n\r\n  >";
char NORMAL[] = "+IPD,0,498:GET /PICKER HTTP/1.1\r\nHost: 192.168.4.1\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36<\r><\n>Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\nReferer: http://192.168.4.1/PICKER\r\nAccept-Encoding: gzip, deflate\r\nAccept-Language: en-US,en;q=0.9,ru;q=0.8,uk;q=0.7\r\n\r\n  >";
char COLORSET[] = "+IPD,1,506:GET /PICKER?picker=%23ffffff HTTP/1.1\r\nHost: 192.168.4.1\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\nReferer: http://192.168.4.1/PICKER?picker=%23004080\r\nAccept-Encoding: gzip, deflate\r\nAccept-Language: en-US,en;q=0.9,ru;q=0.8,uk;q=0.7\r\n >";

static void test_esp_request_not_found(void **state)
{
    ClearSendESPData();
    SetAnswer(" ", 1);
    ESP_Request(NULL, NULL, 0);
    ESP_Request(PAGES, FUNCTIONS, 2);
    for(int i = 0; i < 512; i++)
    {
        assert_int_equal(0, GetSendESPData()[i]);
    }
}

static void test_esp_request_not_found_page(void **state)
{
    ClearSendESPData();
    SetAnswer(NOT_FOUND, 538);
    ESP_Request(PAGES, FUNCTIONS, 2);
    assert_memory_equal(test, GetSendESPData(), strlen(test));
}

static void test_esp_request_id_found(void **state)
{
    ClearSendESPData();
    SetAnswer(INCORRECTID, 538);
    ESP_Request(PAGES, FUNCTIONS, 2);
    for(int i = 0; i < 512; i++)
    {
        assert_int_equal(0, GetSendESPData()[i]);
    }
}

static void test_esp_request_page_found(void **state)
{
    SetAnswer(NORMAL, 538);
    ESP_Request(PAGES, FUNCTIONS, 2);
}

static void test_esp_request_page_set(void **state)
{
    SetAnswer(COLORSET, 535);
    ESP_Request(PAGES, FUNCTIONS, 2);
    assert_int_equal(Led_Get_Color(eRed), 65535);
    assert_int_equal(Led_Get_Color(eGreen), 65535);
    assert_int_equal(Led_Get_Color(eBlue), 65535);
}

static void test_esp_request_page_null(void **state)
{
    ClearSendESPData();
    SetAnswer(NORMAL, 538);
    ESP_Request(NULL, NULL, 2);
    assert_memory_equal(test, GetSendESPData(), strlen(test));
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
            cmocka_unit_test(test_esp_request_not_found)
           ,cmocka_unit_test(test_esp_request_not_found_page)
           ,cmocka_unit_test(test_esp_request_id_found)
           ,cmocka_unit_test(test_esp_request_page_found)
           ,cmocka_unit_test(test_esp_request_page_set)
           ,cmocka_unit_test(test_esp_request_page_null)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
