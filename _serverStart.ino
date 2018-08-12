String toFormat(int value) {
  if (value < 10) {
    return '0' + String(value); 
  }
  else {
    return String(value);
  }
}

void settings() {
    String root = "{}";  // Формировать строку для отправки в браузер json формат
    //{"SSDP":"SSDP-test","ssid":"home","password":"i12345678","ssidAP":"WiFi","passwordAP":"","ip":"192.168.0.101"}
    // Резервируем память для json обекта буфер может рости по мере необходимти, предпочтительно для ESP8266
    DynamicJsonBuffer jsonBuffer;
    //  вызовите парсер JSON через экземпляр jsonBuffer
    JsonObject& json = jsonBuffer.parseObject(root);
    json["ssid"] = ssid;
    json["password"] = password;
    json["day"] = toFormat(day());
    json["month"] = toFormat(month());
    json["year"] = year();
    json["hour"] = toFormat(hour());
    json["minute"] = toFormat(minute());
    json["timeZone"] = timeZone;
    json["waterStartH"] = waterStartH;
    json["waterStopH"] = waterStopH;
    json["waterStartM"] = waterStartM;
    json["waterStopM"] = waterStopM;
    json["lightStartH"] = lightStartH;
    json["lightStopH"] = lightStopH;
    json["lightStartM"] = lightStartM;
    json["lightStopM"] = lightStopM;
    if (lightStatus == 1) {
      json["lightStatus"] = "Оcвещение выключено.";
    }
    else {
      json["lightStatus"] = "Оcвещение включено.";
    }
    if (waterStatus == 1) {
      json["waterStatus"] = "Полив выключен.";
    }
    else {
      json["waterStatus"] = "Полив включен.";
    }
    
    root = "";
    json.printTo(root);
    server.send(200, "text/json", root);
}

void updateWaterLight() {
  lightStartH = server.arg("lightStartH").toInt(); // Получаем значение из запроса сохраняем в глобальной переменной
  lightStopH = server.arg("lightStopH").toInt();
  lightStartM = server.arg("lightStartM").toInt();
  lightStopM = server.arg("lightStopM").toInt();
  
  waterStartH = server.arg("waterStartH").toInt();
  waterStopH = server.arg("waterStopH").toInt();
  waterStartM = server.arg("waterStartM").toInt();
  waterStopM = server.arg("waterStopM").toInt();
  
  
  checkLightWater();
  saveConfig();
  server.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
}


void updateSettings() {
  ssid =  server.arg("ssid");
  password = server.arg("password");
  timeZone = server.arg("timeZone").toInt();
  Serial.println(server.arg("dateValue"));
  Serial.println(server.arg("timeValue"));
  saveConfig();
  server.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
}

void restartDevice  () {
  String restart = server.arg("device");          // Получаем значение device из запроса
  if (restart == "ok") {                         // Если значение равно Ок
    server.send(200, "text / plain", "Reset OK"); // Oтправляем ответ Reset OK
    ESP.restart();                                // перезагружаем модуль
  }
  else {                                        // иначе
    server.send(200, "text / plain", "No Reset"); // Oтправляем ответ No Reset
  }
}



void serverStart(void){
  
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  

  
  server.on("/list", HTTP_GET, handleFileList);
  //load editor
  server.on("/edit", HTTP_GET, [](){
    if(!handleFileRead("/edit.htm")) server.send(404, "text/plain", "FileNotFound");
  });
  //create file
  server.on("/edit", HTTP_PUT, handleFileCreate);
  //delete file
  server.on("/edit", HTTP_DELETE, handleFileDelete);
  //first callback is called after the request has ended with all parsed arguments
  //second callback handles file uploads at that location
  server.on("/edit", HTTP_POST, [](){ server.send(200, "text/plain", ""); }, handleFileUpload);

  //called when the url is not defined here
  //use it to load content from SPIFFS
  server.onNotFound([](){
    if(!handleFileRead(server.uri()))
      server.send(404, "text/plain", "FileNotFound");
  });

  //get heap status, analog input value and all GPIO statuses in one json call
  server.on("/settings", settings);
  server.on("/updateWaterLight", updateWaterLight);
  server.on("/updateSettings", updateSettings);
  server.on("/restart", restartDevice);
  server.on("/functionLightOn", functionLightOn);
  server.on("/functionLightOff", functionLightOff);
  server.on("/functionWaterOn", functionWaterOn);
  server.on("/functionWaterOff", functionWaterOff);
  
  server.begin();
  Serial.println("HTTP server started");
}


