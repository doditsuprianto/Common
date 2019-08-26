int incomingByte = 0;
int fnd_pin[8] = {2, 3, 4, 5, A2, A3, A4, A5};
int fnd_digits[10][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0},
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

String inString = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {
    pinMode(fnd_pin[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //for (int i = 0; i < 10; i++) {
  //  display(i);
  //  delay(1000);
  //}


  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      inString += (char)inChar;
    }

    if (inChar == '\n') {
      Serial.print("Value:");
      Serial.println(inString.toInt());
      Serial.print("String: ");
      Serial.println(inString);
      // clear the string for new input:
      inString = "";

      display(inString.toInt());
    }
  }
}

void display(int num) {
  if (num < 0) num = 0;
  else if (num >= 10) num = 9;

  for (int i = 0; i < 8; i++) {
    digitalWrite(fnd_pin[i], fnd_digits[num][i]);
  }
}
