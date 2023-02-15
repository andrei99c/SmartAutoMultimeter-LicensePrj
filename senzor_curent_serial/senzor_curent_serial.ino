#include <Wire.h>
#include <Adafruit_INA219.h>
#include <SoftwareSerial.h>
Adafruit_INA219 ina219;

#define rxPin 4
#define txPin 3
SoftwareSerial softSerial =  SoftwareSerial(rxPin, txPin);

void setup(void) 
{
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);    
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  softSerial.begin(9600);
  Serial.begin(115200);
  while (!Serial) {
      // will pause until serial console opens
      delay(1);
  }
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
 ina219.begin();
  // To use a slightly lower 32V, 1A range (higher precision on amps):
 // ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
 // ina219.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with INA219 ...");
  digitalWrite(13, HIGH);
}

void loop(void) 
{
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

   shuntvoltage = ina219.getShuntVoltage_mV();
   busvoltage = ina219.getBusVoltage_V()+0.03;
   current_mA = ((ina219.getCurrent_mA()*10)+5);
   power_mW = ina219.getPower_mW();
   loadvoltage = busvoltage + (shuntvoltage / 1000);

    //start led zone

  if( current_mA > 300 )  //the red one
  { digitalWrite(5, HIGH);}
  else { digitalWrite(5, LOW);} 

  if( current_mA > 200 ) // the blue one
  { digitalWrite(7, HIGH);}
  else { digitalWrite(7, LOW); }

  if(current_mA > 100 )  //the yelow one
  { digitalWrite(6, HIGH);}
  else { digitalWrite(6, LOW); }

   if( current_mA > 20 )   //the green one
  { digitalWrite(8, HIGH);
  }
  else { digitalWrite(8, LOW);
  }
  
  if( current_mA > 20 && current_mA < 120  )
  { digitalWrite(9, LOW);}
  else { digitalWrite(9, HIGH);}

  //end led zone


  Serial.print("Current:       "); Serial.print(current_mA,0); Serial.println(" mA");

  if( current_mA > 5)
      { softSerial.print(current_mA,0); }
  else if( current_mA > -5 and current_mA < 5) { softSerial.print("0.00");}

  if( current_mA < -5 )
  { softSerial.print("wrong"); }

   softSerial.print(";");
   
   Serial.print("");

   if( busvoltage > 0.03 )
      { softSerial.print(busvoltage); }
   else { softSerial.print("0.00");} 
   
   Serial.print("Voltage:  "); Serial.print(busvoltage); Serial.println(" V");
  
   softSerial.print(";");
   Serial.print("");
   Serial.print("Power:         "); Serial.print(power_mW,0); Serial.println(" mW");
   softSerial.print(power_mW,0);
   softSerial.println(";");
    
   Serial.println()

;
delay(1000);
}
