#include <EEPROM.h>
#include "RelayFunctions.h"

// ------ Device To Compile ----------

#ifdef _MAINROOM_
#include "../include/Devices/MainRoom.h"
#endif

#ifdef _LOBBY_
#include "../include/Devices/Lobby.h"
#endif

// ----------------------------------------------------



void relayAlterDevice(const uint16_t &device, const uint8_t &state)
{
  Console(println(" --> relayalter"));
  
  bool iState = LOW;
  if (state != 0) {
    iState = HIGH;
  }

  Console(println("istate -> "));
  Console(println(iState));

  digitalWrite(Devices[0][device], !iState);
  EEPROM.update(Devices[2][device], iState);
  Console(println(Devices[2][device]));
  
}

void relayCheckSwitch()
{
  uint16_t index = 0; 
  while (index < Devices_no)
  {
    if(!digitalRead(Devices[1][index]) != Devices_Switch[index]){
      Console(println("switchesL -- "));
      Console(println(Devices_Switch[index]));
      Console(println(!digitalRead(Devices[1][index])));
      Console(println(index));

      Devices_Switch[index] = !digitalRead(Devices[1][index]);

      digitalWrite(Devices[0][index],!Devices_Switch[index]);
      EEPROM.update(Devices[2][index],Devices_Switch[index]);
      EEPROM.update(Devices[2][index]+1,Devices_Switch[index]);
      
    }
    index++;
  }
}


void relaySetup()
{
  Console(println("InSetup"));
  uint16_t index = 0; 
  while (index < Devices_no)
  {
    pinMode(Devices[0][index], OUTPUT);
    pinMode(Devices[1][index], INPUT_PULLUP);

    Devices_Switch[index] = !digitalRead(Devices[1][index]);
    Console(println("Switch State :- "));
    Console(println(Devices_Switch[index]));

    if(EEPROM.read(Devices[2][index] + 1) == Devices_Switch[index]) {

      digitalWrite(Devices[0][index],!EEPROM.read(Devices[2][index]));
    }
    else {
      Console(println("INELSE"));
      digitalWrite(Devices[0][index],!Devices_Switch[index]);
      EEPROM.update(Devices[2][index],Devices_Switch[index]);
      EEPROM.update(Devices[2][index]+1,Devices_Switch[index]);
    }
    index++;
  }
}

String realyGetDeviceStatus()
{
  String status = "";
  uint16_t index = 0; 

  while (index < Devices_no)
  {
    status.concat(EEPROM.read(Devices[2][index]));
    index++;
  }
  return status;
}
