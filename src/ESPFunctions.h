#pragma once
#include <Arduino.h>
#include "../include/GlobalDefinations.h"

void espWaitRead(uint16_t size = 0);
void espCloseClient(const char &DeviceIndex);
void espSendRead(const String &command, uint16_t size = 0);
void espSendStatus(const char &DeviceIndex,const String & data);

