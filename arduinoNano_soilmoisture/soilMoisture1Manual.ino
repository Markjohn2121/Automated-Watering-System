#include <Arduino.h>

unsigned long prevpumpTime;



void setSoilMoistureOneManual(){





  
  if(manualState == 1){

// CHECK IF DEFAULT POSITION IS ON
    while(digitalRead(btnStarting) == HIGH ) { // while btnStarting is OFF

        digitalWrite(forward, LOW);
        digitalWrite(backward, HIGH);
        Serial.println("BACKWARDING to default");
      }
       digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);
    

      while (digitalRead(btnPosition1) == HIGH) { // while btnPosition1 is OFF
        digitalWrite(forward, HIGH);
        digitalWrite(backward, LOW);
        Serial.println("FORWARDING ");
      }

      //STOP motor driver if btnPosition1 is ON
      
      digitalWrite(forward, LOW);
      digitalWrite(backward, LOW);
      Serial.println("STOP ");
      delay(2000);
      
      //and START waterpump relay


 prevpumpTime = millis();

      //    Start pumping for desire time
    while (millis() - prevpumpTime < 60000) {
      // Perform the desired actions inside the while loop
       digitalWrite(pumpRelay, LOW);
        soilMoisture1VALUE = analogRead(soilMoisture1);
        Serial.println("PUMPING ON ");
      
        RecieveSerialCom();


//        previousIfTime = whileInterval;
    }

      
      //STOP waterpump relay
      digitalWrite(pumpRelay, HIGH);
      Serial.println("PUMPING OFF");
      delay(2000);

     

      while (digitalRead(btnPosition2) == HIGH) { // while btnPosition1 is OFF
        digitalWrite(forward, HIGH);
        digitalWrite(backward, LOW);
        Serial.println("FORWARDING ");
      }

      //STOP motor driver if btnPosition1 is ON
      
      digitalWrite(forward, LOW);
      digitalWrite(backward, LOW);
      Serial.println("STOP ");
      delay(2000);
      
      //and START waterpump relay
      prevpumpTime = millis();
while (millis() - prevpumpTime < 60000) {
      // Perform the desired actions inside the while loop
       digitalWrite(pumpRelay, LOW);
        soilMoisture1VALUE = analogRead(soilMoisture1);
        Serial.println("PUMPING ON ");
      
        RecieveSerialCom();


//        previousIfTime = whileInterval;
    }
      
      //STOP waterpump relay
      digitalWrite(pumpRelay, HIGH);
      Serial.println("PUMPING OFF");
      delay(2000);

// CHECK IF DEFAULT POSITION IS ON
    while(digitalRead(btnStarting) == HIGH ) { // while btnStarting is OFF

        digitalWrite(forward, LOW);
        digitalWrite(backward, HIGH);
        Serial.println("BACKWARDING to default");
      }
       digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);
    
  
}else{
  Serial.print(manualState);
}

}

//
//if (soilMoistureOneManual == "ON") {
//
//  if (digitalRead(btnPosition1) == HIGH && digitalRead(btnStarting) == LOW) {  // if btnPosition1 is OFF and btnStarting is ON
//    //run motor driver forward
//
//    while (digitalRead(btnPosition1) == HIGH) { // while btnPosition1 is OFF
//      digitalWrite(forward, HIGH);
//      digitalWrite(backward, LOW);
//      Serial.println("FORWARDING ");
//    }
//
//    //STOP motor driver if btnPosition1 is ON
//
//    digitalWrite(forward, LOW);
//    digitalWrite(backward, LOW);
//    Serial.println("STOP ");
//    delay(2000);
//
//    //and START waterpump relay
//
//    while (soilMoisture1VALUE > OneWet) {   //while dry
//      digitalWrite(pumpRelay, LOW);
//      soilMoisture1VALUE = analogRead(soilMoisture1);
//      Serial.println("PUMPING ON ");
//    }
//
//    //STOP waterpump relay
//    digitalWrite(pumpRelay, HIGH);
//    Serial.println("PUMPING OFF");
//    delay(2000);
//
//
//
//
//    if (getSoilMoistureTwoValue() < 800) { //if soil moisture 2 is wet
//
//      while (digitalRead(btnStarting) == HIGH) { // back to Starting Position if 2 sensor is wet
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
//    }
//
//
//
//
//
//  } else if (digitalRead(btnPosition2) == LOW) {  // if btnPosition2 is ON it will backward
//
//    //run motor driver backward
//
//    while (digitalRead(btnPosition1) == HIGH) { // while btnPosition1 is OFF
//      digitalWrite(forward, LOW);
//      digitalWrite(backward, HIGH);
//      Serial.println("BACKWARDING ");
//    }
//
//    //STOP motor driver if btnPosition1 is ON
//
//    digitalWrite(forward, LOW);
//    digitalWrite(backward, LOW);
//    Serial.println("STOP ");
//    delay(2000);
//
//    //and START waterpump relay
//
//    while (soilMoistureOneManual == "ON) {   //while dry
//      digitalWrite(pumpRelay, LOW);
//    RecieveSerialCom();
//      Serial.println("PUMPING ON ");
//    }
//
//    //STOP waterpump relay
//    digitalWrite(pumpRelay, HIGH);
//    Serial.println("PUMPING OFF");
//    delay(2000);
//
//
//
//
//    if (getSoilMoistureTwoValue() < 800) { //if soil moisture 2 is wet
//
//      while (digitalRead(btnStarting) == HIGH) { // back to Starting Position if 2 sensor is wet
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
//    }
//
//
//
//
//  }
//
//
//
//}
