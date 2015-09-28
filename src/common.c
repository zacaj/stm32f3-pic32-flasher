/*
 * common.c
 *
 *  Created on: Nov 14, 2012
 *      Author: andrei
 */


#include "common.h"


__IO uint32_t TimingDelay = 0;


/**
 * @brief  Inserts a delay time.
 * @param  nTime: specifies the delay time length, in 10 ms.
 * @retval None
 */
int usTicks=0;
/**********************************/
uint32_t msTicks,msElapsed;
void SysTick_Handler(void)
{
  usTicks++;
  if(usTicks==1000) {
	  msTicks++;
	  msElapsed++;
  }
}
