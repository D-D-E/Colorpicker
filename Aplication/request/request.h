#ifndef REQUEST_REQUEST_H_
#define REQUEST_REQUEST_H_
#include "stdint.h"

typedef void (*foo)();

extern const char *PAGES[];
extern const foo FUNCTIONS[];

void PICKER();
void PICKER_parse();
void PickerParseLed();

void ESP_Request(const char ** pages, const foo * functions, uint8_t number);

#endif /* REQUEST_REQUEST_H_ */
