void checkEvents() {
  
    //Проверка раз в день
    if (NOWDAY != day()) {
            spiffsStart();
            loadConfig();
            wifiSetup();
            updateTime();
            serverStart();
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
