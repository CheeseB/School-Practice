#include "MOVE_UART.h" //GPIO 사용을 위한 헤더 참조

int Motor[6]={22, 23, 24, 25, 4, 5}; //전역변수 배열 선언
int PWM_value = 165;
//모터 제어를 위한 핀 번호를 저장
//22~25는 각각 좌측(A, B), 우측(A, B), 4, 5는 좌우측 속도 제어 핀

void setup(){
	int z;
Serial.begin(115200);
	for (z=0; z<6; z++){ //배열 Motor[]를 초기화하는 과정
		pinMode(Motor[z], OUTPUT); //제어 포트를 출력으로 설정
		digitalWrite(Motor[z], LOW); //LOW 즉 0으로 초기화
	}
	Motor_Control('A',PWM_value);
}

void loop() {

}


void Motor_mode(int da){
	int z;
	for (z=0; z<4; z++)
		digitalWrite(Motor[z], (da>>z)&0x01);
}

void Motor_Control(char da, unsigned int OC_value){
	switch(da){
	case 'L': //좌측 모터를 동작하도록 함
		analogWrite(Motor[4], OC_value);
		break;
	case 'R': //우측 모터를 동작하도록 함
		analogWrite(Motor[5], OC_value);
		break;
	case 'A': //좌우측 모터를 동작하도록 함
		analogWrite(Motor[4], OC_value);
		analogWrite(Motor[5], OC_value);
		break;
	}
}

void serialEvent()
{
	char data = Serial.read();
	Serial.write(data);
	switch(data)
	{
	case'y':
		Motor_mode(FORWARD);
		break;
	case'b':
			Motor_mode(BACKWARD);
			break;
	case'g':
			Motor_mode(LEFT);
			break;
	case'j':
			Motor_mode(RIGHT);
			break;
	case't':
			Motor_mode(LEFT_U);
			break;
	case'u':
			Motor_mode(RIGHT_U);
			break;
	case's':
			Motor_mode(STOP);
			break;
	case'1':
			Motor_Control('A',165);
			break;
	case'2':
			Motor_Control('A',205);
			break;
	case'3':
			Motor_Control('A',245);
			break;
	}
}