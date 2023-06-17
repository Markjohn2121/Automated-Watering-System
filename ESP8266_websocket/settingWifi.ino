#include <Arduino.h>

char* ssid = "AWTsystem";
char* password = "AWTsystemesp8266";


void settingWifi(){
//For AP mod IPADDRESS==========
IPAddress apIP(192,168,4,1);
IPAddress apGW(192,168,1,1);
IPAddress apSM(255,255,0,0);
IPAddress apDNS1(8,8,8,8);
IPAddress apDNS2(8,8,4,4);
char static_ip[16] = "10,0,1,78";
char static_gw[16] = "10,0,1,1";
char static_sm[16] = "255,255,255,0";
//For AP mod IPADDRESS==========
  

if(digitalRead(onlineBtn) == HIGH){ // OFFLINE MODE IF BTN IF OFF
  delay(500);
    Serial.println("OfflineMode");
    digitalWrite(onlineLed,LOW);
     delay(500);
     WiFi.mode(WIFI_AP);
      WiFi.softAPConfig(apIP,apIP,IPAddress(255,255,255,0));
      WiFi.softAP(ssid,password);
  

  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
    

  
}else {
    delay(500);
        digitalWrite(onlineLed,HIGH);
//    if(!WiFi.config(apIP,apGW,apSM,apDNS1,apDNS2)){
//      Serial.println("STA failed to config");
//    }
//
//      Serial.println("STA connecting to YOUR_SSID ");
//      WiFi.begin("YOUR_SSID","YOUR_PASSWORD");
//      while(WiFi.status() != WL_CONNECTED){
//        delay(500);
//        Serial.print(".");
//      }
//  Serial.println("");
//    Serial.println("IP Address: ");
//      Serial.println(WiFi.localIP());
      
//   Serial.println("OnlineMode");
//    delay(500);
//   //=============ONLINE MODE=======
//    // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
//    // it is a good practice to make sure your code sets wifi mode how you want it.
//
//    // put your setup code here, to run once:
//    Serial.begin(115200);
//
//   
//    
//    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;
//
//    // reset settings - wipe stored credentials for testing
//    // these are stored by the esp library
 // wm.resetSettings();
//
////  IPAddress _ip,_gw,_sm ;
////  _ip.fromString(static_ip);
////    _gw.fromString(static_gw);
////    _sm.fromString(static_sm);
//
//
////  IPAddress _ip = IPAddress(10,0,1,78);
////  IPAddress _gw = IPAddress(10,0,1,1);
////  IPAddress _sm = IPAddress(255,255,255,0);
//wm.setSTAStaticIPConfig(IPAddress(192,168,0,99),IPAddress(192,168,0,1),IPAddress(255,255,255,0));
    bool res;   
    res = wm.autoConnect(ssid,password); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
            digitalWrite(wifiLed,HIGH);
    }
//======================
}
}
