#include <Arduino.h>

const int TwoWet = 450;
const int TwoDry = 900;




int getSoilMoistureTwoValue() {
  return analogRead(soilMoisture2);
}



void soilMoistureTWO() {
  soilMoisture2VALUE = analogRead(soilMoisture2);


//  Serial.print("SOILMOISTURE2 VALUE: ");
//  Serial.println(soilMoisture2VALUE);

  if (soilMoisture2VALUE >= TwoDry ) {  // if dry

    Serial.println("STOP ");

    delay(2000);
    if (digitalRead(btnPosition2) == HIGH ) {   // if btnPosition2 is OFF
      //run motor driver forward

//backTostartPosition(); //back if needed
      while (digitalRead(btnPosition2) == HIGH) { // while btnPosition2 is OFF
        digitalWrite(forward, HIGH);
        digitalWrite(backward, LOW);
        Serial.println("FORWARDING ");
          RecieveSerialCom();
      }

      //STOP motor driver if btnPosition2 is ON

      digitalWrite(forward, LOW);
      digitalWrite(backward, LOW);
      Serial.println("STOP 2 ");
      delay(2000);

      //and START waterpump relay

      while (soilMoisture2VALUE >= TwoWet) {   //while dry
        digitalWrite(pumpRelay, LOW);
        soilMoisture2VALUE = analogRead(soilMoisture2);
        Serial.println("PUMPING 2 ON ");
          RecieveSerialCom();
      }

      //STOP waterpump relay
      digitalWrite(pumpRelay, HIGH);
      Serial.println("PUMPING 2 OFF");
      delay(2000);




      if (getSoilMoistureOneValue() > 700) { //if soil moisture 1 is dry

soilMoistureONE();


      }else{
                while (digitalRead(btnStarting) == HIGH) { // back to Starting Position if 2 sensor is wet
          digitalWrite(forward, LOW);
          digitalWrite(backward, HIGH);
          Serial.println("BACKWARDING ");
            RecieveSerialCom();
        }

        // and stop when its in starting position
        digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);
        Serial.println("STOP Starting position");
        delay(2000);
      }





    } else if (digitalRead(btnPosition2) == LOW) {  // if btnPosition2 is ON






      //STOP motor driver if btnPosition2 is ON

      digitalWrite(forward, LOW);
      digitalWrite(backward, LOW);
      Serial.println("STOP 2 ");
      delay(2000);

      //and START waterpump relay

      while (soilMoisture2VALUE > TwoWet) {   //while dry
        digitalWrite(pumpRelay, LOW);
        soilMoisture2VALUE = analogRead(soilMoisture2);
        Serial.println("PUMPING 2 ON ");
          RecieveSerialCom();
      }

      //STOP waterpump relay
      digitalWrite(pumpRelay, HIGH);
      Serial.println("PUMPING 2 OFF");
      delay(2000);




      if (getSoilMoistureOneValue() < 700) { //if soil moisture 1 is wet

        while (digitalRead(btnStarting) == HIGH) { // back to Starting Position if 2 sensor is wet
          digitalWrite(forward, LOW);
          digitalWrite(backward, HIGH);
          Serial.println("BACKWARDING ");
            RecieveSerialCom();
        }

        // and stop when its in starting position
        digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);
        Serial.println("STOP Starting position");
        delay(2000);


      }





    } else {




      Serial.print("WET SOIL");
        RecieveSerialCom();
    }



  }
}
  
