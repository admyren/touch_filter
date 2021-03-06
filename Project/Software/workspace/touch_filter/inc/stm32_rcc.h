/*
 * stm32_rcc.h
 *
 *  Created on: 11 sep. 2021
 *      Author: Myren
 */

#ifndef STM32_RCC_H_
#define STM32_RCC_H_

#include <stdint.h>

#include "stm32f405xx.h"
#include "common.h"



#define HSE_CLK_FREQ_MHZ 16
#define HSI_CLK_FREQ_MHZ 16

#if 0
#define RCC_ADDR 0x40023800

typedef struct
{
   volatile uint32_t CR;
   volatile uint32_t PLLCFGR;
   volatile uint32_t CFGR;
   volatile uint32_t CIR;
   volatile uint32_t AHB1RSTR;
   volatile uint32_t AHB2RSTR;
   volatile uint32_t AHB3RSTR;
   volatile uint32_t reserved_1;
   volatile uint32_t APB1RSTR;
   volatile uint32_t APB2RSTR;
   volatile uint32_t reserved_2;
   volatile uint32_t reserved_3;
   volatile uint32_t AHB1ENR;
   volatile uint32_t AHB2ENR;
   volatile uint32_t AHB3ENR;
   volatile uint32_t reserved_4;
   volatile uint32_t APB1ENR;
   volatile uint32_t APB2ENR;
   volatile uint32_t reserved_5;
   volatile uint32_t reserved_6;
   volatile uint32_t AHB1LPENR;
   volatile uint32_t AHB2LPENR;
   volatile uint32_t AHB3LPENR;
   volatile uint32_t reserved_7;
   volatile uint32_t APB1LPENR;
   volatile uint32_t APB2LPENR;
   volatile uint32_t reserved_8;
   volatile uint32_t reserved_9;
   volatile uint32_t BDCR;
   volatile uint32_t CSR;
   volatile uint32_t reserved_10;
   volatile uint32_t reserved_11;
   volatile uint32_t SSCGR;
   volatile uint32_t PLLI2SCFGR;
}rcc_device_t;

#define RCC ((rcc_device_t*)RCC_ADDR)
#endif

typedef enum
{
   HSE_CLK,
   HSI_CLK
}PPL_src_e;

typedef enum
{
   APB_DIV_NO_DIV = 0,
   APB_DIV_2 = 2,
   APB_DIV_4 = 4,
   APB_DIV_8 = 8,
   APB_DIV_16 = 16
}APB_clk_div_e;

typedef enum
{
   AHB_DIV_NO_DIV = 0,
   AHB_DIV_2 = 2,
   AHB_DIV_4 = 4,
   AHB_DIV_8 = 8,
   AHB_DIV_16 = 16,
   AHB_DIV_64 = 64,
   AHB_DIV_128 = 128,
   AHB_DIV_256 = 256,
   AHB_DIV_512 = 512
}AHB_clk_div_e;

typedef struct
{
   PPL_src_e source; /* PPL input clock source */
   enable_disable_e PLL_enable; /* If PLL should be used or not */
   uint32_t PLLM; /* Clock source divider */
   uint32_t PLLN; /* PLL multiplier */
   uint32_t PLLP; /* PPL output clock divider for SYSCLK */
   uint32_t PLLQ; /* PPL output clock divider for 48 MHz peripheral clock */
   AHB_clk_div_e AHB_prescaler; /* Max 168 MHz */
   APB_clk_div_e APB1_prescaler; /* Max 42 MHx */
   APB_clk_div_e APB2_prescaler; /* Max 84 MHz */
}clock_conf_t;

typedef struct
{
   uint32_t PLLN;
   uint32_t PLLR;
}PLL_I2S_conf_t;

uint32_t RCC_PLL_config(RCC_TypeDef* rcc_dev, clock_conf_t* clock_conf);
uint32_t RCC_PLLI2S_config(void);

uint32_t RCC_get_AHB_freq(void);
uint32_t RCC_get_APB1_freq(void);
uint32_t RCC_get_APB2_freq(void);


#endif /* STM32_RCC_H_ */
