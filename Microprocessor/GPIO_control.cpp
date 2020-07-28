#include "GPIO_control.h"

int Motor[6] = { 22, 23, 24, 25, 4, 5 };
int PWM_value = 165;

void setup() {
	int z;
	Serial.begin(115200);
	for (z = 0; z < 6; z++) {
		pinMode(Motor[z], OUTPUT);
		digitalWrite(Motor[z], LOW);
	}
	Motor_Control('A', PWM_value);
}
void loop() {
}
void Motor_mode(int da) {
	int z;
	for (z = 0; z < 4; z++)
		digitalWrite(Motor[z], (da >> z) & 0x01);
}
void Motor_Control(char da, unsigned int OC_value) {
	switch (da) {
	case 'L':
		analogWrite(Motor[4], OC_value);
		break;
	case 'R':
		analogWrite(Motor[5], OC_value);
		break;
	case 'A':
		analogWrite(Motor[4], OC_value);
		analogWrite(Motor[5], OC_value);
		break;
	}
}
void serialEvent() {
	char data = Serial.read();
	Serial.write(data);
	switch (data) {
	case 'y':
		Motor_mode (FORWARD);
		break;

	case 'b':
		Motor_mode (BACKWARD);
		break;
	case 't':
		Motor_mode (LEFT_U);

		break;
	case 'u':
		Motor_mode (RIGHT_U);
		break;
	case 's':
		Motor_mode (STOP);
		break;
	}
}
