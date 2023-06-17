#include <Arduino.h>
StaticJsonDocument<200> doc_tx;
void sendDataToServer(String led){
      JsonObject object = doc_tx.to<JsonObject>();
     String jsonString = "";
     
       object["soilMoisture1VALUE"] = soilMoisture1VALUE;
       object["soilMoisture2VALUE"] = soilMoisture2VALUE;
       object["currentMode"] = currentMode;
       object["schedStatus"] = schedStatus;
       object["manualStatus"] = manualStatus;
       object["autoActivate"] = autoActivate;
       object["schedActivate"] = schedActivate;
       object["manualActivate"] = manualActivate;
        object["schedValue"] =  schedValue;
         object["schedDone"] =  schedDone;
        
      
      serializeJson(doc_tx,jsonString);
        char c[] = {(char)Serial.read()};
    
    webSocket.broadcastTXT(jsonString);
}
