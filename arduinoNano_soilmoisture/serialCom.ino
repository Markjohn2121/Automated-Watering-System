#include<Arduino.h>

String content = "";
char character;


unsigned long  prevTime = 0;
long lapse = 1500;


// SEND TO ESP SERIAL COM
void sendSerialCom() {
 soilMoisture1VALUE = analogRead(soilMoisture1);
 soilMoisture2VALUE = analogRead(soilMoisture2);
  


  //send data to esp ESP

//  A = soilMoisture1VALUE ,B = soilMoisture2VALUE, C = Mode, 
  ArduinoUno.println("A"+String(soilMoisture1VALUE)+"A" + 
                     "B"+String(soilMoisture2VALUE)+"B" + 
                     "C" +currentMode + "C" + 
                     "D" + schedStatus + "D" +
                     "E" + manualStatus + "E" +
                     "F" + autoActivate + "F" +
                    "G" + schedActivate + "G" +
                     "H" + manualActivate + "H" +
                     "I" + schedDone + "I");

}




// RECIEVE FROM ESP SERIAL COM
void RecieveSerialCom() {
  const unsigned long  currentMillis = millis();
  if ((currentMillis - prevTime) >= lapse) {

    //recieve data from esp
    while (ArduinoUno.available()) {
      character = ArduinoUno.read();
      content.concat(character);
      
    }
  content.trim();

if(content != ""){

  Mode = content.substring(content.indexOf("A")+1,content.lastIndexOf("A"));
  schedValue = content.substring(content.indexOf("B")+1,content.lastIndexOf("B")).toInt();
  manualState = content.substring(content.indexOf("C")+1,content.lastIndexOf("C")).toInt();
  
    schedpump = content.substring(content.indexOf("E")+1,content.lastIndexOf("E")).toInt();
    
Serial.println("Mode :"+ Mode + " schedValue : " + String(schedValue) + " manualState : " + String(manualState)+ " manualState : " + String(schedpump));

 
}

    




   
    content = "";
    character;

    prevTime = currentMillis;
sendSerialCom();
  }

}
