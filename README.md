## connectToAP
---
Avoid hard coding the credentials in the firmeare. Hard coding the credentials of the Access Point(AP) will allow to connect only to that particular AP. When you want to connect your device to a differnet AP you have to again hard code the credentials and flash the firmware into the chip. This is inefficient and tedious process.

This ```connectToAP``` library provies API to pass the credentials to uContr over the smartConfig, using esp Touch mobile application which is availabel in the playtore and app store. 

```connectToAP``` utilizes the EEPROM of the uContr to store the credential when the uContr is OFF. When the uContr turns ON the uContr loads the credentials from the EEPROM and connects to the AP. So the user don't have to reenter the credentials. 

```connectToAP``` also provides an API to reset the EEPROM. Invoking this function erases the EEPROM of the uContr completely. User can use this function and add additional features to the device like erasing the credentials that are stored with a press of the button. 

