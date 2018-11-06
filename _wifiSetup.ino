bool wifiSetup() {
  WiFi.mode(WIFI_STA);
  byte tries = 40;
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Connect to WiFi ");
  while (WiFi.status() != WL_CONNECTED  && tries--) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected. Start in setup mode. Connect to 192.168.4.1");
    IPAddress apIP(192, 168, 4, 1);
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid.c_str(),"");
  }
  else {
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

