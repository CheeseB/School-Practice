#include "LED_UART.h"

int Front_LED = 10;
int BACK_LED = 9;
int BUZZER = 45;
unsigned char LED_value = 0, LED_mode=0, Blink=0, Buzzer=0, LED_status=STOP;
unsigned char Command = 0;

void setup()
{
	PORT_init();
	Serial.begin(115200);
	Serial.print("SmartCAR >>");
	Timer2::set(500000,Timer2_ISR);
	Timer2::start();
}

void loop()
{
	if(Serial.available() > 0)
	{
		Command = Serial.read();
		Serial.write(Command);
		switch(Command)
		{
			case 'y':
				LED_status = FORWARD;
				break;
			case 's':
				LED_status = STOP;
				break;
			case 'b':
				LED_status = BACK;
				break;
			case 't':
				LED_status = LEFT_U;
				break;
			case 'u':
				LED_status = RIGHT_U;
				break;
			case 'e':
				LED_status = EMERGENCY;
				break;
			default:
				LED_status=IDLE;
				break;
		}
	}
}

void Timer2_ISR()
{
	switch(LED_status)
	{
		case FORWARD:
			LED_value = 1;
			Blink = BLINK_OFF;
			Buzzer = 0;
			break;
		case BACK:
			LED_value = 2;
			Blink = BLINK_ON;
			Buzzer = 0;
			break;
		case LEFT_U:
		case RIGHT_U:
			LED_value = 3;
			Blink = BLINK_ON;
			Buzzer = 0;
			break;
		case EMERGENCY:
			LED_value = 3;
			Blink = BLINK_ON;
			Buzzer = 1;
			break;
		case IDLE:
		default:
			LED_value=0;
			Blink= BLINK_OFF;
			Buzzer = 0;
			break;
	}

	LED_control(LED_value);
	if(LED_mode==0)
	{
		if(Blink ==BLINK_ON)
		{
			LED_control(0);
		}
		LED_mode =1;
	}
	else
		LED_mode = 0;

		digitalWrite(BUZZER,Buzzer);
}

void LED_control(int da)
{
	digitalWrite(Front_LED,(da & 0x01));
	digitalWrite(BACK_LED,((da>>1))&0x01);
}

void PORT_init()
{
	pinMode(Front_LED,OUTPUT);
	pinMode(BACK_LED,OUTPUT);
	pinMode(BUZZER,OUTPUT);
	digitalWrite(Front_LED,LOW);
	digitalWrite(BACK_LED,LOW);
	digitalWrite(BUZZER,LOW);
}
