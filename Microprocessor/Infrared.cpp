#include "Infrared.h"

int S_DIN = 42, S_SCLK = 43, S_SYNCN =44, IN_SEN_EN = 26;
int SensorA[8] = {A0,A1,A2,A3,A4,A5,A6,A7};
int SensorD[8] = {30,31,32,33,34,35,36,37};
int Motor[6] = {22,23,24,25,4,5};
unsigned int Buff_A[8] = {0,0,0,0,0,0,0,0};
unsigned int ADC_MAX[8] = {0,0,0,0,0,0,0,0};
unsigned int ADC_MIN[8] = {1023,1023,1023,1023,1023,1023,1023,1023};
unsigned int ADC_MEAN[8] = {0,0,0,0,0,0,0,0};
unsigned char Sensor_data = 0;
int DAC_data = 0;



void setup(){
	int z;
	pinMode(IN_SEN_EN,OUTPUT);
	pinMode(S_DIN,OUTPUT);
	pinMode(S_SCLK,OUTPUT);
	pinMode(S_SYNCN,OUTPUT);
	digitalWrite(S_SCLK,LOW);
	digitalWrite(S_SYNCN,HIGH);
	digitalWrite(IN_SEN_EN,HIGH);

	for (z=0; z<6; z++){ //배열 Motor[]를 초기화하는 과정
		pinMode(Motor[z], OUTPUT); //제어 포트를 출력으로 설정
		digitalWrite(Motor[z], LOW); //LOW 즉 0으로 초기화
	}
	for ( z=0; z<8;z++)
	{
		pinMode(SensorD[z],INPUT);
	}
	Serial.begin(115200);
	DAC_setting(0x9000);
	for ( z=0; z<8;z++)
		{
			DAC_CH_Write(z,255);
		}
	infrared_init();
}

void loop() {

	int z;
	Serial.print("\n\r Infrared Data : ");

	SensorA_read();
	for ( z=0; z<8;z++)
		{
			Serial.print(digitalRead(SensorD[7-z]));
		}
	Serial.print("\n\r ADC_data:");
	for ( z=0; z<8;z++)
		{
			Serial.print(" ");
			Serial.print(Buff_A[z]);
		}
	Serial.print("\n\r ADC_MEAN:");
	for ( z=0; z<8;z++)
			{
				Serial.print(",");
				Serial.print(ADC_MEAN[z]);
			}
	delay(200);
}

void ADC_Compare(void){
	int z;
	for ( z=0; z<8;z++)
		{
			if(ADC_MAX[z]<Buff_A[z])
				ADC_MAX[z]=Buff_A[z];
			if(ADC_MIN[z]>Buff_A[z])
				ADC_MIN[z]=Buff_A[z];
		}
}

unsigned char SensorD_read(void){
	unsigned char data =0,z;
	for(z=0;z<8;z++){
		data>>=1;
		if(digitalRead(SensorD[z]))
			data |=0x80;
	}
	return data;
}

void SensorA_read(void){
	int z;
	for(z=0;z<8;z++)
		Buff_A[z]=analogRead(SensorA[z]);
}

void DAC_CH_Write(unsigned int ch, unsigned int da){
	unsigned int data = ((ch<<12)&0x7000)|((da<<4)&0x0FF0);
	DAC_setting(data);
}

void DAC_setting(unsigned int data){
	int z;

	digitalWrite(S_SCLK,HIGH);
	delayMicroseconds(1);
	digitalWrite(S_SCLK,LOW);
	delayMicroseconds(1);
	digitalWrite(S_SYNCN,LOW);
	delayMicroseconds(1);
	for(z=16;z>0;z--){
		digitalWrite(S_DIN,(data>>(z-1))&0x1);
		digitalWrite(S_SCLK,HIGH);
		delayMicroseconds(1);
		digitalWrite(S_SCLK,LOW);
		delayMicroseconds(1);
	}
	digitalWrite(S_SYNCN,HIGH);
}

void infrared_init(){
	int z, error=0;
	Serial.println("infrared init Start");
	Motor_Control('A',160);
	while(1){
		Motor_mode(LEFT_U);
		for(z=0;z<50;z++){
			SensorA_read();
			ADC_Compare();
			delay(8);
		}
		Motor_mode(RIGHT_U);
		for(z=0;z<100;z++){
				SensorA_read();
				ADC_Compare();
				delay(8);
				}

		Motor_mode(LEFT_U);
		delay(400);
		Motor_mode(STOP);

		Serial.println("\n\r ADC MAX");
		for(z=0;z<8;z++){
			Serial.print(" ");
			Serial.print(ADC_MAX[z]);
		}
		Serial.println("\n\r ADC MIN");
			for(z=0;z<8;z++){
				Serial.print(" ");
				Serial.print(ADC_MIN[z]);
				}
			delay(1000);
			for(z=0;z<8;z++)
			{
				if(ADC_MAX[z]-ADC_MIN[z]<200)
					error++;
			}
			if(error == 0)
			{
				Serial.println("\n\r infrared init END");
				break;
			}
			else
			{
				error = 0;
				Serial.println("\n\r infrared init Restart");
				for(z=0;z<8;z++)
				{
					ADC_MAX[z] = 0 ;
					ADC_MIN[z] = 1023;
				}
			}
	}
	Serial.println("DAC Setting Start");
	for(z=0;z<8;z++){
		ADC_MEAN[z] = (ADC_MAX[z]+ADC_MIN[z])/2;
		DAC_CH_Write(z,ADC_MEAN[z]/4);
		}
	Serial.println(" DAC_Setting");
	for(z=0;z<8;z++)
	{
		Serial.print(" ");
		Serial.print(ADC_MEAN[z]);
	}
	Serial.println("\n\r DAC setting End");
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