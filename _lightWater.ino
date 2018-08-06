void checkLightWater() {
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

void functionLightOff() {
    lightStatus = 1;
    digitalWrite(lightPin, lightStatus);
    server.send(200, "text/plain", "Свет выключен!"); // отправляем ответ о выполнении
    PRINTLOG("LIGHT is OFF!");
}
  
void functionLightOn() {
    lightStatus = 0;
    digitalWrite(lightPin, lightStatus);
    server.send(200, "text/plain", "Свет включен!"); // отправляем ответ о выполнении
    PRINTLOG("LIGHT is ON!");
}

void functionWaterOff() {
    waterStatus = 1;
    digitalWrite(waterPin, waterStatus);
    server.send(200, "text/plain", "Орошение выключено!"); // отправляем ответ о выполнении
    PRINTLOG("WATER is OFF!");
}
void functionWaterOn() {
    waterStatus = 0;
    digitalWrite(waterPin, waterStatus);
    server.send(200, "text/plain", "Орошение включено!"); // отправляем ответ о выполнении
    PRINTLOG("WATER is ON!");
}
