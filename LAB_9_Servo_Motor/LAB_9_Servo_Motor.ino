#include <Servo.h>

Servo myServo;
int angle = 0;

void setup() {
  Serial.begin(9600);
  myServo.attach(3);
}

void loop() {
  static unsigned long tick = millis();

  if ((millis() - tick) > 60000) // sampling period 6 seconds
  {
    swing();
    tick = millis();
  }


}

void swing() {
  for (int ulang = 0; ulang < 10; ulang++) {
    for (angle = 0; angle < 180; angle++) {
      myServo.write(angle);
      //delay(15);
    }

    for (angle = 180; angle > 0; angle--) {
      myServo.write(angle);
      //delay(15);
    }
  }
}
