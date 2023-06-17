#include <Arduino.h>





void setSoilMoistureTwoManual(){





  
  if(soilMoistureTwoManual == "On"){

// CHECK IF DEFAULT POSITION IS ON
    while(digitalRead(btnStarting) == HIGH ) { // while btnPosition1 is OFF

        digitalWrite(forward, LOW);
        digitalWrite(backward, HIGH);
        Serial.println("BACKWARDING to default");
      }
       digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);
    

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

      while (soilMoistureTwoManual == "on") {   // manual is on
        digitalWrite(pumpRelay, LOW);
        soilMoisture2VALUE = analogRead(soilMoisture2);
        Serial.println("PUMPING ON ");
        RecieveSerialCom();
      }
      
      //STOP waterpump relay
      digitalWrite(pumpRelay, HIGH);
      Serial.println("PUMPING OFF");
      delay(2000);


    // CHECK IF DEFAULT POSITION IS ON
    while(digitalRead(btnStarting) == HIGH ) { // while btnPosition1 is OFF

        digitalWrite(forward, LOW);
        digitalWrite(backward, HIGH);
        Serial.println("BACKWARDING to default");
      }
       digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);
  
    
   
    }else{
      // CHECK IF DEFAULT POSITION IS ON
    while(digitalRead(btnStarting) == HIGH ) { // while btnPosition1 is OFF

        digitalWrite(forward, LOW);
        digitalWrite(backward, HIGH);
        Serial.println("BACKWARDING to default");
      }
       digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);
      }
    
  
}
