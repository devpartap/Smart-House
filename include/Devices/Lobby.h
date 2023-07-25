#define Devices_no 4

const uint8_t Devices[3][Devices_no] = {
  {8,9,10,11},            // {Relay Pins}
  {4,5,6,7},            // {Switch Pins}
  {0 , 2, 4, 6}             // {EEPROM Adress}
  };

bool Devices_Switch[Devices_no] = {0,0,0,0};