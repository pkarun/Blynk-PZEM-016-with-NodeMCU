#define BLYNK_PRINT Serial           // Uncomment for debugging 

#include "settings.h"           
//#include "secret.h"                   // <<--- UNCOMMENT this before you use and change values on config.h tab
#include "my_secret.h"                  // <<--- COMMENT-OUT or REMOVE this line before you use. This is my personal settings.

#include <ArduinoOTA.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <ModbusMaster.h>
#include <ESP8266WiFi.h>

#include <SoftwareSerial.h>  //  ( NODEMCU ESP8266 )

#define MAX485_DE      D1
#define MAX485_RE_NEG  D2

SoftwareSerial pzem(D5, D6, false,256);
 
ModbusMaster node;

BlynkTimer timer;

double voltage_usage, current_usage, active_power, active_energy, frequency, power_factor, over_power_alarm; 

uint8_t result;  uint16_t data[6];

void preTransmission()
{
  digitalWrite(MAX485_RE_NEG, 1);
  digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
}

void setup() {

  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  
  // Init in receive mode
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);

  Serial.begin(9600);
  pzem.begin(9600);

  // Modbus slave ID 1
  node.begin(1, pzem);
  
  // Callbacks allow us to configure the RS485 transceiver correctly
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
 
#if defined(USE_LOCAL_SERVER) 
  Blynk.begin(AUTH, WIFI_SSID, WIFI_PASS, SERVER, PORT);
#else
  Blynk.begin(AUTH, WIFI_SSID, WIFI_PASS);
#endif
  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.begin();

timer.setInterval(10000L, sendtoBlynk); // send values blynk server every 10 sec

}

void sendtoBlynk() {
  Blynk.virtualWrite(vPIN_VOLTAGE,               voltage_usage);
  Blynk.virtualWrite(vPIN_CURRENT_USAGE,         current_usage);
  Blynk.virtualWrite(vPIN_ACTIVE_POWER,          active_power);
  Blynk.virtualWrite(vPIN_ACTIVE_ENERGY,         active_energy);
  Blynk.virtualWrite(vPIN_FREQUENCY,             frequency);
  Blynk.virtualWrite(vPIN_POWER_FACTOR,          power_factor);
  Blynk.virtualWrite(vPIN_OVER_POWER_ALARM,      over_power_alarm);
}


void pzemdata(){

    //node.clearResponseBuffer();
    
    ESP.wdtDisable();
    result = node.readInputRegisters(0x0000, 10);
    ESP.wdtEnable(1);
    
    if (result == node.ku8MBSuccess)  
    {
    voltage_usage      = (node.getResponseBuffer(0x00) / 10.0f);
    current_usage      = (node.getResponseBuffer(0x01) / 1000.000f);
    active_power       = (node.getResponseBuffer(0x03) / 10.0f);
    active_energy      = (node.getResponseBuffer(0x05) / 1000.0f);
    frequency          = (node.getResponseBuffer(0x07) / 10.0f);
    power_factor       = (node.getResponseBuffer(0x08) / 100.0f);
    over_power_alarm   = (node.getResponseBuffer(0x09));

  Serial.print("VOLTAGE:           ");   Serial.println(voltage_usage);   // V
  Serial.print("CURRENT_USAGE:     ");   Serial.println(current_usage, 3);  //  A
  Serial.print("ACTIVE_POWER:      ");   Serial.println(active_power);   //  W
  Serial.print("ACTIVE_ENERGY:     ");   Serial.println(active_energy, 3);  // kWh
  Serial.print("FREQUENCY:         ");   Serial.println(frequency);    // Hz
  Serial.print("POWER_FACTOR:      ");   Serial.println(power_factor);
  Serial.print("OVER_POWER_ALARM:  ");   Serial.println(over_power_alarm, 0);
  Serial.println("====================================================");  
    }
    else{
      Serial.println("Failed to read Modbus");
    }
}

void loop() {
  Blynk.run();
  ArduinoOTA.handle();
  timer.run();
  pzemdata();
}
