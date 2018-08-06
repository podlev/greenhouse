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

    //Проверка раз в час
    if (NOWHOUR != hour()) {
       if (hour() == lightStart) {
           functionLightOn();
       }
       if (hour() == lightStop) {
           functionLightOff();
       }
       NOWHOUR = hour();
    }
    
    //Проверка раз в минуту
    if (NOWMINUTE != minute())
    {
        if (minute() == waterStart) {
           functionWaterOn();
        }
        if (minute() == waterStop) {
           functionWaterOff();
        }
     NOWMINUTE = minute();
   } 
}
