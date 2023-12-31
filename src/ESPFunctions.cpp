#include "ESPFunctions.h"

void espCloseClient(const char &DeviceIndex)
{
  
  Console(println(DeviceIndex));
  String Command = "AT+CIPSEND=" + (String)DeviceIndex + ",89"; 
  ESP8266.println(Command);
  delay(10);
  //espSendRead(Command.c_str(),25);
  
  ESP8266.println("HTTP/1.1 200 OK");
  ESP8266.println("Access-Control-Allow-Origin: *");
  ESP8266.println("Connection: close");
  ESP8266.println("Content-Length: 0");
  ESP8266.println("");

  Console(println("wait reding"));
  espWaitRead(65);
  Console(println("done!!"));
}

void espWaitRead(uint16_t size)
{
  Console(println("IN WAITREAD!"));

  while (!ESP8266.available())
  {
    delay(10);
  }

  String msg = ESP8266.readString();
  Console(println(msg.length()));
  Console(println("\n----- ESP -----\n" + msg + "---------------\n"));

  if (msg.length() >= size + 5)
  {
    processRequest(msg);
    Console(println("wrinprocess"));
  }
}

void espSendRead(const String &command, uint16_t size)
{
  ESP8266.println(command);
  ESP8266.flush();

  String msg = ESP8266.readString();
  Console(println(msg.length()));
  Console(println("\n----- ESP -----\n" + msg + "---------------\n"));

  if (msg.length() >= size + 5)
  {
    processRequest(msg);
    Console(println("inprocess"));
  }
}

void espSendStatus(const char &DeviceIndex,const String & data)
{
 
#ifdef _LOBBY_
  String Command = "AT+CIPSEND=" + (String)DeviceIndex + ",121";
#endif  
#ifdef _MAINROOM_
  String Command = "AT+CIPSEND=" + (String)DeviceIndex + ",123";
#endif  
  ESP8266.println(Command);
  delay(10);
  
  //espSendRead(Command.c_str(),25);
  ESP8266.println("HTTP/1.1 200 OK");

#ifdef _LOBBY_
  ESP8266.println("Content-Length: 6");
#endif 
#ifdef _MAINROOM_
  ESP8266.println("Content-Length: 8");
#endif  
  
  ESP8266.println("Content-Type: text/plain");
  ESP8266.println("Access-Control-Allow-Origin: *");
  ESP8266.println("Connection: close");
  ESP8266.println("");
  ESP8266.println(data);

  espWaitRead(68);
  Console(println("done!!"));
  Console(println("request answered!"));
}
