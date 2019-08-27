#define LIGHT A3
#define LED 9

void setup() {
  Serial.begin(9600);
  pinMode(LIGHT, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  int value = analogRead(LIGHT);
  int data = map(value, 0, 1023, 1023, 0);

  Serial.print("LIGHT : ");
  Serial.println(data);
  analogWrite(LED, value);    
  //analogWrite(LED, 1023);    
  Serial.print("ANALOG VALUE: ");
  Serial.println(value);
  delay(200);
}
