#define saklar 2

int fnd_pin[8] = {2, 3, 4, 5, A2, A3, A4, A5};
int fnd_digits[11][8] = {
  {1, 1, 1, 1, 1, 1, 0, 1},
  {0, 1, 1, 0, 0, 0, 0, 0},
  {1, 1, 0, 1, 1, 0, 1, 0},
  {1, 1, 1, 1, 0, 0, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {1, 0, 1, 1, 0, 1, 1, 0},
  {1, 0, 1, 1, 1, 1, 1, 0},
  {1, 1, 1, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 0},
  {1, 1, 1, 1, 0, 1, 1, 0}
};

void setup() {
  for (int i = 0; i < 10; i++) {
    pinMode(fnd_pin[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 9; i >= 0; i--) {
    display(i);
    delay(500);
    if (i == 0) {
      for (int j = 1; j <= 5; j++)
      {
        ketam();
        wolu();
      }
    }
  }
}

void display(int num) {
  if (num < 0) num = 0;
  else if (num >= 10) num = 9;

  for (int i = 0; i < 9; i++) {
    digitalWrite(fnd_pin[i], fnd_digits[num][i]);
  }
}

void ketam() {
  for (int i = 0; i < 9; i++) {
    digitalWrite(fnd_pin[i], LOW);
  }
  delay(500);
}

void wolu() {
  for (int i = 0; i < 9; i++) {
    digitalWrite(fnd_pin[i], HIGH);
  }
  delay(500);
}
