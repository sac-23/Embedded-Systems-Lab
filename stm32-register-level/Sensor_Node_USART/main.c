// Read from ADC, send data and receive ACK via USART
#include <stdint.h>

// RCC
volatile uint32_t *pAPB1ENR = (volatile uint32_t*) 0x4002101c;
volatile uint32_t *pAPB2ENR = (volatile uint32_t*) 0x40021018;
volatile uint32_t *pCFGR = (volatile uint32_t*) 0x40021004;

// GPIO
volatile uint32_t *pCRL = (volatile uint32_t*) 0x40010800;

// USART
volatile uint32_t *pUSART_SR = (volatile uint32_t*) 0x40004400;
volatile uint32_t *pUSART_CR1 = (volatile uint32_t*) 0x4000440c;
volatile uint32_t *pUSART_DR = (volatile uint32_t*) 0x40004404;
volatile uint32_t *pBRR = (volatile uint32_t*) 0x40004408;

// ADC
volatile uint32_t *pADC_SR = (volatile uint32_t*) 0x40012400;
volatile uint32_t *pADC_DR = (volatile uint32_t*) 0x4001244c;
volatile uint32_t *pADC_CR1 = (volatile uint32_t*) 0x40012404;
volatile uint32_t *pADC_CR2 = (volatile uint32_t*) 0x40012408;
volatile uint32_t *pADC_SMPR2 = (volatile uint32_t*) 0x40012410;
volatile uint32_t *pADC_SQR1 = (volatile uint32_t*) 0x4001242c;
volatile uint32_t *pADC_SQR3 = (volatile uint32_t*) 0x40012434;

void vClock_Enable ();
void vGPIOA_Config ();
void vUSART_Config ();
void vADC_Config ();
void vPower_and_calibration ();
uint16_t xADC_Read (void);
void vUSART_Send (uint16_t value);
void vSend_String (char *buff);
void vSend_Byte (uint8_t byte);
void delay (volatile int delay);


uint16_t ADC_Value;
char ACK;


void vClock_Enable () {

	// USART
	*pAPB1ENR |= (1 << 17);

	// GPIOA and ADC1
	*pAPB2ENR |= ((1 << 9) | (1 << 2));
}

void vGPIOA_Config () {

	// PA3 (USART2_RX): [CNF3 MODE3] = 0100
	// PA2 (USART2_TX): [CNF2 MODE2] = 1010
	// PA0 (ADC IN0)  : [CNF0 MODE0] = 0000
	*pCRL = ((*pCRL & ~((0xF << 12) | (0xF << 8) | (0xF << 0))) | ((4 << 12) | (10 << 8)));
}

void vUSART_Config () {

	// USART Disable
	*pUSART_CR1 &= ~(1 << 13);

	// M = 0 (8 bit length)
	// PCE = 0 (Parity Control Disable)
	// TX Enable
	// RX Enable
	*pUSART_CR1 = ((*pUSART_CR1 & ~((1 << 12) | (1 << 10) | (1 << 3) | (1 << 2))) | ((1 << 3) | (1 << 2)));

	// Baud rate = 9600
	*pBRR = 0x341;

	// USART Enable
	*pUSART_CR1 |= (1 << 13);
}

void vADC_Config () {
	// ADC1 Prescaler (Pclk / 6) ADC clk = 12 < 14
	// 6 = 15th to 1 and 14th bit to 0
	*pCFGR = ((*pCFGR & ~(0x3 << 14)) | (0x2 << 14));

	// Enabling Single Conversion using CONT
	*pADC_CR2 &= ~(1 << 1);

	// Disabling External trigger and selecting SWSTART
	*pADC_CR2 = (*pADC_CR2 & ~(0xF << 17)) | (0x7 << 17);

	// Enabling Right ALIGN
	*pADC_CR2 &= ~(1 << 11);

	// Scan mode = 0, using of single channel
	*pADC_CR1 &= ~(1 << 8);

	// Sampling Time of Channel 0 = 239.5 cycle
	*pADC_SMPR2 = (*pADC_SMPR2 & ~(0x7 << 0)) | (0x7 << 0);
}

void vPower_and_calibration (){

	// ADC is on
	*pADC_CR2 |= (1 << 0);

	// Delay for Stabilization
	for (volatile int i = 0; i < 10000; i++);

	*pADC_CR2 |= (1 << 3); // RESET of Calibration register
	while (*pADC_CR2 & (1 << 3)); // wait for RESET of Calibration register

	*pADC_CR2 |= (1 << 2); // Start of the Calibration
	while (*pADC_CR2 & (1 << 2)); // wait for Calibration completion
}

uint16_t xADC_Read (){

	// One Conversion in Regular Sequence
	*pADC_SQR1 &= ~(0xF << 20); // L[23:20] = 0000 for one conversion

	// Channel 0 Selection (A0)
	*pADC_SQR3 &= ~(0x1F << 0); // Clear SQ1[4:0]
	*pADC_SQR3 |= (0 << 0); // SQ1[4:0] -> 0 for channel 0

	// START conversion (STM32F1 way)
	*pADC_CR2 |= (1 << 0);   // ADON again

	// Wait for EOC
	while (!(*pADC_SR & (1 << 1)));

	// Return of Result from DR
	return (uint16_t)(*pADC_DR & 0x0FFF);
}

void vUSART_Send (uint16_t value) {

	char buffer[6];
	int i = 0;

	if (value == 0){
		buffer[i++] = '0';
	}
	else{
		char temp[6];
		int j = 0;

		while (value > 0){
			temp[j++] = value % 10 + '0';
			value /= 10;
		}

		while (j > 0){
			buffer[i++] = temp[--j];
		}
	}

	buffer[i++] = '\n';
	buffer[i] = '\0';
	vSend_String(buffer);
}

void vSend_String (char *buff){

	while (*buff){
		vSend_Byte(*buff);
		buff++;
	}
}

void vSend_Byte (uint8_t byte){

	// Wait till TX register is empty (TXE)
	while (!(*pUSART_SR & (1 << 7)));

	*pUSART_DR = byte;
}

void delay (volatile int delay){

	while (--delay);
}

char xUSART_Receive (){

	// Wait till RXNE is not Empty (data in RX register)
	while (!(*pUSART_SR & (1 << 5)));

	return (char)*pUSART_DR;
}

int main(void)
{

	vClock_Enable ();
	vGPIOA_Config ();
	vUSART_Config ();
	vADC_Config ();
	vPower_and_calibration ();

	while (1){
		ADC_Value = xADC_Read();
		vUSART_Send (ADC_Value);
		delay (300000);
		ACK = xUSART_Receive ();

		if (ACK == 'y'){
			continue;
		}
		else {
			break;
		}

	}


}
