#include <Arduino.h>
StaticJsonDocument<200> doc_rx;


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  if(type == WStype_TEXT){
    
    if(payload[0] == '#'){
    
     Mode   = (uint16_t) strtol((const char *) &payload[1], NULL, 10);
      


    }

    
//    Get pot One sched value
     if(payload[0] == '$'){
     schedValue = (long) strtol((const char *) &payload[1], NULL, 10);
  
    }

////    Get pot two sched value
//        if(payload[0] == ''){
//      schedTwoPotValue = (uint16_t) strtol((const char *) &payload[1], NULL, 10);
// 
//
//    }

   if(payload[0] == '&'){
      schedpump = (long) strtol((const char *) &payload[1], NULL, 10);
 

    }

     if(payload[0] == '@'){
      schedDone = (boolean) strtol((const char *) &payload[1], NULL, 10);
 

    }

    if(payload[0] == '%'){
      manualState = (uint16_t) strtol((const char *) &payload[1], NULL, 10);
 

    }


    else{
      for(int i = 0; i < length; i++)
        Serial.print((char) payload[i]);
      Serial.println();
    }
  }
  
}
