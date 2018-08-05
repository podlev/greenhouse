#define lightPin D0
#define waterPin D1

#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>

File fsUploadFile;

ESP8266WebServer server(80);


String ssid = "podlev";
String password = "89278615058";

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

void functionLightOff() {
    lightStatus = 1;
    digitalWrite(lightPin, lightStatus);
    server.send(200, "text/plain", "LIGHT is OFF!"); // отправляем ответ о выполнении
    PRINTLOG("LIGHT is OFF!");
}
  
void functionLightOn() {
    lightStatus = 0;
    digitalWrite(lightPin, lightStatus);
    server.send(200, "text/plain", "LIGHT is ON!"); // отправляем ответ о выполнении
    PRINTLOG("LIGHT is ON!");
}

void functionWaterOff() {
    waterStatus = 1;
    digitalWrite(waterPin, waterStatus);
    PRINTLOG("WATER is OFF!");
}
void functionWaterOn() {
    waterStatus = 0;
    digitalWrite(waterPin, waterStatus);
    PRINTLOG("WATER is ON!");
}

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
            while (!updateTime()) {
            Serial.println("!!!");  
            delay(10000);
        }
    }

    NOWDAY = day();
    NOWHOUR = hour();
    NOWMINUTE = minute();
    NOWSECOND = second();

    if (hour() >= lightStart && hour() <= lightStop) {
        functionLightOn();
    }
    else {
        functionLightOff();
    }

    if (minute() >= waterStart && minute() <= waterStop) {
        functionWaterOn();
    }
    else {
        functionWaterOff();
    }
    
}


void loop() {
   checkEvents();
   server.handleClient();
}
