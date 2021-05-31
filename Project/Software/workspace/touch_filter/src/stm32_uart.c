/*
 * stm32_uart.c
 *
 *  Created on: 28 mars 2021
 *      Author: Myren
 */
#include "stm32_uart.h"
#include "rcc.h"

uint32_t UART_config(uart_reg_t* uart_dev, uart_config_t* uart_conf)
{
   uint32_t ret = 0;
   uint32_t hclk;
   uint32_t uart_div;

   /* Set OVER8 bit to over sample by 8 */
   uart_dev->CR1 |= 1 << 15;

   /* UART 2, 3, 4 and 5 is part of APB1 and uses
    * UART 1 and 6 is part of APB2 */

   hclk = RCC_get_APB1_freq();
   uart_div = (2000000 * hclk) / uart_conf->baud_rate;
   uart_dev->BRR = uart_div;

   if (DATA_BITS_8 == uart_conf->data_bits)
   {
      uart_dev->CR1 &= ~(1 << 12);
   }
   else
   {
      uart_dev->CR1 |= 1 << 12;
   }

   uart_dev->CR2 &= ~(0x3 << 12);
   if (STOP_BITS_2 == uart_conf->stop_bits)
   {
      uart_dev->CR2 |= 1 << 13;
   }

   if (enable == uart_conf->RX_enable)
   {
      uart_dev->CR1 |= 1 << 2;
   }

   if (enable == uart_conf->TX_enable)
   {
      uart_dev->CR1 |= 1 << 3;
   }



   /* Enable UART */
   uart_dev->CR1 |= 1 << 13;

   return(ret);
}

void UART_tx(uart_reg_t* uart_dev, uint8_t* data, uint32_t size)
{
   uint32_t i;
   for (i=0; i<size; i++)
   {
      uart_dev->DR = data[i];
      while(!(uart_dev->SR & (1 << 7)));
   }

}