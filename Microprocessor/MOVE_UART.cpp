#include "MOVE_UART.h" //GPIO ����� ���� ��� ����

int Motor[6]={22, 23, 24, 25, 4, 5}; //�������� �迭 ����
int PWM_value = 165;
//���� ��� ���� �� ��ȣ�� ����
//22~25�� ���� ����(A, B), ����(A, B), 4, 5�� �¿��� �ӵ� ���� ��

void setup(){
	int z;
Serial.begin(115200);
	for (z=0; z<6; z++){ //�迭 Motor[]�� �ʱ�ȭ�ϴ� ����
		pinMode(Motor[z], OUTPUT); //���� ��Ʈ�� ������� ����
		digitalWrite(Motor[z], LOW); //LOW �� 0���� �ʱ�ȭ
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
	case 'L': //���� ���͸� �����ϵ��� ��
		analogWrite(Motor[4], OC_value);
		break;
	case 'R': //���� ���͸� �����ϵ��� ��
		analogWrite(Motor[5], OC_value);
		break;
	case 'A': //�¿��� ���͸� �����ϵ��� ��
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