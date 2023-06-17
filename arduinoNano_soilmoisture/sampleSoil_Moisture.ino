#include <SoftwareSerial.h>
SoftwareSerial ArduinoUno(12,11);

// ===== Virables =====
String soilMoistureOneManual;
String soilMoistureTwoManual;



//SEND TO ESP SERIAL COM VARIABLES
int soilMoisture2VALUE =0,
    soilMoisture1VALUE =0;
String schedStatus,
       manualStatus,
       autoActivate,
       schedActivate,
       manualActivate,
       currentMode,
       schedDone = "";



// RECIEEVE FROM ESP SERIAL COM VARIABLES
String Mode = "1";
unsigned long schedValue = 0,schedpump =0;
int manualState;


long potValue1,potValue2;
long schedOne;
long schedTwo;

boolean isschedStart = false;
unsigned long ifInterval = 60000; 
unsigned long previousIfTime = 0;






// ======= RX and TX COMM ====
const int tx = 11;
const int rx = 12;
// ======= RX and TX COMM ====

//====== PUMP RELAY =======
const int pumpRelay = 4;
//====== PUMP RELAY =======

// ====== MOTOR DRIVER  =========

const int forward = 2;
const int backward = 3;

// ====== MOTOR DRIVER  =========


// ====== BUTTONS ==========

const int btnStarting = 5;
const int btnPosition1 = 6;
const int btnPosition2 = 7;

// ====== BUTTONS ==========

//=== SOIL MOISTURE =========

const int soilMoisture1 = A0;
const int soilMoisture2 = A1;
 

//=== SOIL MOISTURE =========







void setup() {
Serial.begin(115200);
ArduinoUno.begin(9600);
pinMode(soilMoisture1,INPUT);
pinMode(soilMoisture2,INPUT);

pinMode(btnStarting,INPUT_PULLUP);
pinMode(btnPosition1,INPUT_PULLUP);
pinMode(btnPosition2,INPUT_PULLUP);

pinMode(forward,OUTPUT);
pinMode(backward,OUTPUT);

pinMode(pumpRelay,OUTPUT);
digitalWrite(pumpRelay,HIGH);

backTostartPosition();






}



void backTostartPosition(){

  
// CHECK IF DEFAULT POSITION IS ON
    while(digitalRead(btnStarting) == HIGH) { // while btnPosition1 is OFF

        digitalWrite(forward, LOW);
        digitalWrite(backward, HIGH);
        Serial.println("BACKWARDING to default");
      }
       digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);

}


void loop() {
RecieveSerialCom();

if(Mode == "1" ){ // if Auto Mode
  isschedStart = false;
  
previousIfTime += millis();
Serial.println("Auto " );
soilMoistureONE();
soilMoistureTWO();
currentMode = "auto";
autoActivate = "activated";
schedActivate = "";
manualActivate = "";
RecieveSerialCom();

}else if(Mode == "3"){ // If Manual Mode
 Serial.println("Manual");
   isschedStart = false;
 previousIfTime += millis();
 setSoilMoistureOneManual();
//  setSoilMoistureTwoManual();
currentMode = "manual";
autoActivate = "";
schedActivate = "";
manualActivate = "activated";

Serial.println(manualState);
  RecieveSerialCom();
}else if(Mode =="2" ){ // if Sched Mode
  currentMode = "schedule";
  autoActivate = "";
schedActivate = "activated";
ifInterval = schedValue;
manualActivate = "";
  Serial.println("Sched : " + String(previousIfTime) + ifInterval + "  " + schedpump);
//ifInterval = potValue1;
if(isschedStart){
//previousIfTime = 0;

}else{

previousIfTime = millis();
  
}




   
startSchedOne();
  RecieveSerialCom();
}else{
  currentMode = "manual";
autoActivate = "";
schedActivate = "";
manualActivate = "";
  Serial.println("Deactivated All");
   isschedStart = false;
 previousIfTime += millis();
   RecieveSerialCom();
}

   


delay(10);


}
