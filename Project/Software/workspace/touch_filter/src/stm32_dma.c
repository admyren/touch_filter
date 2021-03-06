/*
 * stm32_dma.c
 *
 *  Created on: 24 aug. 2021
 *      Author: Myren
 */

#include "stm32_dma.h"
#include "stm32f405xx.h"


void DMA_config(DMA_Stream_TypeDef* hdma, DMA_InitVals idma)
{
   // Channel
   hdma->CR |= (idma.channel << 25);
   // Priority very high
   hdma->CR |= (3 << 16);
   // Data size for transfers
   hdma->CR |= (idma.memDataSize << 13) | (idma.periphDataSize << 11);
   // Memory increment mode
   hdma->CR |= (1 << 10);
   // Circular mode
   //hdma->CR |= (1 << 8);
   // Number of transfers
   hdma->NDTR = idma.bufferSize;
   // Address to peripheral data registers
   hdma->PAR = idma.periphAddr;
   // Memory address
   hdma->M0AR = idma.memAddr;
   // Direction
   hdma->CR |= (idma.direction << 6);
   // Transfer and half transfer complete interrupt enable
   hdma->CR |= (idma.compIntEnable << 4) | (idma.halfIntEnable << 3);
   // Circular mode
   hdma->CR |= (idma.mode << 8);
   // Enable DMA
   if (1 == idma.dma_enable)
   {
      hdma->CR |= (1 << 0);
   }
}

void DMA_start_TX(DMA_Stream_TypeDef* hdma, uint32_t buff_size)
{
   /* Set size of buffer to be sent */
   hdma->NDTR = buff_size;
   /* Enable DMA to start transmit */
   hdma->CR |= (1 << 0);
}

/* TODO: Write functions to check/clear interrupt flags */
