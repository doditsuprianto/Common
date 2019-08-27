int distance = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  static unsigned long tick = millis();

  if ((millis() - tick) > 500) // sampling period 2 seconds
  {
    int volt = map(analogRead(A0), 0, 1023, 0, 5000);
    distance = (27.61 / (volt - 0.1696)) * 1000; // DOING CALIBRATION

    Serial.print(distance);
    Serial.println(" cm");

    tick = millis();
  }
}
