void temperature() {
  int check;
  check = dht.read();
  switch (check) {
    case DHT_OK:
      Serial.print("Temperature = ");
      valueT = dht.getTemperatureC();
      Serial.print(valueT);
      Serial.print("C \t");
      valueH = dht.getHumidity();
      Serial.print("Humidity = ");
      Serial.print(valueH);
      Serial.println("%");
      break;
    case DHT_ERROR_CHECKSUM:
      Serial.println("Checksum error");
      break;
    case DHT_ERROR_TIMEOUT:
      Serial.println("Time out error");
      break;
    default:
      Serial.println("Unknown error");
      break;
  }
}
