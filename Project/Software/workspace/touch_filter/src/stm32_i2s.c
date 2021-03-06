/*
 * stm32_i2s.c
 *
 *  Created on: 11 sep. 2021
 *      Author: Myren
 */

#include "stm32f405xx.h"
#include "stm32_i2s.h"


void i2s_config(void)
{
   /* I2S2ext, I2S2 (SPI2) */

   /* Enable I2S2 (SPI2) peripheral clock */
   RCC->APB1ENR |= (1 << 14);

   /* Configure GPIO used by I2S */
   /*
   MCLK - PC6
   LRCLK (WS) - PB12
   BCLK (CK) - PB13
   ADCDAT (EXT_SD) - PB14
   DACDAT (SD) - PB15
   */

   /* Enable GPIOB peripheral clock */
   RCC->AHB1ENR |= (1 << 1);
   /* Enable GPIOC peripheral clock */
   RCC->AHB1ENR |= (1 << 2);
   /* Alternate function */
   GPIOB->MODER |= (2 << 30) | (2 << 28) | (2 << 26) | (2 << 24);
   GPIOC->MODER |= (2 << 12);
   /* I2S2ext is on AF6, I2S2 is on AF5 */
   GPIOB->AFR[1] |= (5 << 28) | (6 << 24) | (5 << 20) | (5 << 16);
   GPIOC->AFR[0] |= (5 << 24);

   /* Set ODD bit I2SDIV value */
   SPI2->I2SPR |= (1 << 8) | 3u;

   /* Select clock polarity */
   SPI2->I2SCFGR &= ~(1 << 3);

   /* Enable master output clock to audio CODEC */
   SPI2->I2SPR |= (1 << 9);

   /* Select mode: I2S */
   SPI2->I2SCFGR |= (1 << 11);

   /* Chose I2S standard */
   SPI2->I2SCFGR &= ~(3u << 4);

   /* Select data length, 16-bit */
   SPI2->I2SCFGR &= ~(3u << 1);

   /* Select nr of bits per channel, 16-bit */
   SPI2->I2SCFGR &= ~(0x1);

   /* Select I2S master transmit mode */
   SPI2->I2SCFGR |= (2u << 8);

   /***** Enable I2S2ext in slave receiver mode to achieve full duplex com *****/
   /* Select mode: I2S */
   I2S2ext->I2SCFGR &= ~(3u << 4);
   /* Chose I2S standard */
   I2S2ext->I2SCFGR &= ~(3u << 4);
   /* Select data length, 16-bit */
   I2S2ext->I2SCFGR &= ~(3u << 1);
   /* Select nr of bits per channel, 16-bit */
   I2S2ext->I2SCFGR &= ~(0x1);
   /* Select I2S slave receiver mode */
   I2S2ext->I2SCFGR |= (1u << 8);


   /* Configure DMA */
   //SPI2->CR2 |= (1 << 1) | (1 << 0);

   /* Enable I2S */
   SPI2->I2SCFGR |= (1 << 10);
   I2S2ext->I2SCFGR |= (1 << 10);

}

