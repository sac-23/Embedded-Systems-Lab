#include "spi.h"
#include "gpio.h"
#include "stm32f103x6.h"

volatile uint8_t g_ucRxData;

void vSPI_Init(void) {

	// CLOCK ENABLE FOR GPIOA AND SPI1
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_SPI1EN;

	/*
	 * PIN CONFIGURATION FOR SPI1
	 * PA4 - NSS
	 * MODE[1:0] 00: INPUT MODE
	 * CNF[1:0] 01: FLOATING INPUT
	 */
	GPIOA->CRL = (GPIOA->CRL & ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4)) | (GPIO_CRL_CNF4_0);
	//GPIOA->CRL = (GPIOA->CRL & ~(0XF << 16)) | (1 << 18);


    /*
	 * PIN CONFIGURATION FOR SPI1
	 * PA5 - CLK
	 * MODE[1:0] 00: INPUT MODE
	 * CNF[1:0] 01 : FLOATING INPUT
	 */
	GPIOA->CRL = (GPIOA->CRL & ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5)) | (GPIO_CRL_CNF5_0);
	//GPIOA->CRL = (GPIOA->CRL & ~(0XF << 20)) | (1 << 22);

    /*
	 * PIN CONFIGURATION FOR SPI1
	 * PA6 - MISO
	 * MODE[1:0] 11: OUTPUT MODE, MAX SPEED 50 MHz.
	 * CNF[1:0] 10: ALTERNATE FUNCTION OUTPUT PUSH-PULL
	*/
	GPIOA->CRL = (GPIOA->CRL & ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6)) | (GPIO_CRL_MODE6 | GPIO_CRL_CNF6_1);
	//GPIOA->CRL = (GPIOA->CRL & ~(0XF << 24)) | ((1 << 27) | (3 <<24);

    /*
	 * PIN CONFIGURATION FOR SPI1
	 * PA7 - MOSI
	 * MODE[1:0] 00: INPUT MODE
	 * CNF[1:0] 01: FLOATING INPUT
	 */
	GPIOA->CRL = (GPIOA->CRL & ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7)) | (GPIO_CRL_CNF7_0);
	//GPIOA->CRL = (GPIOA->CRL & ~(0XF << 28)) | (1 << 30);

	// SPI1 CONFIGURATION
	SPI1->CR1 = 0;

	/*
	 * SPI1 MODE 0
	 * CPOL = 0 THE IDEAL STATE IS LOW
	 * CPHA = 0 THE DATA SAMPLEING AT RAISING EDGE
	 */
	SPI1->CR1 &= ~SPI_CR1_CPHA;
	SPI1->CR1 &= ~SPI_CR1_CPOL;

	// SLAVE SELECTION
	SPI1->CR1 &= ~SPI_CR1_MSTR;

	// MSB IS TRANSMITTED FIRST
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;

	// HARDWARE SLAVE MANAGEMENT
	SPI1->CR1 &= ~SPI_CR1_SSM;

	// 8-BIT DATA FRAME FORMATE
	SPI1->CR1 &= ~SPI_CR1_DFF;

	//RXNEIE (SPI RXNE INTERRRUPT ENABLE)
	SPI1->CR2 |= SPI_CR2_RXNEIE;

	// NVIC SPI INTERRUPT ENABLE
	NVIC->ISER[1] |= (1 << 3);

	// SPI1 ENABLE
	SPI1->CR1 |= SPI_CR1_SPE;

}


uint8_t ucSPI_Receive(void) {

	// WATING TILL THE RECEIVER BUFFER IS NOT EMPTY
	while (!(SPI1->SR & SPI_SR_RXNE));

	// RETURNING THE DATA
	return (uint8_t)SPI1->DR;
}

void SPI1_IRQHandler(void)
{
	if(SPI1->SR & SPI_SR_RXNE)
	    {
	        g_ucRxData = (uint8_t)SPI1->DR;

	        if (g_ucRxData == 'A'){
	        vGPIO_TogglePin();
	        }
	    }
}
