#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>

#define LIGHT A3
#define LED 9
#define BUZZER 6

IoTMakers g_im;
#define deviceID    "dodit0D1566352364009"
#define authnRqtNo  "g1s4dsarv"
#define extrSysID   "OPEN_TCP_001PTL001_1000007609"
#define WIFI_SSID   "ICT-LAB-2.4G"
#define WIFI_PASS   "12345678"
#define TAG_ID "LEDAMBIENT"

void init_iotmakers()
{
  while (1)
  {
    Serial.print(F("Connect to AP..."));
    while (g_im.begin(WIFI_SSID, WIFI_PASS) < 0)
    {
      Serial.println(F("retrying"));
      delay(100);
    }

    Serial.println(F("Success"));

    g_im.init(deviceID, authnRqtNo, extrSysID);

    Serial.print(F("Connect to platform..."));
    while (g_im.connect() < 0)
    {
      Serial.println(F("retrying."));
      delay(100);
    }
    Serial.println(F("Success"));

    Serial.print(F("Auth..."));
    if (g_im.auth_device() >= 0)
    {
      Serial.println(F("Success..."));
      return;
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LIGHT, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  init_iotmakers();
}

void loop() {
  static unsigned long tick = millis();

  if (g_im.isServerDisconnected() == 1)
  {
    init_iotmakers();
  }

  if ((millis() - tick) > 1000) // sampling period 2 seconds
  {
    send_ambient_of_LED();
    tick = millis();
  }

  g_im.loop();
}

int send_ambient_of_LED() {
  int value = analogRead(LIGHT);
  int data = map(value, 0, 1023, 1023, 0);

  Serial.print("LIGHT : ");
  Serial.println(data);

  if (data < 500) {
    tone(BUZZER, 500, 500);
    Serial.println("Sensor found the obstacle");
  } else {
    Serial.println("No obstacle");
  }

  analogWrite(LED, value);
  //delay(1000);
  
// --------------
  if (g_im.send_numdata(TAG_ID, (double)data) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }
  else
  {
    Serial.println(F("OK"));
  }
  return 0;
}
