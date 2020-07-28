// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef LED_UART_H_
#define LED_UART_H_
#include "Arduino.h"
#include "Timer2.h"
//add your includes for the project LED_UART here


#define FORWARD 0x09
#define BACK 0x06
#define STOP 0x00
#define LEFT_U 0x0A
#define RIGHT_U 0x05
#define EMERGENCY 0xEE
#define IDLE 0x00

#define BLINK_OFF 0
#define BLINK_ON 1

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project LED_UART here

void Timer2_ISR();
void LED_control(int da);
void PORT_init();


//Do not add code below this line
#endif /* LED_UART_H_ */
