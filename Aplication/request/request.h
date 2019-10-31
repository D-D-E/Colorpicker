#ifndef REQUEST_REQUEST_H_
#define REQUEST_REQUEST_H_
#include "stdint.h"

typedef void (*function_pointer)();

extern const char *PAGES[];
extern const function_pointer FUNCTIONS[];

void CONFIG();
void CONFIG_parse();

void PICKER();
void PICKER_parse();

void PickerParseLed();

void ESP_Request(const char ** pages, const function_pointer * functions, uint8_t number);

#endif /* REQUEST_REQUEST_H_ */
