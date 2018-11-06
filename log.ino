void printlog (String message) {
  printtime();
  //time_t t = now();
  //Serial.println(t);
  Serial.println(message);
}

void printtime() {
  Serial.print(day());
  Serial.print(".");
  Serial.print(month());
  Serial.print(".");
  Serial.print(year());
  Serial.print(" ");
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print(" ");
}

