#define ledMerah 8
#define ledHijau 9
#define ledBiru 10

void setup() {
  // put your setup code here, to run once:
  pinMode(ledMerah, OUTPUT);
  pinMode(ledHijau, OUTPUT);
  pinMode(ledBiru, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  setColor(255, 0, 0);
  delay(1000);
  setColor(0, 255, 0);
  delay(1000);
  setColor(0, 0, 255);
  delay(1000);
  setColor(255, 255, 0);
  delay(1000);
  /*
  setColor(80, 0, 80);
  delay(1000);
  setColor(0, 255, 255);
  delay(1000);
  */
}

void setColor(int red, int green, int blue)
{
  analogWrite(ledMerah, 255 - red);
  analogWrite(ledHijau, 255 - green);
  analogWrite(ledBiru, 255 - blue);
}
