void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}


void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  if (sensorValue > 800)
  {
    Serial.println("Tempo seco");
  }
  else if (sensorValue > 500)
  {
    Serial.println("Chuva fraca");
  }
  else if (sensorValue > 300)
  {
    Serial.println("Chuva moderada");
  }
  else
  {
    Serial.println("Chuva forte");
  }
  Serial.println(sensorValue);
  delay(100);

}

