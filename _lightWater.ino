void checkLightWater() {
  if (hour() >= lightStartH && hour() <= lightStopH) {
    if (minute() >= lightStartM && minute() <= lightStopM) {
      lightStatus = 0;
      digitalWrite(lightPin, lightStatus);  
      PRINTLOG("LIGHT is ON!"); 
    }
    else {
      lightStatus = 1;
      digitalWrite(lightPin, lightStatus);
      PRINTLOG("LIGHT is OFF!");
    }
  }
  else {
    lightStatus = 1;
    digitalWrite(lightPin, lightStatus);
    PRINTLOG("LIGHT is OFF!");
  }
  if (hour() >= waterStartH && hour() <= waterStopH && (hour() % period == 0)) {
    if (minute() >= waterStartM && minute() <= waterStopM) {
       waterStatus = 0;
       digitalWrite(waterPin, waterStatus);
       PRINTLOG("WATER is ON!");
    }
    else {
       waterStatus = 1;
       digitalWrite(waterPin, waterStatus);
       PRINTLOG("WATER is OFF!");
    }
  }
  else {
    waterStatus = 1;
    digitalWrite(waterPin, waterStatus);
    PRINTLOG("WATER is OFF!");
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
    server.send(200, "text/plain", "Полив выключено!"); // отправляем ответ о выполнении
    PRINTLOG("WATER is OFF!");
}
void functionWaterOn() {
    waterStatus = 0;
    digitalWrite(waterPin, waterStatus);
    server.send(200, "text/plain", "Полив включен!"); // отправляем ответ о выполнении
    PRINTLOG("WATER is ON!");
}
