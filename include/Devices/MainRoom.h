#define _MAINROOM_

#define Devices_no 6

const uint8_t Devices[3][Devices_no] = {
  {43,45,47,49,51,53},            // {Relay Pins}
  {28,30,32,34,36,38},            // {Switch Pins}
  {0 , 2, 4, 6, 8,10}             // {EEPROM Adress}
  };

bool Devices_Switch[Devices_no] = {0,0,0,0,0,0};