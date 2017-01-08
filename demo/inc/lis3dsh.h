#pragma once

#define LIS3DSH_WHOAMI_REG	0x0F
#define LIS3DSH_REG3_REG 	0x23
#define LIS3DSH_REG4_REG	0x20
#define LIS3DSH_OUT_T_REG	0x0C
#define LIS3DSH_STATUS_REG	0x27
#define LIS3DSH_OUT_X_L_REG	0x28
#define LIS3DSH_OUT_X_H_REG	0x29

#define LIS3DSH_OUT_Y_L_REG	0x2A
#define LIS3DSH_OUT_Y_H_REG	0x2B

#define LIS3DSH_OUT_Z_L_REG	0x2C
#define LIS3DSH_OUT_Z_H_REG	0x2D

uint8_t LIS3DSH_Whoami();
uint8_t LIS3DSH_On();
uint8_t LIS3DSH_IntteruptOn();
uint8_t LIS3DSH_Temp();
uint8_t LIS3DSH_Out_x_l();
uint8_t LIS3DSH_Out_x_h();
uint8_t LIS3DSH_Out_z_l();
uint8_t LIS3DSH_Out_z_h();
uint8_t LIS3DSH_Status();