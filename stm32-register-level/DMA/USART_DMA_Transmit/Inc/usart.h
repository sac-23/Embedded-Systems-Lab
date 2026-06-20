/*
 * usart.h
 *
 *  Created on: Jun 16, 2026
 *      Author: Sachin Narendra
 */
#include <stdint.h>

#ifndef USART_H_
#define USART_H_

void vUSART_Init(void);

void vUSART_SendChar(uint8_t Data);

void vUSART_SendString(uint8_t *Str);

#endif /* USART_H_ */
