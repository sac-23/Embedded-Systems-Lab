#include "gpio.h"
#include "stm32f103x6.h"

void vGPIO_Init(void) {

	// ENABLE CLOCK FOR GPIO C
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

	/*
	 * PIN CONFIGURATION
	 * PC13
	 * MODE[1:0] = 11: Output mode, max speed 50 MHz.
	 * CNF[1:0] = 00: General purpose output push-pull
	 */
	//
	GPIOC->CRH = ((GPIOC->CRH & ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13)) | (GPIO_CRH_MODE13));
	//GPIOC->CRH = ((GPIOC->CRH & ~ (0XF << 20)) | (0X3 << 20));

}

void vGPIO_SetPin(void) {

	// LED IS ACTIVE LOW SO REST TO TURN ON THE LED
	GPIOC->ODR &= ~GPIO_ODR_ODR13;

}


void vGPIO_ResetPin(void) {

	// LED IS ACTIVE LOW SO SET TO TURN OFF THE LED
	GPIOC->ODR |= GPIO_ODR_ODR13;

}

void vGPIO_TogglePin(void) {

	// TOGGLE USING XOR OPERATOR
	GPIOC->ODR ^= GPIO_ODR_ODR13;

}

