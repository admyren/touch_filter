/*
 * stm32_gpio.h
 *
 *  Created on: 24 aug. 2021
 *      Author: Myren
 */

#ifndef STM32_GPIO_H_
#define STM32_GPIO_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32f405xx.h"

#if 0
#define GPIO_A_ADDR 0x40020000
#define GPIO_B_ADDR 0x40020400
#define GPIO_C_ADDR 0x40020800
#define GPIO_D_ADDR 0x40020C00
#define GPIO_E_ADDR 0x40021000
#define GPIO_F_ADDR 0x40021400
#define GPIO_G_ADDR 0x40021800
#define GPIO_H_ADDR 0x40021C00
#define GPIO_I_ADDR 0x40022000

typedef struct
{
   volatile uint32_t MODER;   /*  */
   volatile uint32_t OTYPER;  /*  */
   volatile uint32_t OSPEEDR; /*  */
   volatile uint32_t PUPDR;   /*  */
   volatile uint32_t IDR;     /*  */
   volatile uint32_t ODR;     /*  */
   volatile uint32_t BSRR;    /*  */
   volatile uint32_t LCKR;    /*  */
   volatile uint32_t AFR[2];  /*  */
}gpio_device_t;

#define GPIOA ((gpio_device_t*)GPIO_A_ADDR)
#define GPIOB ((gpio_device_t*)GPIO_B_ADDR)
#define GPIOC ((gpio_device_t*)GPIO_C_ADDR)
#define GPIOD ((gpio_device_t*)GPIO_D_ADDR)
#define GPIOE ((gpio_device_t*)GPIO_E_ADDR)
#define GPIOF ((gpio_device_t*)GPIO_F_ADDR)
#define GPIOG ((gpio_device_t*)GPIO_G_ADDR)
#define GPIOH ((gpio_device_t*)GPIO_H_ADDR)
#define GPIOI ((gpio_device_t*)GPIO_I_ADDR)
#endif


/* Port mode */
typedef enum
{
   gpio_input = 0, /* Input */
   gpio_gpo,   /* General purpose output */
   gpio_af,    /* Alternate function */
   gpio_am     /* Analog */
}gpio_mode_e;

/* Output type */
typedef enum
{
   gpio_opp = 0, /* Output push-pull */
   gpio_ood  /* Output open-drain */
}gpio_otype_e;

/* Output speed */
typedef enum
{
   gpio_ls = 0, /* Low speed */
   gpio_ms, /* Medium speed */
   gpio_hs, /* High speed */
   gpio_vhs /* Very high speed */
}gpio_ospeed_e;

/* Pull-up/Pull-down */
typedef enum
{
   gpio_no_pull = 0,
   gpio_pull_up,
   gpio_pull_down
}gpio_pupd_e;

/* Alternate function */
typedef enum
{
   gpio_af_0 = 0,  /* SYS */
   gpio_af_1,  /* TIM1/2 */
   gpio_af_2,  /* TIM3/4/5 */
   gpio_af_3,  /* TIM8/9/10/11 */
   gpio_af_4,  /* I2C1/2/3 */
   gpio_af_5,  /* SPI1/SPI2/I2S2/I2S2ext */
   gpio_af_6,  /* SPI3/I2Sext/I2S3 */
   gpio_af_7,  /* USART1/2/3/I2S3ext */
   gpio_af_8,  /* UART4/5/USART6 */
   gpio_af_9,  /* CAN1/2TIM12/13/ 14 */
   gpio_af_10, /* OTG_FS/OTG_HS */
   gpio_af_11, /* ETH */
   gpio_af_12, /* FSMC/SDIO/OTG_FS */
   gpio_af_13, /* DCMI */
}gpio_af_e;

typedef enum
{
   gpio_lock_off = 0,
   gpio_lock_on

}gpio_lock_e;

typedef enum
{
   gpio_pin_0 = 0x0001,
   gpio_pin_1 = 0x0002,
   gpio_pin_2 = 0x0004,
   gpio_pin_3 = 0x0008,
   gpio_pin_4 = 0x0010,
   gpio_pin_5 = 0x0020,
   gpio_pin_6 = 0x0040,
   gpio_pin_7 = 0x0080,
   gpio_pin_8 = 0x0100,
   gpio_pin_9 = 0x0200,
   gpio_pin_10 = 0x0400,
   gpio_pin_11 = 0x0800,
   gpio_pin_12 = 0x1000,
   gpio_pin_13 = 0x2000,
   gpio_pin_14 = 0x4000,
   gpio_pin_15 = 0x8000

}gpio_pin_e;

typedef struct
{
   gpio_mode_e mode;
   gpio_otype_e output_type;
   gpio_ospeed_e output_speed;
   gpio_pupd_e pull_up_down;
   gpio_af_e alternate_func;
   gpio_lock_e lock;
   uint32_t pins;

}gpio_config_t;

uint32_t gpio_init(GPIO_TypeDef* gpio_dev, gpio_config_t* gpio_conf);
void gpio_pin_set(GPIO_TypeDef* gpio_dev, uint32_t pins);
void gpio_pin_reset(GPIO_TypeDef* gpio_dev, uint32_t pins);
void gpio_pin_toggle(GPIO_TypeDef* gpio_dev, uint32_t pins);
uint32_t gpio_pin_read(GPIO_TypeDef* gpio_dev, gpio_pin_e pin);


#endif /* STM32_GPIO_H_ */
