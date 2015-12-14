#define feedback P1_5
 
//just sense the voltage
 
void setup(){
	pinMode(feedback, OUTPUT);
}

void senddata(int data, int howmanybits){
	for(int i=howmanybits-1; i>=0; i--){
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
	int ad=analogRead(A2);
	senddata(ad, 10);
	digitalWrite(feedback, 0);
	delay(5);
}
