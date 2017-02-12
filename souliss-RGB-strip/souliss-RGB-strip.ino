/*
   Example of an Soulissc enable RGBW led strip for the wemos D1 RGBW shield
   https://github.com/RiRomain/wemos-rgbw-shield
   You need to install the Souliss library from the library manager
   (Sketch -> Include Library -> Manage Libraries)
   This is meant to be used in adjonction with souliss as an rgb light strip
   The white channel is not supported by this code.
   DHCP is used to get the IP address. Use serial output (76800) to get the actual IP adress.
*/

// Let the IDE point to the Souliss framework
#include "SoulissFramework.h"

// Configure the framework
#include "bconf/MCU_ESP8266.h"              // Load the code directly on the ESP8266
#include "conf/Gateway.h"                   // The main node is the Gateway, we have just one node

// Include framework code and libraries
#include <ESP8266WiFi.h>
#include "Souliss.h"
#include <EEPROM.h>

// **** Define the WiFi name and password ****
#define WIFICONF_INSKETCH
#define WiFi_SSID               "YourWifiName"
#define WiFi_Password           "YourWifiPassword"

#define LEDCONTROL          0               // This is the memory slot for the logic that handle the light
#define LEDRED              1               // This is the memory slot for the logic that handle the light
#define LEDGREEN            2               // This is the memory slot for the logic that handle the light
#define LEDBLUE             3               // This is the memory slot for the logic that handle the light


#define RED_PIN D5
#define GREEN_PIN D6
#define BLUE_PIN D7
//#define WHITE_PIN D8

void setup() {
  // put your setup code here, to run once:
  delay(10);
  Serial.begin(76800);
  delay(20);
  Serial.println("Going to initialize");
  Initialize();
  Serial.println("Initialisation finished");

  // Connect to the WiFi network and get an address from DHCP
  GetIPAddress();
  //Uncomment the next line to define a fixed IP address (consult Soulis documentation for more info)
  // SetIPAddress(ip_address, subnet_mask, ip_gateway);
  SetAsGateway(myvNet_dhcp);       // Set this node as gateway for SoulissApp
  Serial.println("Received IP address: ");
  Serial.println(WiFi.localIP());
  // This is the vNet address for this node, used to communicate with other
  // nodes in your Souliss network
  SetAddress(0xAB01, 0xFF00, 0x0000);
  SetAsPeerNode(0xAB02, 1);
  Serial.println("Node set as peer");

  Set_T16(LEDCONTROL);


  // Define outputs pins
  pinMode(RED_PIN, OUTPUT);                // Red LED output
  pinMode(GREEN_PIN, OUTPUT);              // Green LED output
  pinMode(BLUE_PIN, OUTPUT);               // Blue LED output
}

// Following variable are used to save souliss set LED value. Souliss use 8 bit PWM output (0-255),
// whereas ESP8266 have 10 bit PWM output (0-1023). The variable are used to make the conversion.
int ledBlue = 0;
int ledGreen = 0;
int ledRed = 0;
void loop() {
  // put your main code here, to run repeatedly:
  // Here we start to play
  EXECUTEFAST() {
    UPDATEFAST();

    FAST_10ms() {   // We process the logic and relevant input and output every 10 milliseconds
      Logic_T16(LEDCONTROL);
      ledBlue = mOutput(LEDBLUE);
      ledGreen = mOutput(LEDGREEN);
      ledRed = mOutput(LEDRED);
      if (ledBlue != 0) {
        analogWrite(BLUE_PIN, (ledBlue + 1) * 4);
      } else {
        analogWrite(BLUE_PIN, 0);
      }
      if (ledGreen != 0) {
        analogWrite(GREEN_PIN, (ledGreen + 1) * 4);
      } else {
        analogWrite(GREEN_PIN, 0);
      }
      if (ledRed != 0) {
        analogWrite(RED_PIN, (ledRed + 1) * 4);
      } else {
        analogWrite(RED_PIN, 0);
      }
      ProcessCommunication();
    }

    // Here we handle here the communication with Android
    FAST_GatewayComms();
  }
  EXECUTESLOW() {
    UPDATESLOW();

    SLOW_10s() {
      // Timer associated to the LED logic control
      Timer_T16(LEDCONTROL);
      // Test phase output to ensure device is running
      Serial.println("Device is still running ");
    }

  }
}
