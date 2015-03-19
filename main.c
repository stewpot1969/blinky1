/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

//#include <libopencm3/stm32/f1/rcc.h>
//#include <libopencm3/stm32/f1/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>


static void gpio_setup(void)
{

	rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_IOPBEN);
	rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_IOPCEN);

	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, GPIO12|GPIO13|GPIO14|GPIO15);

	gpio_set_mode(GPIOC, GPIO_MODE_INPUT,
		      GPIO_CNF_INPUT_PULL_UPDOWN, GPIO6|GPIO7|GPIO8);
		      
  gpio_set(GPIOC,GPIO6|GPIO7|GPIO8);
  
}

void dlay(int j) {
  int i;
  for (i=0;i<j;i++)
    __asm__("nop");
}

int main(void)
{
  uint16_t inbits;
  int i=100000;
	gpio_setup();

	while (1) {
	
    // read button and set delay accordingly
    inbits=GPIOC_IDR;
    if ((inbits & (1<<6))==0) {
      i=70000;      // KEY1
    }
    else if ((inbits & (1<<7))==0) {
      i=35000;      // KEY2
    }
    else if ((inbits & (1<<8))==0) {
      i=12000;      // KEY3
    }    

		/* Using API function gpio_toggle(): */
		gpio_set(GPIOB, GPIO12);	/* LED on/off */
    dlay(i);
		gpio_clear(GPIOB, GPIO13);	/* LED on/off */
    dlay(i);
		gpio_set(GPIOB, GPIO14);	/* LED on/off */
		dlay(i);
		gpio_clear(GPIOB, GPIO15);	/* LED on/off */
    dlay(i);
		gpio_set(GPIOB, GPIO13);	/* LED on/off */
    dlay(i);
		gpio_clear(GPIOB, GPIO12);	/* LED on/off */
    dlay(i);
		gpio_set(GPIOB, GPIO15);	/* LED on/off */
    dlay(i);
		gpio_clear(GPIOB, GPIO14);	/* LED on/off */
    dlay(i);
	}

	return 0;
}
