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

void init_iotmakers()
{
  while(1)
  {
    Serial.print(F("Connect to AP..."));
    while(g_im.begin(WIFI_SSID, WIFI_PASS) < 0)
    {
      Serial.println(F("retrying"));
      delay(100);
    }

    Serial.println(F("Success"));

    g_im.init(deviceID, authnRqtNo, extrSysID);
  
    Serial.print(F("Connect to platform..."));
    while(g_im.connect() < 0)
    {
      Serial.println(F("retrying."));
      delay(100);
    }
    Serial.println(F("Success"));
  
    Serial.print(F("Auth..."));
    if(g_im.auth_device() >= 0)
    {
      Serial.println(F("Success..."));
      return;
    }
  }
}

void setup() {
  Serial.begin(9600);

  sensors.begin();
  
  init_iotmakers();
}

void loop() {
  static unsigned long tick = millis();

  if(g_im.isServerDisconnected() == 1)
  {
    init_iotmakers();
  }

  if((millis() - tick) > 1000)
  {
    send_temperature();
    tick = millis();
  }

  g_im.loop();
}

int send_temperature()
{
  // This Scope is package of temperature sensor
  // Raw coding (with register address) look at "5_Temperature_Sensor Project"
  sensors.requestTemperatures();
  int data = sensors.getTempCByIndex(0);

  Serial.print("Temperature : ");
  Serial.print(data);
  Serial.println(" Celsius");
  
  if(g_im.send_numdata(TAG_ID, (double)data) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }

  return 0;
}
