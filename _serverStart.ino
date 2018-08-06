void configJson() {
    String root = "{}";  // Формировать строку для отправки в браузер json формат
    //{"SSDP":"SSDP-test","ssid":"home","password":"i12345678","ssidAP":"WiFi","passwordAP":"","ip":"192.168.0.101"}
    // Резервируем память для json обекта буфер может рости по мере необходимти, предпочтительно для ESP8266
    DynamicJsonBuffer jsonBuffer;
    //  вызовите парсер JSON через экземпляр jsonBuffer
    JsonObject& json = jsonBuffer.parseObject(root);
    json["ssid"] = ssid;
    json["password"] = password;
    json["dateValue"] = String(day()) + "." + String(month()) + "." + String(year());
    json["timeValue"] = String(hour()) + "." + String(minute()) + "." + String(second());
    json["timeZone"] = timeZone;
    json["waterStart"] = waterStart;
    json["waterStop"] = waterStop;
    json["lightStart"] = lightStart;
    json["lightStop"] = lightStop;
    json["lightStatus"] = lightStatus;
    json["waterStatus"] = waterStatus;
    root = "";
    json.printTo(root);
    server.send(200, "text/json", root);
}

void updateConfig() {
  lightStart = server.arg("lightStart").toInt(); // Получаем значение из запроса сохраняем в глобальной переменной
  waterStart = server.arg("waterStart").toInt();
  lightStop = server.arg("lightStop").toInt();
  waterStop = server.arg("waterStop").toInt();
  timeZone = server.arg("timeZone").toInt();
  checkLightWater();
  saveConfig();
  server.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
}

void serverStart(void){
  
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  SPIFFS.begin();
  {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {    
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
      Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
    }
    Serial.printf("\n");
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
  server.on("/configs.json", configJson);
  server.on("/updateConfig", updateConfig);
  server.on("/functionLightOn", functionLightOn);
  server.on("/functionLightOff", functionLightOff);
  server.on("/functionWaterOn", functionWaterOn);
  server.on("/functionWaterOff", functionWaterOff);
  
  server.begin();
  Serial.println("HTTP server started");
}


