#include <Arduino.h>
#include <Ethernet.h>
#include <SPI.h>
#include <IoTStarterKit_Eth.h>

/*
IoTMakers
*/
IoTStarterKit_Eth g_im;

#define deviceID    "dodit0D1566352364009"                   
#define authnRqtNo  "g1s4dsarv"                   
#define extrSysID   "OPEN_TCP_001PTL001_1000007609"  


/*
 Ethernet
*/
EthernetClient client;

const char mac[] = { 0x70, 0xB3, 0xD5, 0x6A, 0x60, 0xE8 }; //Mac Address


/*
 Arduino
*/
#define PIN_LED 2
#define TAG_ID "LED"

//Initialize IoT Makers connection
void init_iotmakers()
{
  int tryCount = 0; //Stores the number of connection attempt
  
  while(1)
  {
    // Ethernet connection attempt
    Serial.print("Begin the Ethernet...");
    tryCount = 0;
    while( (Ethernet.begin(mac) == 0) && tryCount < 5 )
    {
      Serial.println(F("retrying."));
      delay(2000);
      tryCount++;
    }
    if(tryCount < 5)
    {
      Serial.println("success");
    }
    else
    {
      Serial.println("fail");
      continue;
    }

    // 인자값으로 받은 정보로 KT IoT Makers 접속
    // Access KT IoT Makers with information received as a parameter
    g_im.init(deviceID, authnRqtNo, extrSysID, client);

    g_im.set_strdata_handler(mycb_strdata_handler); 
    // IoTMakers platform connection
    Serial.print("Connect to Platform... ");
    tryCount = 0;
    while ( (g_im.connect() < 0) && tryCount < 5 ){
      Serial.println("retrying.");
      delay(1000);
      tryCount++;
    }
    if(tryCount < 5)
    {
      Serial.println("success");
    }
    else
    {
      Serial.println("fail");
      continue;
    }
    
    //IoTMakers platform certification
    Serial.print("Auth... ");
    if(g_im.auth_device() >= 0)
    {
      Serial.println("success ");
      return;
    }
    Serial.println("fail");
  }
}

void setup()
{
  Serial.begin(9600);
    
  pinMode(PIN_LED,OUTPUT);
  digitalWrite(PIN_LED, HIGH);
  
  init_iotmakers();
}


//Where action takes place
void loop()
{
  // IoTMakers 플랫폼 수신처리 및 keepalive 송신
  // IoTMakers platform receiving process and keepalive transmission
  g_im.loop();
}


//What to send to Platform
void mycb_strdata_handler(char *tagid, char *strval)
{
  if ( strcmp(tagid, TAG_ID) == 0 && strcmp(strval, "on") == 0 )
  {
    digitalWrite(PIN_LED, LOW);  
    Serial.println("LED ON");
  }
  
  else if ( strcmp(tagid, TAG_ID) == 0 && strcmp(strval, "off") == 0 )
  {
    digitalWrite(PIN_LED, HIGH);    
    Serial.println("LED OFF");
  }
}
