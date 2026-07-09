#include "adxl345.h"

void vADXL345_WriteRegister(uint8_t reg, uint8_t data) {

	// GENERATE A START CONDITION
	vI2C1_Start(0);

	// SENDING SLAVE ADDRESS WITH WRITE
	vI2C1_SendAddress(ADXL345_ADDRESS, I2C_WRITE);

	// SEND REGISTER ADDRESS
	vI2C1_WriteByte(reg);

	// SEND REGISTER DATA
	vI2C1_WriteByte(data);

	// GENERATE A STOP CONDITION
	vI2C1_Stop();

}

uint8_t uADXL345_ReadRegister(uint8_t reg) {

	// VARIABLE TO STORE A DATA
	uint8_t data = 0;

	// GENERATE A START CONDITION
	vI2C1_Start(0);

	// SENDING SLAVE ADDRESS WITH WRITE
	vI2C1_SendAddress(ADXL345_ADDRESS, I2C_WRITE);

	// SEND REGISTER ADDRESS
	vI2C1_WriteByte(reg);

	// GENERATE A REPEATED START CONDITION
	vI2C1_Start(1);

	// SENDING SLAVE ADDRESS WITH READ
	vI2C1_SendAddress(ADXL345_ADDRESS, I2C_READ);

	// READ THE DATA
	data = uI2C1_ReadByte_NACK();

	// GENERATE A STOP CONDITION
	vI2C1_Stop();

	// RETURN DATA
	return data;

}

void vADXL345_ReadRegisters(uint8_t startReg, uint8_t *buffer, uint8_t length) {

	// GENERATE A START CONDITION
	vI2C1_Start(0);

	// SENDING SLAVE ADDRESS WITH WRITE
	vI2C1_SendAddress(ADXL345_ADDRESS, I2C_WRITE);

	// SEND START REGISTER ADDRESS
	vI2C1_WriteByte(startReg);

	// GENERATE A REPEATED START CONDITION
	vI2C1_Start(1);

	// SENDING SLAVE ADDRESS WITH READ
	vI2C1_SendAddress(ADXL345_ADDRESS, I2C_READ);

	for (uint8_t i = 0; i < length; i++){

		// CONDITION TO CHECK FOR THE LAST ELEMENT
		if (i == (length - 1)) {

			// READ AND NACK
			buffer[i] = uI2C1_ReadByte_NACK();
		}
		else {

			// READ AND ACK
			buffer[i] = uI2C1_ReadByte_ACK();
		}
	}

	// GENERATE A STOP CONDITION
	vI2C1_Stop();

}

void vADXL345_Init() {

	/*
	 * CONFIGURE OF DATA FORMATE
	 * FULL RESOLUTION
	 * RANGE = ±2g
	 * JUSTIFY RIGHT
	 */
	vADXL345_WriteRegister(ADXL345_DATA_FORMAT, ADXL345_FULL_RES | ADXL345_RANGE_2G);

	// ENABLE MEASUREMENT MODE
	vADXL345_WriteRegister(ADXL345_POWER_CTL, ADXL345_MEASURE);
}

void vADXL345_ReadXYZ(ADXL345_Data_t *data) {

	// BUFFER INITIALIZATION
	uint8_t buffer[6];

	// CHECKING FOR POINTER EMPTY
	if (!data) {
		return;
	}

	// READ DATA FROM THE REGISTER AND STORED IN BUFFER
	vADXL345_ReadRegisters(ADXL345_DATAX0, buffer, 6);

	// COMBINE X-AXIS LSB AND MSB INTO SIGNED 16 BIT VALUE
	data->x = (int16_t)((buffer[1] << 8) | (buffer[0]));

	// COMBINE Y-AXIS LSB AND MSB INTO SIGNED 16 BIT VALUE
	data->y = (int16_t)((buffer[3] << 8) | (buffer[2]));

	// COMBINE Z-AXIS LSB AND MSB INTO SIGNED 16 BIT VALUE
	data->z = (int16_t)((buffer[5] << 8) | (buffer[4]));

}
