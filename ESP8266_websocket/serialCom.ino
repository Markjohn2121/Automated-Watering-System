#include<Arduino.h>

String content = "";
char character;


unsigned long  prevTime = 0;
long lapse = 1500;


void sendSerialCom() {

  String smode = String(Mode);
  String sPotvalue1 = String(schedOnePotValue);
//  String sPotvalue2 = String(schedTwoPotValue);
  //send data from ESP
 NodeMCU.println("A"+String(Mode)+"A" + 
                     "B"+String(schedValue)+"B" + 
                     "C" +String(manualState) + "C" +
                     "D" + String(schedDone) + "D" +
                     "E" + String(schedpump) + "E" +
                     "F" + String(manualStatus) + "F");

}



void RecieveSerialCom() {
  const unsigned long  currentMillis = millis();
  if ((currentMillis - prevTime) >= lapse) {

    //recieve data from esp
    while (NodeMCU.available()) {
      character = NodeMCU.read();
      content.concat(character);
      
    }

    
  content.trim();

if(content != ""){
soilMoisture1VALUE = content.substring(content.indexOf("A")+1,content.lastIndexOf("A"));
soilMoisture2VALUE = content.substring(content.indexOf("B")+1,content.lastIndexOf("B"));
currentMode =  content.substring(content.indexOf("C")+1,content.lastIndexOf("C"));
schedStatus =  content.substring(content.indexOf("D")+1,content.lastIndexOf("D"));
manualStatus =  content.substring(content.indexOf("E")+1,content.lastIndexOf("E"));
autoActivate =  content.substring(content.indexOf("F")+1,content.lastIndexOf("F"));
schedActivate =  content.substring(content.indexOf("G")+1,content.lastIndexOf("G"));
manualActivate =  content.substring(content.indexOf("H")+1,content.lastIndexOf("H"));
schedDone = content.substring(content.indexOf("I")+1,content.lastIndexOf("I"));
  Serial.println("MOISTURE1 :" + soilMoisture1VALUE+" MOISTURE2 : "+soilMoisture2VALUE+ 
  "currentMode" + String(currentMode) + 
  "Pot Value : " + String(schedOnePotValue) +
  " sched status : " + schedStatus + " manualStatus :" +manualStatus + " autoActivate : " + autoActivate + 
  " schedActivate : " + schedActivate + " manualActivate : " + manualActivate + " schedDone  " 
 + String(schedDone));


  // convert thsi to long
//  schedOne =  content.substring(content.indexOf("D")+1,content.lastIndexOf("D"));
//  schedTwo =  content.substring(content.indexOf("E")+1,content.lastIndexOf("E"));
   sendDataToServer("off");
}

    




   
    content = "";
    character;

    prevTime = currentMillis;


sendSerialCom();

  }

}
