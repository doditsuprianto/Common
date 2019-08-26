#define saklar 2
#define BUZZER 6
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZER, OUTPUT);
}

void loop() {
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
    nada1();
  }
  else if (counter == 1)
  {
    nada2();
  }
  else if (counter == 2)
  {
    nada3();
  }
  else if (counter == 3)
  {
    nada4();
    counter = 0;
  }
}

void nada1() {
  tone(BUZZER, 500, 500);
}

void nada2() {
  tone(BUZZER, 1000, 500);
}

void nada3() {
  tone(BUZZER, 1500, 500);
}

void nada4() {
  tone(BUZZER, 2000, 500);
}
