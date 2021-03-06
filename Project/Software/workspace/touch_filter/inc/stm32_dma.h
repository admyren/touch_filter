/*
 * stm32_dma.h
 *
 *  Created on: 24 aug. 2021
 *      Author: Myren
 */

#ifndef STM32_DMA_H_
#define STM32_DMA_H_

#include "stm32f405xx.h"

typedef enum
{
   SIZE_BYTE = 0,
   SIZE_HALF_WORD = 1,
   SIZE_WORD = 2
}DMA_DataSize;

typedef struct
{
   uint32_t channel;             /* DMA channel */
   DMA_DataSize periphDataSize;  /* Peripheral data size */
   DMA_DataSize memDataSize;     /* Memory data size */
   uint32_t direction;           /* Direction, memory->peripheral(1) or peripheral->memory(0) */
   uint32_t bufferSize;          /* Number of element in the DMA buffer */
   uint32_t periphAddr;          /* Address to peripheral data register */
   uint32_t memAddr;             /* Address to first element of DMA buffer */
   uint32_t halfIntEnable;       /* DMA half transfer complete interrupt enable */
   uint32_t compIntEnable;       /* DMA transfer complete interrupt enable */
   uint32_t mode;                /* Circular mode or not */
   uint32_t dma_enable;          /* DMA enable */
}DMA_InitVals;

void DMA_config(DMA_Stream_TypeDef* hdma, DMA_InitVals idma);

void DMA_start_TX(DMA_Stream_TypeDef* hdma, uint32_t buff_size);

#endif /* STM32_DMA_H_ */
