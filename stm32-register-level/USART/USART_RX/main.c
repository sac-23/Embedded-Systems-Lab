// USART RX
#include <stdint.h>

// RCC
volatile uint32_t* pAPB1ENR = (volatile uint32_t*) 0x4002101c;
volatile uint32_t* pAPB2ENR = (volatile uint32_t*) 0x40021018;

// GPIO A
volatile uint32_t* pCRL = (volatile uint32_t*) 0x40010800;

// USART
volatile uint32_t* pCR1 = (volatile uint32_t*) 0x4000440c;
volatile uint32_t* pBRR = (volatile uint32_t*) 0x40004408;
volatile uint32_t* pSR = (volatile uint32_t*) 0x40004400;
volatile uint32_t* pDR = (volatile uint32_t*) 0x40004404;

void vClock_ENF ();
void vGPIOA_Config ();
void vUSART_Config ();
uint8_t xUSART_ReadByte (void);

uint8_t USART_Value;

void vClock_ENF() {

	// USART
	*pAPB1ENR |= (1 << 17);

	// GPIO A
	*pAPB2ENR |= (1 << 2);
}

void vGPIOA_Config () {

	// RX - [CNF3 MODE3] = [0100]
	*pCRL = ((*pCRL & ~(0xf << 12)) | (0x4 << 12));
}

void vUSART_Config () {

	// USART Disable
	*pCR1 &= ~(1 << 13);

	// M = 0 (8 bit length), PCE = 0 (parity Disable) and RX = 1
	*pCR1 = ((*pCR1 & ~((1 << 12) | (1 << 10) | (1 << 2))) | (1 << 2));

	// Baud Rate = 9600 Mantissa = 52 = 0x34 and Fraction = 1 = 0x1
	*pBRR = 0x341;

	// USART Enable
	*pCR1 |= (1 << 13);
}

uint8_t xUSART_ReadByte (void){

	// wait till RXNE become 1 (data is ready)
	while (!(*pSR & (1 << 5)));

	// Return Byte
	return (uint8_t)(*pDR & (0xFF));

}

int main(void)
{
    vClock_ENF ();
    vGPIOA_Config ();
    vUSART_Config ();

	while (1){
		USART_Value = xUSART_ReadByte();
	}
}
