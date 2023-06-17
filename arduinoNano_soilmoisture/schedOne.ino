//unsigned long previousIfTime = 0; // Variable to store the previous time the if statement was executed
unsigned long previousWhileTime = 0; // Variable to store the previous time the while loop was executed
unsigned long previousOtherFunctionTime = 0; // Variable to store the previous time the other function was executed

// unsigned long ifInterval = 10000; // Interval for the if statement (in milliseconds)
unsigned long whileInterval = 10000; // Interval for the while loop (in milliseconds)
const unsigned long otherFunctionInterval = 1500; // Interval for the other function (in milliseconds)

void   startSchedOne() {
  unsigned long currentTime = millis(); // Get the current time

if(schedValue != 0 && schedValue > 0){
schedStatus = "run";
  // Run the if statement every 10 seconds
  if (millis() - previousIfTime >= ifInterval) {

  whileInterval += millis();
    
    previousIfTime = millis(); // Update the previous time
Serial.println("if starting");
    // Run the while loop for 5 seconds



 while (digitalRead(btnPosition1) == HIGH) { // while btnPosition1 is OFF
        digitalWrite(forward, HIGH);
        digitalWrite(backward, LOW);
        Serial.println("FORWARDING TO 1");
        RecieveSerialCom();


      }

      //STOP motor driver if btnPosition1 is ON
      digitalWrite(forward, LOW);
      digitalWrite(backward, LOW);
      Serial.println("STOP ");
      delay(2000);
      
      previousIfTime = millis();
      //and START waterpump relay

//      while (soilMoisture1VALUE > OneWet) {   //while dry
//        digitalWrite(pumpRelay, LOW);
//        soilMoisture1VALUE = analogRead(soilMoisture1);
//        Serial.println("PUMPING ON ");
//        RecieveSerialCom();
//      }
//      
//      //STOP waterpump relay
//      digitalWrite(pumpRelay, HIGH);
//      Serial.println("PUMPING OFF");
//      delay(2000);





//    Start pumping for desire time
    while (millis() - previousIfTime < schedpump) {
      // Perform the desired actions inside the while loop
       digitalWrite(pumpRelay, LOW);
        soilMoisture1VALUE = analogRead(soilMoisture1);
        Serial.println("PUMPING ON ");
        RecieveSerialCom();
        RecieveSerialCom();


//        previousIfTime = whileInterval;
    }

      //STOP waterpump relay
      digitalWrite(pumpRelay, HIGH);
      Serial.println("PUMPING OFF");
      delay(2000);


// go to position 2
  while (digitalRead(btnPosition2) == HIGH) { // while btnPosition2 is OFF
        digitalWrite(forward, HIGH);
        digitalWrite(backward, LOW);
        Serial.println("FORWARDING To 2");
      }

      //STOP motor driver if btnPosition2 is ON

      digitalWrite(forward, LOW);
      digitalWrite(backward, LOW);
      Serial.println("STOP 2 ");
      delay(2000);
 previousIfTime = millis();
      
//    Start pumping for desire time
       while (millis() - previousIfTime < schedpump) {
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

//backwarding
  while (digitalRead(btnStarting) == HIGH) { // back to Starting Position  sensor 1 is wet
        digitalWrite(forward, LOW);
        digitalWrite(backward, HIGH);
        Serial.println("BACKWARDING ");
        RecieveSerialCom();
      }
        digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);
        Serial.println("BACKWARDING ");

    previousIfTime = millis(); // Update the previous time after the while loop
    isschedStart =true;
    schedValue = 0;
    schedDone = "done";
    schedStatus = "stop";
  }else {
isschedStart = true;
    
  }



}else{
  isschedStart = false;
  previousIfTime += millis();
  schedStatus = "stop";
 
  }

  // Continue with other code or actions outside the if statement
}
