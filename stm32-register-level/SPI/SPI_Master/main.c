#include <stdint.h>
#include "stm32f103x6.h"

// CS Control
#define CS_High() (GPIOA->BSRR =GPIO_BSRR_BS15)
#define CS_Low()  (GPIOA->BSRR =GPIO_BSRR_BR15)

// ADXL345 Registers
#define DEVID_R            0x00
#define POWER_CTRL_R       0x2D
#define DATA_FORMAT_R      0x31
#define DATA_START_ADDR    0x32

// ADXL345 Configuration
#define SET_MEASURE_B      0x08
#define FOUR_G             0x01

// X, Y, Z Data
int16_t x, y, z;

// Device ID
uint8_t id;

// Function Prototype
void vClock_enable();
void vGPIO_Config();
void vSPI_Config();
uint8_t xSPI_TxRx(uint8_t data);
void vSPI_Write(uint8_t reg, uint8_t data);
uint8_t xSPI_Read(uint8_t reg);
void ADXL_Read_XYZ ();
void delay(int count);

// Delay Function
void delay(int count){
	while (--count);
}

void vClock_enable() {

	// Enable Clock for AFIO, GPIOA, GPIOB and SPI1
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_SPI1EN;
}

void vGPIO_Config(){

	// Disable JTAG and Enable SWD
	AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG) | AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

	// SPI1 Remap
	AFIO->MAPR |= AFIO_MAPR_SPI1_REMAP;

	// PA15 as GPIO Output (CS)
	GPIOA->CRH = (GPIOA->CRH & ~(GPIO_CRH_CNF15_Msk | GPIO_CRH_MODE15_Msk)) | GPIO_CRH_MODE15;

	// PB3 as SPI1_SCK
	GPIOB->CRL = (GPIOB->CRL & ~(GPIO_CRL_CNF3_Msk | GPIO_CRL_MODE3_Msk))| (GPIO_CRL_CNF3_1 | GPIO_CRL_MODE3);

	// PB4 as SPI1_MISO
	GPIOB->CRL = (GPIOB->CRL & ~(GPIO_CRL_CNF4_Msk | GPIO_CRL_MODE4_Msk)) | GPIO_CRL_CNF4_0;

	// PB5 as SPI1_MOSI
	GPIOB->CRL = (GPIOB->CRL & ~(GPIO_CRL_CNF5_Msk | GPIO_CRL_MODE5_Msk)) | (GPIO_CRL_CNF5_1 | GPIO_CRL_MODE5);

}

void vSPI_Config() {

	// SPI Mode 3 (CPOL = 1, CPHA = 1)
	SPI1->CR1 = SPI1->CR1 & ~(SPI_CR1_CPHA_Msk | SPI_CR1_CPOL_Msk) | (SPI_CR1_CPHA | SPI_CR1_CPOL);

	// Master Mode
	SPI1->CR1 |= SPI_CR1_MSTR;

	// Baud Rate = Fpclk / 8
	SPI1->CR1 = (SPI1->CR1 & ~(SPI_CR1_BR_Msk)) | SPI_CR1_BR_1;

	// MSB First
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;

	// Internal Slave Select
	SPI1->CR1 |= SPI_CR1_SSI;

	// Software Slave Management
	SPI1->CR1 |= SPI_CR1_SSM;

	// 8-bit Data Frame
	SPI1->CR1 &= ~SPI_CR1_DFF;

	// SPI Enable
	SPI1->CR1 |= SPI_CR1_SPE;
}

uint8_t xSPI_TxRx(uint8_t data) {

	// Wait till TX Buffer Empty
	while (!(SPI1->SR & SPI_SR_TXE));

	// Send Data
	SPI1->DR = data;

	// Wait till RX Buffer Not Empty
	while (!(SPI1->SR & SPI_SR_RXNE));

	// Wait till SPI Not Busy
	while (SPI1->SR & SPI_SR_BSY);

	// Return Received Data
	return (uint8_t)SPI1->DR;
}

void vSPI_Write(uint8_t reg, uint8_t data){

	// CS LOW
	CS_Low();

	// Send Register Address
	xSPI_TxRx(reg);

	// Send Data
	xSPI_TxRx(data);

	// CS HIGH
	CS_High();
}

uint8_t xSPI_Read(uint8_t reg) {

	uint8_t value;

	// CS LOW
	CS_Low();

	// Send Read Command
	xSPI_TxRx(0x80 | reg);

	// Read Data
	value = xSPI_TxRx(0x00);

	// CS HIGH
	CS_High();

	return value;
}

void ADXL_Read_XYZ () {

	uint8_t buffer[6];

	// CS LOW
	CS_Low();

	// Multi Byte Read from DATAX0
	xSPI_TxRx(0xC0 | DATA_START_ADDR);

	// Read 6 Bytes
	for (int i = 0; i < 6; i++){
		buffer[i] = xSPI_TxRx(0x00);
	}

	// CS HIGH
	CS_High();

	// Combine X Axis Data
	x = (buffer[1] << 8) | buffer[0];

	// Combine Y Axis Data
	y = (buffer[3] << 8) | buffer[2];

	// Combine Z Axis Data
	z = (buffer[5] << 8) | buffer[4];
}

int main(void)
{
	// Initialization
	vClock_enable();
	vGPIO_Config();
	vSPI_Config();

	// Read Device ID
	id = xSPI_Read(DEVID_R);

	// Enable Measurement Mode
	vSPI_Write(POWER_CTRL_R, SET_MEASURE_B);

	// Set Range = ±4g
	vSPI_Write(DATA_FORMAT_R, FOUR_G);

	while (1){

		// Read X, Y and Z Data
		ADXL_Read_XYZ ();

		delay(30000);
	}
}
