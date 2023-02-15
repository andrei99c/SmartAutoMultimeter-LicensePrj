#include <Wire.h>
#include <SoftwareSerial.h>

void setup(void) {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
   pinMode(7, OUTPUT);
  Serial.begin(115200);
  while (!Serial) {
      // will pause until serial console opens
      delay(1);
  }

}

void loop(void) {
  // put your main code here, to run repeatedly:
digitalWrite(5, HIGH);
digitalWrite(6, HIGH);
 digitalWrite(7, HIGH);
delay(1000);
}
