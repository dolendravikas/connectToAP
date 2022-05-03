/*
    connectTpAP.h - Library for connecting the Wi-Fi enabled 
    uContr (uContr wich uses the Arduino framework) to the local
    Access Point. 
    Created by Addepalli Dolendra Vikas, November 23, 2021
*/

#ifndef connectToAP_h
#define connectToAP_h

#include "Arduino.h"

class connectToAP
{
    public:
        connectToAP();
        void connect();
        void rstEEPROM();
    private:
        String ssid;
        String password;
        unsigned int EEPROMtail;
};

#endif