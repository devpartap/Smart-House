#pragma once
#include <Arduino.h>
#include "../include/GlobalDefinations.h"

void relayAlterDevice(const uint16_t &device, const uint8_t &state);
void relaySetup();
void relayCheckSwitch();
String realyGetDeviceStatus();
