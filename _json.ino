bool loadConfig() {
  // Открываем файл для чтения
  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
  // если файл не найден  
    Serial.println("Failed to open config file");
  //  Создаем файл запиав в него аные по умолчанию
    saveConfig();
    configFile.close();
    return false;
  }
  // Проверяем размер файла, будем использовать файл размером меньше 1024 байта
  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    configFile.close();
    return false;
  }

// загружаем файл конфигурации в глобальную переменную
  jsonConfig = configFile.readString();
  configFile.close();
  // Резервируем памяь для json обекта буфер может рости по мере необходимти предпочтительно для ESP8266 
    DynamicJsonBuffer jsonBuffer;
  //  вызовите парсер JSON через экземпляр jsonBuffer
  //  строку возьмем из глобальной переменной String jsonConfig
    JsonObject& root = jsonBuffer.parseObject(jsonConfig);
  // Теперь можно получить значения из root  
    ssid = root["ssid"].as<String>(); // Так получаем строку
    password = root["password"].as<String>();
    timeZone = root["timeZone"];               // Так получаем число
    waterStart = root["waterStart"];
    waterStop = root["waterStop"];
    lightStart = root["lightStart"];
    lightStop = root["lightStop"];
    return true;
}

// Запись данных в файл config.json
bool saveConfig() {
  // Резервируем память для json обекта буфер может рости по мере необходимти предпочтительно для ESP8266 
  DynamicJsonBuffer jsonBuffer;
  //  вызовите парсер JSON через экземпляр jsonBuffer
  JsonObject& json = jsonBuffer.parseObject(jsonConfig);
  // Заполняем поля json 
  json["ssid"] = ssid;
  json["password"] = password;
  json["timeZone"] = timeZone;
  json["waterStart"] = waterStart;
  json["waterStop"] = waterStop;
  json["lightStart"] = lightStart;
  json["lightStop"] = lightStop;
  // Помещаем созданный json в глобальную переменную json.printTo(jsonConfig);
  json.printTo(jsonConfig);
  // Открываем файл для записи
  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    //Serial.println("Failed to open config file for writing");
    configFile.close();
    return false;
  }
  // Записываем строку json в файл 
  json.printTo(configFile);
  configFile.close();
  return true;
  }


