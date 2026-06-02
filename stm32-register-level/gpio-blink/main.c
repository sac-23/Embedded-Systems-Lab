#include <stdint.h>

// RCC
volatile uint32_t* pAPB2ENR = (volatile uint32_t*) 0x40021018;

// GPIO
volatile uint32_t* pCRH = (volatile uint32_t*) 0x40011004;

// ODR
volatile uint32_t* pODR = (volatile uint32_t*) 0x4001100c;


// DELAY FUNCTION
void Delay(volatile uint32_t count){
	while (count--);
}

// MAIN FUNCTION
int main(void)
{
	// ENABLEING CLOCK FOR GPIOC
	*pAPB2ENR |= (1 << 4);

	// CONFIGURATION OF GPIOC
	*pCRH &= ~(0xF << 20); // RESET
	*pCRH |= (1 << 20); // SET (MODE13[1:0] = 01: Output mode, max speed 10 MHz.
	*pCRH &= ~(1 << 21);
	*pCRH &= ~((1 << 23) | (1 << 22)); // CNF13[1:0] = 00: General purpose output push-pull

	// LOOP
	while (1){

		// LED ON
		*pODR &= ~(1 << 13);
		Delay(500000);

		// LED OFF
		*pODR |= (1 << 13);
		Delay(500000);
	}
}
