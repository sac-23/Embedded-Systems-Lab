// ADC to Read a Value
#include <stdint.h>

// RCC
volatile uint32_t* pAPB2ENR = (volatile uint32_t*) 0x40021018; // Address of APB2 Bus for Enable clock
volatile uint32_t* pAPB2RSTR = (volatile uint32_t*) 0x4002100c; // Address of APB2 bus for Reseting peripheral
volatile uint32_t* pCFGR = (volatile uint32_t*) 0x40021004; // Address of Clock Configure Resister for ADC Prescaler

// GPIO A
volatile uint32_t* pCRL = (volatile uint32_t*) 0x40010800; // Address of GPIO for Configuration

// ADC
volatile uint32_t* pADC1_SR = (volatile uint32_t*) 0x40012400; // Address of SR
volatile uint32_t* pADC1_CR1 = (volatile uint32_t*) 0x40012404; // Address of CR1
volatile uint32_t* pADC1_CR2 = (volatile uint32_t*) 0x40012408; // Address of CR2
volatile uint32_t* pADC1_DR = (volatile uint32_t*) 0x4001244c; // Address of DR
volatile uint32_t* pADC1_SMPR2 = (volatile uint32_t*) 0x40012410; // Address of SMPR2 for Enabling Sampling cycle
volatile uint32_t* pADC1_SQR1 = (volatile uint32_t*) 0x4001242c; // Address of SQR1 for Choosing Length of regular conversion
volatile uint32_t* pADC1_SQR3 = (volatile uint32_t*) 0x40012434; // Address of SQR3 for Enabling Channel 0 of ADC1

volatile uint16_t ADC_value;

void vRCC_Enable ();
void vGPIO_Config ();
void vADC1_Config ();
void vADC1_Power_and_Calibration ();
uint16_t xADC1_Read(void);


void vRCC_Enable (){

	//Clock Enable for ADC1 and GPIO A in APB2 bus
	*pAPB2ENR |= (1 << 2); //Enable Clock for GPIO A (2nd Bit)
	*pAPB2ENR |= (1 << 9); //Enable Clock for ADC1 (9th Bit)

	//Resting the ADC1
	*pAPB2RSTR |= (1 << 9); // Assert reset ADC1
	*pAPB2RSTR &= ~(1 << 9); // De - Assert reset ADC1
}


void vGPIO_Config (){

	*pCRL &= ~(0xF << 0); // Mode = 00 (Input Mode), CNF = 00 (Analog Mode)

}

void vADC1_Config (){

	// ADC1 Prescaler (Pclk / 6) ADC clk = 12 < 14
	// 6 = 15th to 1 and 14th bit to 0
	*pCFGR = ((*pCFGR & ~(0x3 << 14)) | (0x2 << 14));

	// Single Conversion Mode by Reseting CONT
	*pADC1_CR2 &= ~(1 << 1);

	// Disabling External Trigger by EXTRIG
	*pADC1_CR2 &= ~(1 << 20);

	// Right Data Alignment by ALING
	*pADC1_CR2 &= ~(1 << 11);

	// Single channel mode by disabling Scan mode
	*pADC1_CR1 &= ~(1 << 8);

	// Sampling time: channel 0 = 239.5 cycles
	*pADC1_SMPR2 |= (7 << 0);
}

void vADC1_Power_and_Calibration (){

	// ADC1 Powered ON
	*pADC1_CR2 |= (1 << 0);

	// Delay for Stabilization
	for (volatile int i = 0; i < 10000; i++);

	//RESET Calibration
	*pADC1_CR2 |= (1 << 3);
	while (*pADC1_CR2 & (1 << 3)); // Wait until RESET done

	*pADC1_CR2 |= (1 << 2);
	while (*pADC1_CR2 & (1 << 2)); // Wait until Calibration done

}

uint16_t xADC1_Read(){

	// Making One Conversion in regular Sequence
	*pADC1_SQR1 &= ~(0xF << 20); // L[23:20] = 0000 -> 1 conversion

	// Channel 0 Selection (A0)
	*pADC1_SQR3 &= ~(0x1F << 0); // Clear SQ1[4:0]
	*pADC1_SQR3 |= (0 << 0); // SQ1[4:0] -> 0 for channel 0

	// START conversion (STM32F1 way)
	*pADC1_CR2 |= (1 << 0);   // ADON again

	// Wait for EOC
	while (!(*pADC1_SR & (1 << 1)));

	// Return of Result from DR
	return (uint16_t)(*pADC1_DR & 0x0FFF);

}

int main(void)
{

	vRCC_Enable();
	vGPIO_Config();
	vADC1_Config();
	vADC1_Power_and_Calibration();

	while (1){
		ADC_value = xADC1_Read();
	}
}
