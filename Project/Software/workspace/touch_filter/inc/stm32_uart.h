/*
 * stm32_uart.h
 *
 *  Created on: 28 mars 2021
 *      Author: Myren
 */

#ifndef STM32_UART_H_
#define STM32_UART_H_

#include "stm32f4xx.h"
#include "stm32f405xx.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdlib.h>


void UART_Init(USART_TypeDef* huart,
               uint32_t baud,
               uint8_t* RX_buff,
               uint8_t RX_size);
void UART_Transmit(USART_TypeDef* huart, uint8_t* data, uint8_t size);
void UART_Transmit_DMA(USART_TypeDef* huart, uint8_t* data_buffer, uint32_t size);

void UART_register_rx_complete_func(void (*func)(void));

void UART_register_tx_complete_func(void (*func)(void));

void DMA1_Stream2_IRQHandler(void);
void DMA1_Stream4_IRQHandler(void);
void UART4_IRQHandler(void);

//void initUART(uint32_t BAUD);
//void UART_puts(uint8_t* data, uint16_t size);


#if 0
#include <stdint.h>

#include "common.h"

#define UART_1_ADDR 0x40011000
#define UART_2_ADDR 0x40004400
#define UART_3_ADDR 0x40004800
#define UART_4_ADDR 0x40004C00
#define UART_5_ADDR 0x40005000
#define UART_6_ADDR 0x40011400

typedef struct
{
   volatile uint32_t SR;
   volatile uint32_t DR;
   volatile uint32_t BRR;
   volatile uint32_t CR1;
   volatile uint32_t CR2;
   volatile uint32_t CR3;
   volatile uint32_t GTPR;
}uart_reg_t;

#define UART1 ((uart_reg_t*)UART_1_ADDR)
#define UART2 ((uart_reg_t*)UART_2_ADDR)
#define UART3 ((uart_reg_t*)UART_3_ADDR)
#define UART4 ((uart_reg_t*)UART_4_ADDR)
#define UART5 ((uart_reg_t*)UART_5_ADDR)
#define UART6 ((uart_reg_t*)UART_6_ADDR)

typedef enum
{
   STOP_BITS_1 = 0,
   STOP_BITS_2,
}uart_stop_bit_e;

typedef enum
{
   DATA_BITS_8 = 0,
   DATA_BITS_9
}uart_data_bits_e;

typedef enum
{
   PARITY_EVEN = 0,
   PARITY_ODD
}uart_parity_e;

typedef enum
{
   BAUD_9600 = 9600,
   BAUD_19200 = 19200,
   BAUD_38400 = 38400,
   BAUD_57600 = 57600,
   BAUD_115200 = 115200
}uart_baud_rates_e;

typedef struct
{
   uart_baud_rates_e baud_rate;
   uart_stop_bit_e stop_bits;
   uart_data_bits_e data_bits;
   enable_disable_e parity_enable;
   uart_parity_e parity;
   enable_disable_e RX_enable;
   enable_disable_e TX_enable;
}uart_config_t;

uint32_t UART_config(uart_reg_t* uart_dev, uart_config_t* uart_conf);
void UART_tx(uart_reg_t* uart_dev, uint8_t* data, uint32_t size);
#endif



#endif /* STM32_UART_H_ */
