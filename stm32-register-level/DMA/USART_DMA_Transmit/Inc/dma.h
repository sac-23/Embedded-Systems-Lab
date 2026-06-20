#include <stdint.h>

#ifndef DMA_C_
#define DMA_C_

void vDMA_Init(void);

void vDMA_USART_Transmit (uint8_t *buffer, uint16_t length);

#endif /* DMA_C_ */
