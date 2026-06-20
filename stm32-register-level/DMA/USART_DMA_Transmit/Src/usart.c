#include "usart.h"
#include "stm32f103x6.h"

void vUSART_Init(void) {

	// CLOCK ENABLE FOR USART 1 IN ABP2 BUS
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	// TRANSMITTER ENABLE
	USART1->CR1 |= USART_CR1_TE;

	//  PARITY CONTROL DISABLED AND WORD LENGTH = 1 Start bit, 8 Data bits, n Stop bit
	USART1->CR1 &= ~(USART_CR1_PCE | USART_CR1_M);

	// BAUD RATE 9600
	USART1->BRR =0x341;

	// USART ENABLE
	USART1->CR1 |= USART_CR1_UE;

	// DMA ENABLE TRANSMITTER
	USART1->CR3 |= USART_CR3_DMAT;
}

void vUSART_SendChar(uint8_t data) {

	while (!(USART1->SR & USART_SR_TXE));

	USART1->DR = (uint8_t)data;
}

void vUSART_SendString(uint8_t *str) {

	while (*str != '\0') {
		vUSART_SendChar(*str++);
	}

	while (!(USART1->SR & USART_SR_TC));
}
