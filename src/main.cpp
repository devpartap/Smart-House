#include <Arduino.h>

#include "Definations.h"
#include "ESPFunctions.h"
#include "RelayFunctions.h"

void setup()
{

  Console(begin(115200));
  ESP8266.begin(115200);
  ESP8266.setTimeout(10);


  Console(println("start"));

  pinMode(test_led,OUTPUT);
  digitalWrite(test_led,HIGH);
  delay(4000);
  digitalWrite(test_led,LOW);

  relaySetup();
  espSendRead("AT+CIPMUX=1",19);
  espSendRead("AT+CIPSERVER=1,0080",38);
}

void loop()
{
  if (ESP8266.available())
  {
    Console(println("readingst"));
    String data = ESP8266.readString();
    Console(println("donest"));
    Console(println(data));
    Console(println(data.length()));
    processRequest(data);
  }
  relayCheckSwitch();
}

void processRequest(String &req)
{
  int16_t index = 0;
  uint16_t msg_index;
  uint16_t info_Index;
  uint16_t client_Index;

  uint16_t Device;
  uint8_t DeviceStatus;

  String ClientInfo;

  index = req.indexOf("POST", index);

  while (index != -1) {

    Console(println("POST receved!"));
    msg_index = req.indexOf("{",index+230);

    if(index >= 25) {
    client_Index = req.indexOf(",CONN",index - 25) - 1;
    } 
    else {
     client_Index = req.indexOf(",CONN") - 1;
    }

    if(req[msg_index + 1] == '?')
    {
      Console(println("SERVERREQUESTEDINFO"));
      Console(println(realyGetDeviceStatus()));

      espSendStatus(req[client_Index],realyGetDeviceStatus());

      index = req.indexOf("POST", index+240);
      continue;
    }

    Device = req[msg_index + 1] - '0';
    DeviceStatus = req[msg_index + 3] - '0';

    Console(println("sentrelay"));
    relayAlterDevice(Device,DeviceStatus);
    Console(println("donesentrelay"));


    Console(println("colsing client"));
    espCloseClient(req[client_Index]);
    Console(println("closed client"));

    info_Index = req.indexOf(':', index + 30);
    ClientInfo = req.substring(info_Index + 1, req.indexOf('\n', info_Index));

    Console(println(ClientInfo));
    Console(println(index));
    Console(println(msg_index));
    Console(println(info_Index));
    Console(println(client_Index));
    Console(println(Device));
    Console(println(DeviceStatus));

    index = req.indexOf("POST", index+240);
  }
}