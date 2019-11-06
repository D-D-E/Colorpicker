#ifndef STATUS_LED_STATUS_LED_H_
#define STATUS_LED_STATUS_LED_H_

void StatusLedInit(void);

void StatusLedON();
void StatusLedOFF();

void APModeBlink();
void ErrorPowerBlink();
void ErrorBlink();

#endif /* STATUS_LED_STATUS_LED_H_ */
