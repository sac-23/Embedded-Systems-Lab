#ifndef I2C_H
#define I2C_H

#include "stm32f103x6.h"
#include <stdint.h>

#define I2C_READ 1
#define I2C_WRITE 0

void vI2C1_Init(void);

void vI2C1_Start(uint8_t repeated);
void vI2C1_Stop(void);

void vI2C1_SendAddress(uint8_t address, uint8_t direction);

void vI2C1_WriteByte(uint8_t data);

uint8_t uI2C1_ReadByte_ACK(void);
uint8_t uI2C1_ReadByte_NACK(void);


#endif /* I2C_H_ */
