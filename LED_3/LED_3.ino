#define ledMerah 2
#define ledHijau 3
#define ledKuning 4
#define saklar 5

int counter = 0;
//boolean status_saklar = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledHijau, OUTPUT);
  pinMode(ledMerah, OUTPUT);
  pinMode(ledKuning, OUTPUT);
  pinMode(saklar, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(saklar), interrupt, CHANGE);

  //digitalWrite(ledMerah, LOW);
  //digitalWrite(ledHijau, LOW);
  //digitalWrite(ledKuning, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState;
  buttonState = digitalRead(saklar);
  if (buttonState == LOW)
  {
    counter++;
    delay(200);
    if (counter == 4) counter = 0;
  }

  if (counter == 0)
  {
    digitalWrite(ledMerah, LOW);
    digitalWrite(ledHijau, LOW);
    digitalWrite(ledKuning, LOW);
  }
  else if (counter == 1)
  {
    digitalWrite(ledMerah, HIGH);
    digitalWrite(ledHijau, LOW);
    digitalWrite(ledKuning, LOW);
  }
  else if (counter == 2)
  {
    digitalWrite(ledMerah, LOW);
    digitalWrite(ledHijau, HIGH);
    digitalWrite(ledKuning, LOW);
  }
  else if (counter == 3)
  {
    digitalWrite(ledMerah, LOW);
    digitalWrite(ledHijau, LOW);
    digitalWrite(ledKuning, HIGH);
  }

  Serial.println(counter);
}
