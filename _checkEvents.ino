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
              lightStatus = 0;
              digitalWrite(lightPin, lightStatus);  
              PRINTLOG("LIGHT is ON!"); 
           }
           if (minute() == lightStopM + 1) {
              lightStatus = 1;
              digitalWrite(lightPin, lightStatus);  
              PRINTLOG("LIGHT is OFF!"); 
           }
       }
       if (hour() >= waterStartH && hour() <= waterStopH && (hour() % period == 0)) {
           if (minute() == waterStartM) {
              waterStatus = 0;
              digitalWrite(waterPin, waterStatus);
              PRINTLOG("WATER is ON!");
           }
           if (minute() == waterStopM + 1) {
              waterStatus = 1;
              digitalWrite(waterPin, waterStatus);
              PRINTLOG("WATER is OFF!");
              
           }
       }
       temperature();
       NOWMINUTE = minute();
    }
}
