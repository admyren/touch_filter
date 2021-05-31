/*
 * rcc.c
 *
 *  Created on: 17 mars 2021
 *      Author: Myren
 */

#include "rcc.h"
#include "gpio.h"
#include "stm32_flash.h"

uint32_t AHB_clk_freq = 0;
uint32_t APB1_clk_freq = 0;
uint32_t APB2_clk_freq = 0;

uint32_t RCC_PLL_config(rcc_device_t* rcc_dev, clock_conf_t* clock_conf)
{
   uint32_t ret = 0;
   uint32_t PLLP_temp;
   uint32_t sysclk_freq;
   uint32_t div;
   uint32_t input_clk_freq;

   if (HSE_CLK == clock_conf->source)
   {
      /* Turn on HSE clock and wait for it to stabilize  */
      rcc_dev->CR |= (1 << 16); /* HSEON bit */
      while (!(rcc_dev->CR & (1 << 17))); /* Wait for HSERDY bit to go high */
   }

   if (enable == clock_conf->PLL_enable)
   {
      /* Configure PLL */
      /* Set PLLM */
      rcc_dev->PLLCFGR &= ~(0x3F);
      rcc_dev->PLLCFGR |= (clock_conf->PLLM & 0x3F);
      /* Set PLLN */
      rcc_dev->PLLCFGR &= ~(0x1FF << 6);
      rcc_dev->PLLCFGR |= (clock_conf->PLLN & 0x1FF) << 6;
      /* Set PLLP */
      PLLP_temp = (clock_conf->PLLP - 2) >> 1;
      rcc_dev->PLLCFGR &= ~(0x3 << 16);
      rcc_dev->PLLCFGR |= (PLLP_temp & 0x3) << 16;
      /* Set PLLQ */
      rcc_dev->PLLCFGR &= ~(0xF << 24);
      rcc_dev->PLLCFGR |= (clock_conf->PLLQ & 0xF) << 24;

      if (HSE_CLK == clock_conf->source)
      {
         rcc_dev->PLLCFGR |= 1 << 22; /* Set PLLSRC bit */
         input_clk_freq = HSE_CLK_FREQ_MHZ;
      }
      else
      {
         rcc_dev->PLLCFGR &= ~(1 << 22); /* Clear PLLSRC bit */
         input_clk_freq = HSI_CLK_FREQ_MHZ;
      }

      rcc_dev->CR |= 1 << 24; /* Turn on PLL by setting PLLON bit */

      while (!(rcc_dev->CR & (1 << 25))); /* Wait for PLLRDY bit to go high */
      gpio_pin_set(GPIOC, gpio_pin_3);

      /* Calculate sys clk freq to determine flash wait states */
      sysclk_freq = ((input_clk_freq / clock_conf->PLLM) * clock_conf->PLLN) /
            clock_conf->PLLP;
      /* Select wait states for flash memory */
      FLASH->ACR &= ~0x7;
      if (sysclk_freq <= 30)
      {
         FLASH->ACR |= 0x0; /* Zero wait states */
      }
      else if (sysclk_freq <= 60)
      {
         FLASH->ACR |= 0x1; /* One wait state */
      }
      else if (sysclk_freq <= 90)
      {
         FLASH->ACR |= 0x2; /* Two wait states */
      }
      else if (sysclk_freq <= 120)
      {
         FLASH->ACR |= 0x3; /* Three wait states */
      }
      else if (sysclk_freq <= 150)
      {
         FLASH->ACR |= 0x4; /* Four wait states */
      }
      else if (sysclk_freq <= 180)
      {
         FLASH->ACR |= 0x5; /* Five wait states */
      }
      else if (sysclk_freq <= 210)
      {
         FLASH->ACR |= 0x6; /* Six wait states */
      }
      else if (sysclk_freq <= 240)
      {
         FLASH->ACR |= 0x7; /* Seven wait states */
      }

      /* Select PLL as system clock source */
      rcc_dev->CFGR &= ~0x3;
      rcc_dev->CFGR |= 0x2;
   }
   else
   {
      /* Select clock source */
      switch(clock_conf->source)
      {
      case HSE_CLK:
         rcc_dev->CFGR &= ~0x2;
         rcc_dev->CFGR |= 0x1;
         sysclk_freq = HSE_CLK_FREQ_MHZ;
         break;
      case HSI_CLK:
         rcc_dev->CFGR &= ~0x3;
         sysclk_freq = HSI_CLK_FREQ_MHZ;
         break;
      default:
         break;
      }
   }

   /* AHB prescaler */
   AHB_clk_freq = sysclk_freq;
   rcc_dev->CFGR &= ~(0xF << 4);
   switch(clock_conf->AHB_prescaler)
   {
   case AHB_DIV_2:
      div = 0x8;
      AHB_clk_freq >>= 1;
      break;
   case AHB_DIV_4:
      div = 0x9;
      AHB_clk_freq >>= 2;
      break;
   case AHB_DIV_8:
      div = 0xA;
      AHB_clk_freq >>= 3;
      break;
   case AHB_DIV_16:
      div = 0xB;
      AHB_clk_freq >>= 4;
      break;
   case AHB_DIV_64:
      div = 0xC;
      AHB_clk_freq >>= 6;
      break;
   case AHB_DIV_128:
      div = 0xD;
      AHB_clk_freq >>= 7;
      break;
   case AHB_DIV_256:
      div = 0xE;
      AHB_clk_freq >>= 8;
      break;
   case AHB_DIV_512:
      div = 0xF;
      AHB_clk_freq >>= 9;
      break;
   default:
      break;
   }
   rcc_dev->CFGR |= div << 4;

   /* APB1 prescaler */
   APB1_clk_freq = AHB_clk_freq;
   rcc_dev->CFGR &= ~(0x7 << 10);
   switch(clock_conf->APB1_prescaler)
   {
   case APB_DIV_2:
      div = 0x4;
      APB1_clk_freq >>= 1;
      break;
   case APB_DIV_4:
      div = 0x5;
      APB1_clk_freq >>= 2;
      break;
   case APB_DIV_8:
      div = 0x6;
      APB1_clk_freq >>= 3;
      break;
   case APB_DIV_16:
      div = 0x7;
      APB1_clk_freq >>= 4;
      break;
   default:
      break;
   }
   rcc_dev->CFGR |= div << 10;

   /* APB2 prescaler */
   APB2_clk_freq = AHB_clk_freq;
   rcc_dev->CFGR &= ~(0x7 << 13);
   switch(clock_conf->APB2_prescaler)
   {
   case APB_DIV_2:
      div = 0x4;
      APB2_clk_freq >>= 1;
      break;
   case APB_DIV_4:
      div = 0x5;
      APB2_clk_freq >>= 2;
      break;
   case APB_DIV_8:
      div = 0x6;
      APB2_clk_freq >>= 3;
      break;
   case APB_DIV_16:
      div = 0x7;
      APB2_clk_freq >>= 4;
      break;
   default:
      break;
   }
   rcc_dev->CFGR |= div << 13;

   return(ret);
}

uint32_t RCC_get_AHB_freq(void)
{
   return(AHB_clk_freq);
}

uint32_t RCC_get_APB1_freq(void)
{
   return(APB1_clk_freq);
}

uint32_t RCC_get_APB2_freq(void)
{
   return(APB2_clk_freq);
}





