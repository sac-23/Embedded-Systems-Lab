#include "gpio.h"
#include "stm32f103x6.h"

void vGPIOA_Init(void) {

	// CLOCK ENABLE FOR GPIOA VIA APB2(ADVANCED PERIPHERIAL BUSS 2)
	RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN);

	/*
	 * PIN CONFIGURATION
	 * PA9
	 * MODE[1:0] = 11: Output mode, max speed 50 MHz.
	 * CNF[1:0] = 10: Alternate function output Push-pull
	 */

	GPIOA->CRH = (GPIOA->CRH & ~(GPIO_CRH_CNF9_Msk |GPIO_CRH_MODE9_Msk)) | (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_1 | GPIO_CRH_MODE9_0);
	//GPIOA->CRH = (GPIOA->CRH & ~(0XF << 4)) | ((0X3 << 4) | (1 << 7));

}
