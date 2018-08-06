#define lightPin D0
#define waterPin D1

#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <ArduinoJson.h> 

File fsUploadFile;

ESP8266WebServer server(80);


String ssid = "podlev";
String password = "89278615058";
String jsonConfig = "{}";

int timeZone = 3; // Central European Time

//интервал освещения в часах
byte lightStart = 19; // [10,23]
byte lightStop = 20;

//интервал полива в минутах
byte waterStart = 0; //[0,15]
byte waterStop = 40;

byte lightStatus;
byte waterStatus;

byte NOWDAY;
byte NOWHOUR;
byte NOWMINUTE;
byte NOWSECOND;



void setup() {
    //Настройка Pin
    pinMode(lightPin, OUTPUT);
    pinMode(waterPin, OUTPUT);
    digitalWrite(lightPin, 1);
    digitalWrite(waterPin, 1);
    //Монитор порта
    Serial.begin(115200);
    //Ожидания подключения к интернет
    if (wifiSetup()) { 
        serverStart(); 
        loadConfig();
            while (!updateTime()) {
            Serial.println("!!!");  
            delay(10000);
        }
    }
    else {
      serverStart();
      loadConfig();
    }

    NOWDAY = day();
    NOWHOUR = hour();
    NOWMINUTE = minute();
    NOWSECOND = second();

    checkLightWater();
    
}


void loop() {
   checkEvents();
   server.handleClient();
}
