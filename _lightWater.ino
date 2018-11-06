void checkLightWater() {
  if (hour() >= lightStartH && hour() <= lightStopH) {
    if (minute() >= lightStartM && minute() <= lightStopM) {
      functionLightOn();
    }
    else {
      functionLightOff();
    }
  }
  else {
    functionLightOff();
  }
  if (hour() >= waterStartH && hour() <= waterStopH && (hour() % period == 0)) {
    if (minute() >= waterStartM && minute() <= waterStopM) {
       functionWaterOn();
    }
    else {
       functionWaterOff();
    }
  }
  else {
    functionWaterOff();
  }
}

void functionLightOff() {
    lightStatus = 1;
    digitalWrite(lightPin, lightStatus);
    server.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
    printlog("light is Off");
}
  
void functionLightOn() {
    lightStatus = 0;
    digitalWrite(lightPin, lightStatus);
    server.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
    printlog("light is On");
}

void functionWaterOff() {
    waterStatus = 1;
    digitalWrite(waterPin, waterStatus);
    server.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
    printlog("water is Off");
}
void functionWaterOn() {
    waterStatus = 0;
    digitalWrite(waterPin, waterStatus);
    server.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
    printlog("water is On");
}
