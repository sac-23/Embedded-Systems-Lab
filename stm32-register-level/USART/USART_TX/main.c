// USART TX
#include <stdint.h>

// RCC
volatile uint32_t* pAPB1ENR = (volatile uint32_t*) 0x4002101c;
volatile uint32_t* pAPB2ENR = (volatile uint32_t*) 0x40021018;

// GPIOA
volatile uint32_t* pGPIOA_CRL = (volatile uint32_t*) 0x40010800;

// USART
volatile uint32_t* pCR1 = (volatile uint32_t*) 0x4000440c;
volatile uint32_t* pBRR = (volatile uint32_t*) 0x40004408;
volatile uint32_t* pSR = (volatile uint32_t*) 0x40004400;
volatile uint32_t* pDR = (volatile uint32_t*)0x40004404;

void vClock_ENF ();
void vGPIOA_Config ();
void vUSART_Config ();
void vUSART_SendByte(uint8_t data);
void vUSART_SendString(const char *str);

void vClock_ENF (){

	// GPIO A
	*pAPB2ENR |= (1 << 2);

	// USART 2
	*pAPB1ENR |= (1 << 17);
}

void vGPIOA_Config (){

	// PA2 as TX [CNF2 MODE2] = 1010 and PA3 as RX [CNF3 MODE3] = 0100
	*pGPIOA_CRL = ((*pGPIOA_CRL & ~(0xFF00)) | (0x4A << 8));

}

void vUSART_Config (){

	// USART Disable
	*pCR1 &= ~(1 << 13);

	// M = 0 (8 bit length), PCE = 0 (no parity) and TX = 1
	*pCR1 = ((*pCR1 & ~((1 << 12) | (1 << 10) | (1 << 3))) | (1 << 3));

	// Baud Rate = 9600 Mantissa = 52 = 0x34 and Fraction = 1 = 0x1
	*pBRR = 0x341;

	// USART Enable
	*pCR1 |= (1 << 13);
}

void vUSART_SendByte (uint8_t data){

	// Wait till TXE is EMPTY
	while (!(*pSR & (1 << 7)));

	*pDR = data;
}

void vUSART_SendString (const char *str){

	while (*str != '\0'){
		vUSART_SendByte (*str);
		str++;
	}
}

int main(void)
{
    vClock_ENF ();
    vGPIOA_Config ();
    vUSART_Config ();
    vUSART_SendString("USART");
	for(;;);
}
