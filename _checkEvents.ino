void checkEvents() {
  
    //Проверка раз в день
    if (NOWDAY != day()) {
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
    }

    //Проверка раз в минуту
    if (NOWMINUTE != minute()) {
       if (hour() >= lightStartH && hour() <= lightStopH) {
           if (minute() == lightStartM) {
              functionLightOn();
           }
           if (minute() == lightStopM + 1) {
              functionLightOff();
           }
       }
       if (hour() >= waterStartH && hour() <= waterStopH) {
           if (minute() == waterStartM) {
              functionWaterOn();
           }
           if (minute() == waterStopM + 1) {
              functionWaterOff();
           }
       }
       NOWMINUTE = minute();
    }
}
