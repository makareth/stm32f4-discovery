#pragma once

#define CS43L12_ADDRESS	0x94

uint8_t CS43L12_Init();

uint8_t CS43L12_BeepContinuous();

uint8_t CS43L12_ReadId();
uint8_t CS43L12_ReadError();
uint8_t CS43L12_ReadMasterVolume();
uint8_t CS43L12_ReadPower();

