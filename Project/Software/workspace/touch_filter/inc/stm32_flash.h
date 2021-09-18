/*
 * stm32_flash.h
 *
 *  Created on: 28 mars 2021
 *      Author: Myren
 */

#ifndef STM32_FLASH_H_
#define STM32_FLASH_H_


#define FLASH_ADDR 0x40023C00

typedef struct
{
   volatile uint32_t ACR;
   volatile uint32_t KEYR;
   volatile uint32_t OPTKEYR;
   volatile uint32_t SR;
   volatile uint32_t CR;
   volatile uint32_t OPTCR;
}flash_reg_t;

#define FLASH ((flash_reg_t*)FLASH_ADDR)

#endif /* STM32_FLASH_H_ */
