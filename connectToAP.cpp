#include "Arduino.h"
#include "connectToAP.h"
#include <ESP8266WiFi.h>
#include <EEPROM.h>

connectToAP::connectToAP()
{
    /*Variables to store AP credentials*/
    String ssid = "";
    String password = "";
    unsigned int EEPROMtail;
}

void connectToAP::connect() {  
  if(EEPROM.read(0) == 1){
    // Load the AP credentials forom the EEPROM
    Serial.println("Loading AP credentials from EEROM.");
    for(int i = 0; i<EEPROM.read(1); i++)
      ssid += char(EEPROM.read(i+2));
    for(int i = 0; i<EEPROM.read(35); i++)
      password += char(EEPROM.read(i+36));
    Serial.println("AP credentials loaded.");
    // Print the AP credentials to the serial monitor
    Serial.print("Acesspoint SSID : ");
    Serial.println(ssid.c_str());
    Serial.print("Acesspoint password : ");
    Serial.println(password.c_str());

    // Connect the ESP12E to the AP
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.println("Connecting to AP.");
    while(WiFi.status() != WL_CONNECTED){
      delay(250);
      Serial.print(".");
    }
    Serial.println(".");
    Serial.println("Connected to AP.");
  }
  else{
      // Operate the ESP12E in wifi station mode for smart config
      WiFi.mode(WIFI_STA);

      // Begin the smart configuration to get the Access Point credentials
      WiFi.beginSmartConfig();
      Serial.println("Waiting for SmartConfig.");
      while (!WiFi.smartConfigDone()) {
        delay(250);
        Serial.println("Connecting....");
      }
      Serial.println("SmartConfig done, received AP credentials.");

      // Print the AP credentials to the serial monitor
      ssid = WiFi.SSID();
      password = WiFi.psk();
      Serial.print("Acesspoint SSID : ");
      Serial.println(ssid);
      Serial.print("Acesspoint password : ");
      Serial.println(password);

      // Save the AP credentials to the EEPROM
      EEPROM.write(0,1);
      EEPROM.write(1,ssid.length());
      EEPROM.write(35,password.length());
      for(int i=0; i<ssid.length(); i++){
        EEPROM.write(2+i,ssid[i]);
      }
      for(int i=0; i<password.length(); i++){
        EEPROM.write(36+i,password[i]);
        EEPROMtail = i+1;
      }      
      EEPROM.commit();

      // Connect the ESP12E to the AP
      Serial.println("Connecting to AP");
      while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
      }
      Serial.println(".");
      Serial.println("Connected to AP.");
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Begin the Web Scoket by starting the server. 
  server.begin();
}

void connectToAP:: rstEEPROM(){
  for(int i=0; i<512; i++){
    EEPROM.write(i,0);
  }
  EEPROM.commit();
}