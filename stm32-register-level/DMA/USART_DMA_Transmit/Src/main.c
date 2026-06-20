#include <stdint.h>
#include "stm32f103x6.h"
#include "gpio.h"
#include "usart.h"
#include "dma.h"

uint8_t msg[] = "Hello DMA\r\n";

int main(void)
{
	vGPIOA_Init();
    vUSART_Init();
    vDMA_Init();

    while(1)
    {
    	vDMA_USART_Transmit(msg, sizeof(msg)-1);

    	while(!(DMA1->ISR & DMA_ISR_TCIF4));

        for(volatile uint32_t i=0; i<1000000; i++);
    }
}
