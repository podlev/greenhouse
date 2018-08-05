void configJson() {
    String json = "{";
    
    json += "\"dateValue\":"+String(day());

    json += ", \"timeValue\":"+String(hour());

    json += ", \"timeZone\":"+String(timeZone);
    
    json += ", \"waterStart\":"+String(waterStart);
    json += ", \"waterStop\":"+String(waterStop);
    json += ", \"lightStart\":"+String(lightStart);
    json += ", \"lightStop\":"+String(lightStop);
    
    json += ", \"lightStatus\":"+String(lightStatus);
    json += ", \"waterStatus\":"+String(waterStatus);
    
    json += "}";
    server.send(200, "text/json", json);
}

void saveConfig() {
  lightStart = server.arg("lightStart").toInt(); // Получаем значение из запроса сохраняем в глобальной переменной
  waterStart = server.arg("waterStart").toInt();
  lightStop = server.arg("lightStop").toInt();
  waterStop = server.arg("waterStop").toInt();
  timeZone = server.arg("timeZone").toInt();
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
  server.on("/saveConfig", saveConfig);
  server.on("/functionLightOn", functionLightOn);
  server.on("/functionLightOff", functionLightOff);
  
  server.begin();
  Serial.println("HTTP server started");
}


