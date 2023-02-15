#include <SoftwareSerial.h>

#define rxPin 3
#define txPin 4

SoftwareSerial softSerial =  SoftwareSerial(rxPin, txPin);

void setup()  {
 
 pinMode(rxPin, INPUT);
 pinMode(txPin, OUTPUT);
 softSerial.begin(9600);

 Serial.begin(115200);
}

void loop() {
 

 softSerial.println("AT+GMR");
 delay(1000);
 Serial.println(softSerial.readStringUntil('\n'));
 

}
