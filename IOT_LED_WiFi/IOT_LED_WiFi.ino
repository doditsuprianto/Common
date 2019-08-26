#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>

/*
 Arduino
*/
#define LED   2
#define TAG_ID  "KITLEDW"

/*
 WIFI Shield
*/
#define WIFI_SSID   "ICT-LAB-2.4G"                       
#define WIFI_PASS   "12345678"                        


/*
 IoTMakers
*/
IoTMakers g_im;

#define deviceID    "dodit0D1566352364009"            
#define authnRqtNo  "g1s4dsarv"            
#define extrSysID   "OPEN_TCP_001PTL001_1000007609"    


//Initialize IoT Makers connection
void init_iotmakers()
{  
  while(1)
  {
    // AP connection
    Serial.print(F("Connect to AP..."));
    while(g_im.begin(WIFI_SSID, WIFI_PASS)<0) { 
      Serial.println(F("retrying."));
      delay(1000);
    }
    Serial.println(F("success"));

    // Access KT IoT Makers with information received as a parameter
    g_im.init(deviceID, authnRqtNo, extrSysID); 

    // String type control handler
    g_im.set_strdata_handler(mycb_strdata_handler); 
    
    // IoTMakers platform connection
    Serial.print(F("Connect to platform... "));
    while ( g_im.connect() < 0 ){
      Serial.println(F("retrying."));
      delay(1000);
    }
    Serial.println(F("success"));
    
    //IoTMakers platform certificate
    Serial.print(F("Auth... "));
    if(g_im.auth_device() >= 0) {
      Serial.println(F("success "));
      return;
    }
    Serial.println(F("fail"));
  }
}


void setup() 
{
	Serial.begin(9600);
  
  pinMode(LED,OUTPUT);
  digitalWrite(LED, HIGH);

	init_iotmakers();
}


void loop()
{
	static unsigned long tick = millis();

  // Reconnect if platform connection is terminated
  if(g_im.isServerDisconnected() == 1) 
  {
    init_iotmakers();
  }

  // IoTMakers 플랫폼 수신처리 및 keepalive 송신
	// IoTMakers platform processing receive and keepalive transmission
	g_im.loop();
}


// What to send to platform
void mycb_strdata_handler(char *tagid, char *strval)
{
  if ( strcmp(TAG_ID, tagid) == 0 && strcmp(strval, "on") == 0 )
  {
    digitalWrite(LED, LOW);  
    Serial.println(F("LED ON"));
  }
  
  else if ( strcmp(TAG_ID, tagid) == 0 && strcmp(strval, "off") == 0 )
  {
    digitalWrite(LED, HIGH);    
    Serial.println(F("LED OFF"));
  }
}
