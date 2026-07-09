#include "i2c.h"

void vI2C1_Init(void) {

	// CLOCK ENABLE FOR GPIOB
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	// CLOCK ENABLE FOR I2C1
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

	/*
	 * PIN CONFIGURATION FOR I2C1
	 * PB6 - SCL
	 * MODE[1:0] 11: OUTPUT MODE, MAX SPEED 50 MHz.
	 * CNF[1:0] 11: 11: Alternate function output Open-drain
	 */
	GPIOB->CRL = (((GPIOB->CRL) & ~(GPIO_CRL_CNF6 | GPIO_CRL_MODE6)) | ((GPIO_CRL_CNF6 | GPIO_CRL_MODE6)));
	//GPIOB->CRL = (((GPIOB->CRL) & ~(0xF << 24)) | ((0xF << 24)));

	/*
	 * PIN CONFIGURATION FOR I2C1
	 * PB7 - SDA
	 * MODE[1:0] 11: OUTPUT MODE, MAX SPEED 50 MHz.
	 * CNF[1:0] 11: 11: Alternate function output Open-drain
	 */
	GPIOB->CRL = (((GPIOB->CRL) & ~(GPIO_CRL_CNF7 | GPIO_CRL_MODE7)) | ((GPIO_CRL_CNF7 | GPIO_CRL_MODE7)));
	//GPIOB->CRL = (((GPIOB->CRL) & ~(0xF << 28)) | ((0xF << 28)));

	// RESET THE I2C PERIPHERIAL
	I2C1->CR1 |= I2C_CR1_SWRST; // UNDER RESET
	I2C1->CR1 &= ~I2C_CR1_SWRST; // NOT UNDER RESET

	// FREQ[5:0] = PCLK1 (APB1 CLOCK)
	I2C1->CR2 = 8;

	/*
	 * CLOCK CONTROL REGISTER:
	 *CCR = PCLK1/(2 *SCL)
	 *PCLK1 = 8 MHZ, SCL=100 KHZ (STANDARD MODE)
	 *CCR = 8,000,000/(2 * 100,000)
	 *CCR = 40
	 */
	I2C1->CCR = 40;

	/*
	 * TRISE
	 * TRISE = ((Trise)/(TPLCK1) + 1)
	 * Trise = 1000 ns: STANDARD MODE
	 * TPCLK1 = 1/PCLK1
	 *     PCLK1 = 8 MHZ
	 *     TPCLK1 = 1/8,000,000 = 125 ns
	 * TRISE = ((1000/125) + 1) = 9
	 */
	I2C1->TRISE = 9;

	//ENABLE I2C1 PERIPHERAL
	I2C1->CR1 |= I2C_CR1_PE;
}

void vI2C1_Start(uint8_t repeated) {

	if (!repeated) {
		// WAIT TILL THE BUS BECOME FREE
		while (I2C1->SR2 & I2C_SR2_BUSY);
	}

	// GENERATE A START CONDITION
	I2C1->CR1 |= I2C_CR1_START;

	// WAIT TILL START IS GENERATED
	while (!(I2C1->SR1 & I2C_SR1_SB));

}

void vI2C1_Stop(void) {

	// GENERATE A STOP CONDITION
	I2C1->CR1 |= I2C_CR1_STOP;

}

void vI2C1_SendAddress(uint8_t address, uint8_t direction) {

	volatile uint32_t dummy;

	// CREATE A 8 BIT ADDRESS
	address <<= 1;

	// ADD 1 TO 8 BIT IF THE DIRECTION IS READ
	if (direction == I2C_READ) {
		address |= 0x01;
	}

	// SEND THE ADDRESS
	I2C1->DR = address;

	// WAIT TILL SLACE ACK
	while (!(I2C1->SR1 & I2C_SR1_ADDR));

	// CLEARING THE ADDR BY HANDSHAKE METHOD
	dummy = I2C1->SR1; // READING SR1
	dummy = I2C1->SR2; // READING SR2

	(void)dummy;
}

void vI2C1_WriteByte(uint8_t data) {

	// WAIT TILL THE DR BECOME EMPTY
	while (!(I2C1->SR1 & I2C_SR1_TXE));

	// SEND DATA
	I2C1->DR = data;

	// WAIT TILL BYTE TRANSFER FINISHED
	while (!(I2C1->SR1 & I2C_SR1_BTF));

}

uint8_t uI2C1_ReadByte_ACK(void) {

	// ENABLE ACK
	I2C1->CR1 |= I2C_CR1_ACK;

	// 	WAIT TILL THE RECEIVER BUFFER IS NOT EMPTY
	while (!(I2C1->SR1 & I2C_SR1_RXNE));

	// READ DATA AND RETURN
	return (uint8_t)I2C1->DR;

}

uint8_t uI2C1_ReadByte_NACK(void) {

	// ENABLE NACK (BY RESET ACK)
	I2C1->CR1 &= ~I2C_CR1_ACK;

	// 	WAIT TILL THE RECEIVER BUFFER IS NOT EMPTY
	while (!(I2C1->SR1 & I2C_SR1_RXNE));

	// READ DATA AND RETURN
	return (uint8_t)I2C1->DR;
}
