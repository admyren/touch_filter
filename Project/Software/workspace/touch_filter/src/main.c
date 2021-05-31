
//#include "stm32f4xx.h"
#include "gpio.h"
#include "rcc.h"
#include "stm32_uart.h"

#define DELAY 1000000

volatile uint32_t count;

void sysclk_init(void)
{
   clock_conf_t clk_conf;

   clk_conf.source = HSE_CLK;
   clk_conf.PLL_enable = enable;
   clk_conf.PLLM = 16;
   clk_conf.PLLN = 336;
   clk_conf.PLLP = 2;
   clk_conf.PLLQ = 7;
   clk_conf.AHB_prescaler = AHB_DIV_NO_DIV; /* 168 MHz */
   clk_conf.APB1_prescaler = APB_DIV_4; /* 42 MHz */
   clk_conf.APB2_prescaler = APB_DIV_2; /* 84 MHz */

   RCC_PLL_config(RCC, &clk_conf);
}

void init_uart(void)
{
   uart_config_t uart_conf;
   gpio_config_t gpio_conf;

   // GPIOC clock enable
   RCC->AHB1ENR |= (1 << 2);
   // UART4 clock enable
   RCC->APB1ENR |= (1 << 19);

   gpio_conf.mode = gpio_af;
   gpio_conf.alternate_func = gpio_af_8;
   gpio_conf.pins = gpio_pin_10 | gpio_pin_11;

   uart_conf.baud_rate = BAUD_115200;
   uart_conf.stop_bits = STOP_BITS_1;
   uart_conf.data_bits = DATA_BITS_8;
   uart_conf.parity_enable = disable;
   uart_conf.TX_enable = enable;
   uart_conf.RX_enable = disable;

   gpio_init(GPIOC, &gpio_conf);

   UART_config(UART4, &uart_conf);

}

void gpio_init_test(void)
{
#if 0
   RCC->AHB1ENR |= (1 << 2);

   GPIOC->MODER |= (1 << 4);

#else
   gpio_config_t gpio_conf;

   gpio_conf.mode = gpio_gpo;
   gpio_conf.output_type = gpio_opp;
   gpio_conf.output_speed = gpio_ms;
   gpio_conf.pull_up_down = gpio_no_pull;
   gpio_conf.alternate_func = gpio_af_0;
   gpio_conf.lock = gpio_lock_off;
   gpio_conf.pins = gpio_pin_2 | gpio_pin_3;

   RCC->AHB1ENR |= (1 << 2);
   gpio_init(GPIOC, &gpio_conf);
#endif
}


int main(void)
{

   sysclk_init();
   gpio_init_test();
   //init_uart();

   while(1)
   {
#if 1
      for(count=0; count<DELAY; count++);
      gpio_pin_set(GPIOC, gpio_pin_2);
      //gpio_pin_reset(GPIOC, gpio_pin_3);
      for(count=0; count<DELAY; count++);
      //gpio_pin_set(GPIOC, gpio_pin_3);
      gpio_pin_reset(GPIOC, gpio_pin_2);

      //UART_tx(UART4, (uint8_t*)"hejhej", 6);
#endif
#if 0
      for(count=0; count<DELAY; count++);
      GPIOC->ODR ^= (1 << 2);
#endif
   }
}
