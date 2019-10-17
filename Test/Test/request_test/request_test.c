#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"
#include <string.h>
#include "led.h"
#include "request.h"
#include "ring_buffer.h"
#include "uart.h"
#include "ESP8266.h"

char test[] = "AT+CIPSEND=0,26\r\nHTTP/1.1 404 Not Found\r\n";
char NOT_FOUND[] = "+IPD,0,498:GET /NEXIST HTTP/1.1\r\nHost: 192.168.4.1\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36<\r><\n>Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\n  >";
char INCORRECTID[] = "+IPD,8,498:GET /PICKER HTTP/1.1\r\nHost: 192.168.4.1\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36<\r><\n>Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\n   >";
char CORRECT_ID0[] = "+IPD,0,498:GET /PICKER HTTP/1.1\r\nHost: 192.168.4.1\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36<\r><\n>Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\n  >";
char CORRECT_ID1[] = "+IPD,1,498:GET /PICKER HTTP/1.1\r\nHost: 192.168.4.1\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36<\r><\n>Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\n  >";
char CORRECT_ID2[] = "+IPD,2,498:GET /PICKER HTTP/1.1\r\nHost: 192.168.4.1\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36<\r><\n>Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\n  >";
char CORRECT_ID3[] = "+IPD,3,498:GET /PICKER HTTP/1.1\r\nHost: 192.168.4.1\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36<\r><\n>Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\n  >";
char CORRECT_ID4[] = "+IPD,4,498:GET /PICKER HTTP/1.1\r\nHost: 192.168.4.1\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36<\r><\n>Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\n  >";
char COLORSET[] = "+IPD,1,506:GET /PICKER?picker=%23ffffff HTTP/1.1\r\nHost: 192.168.4.1\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\n  >";


static void test_esp_request_empty(void **state)
{
    ClearSendData();
    SetReceiveData(" ", 1);
    ESP_Request(NULL, NULL, 0);
    ESP_Request(PAGES, FUNCTIONS, 2);
    for(int i = 0; i < 512; i++)
    {
        assert_int_equal(0, GetSendData()[i]);
    }
}

static void test_esp_request_not_found_page(void **state)
{
    ClearSendData();
    SetReceiveData(NOT_FOUND, strlen(NOT_FOUND));
    ESP_Request(PAGES, FUNCTIONS, 2);
    assert_memory_equal(test, GetSendData(), strlen(test));
}

static void test_esp_request_incorrect_id(void **state)
{
    ClearSendData();
    SetReceiveData(INCORRECTID, strlen(INCORRECTID));
    ESP_Request(PAGES, FUNCTIONS, 2);
    for(int i = 0; i < 512; i++)
    {
        assert_int_equal(0, GetSendData()[i]);
    }
}

static void test_esp_request_page_found_id0(void **state)
{
    ClearSendData();
    RingBuff_Clear();
    SetReceiveData(CORRECT_ID0, strlen(CORRECT_ID0));
    ESP_Request(PAGES, FUNCTIONS, 2);
    assert_int_equal(0, GetLinkID());
}

static void test_esp_request_page_found_id1(void **state)
{
    ClearSendData();
    SetReceiveData(CORRECT_ID1, strlen(CORRECT_ID1));
    ESP_Request(PAGES, FUNCTIONS, 2);
    assert_int_equal(1, GetLinkID());
}

static void test_esp_request_page_found_id2(void **state)
{
    ClearSendData();
    SetReceiveData(CORRECT_ID2, strlen(CORRECT_ID2));
    ESP_Request(PAGES, FUNCTIONS, 2);
    assert_int_equal(2, GetLinkID());
}

static void test_esp_request_page_found_id3(void **state)
{
    ClearSendData();
    SetReceiveData(CORRECT_ID3, strlen(CORRECT_ID3));
    ESP_Request(PAGES, FUNCTIONS, 2);
    assert_int_equal(3, GetLinkID());
}

static void test_esp_request_page_found_id4(void **state)
{
    ClearSendData();
    SetReceiveData(CORRECT_ID4, strlen(CORRECT_ID4));
    ESP_Request(PAGES, FUNCTIONS, 2);
    assert_int_equal(4, GetLinkID());
}

static void test_esp_request_page_picker_set_color(void **state)
{
    ClearSendData();
    SetReceiveData(COLORSET, strlen(COLORSET));
    ESP_Request(PAGES, FUNCTIONS, 2);
    assert_int_equal(Led_Get_Color(eRed), 4095);
    assert_int_equal(Led_Get_Color(eGreen), 4095);
    assert_int_equal(Led_Get_Color(eBlue), 4095);
}

static void test_esp_request_page_null(void **state)
{
    ClearSendData();
    SetReceiveData(CORRECT_ID0, strlen(CORRECT_ID0));
    ESP_Request(NULL, NULL, 2);
    assert_memory_equal(test, GetSendData(), strlen(test));
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
            cmocka_unit_test(test_esp_request_empty)
           ,cmocka_unit_test(test_esp_request_not_found_page)
           ,cmocka_unit_test(test_esp_request_incorrect_id)
           ,cmocka_unit_test(test_esp_request_page_found_id0)
           ,cmocka_unit_test(test_esp_request_page_found_id1)
           ,cmocka_unit_test(test_esp_request_page_found_id2)
           ,cmocka_unit_test(test_esp_request_page_found_id3)
           ,cmocka_unit_test(test_esp_request_page_found_id4)
           ,cmocka_unit_test(test_esp_request_page_picker_set_color)
           ,cmocka_unit_test(test_esp_request_page_null)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
