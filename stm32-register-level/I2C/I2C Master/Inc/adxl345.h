#ifndef ADXL345_H_
#define ADXL345_H_

#include <stdint.h>
#include "i2c.h"

// DEVICE ADDRESS
#define ADXL345_ADDRESS         0x53

// REGISTER ADDRESS
#define ADXL345_DEVID           0x00
#define ADXL345_POWER_CTL       0x2D
#define ADXL345_DATA_FORMAT     0x31

#define ADXL345_DATAX0          0x32
#define ADXL345_DATAX1          0x33

#define ADXL345_DATAY0          0x34
#define ADXL345_DATAY1          0x35

#define ADXL345_DATAZ0          0x36
#define ADXL345_DATAZ1          0x37

// POWER_CTL REGISTER BITS
#define ADXL345_MEASURE         (1U << 3)

// DATA_FORMAT REGISTER
#define ADXL345_FULL_RES   (1U << 3)
#define ADXL345_RANGE_2G   0x00
#define ADXL345_RANGE_4G   0x01
#define ADXL345_RANGE_8G   0x02
#define ADXL345_RANGE_16G  0x03

// DATA STRUCTURE
typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
} ADXL345_Data_t;

// API
void vADXL345_Init(void);

void vADXL345_WriteRegister(uint8_t reg, uint8_t data);

uint8_t uADXL345_ReadRegister(uint8_t reg);

void vADXL345_ReadRegisters(uint8_t startReg, uint8_t *buffer, uint8_t length);

void vADXL345_ReadXYZ(ADXL345_Data_t *data);

#endif /* ADXL345_H_ */
