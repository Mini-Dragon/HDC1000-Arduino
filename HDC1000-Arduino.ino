#include <Wire.h>
#include "HDC1000.h"
#define feedback 7
 
HDC1000 mySensor;
//HDC1000 mySensor(0x40, 2) <-- DRDYn enabled and connected to Arduino pin 2 (allows for faster measurements).
 
void setup(){
	Serial.begin(9600);
	mySensor.begin();
	pinMode(feedback, OUTPUT);
}

void senddata(int data, int howmanybits){
	for(int i=howmanybits+1; i>=0; i--){
		int b = ( data & (1 << i) ) >> i;
		if (b==1){
			for (int j=3; j>=0; j--){
				digitalWrite(feedback, 0);
				delay(1);
				digitalWrite(feedback, 1);
				delay(1);
			}
		}
		else{
			digitalWrite(feedback, 0);
			delay(1);
			digitalWrite(feedback, 1);
			delay(2);
			digitalWrite(feedback, 0);
			delay(2);
			digitalWrite(feedback, 1);
			delay(2);
			digitalWrite(feedback, 0);
			delay(1);
		}
	}
}

void loop(){
	int t = mySensor.getRawTemp(); 
	int h = mySensor.getRawHumi();
        Serial.print(t);
        Serial.print("'");
        Serial.println(h);
        senddata(t, 16);
        senddata(h, 16);
        digitalWrite(feedback, 0);
	delay(5);
}
