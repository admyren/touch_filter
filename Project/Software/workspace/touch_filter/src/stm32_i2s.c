/*
 * stm32_i2s.c
 *
 *  Created on: 11 sep. 2021
 *      Author: Myren
 */
#include <stdint.h>

#include "stm32f405xx.h"
#include "stm32_i2s.h"
#include "stm32_dma.h"

void (*I2S_tx_ready_callb)(void) = 0;
void (*I2S_rx_ready_callb)(void) = 0;


void i2s_config(uint16_t* rx_buff, uint16_t* tx_buff, uint32_t buff_size)
{
   /* Struct for configuring DMA */
   DMA_InitVals DMA_init;

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

   /* Set ODD bit and I2SDIV value */
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
   I2S2ext->I2SCFGR |= (1 << 11);
   /* Chose I2S standard */
   I2S2ext->I2SCFGR &= ~(3u << 4);
   /* Select data length, 16-bit */
   I2S2ext->I2SCFGR &= ~(3u << 1);
   /* Select nr of bits per channel, 16-bit */
   I2S2ext->I2SCFGR &= ~(0x1);
   /* Select I2S slave receiver mode */
   I2S2ext->I2SCFGR |= (1u << 8);

#if 1
   /* Configure DMA */
   /* DMA clocks */
   RCC->AHB1ENR |= (1 << 22) | (1 << 21);
   /* I2S2 TX uses stream 4, ch 0. I2Sext RX uses stream 2, ch 2  */
   /* Enable TX DMA  */
   SPI2->CR2 |= (1 << 1);
   /* Enable RX DMA */
   I2S2ext->CR2 |= (1 << 0);


   DMA_init.channel = 0;             /* DMA channel */
   DMA_init.periphDataSize = SIZE_HALF_WORD;      /* Peripheral data size */
   DMA_init.memDataSize = SIZE_HALF_WORD;         /* Memory data size */
   DMA_init.direction = 1;           /* Direction, memory->peripheral(1) or peripheral->memory(0) */
   DMA_init.bufferSize = buff_size;          /* Number of element in the DMA buffer */
   DMA_init.periphAddr = (uint32_t)(&SPI2->DR);          /* Address to peripheral data register */
   DMA_init.memAddr = (uint32_t)tx_buff;             /* Address to first element of DMA buffer */
   DMA_init.halfIntEnable = 0;       /* DMA half transfer complete interrupt enable */
   DMA_init.compIntEnable = 1;       /* DMA transfer complete interrupt enable */
   DMA_init.mode = 1;                /* Circular mode or not */
   DMA_init.dma_enable = 1;          /* DMA enable */

   /* Enable DMA for I2S2 TX */
   DMA_config(DMA1_Stream4, DMA_init);

   DMA_init.channel = 2;             /* DMA channel */
   DMA_init.periphDataSize = SIZE_HALF_WORD;      /* Peripheral data size */
   DMA_init.memDataSize = SIZE_HALF_WORD;         /* Memory data size */
   DMA_init.direction = 0;           /* Direction, memory->peripheral(1) or peripheral->memory(0) */
   DMA_init.bufferSize = buff_size;          /* Number of element in the DMA buffer */
   DMA_init.periphAddr = (uint32_t)(&I2S2ext->DR);          /* Address to peripheral data register */
   DMA_init.memAddr = (uint32_t)rx_buff;             /* Address to first element of DMA buffer */
   DMA_init.halfIntEnable = 0;       /* DMA half transfer complete interrupt enable */
   DMA_init.compIntEnable = 1;       /* DMA transfer complete interrupt enable */
   DMA_init.mode = 1;                /* Circular mode or not */
   DMA_init.dma_enable = 1;          /* DMA enable */

   /* Enable DMA for I2S2ext RX */
   DMA_config(DMA1_Stream2, DMA_init);

   NVIC_SetPriorityGrouping(2);
   NVIC_SetPriority (DMA1_Stream2_IRQn, 8);
   NVIC_EnableIRQ(DMA1_Stream2_IRQn);

   NVIC_SetPriorityGrouping(2);
   NVIC_SetPriority (DMA1_Stream4_IRQn, 8);
   NVIC_EnableIRQ(DMA1_Stream4_IRQn);
#endif

   /* Enable I2S */
   SPI2->I2SCFGR |= (1 << 10);
   I2S2ext->I2SCFGR |= (1 << 10);

}

void I2S_register_rx_complete_callback(void (*func)(void))
{
   I2S_rx_ready_callb = func;
}

void I2S_register_tx_complete_callback(void (*func)(void))
{
   I2S_tx_ready_callb = func;
}


void DMA1_Stream2_IRQHandler(void)
{
   // Transfer complete interrupt?
   if(DMA1->LISR & (1 << 21))
   {
      // Clear interrupt flag
      DMA1->LIFCR |= 1 << 21;

      if (I2S_rx_ready_callb != 0)
      {
         I2S_rx_ready_callb();
      }
   }
}

void DMA1_Stream4_IRQHandler(void)
{
   // Transfer complete interrupt?
   if(DMA1->HISR & (1 << 5))
   {
      // Clear interrupt flag
      DMA1->HIFCR |= 1 << 5;

      if(I2S_tx_ready_callb != 0)
      {
         I2S_tx_ready_callb();
      }
   }
}

