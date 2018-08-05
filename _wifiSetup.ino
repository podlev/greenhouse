bool wifiSetup() {
  WiFi.mode(WIFI_STA);
  byte tries = 20;
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Connect to WiFi ");
  while (WiFi.status() != WL_CONNECTED  && tries--) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected "); 
    return false;   
  }
  else {
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    return true;
  }
}

