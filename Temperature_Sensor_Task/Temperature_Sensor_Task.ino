//******************************************************//
// Temperature Sensor
// Sample Code 2 [Control the temperature sensor]
//                                      - Kyung-Sik Jang//
//******************************************************//

#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

IoTMakers g_im;

#define deviceID    "dodit0D1566352364009"
#define authnRqtNo  "g1s4dsarv"
#define extrSysID   "OPEN_TCP_001PTL001_1000007609"

#define WIFI_SSID   "ICT-LAB-2.4G"
#define WIFI_PASS   "12345678"

#define ONE_WIRE_BUS 2

// ************************************************************************ //
// Very Important!!!!
// IoTMakers tag stream id must be the same below !!!
#define TAG_ID "Temperature"
// ************************************************************************ //

OneWire ourWire(ONE_WIRE_BUS);
DallasTemperature sensors(&ourWire);
DeviceAddress tempSensor = {0x28, 0xE1, 0xB8, 0x42, 0x0B, 0x00, 0x00, 0x57};
char alarmTemp;

//Alarm Set Points
char lowSetPoint = 20;
char hiSetPoint = 25;

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
  //char alarmTemp;

  Serial.begin(9600);
  sensors.begin();

  // alarm when temp is higher than value assigned to hiSetPoint
  sensors.setHighAlarmTemp(tempSensor, hiSetPoint);

  // alarm when temp is lower than value assigned to lowSetPoint
  sensors.setLowAlarmTemp(tempSensor, lowSetPoint);

  // Set Measurement Resolution
  sensors.setResolution(tempSensor, 12);

  /*
    alarmTemp = sensors.getHighAlarmTemp(tempSensor);
    Serial.print("High Alarm is set to ");
    Serial.print(alarmTemp, DEC);
    Serial.println(" degrees C");

    alarmTemp = sensors.getLowAlarmTemp(tempSensor);
    Serial.print("Low Alarm is set to ");
    Serial.print(alarmTemp, DEC);
    Serial.println(" degrees C");
  */
  init_iotmakers();

}

void loop() {
  static unsigned long tick = millis();

  if (g_im.isServerDisconnected() == 1)
  {
    init_iotmakers();
  }

  if ((millis() - tick) > 2000) // sampling period 2 seconds
  {
    send_temperature();
    tick = millis();
  }

  g_im.loop();
}

int send_temperature()
{

  alarmTemp = sensors.getHighAlarmTemp(tempSensor);
  Serial.print("High Alarm is set to ");
  Serial.print(alarmTemp, DEC);
  //Serial.print(alarmTemp);
  Serial.println(" degrees C");

  alarmTemp = sensors.getLowAlarmTemp(tempSensor);
  Serial.print("Low Alarm is set to ");
  Serial.print(alarmTemp, DEC);
  //Serial.print(alarmTemp);
  Serial.println(" degrees C");

  sensors.requestTemperatures();
  float data = sensors.getTempCByIndex(0);

  Serial.print("Temperature : ");
  Serial.print(String(data));
  Serial.println(" Celsius");

  if (g_im.send_numdata(TAG_ID, (double)data) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }

  return 0;
}
