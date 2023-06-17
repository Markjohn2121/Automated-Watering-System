#include <Arduino.h>

const int OneWet = 450;
const int OneDry = 900;



int getSoilMoistureOneValue(){
  return analogRead(soilMoisture1);
}




void soilMoistureONE() {
  

  soilMoisture1VALUE = analogRead(soilMoisture1);
//
//  Serial.print("SOILMOISTURE1 VALUE: ");
//  Serial.println(soilMoisture1VALUE);

 

  if (soilMoisture1VALUE >= OneDry ) {  // if dry
    
    Serial.println("STOP ");
    Serial.print("DRY : " + digitalRead(btnPosition1) );
    delay(2000);
    RecieveSerialCom();
    if (digitalRead(btnPosition1) == HIGH ) {   // if btnPosition1 is OFF and btnStarting is ON
      //run motor driver forward


//backTostartPosition();//back if needed

      while (digitalRead(btnPosition1) == HIGH) { // while btnPosition1 is OFF
        digitalWrite(forward, HIGH);
        digitalWrite(backward, LOW);
        Serial.println("FORWARDING ");
        RecieveSerialCom();
      }

      //STOP motor driver if btnPosition1 is ON
      
      digitalWrite(forward, LOW);
      digitalWrite(backward, LOW);
      Serial.println("STOP ");
      delay(2000);
      
      //and START waterpump relay

      while (soilMoisture1VALUE >= OneWet) {   //while dry
        digitalWrite(pumpRelay, LOW);
        soilMoisture1VALUE = analogRead(soilMoisture1);
        Serial.println("PUMPING ON ");
        RecieveSerialCom();
      }
      
      //STOP waterpump relay
      digitalWrite(pumpRelay, HIGH);
      Serial.println("PUMPING OFF");
      delay(2000);

if(getSoilMoistureTwoValue() > 700){ //if soil moisture 2 is dry

soilMoistureTWO();
  
}else{
  while (digitalRead(btnStarting) == HIGH) { // back to Starting Position  sensor 1 is wet
        digitalWrite(forward, LOW);
        digitalWrite(backward, HIGH);
        Serial.println("BACKWARDING ");
        RecieveSerialCom();
      }

      // and stop when its in starting position0
      digitalWrite(forward, LOW);
      digitalWrite(backward, LOW);
      Serial.println("STOP Starting position");
      delay(2000);
}





//if(getSoilMoistureTwoValue() > 800){   //if soil moisture 2 is wet
//  
// while (digitalRead(btnStarting) == HIGH) { // back to Starting Position if 2 sensor is wet
//        digitalWrite(forward, LOW);
//        digitalWrite(backward, HIGH);
//        Serial.println("BACKWARDING ");
//      }
//
//      // and stop when its in starting position0
//      digitalWrite(forward, LOW);
//      digitalWrite(backward, LOW);
//      Serial.println("STOP Starting position");
//      delay(2000);
//
//
//}



     

    } else if (digitalRead(btnPosition2) == LOW) {  // if btnPosition2 is ON it will backward

  //run motor driver backward

      while (digitalRead(btnPosition1) == HIGH) { // while btnPosition1 is OFF
        digitalWrite(forward, LOW);
        digitalWrite(backward, HIGH);
        Serial.println("BACKWARDING ");
        RecieveSerialCom();
      }

      //STOP motor driver if btnPosition1 is ON
      
      digitalWrite(forward, LOW);
      digitalWrite(backward, LOW);
      Serial.println("STOP ");
      delay(2000);
      
      //and START waterpump relay

      while (soilMoisture1VALUE > OneWet) {   //while dry
        digitalWrite(pumpRelay, LOW);
        soilMoisture1VALUE = analogRead(soilMoisture1);
        Serial.println("PUMPING ON ");
        RecieveSerialCom();
      }
      
      //STOP waterpump relay
      digitalWrite(pumpRelay, HIGH);
      Serial.println("PUMPING OFF");
      delay(2000);




if(getSoilMoistureTwoValue() < 800){   //if soil moisture 2 is wet
  
 while (digitalRead(btnStarting) == HIGH) { // back to Starting Position if 2 sensor is wet
        digitalWrite(forward, LOW);
        digitalWrite(backward, HIGH);
        Serial.println("BACKWARDING ");
        RecieveSerialCom();
      }

      // and stop when its in starting position0
      digitalWrite(forward, LOW);
      digitalWrite(backward, LOW);
      Serial.println("STOP Starting position");
      delay(2000);


}




    }


  } else {

//    Serial.print("WET SOIL");
  }



}
