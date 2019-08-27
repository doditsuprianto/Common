#define trigPin 13
#define echoPin 12
#define BUZZER 6
#define LED1 8
#define LED2 9
#define LED3 10

void setup()
{
  Serial.begin (9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop()
{
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 17 / 1000;

  if (distance >= 200 || distance <= 0)
  {
    Serial.println("Unable to measure distance");
  }
  else
  {
    Serial.print(distance);
    Serial.println(" cm");
  }

  if (distance < 30) {
    tone(BUZZER, 600);
    delay(distance * 10);
    noTone(BUZZER);
    delay(distance * 10);
  } else {
    delay(500);
  }

  int data = map(distance, 0, 60, 1023, 0);
  if (data > 0) {
    analogWrite(LED1, data);
    //analogWrite(LED2, data);
    //analogWrite(LED3, data);
    Serial.println("Distance Map: " + String(data));
  }
}
