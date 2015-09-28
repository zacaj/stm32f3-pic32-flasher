/**
*****************************************************************************
**
**  File        : main.c
**
**  Abstract    : main function.
**
**  Functions   : main
**
**  Environment : Atollic TrueSTUDIO(R)
**
**  Distribution: The file is distributed
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. This file may only be built (assembled or compiled and linked)
**  using the Atollic TrueSTUDIO(R) product. The use of this file together
**  with other tools than Atollic TrueSTUDIO(R) is not permitted.
**
*****************************************************************************
*/

/* Includes */
#include <stdint.h>
#include "stm32f30x.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_conf.h"
#include "stm32f3_discovery.h"
#include <stdio.h>
#include <math.h>
#include "io.h"
#include "Arduino.h"
void pinMode(IOPin pin, int mode) {
	if(mode == OUTPUT)
		initOutput(pin);
	else
		initInput(pin, NO_PULL);
}

extern int usTicks;
void delayMicroseconds(int us) {
	long start=usTicks;
	while(start-usTicks>us);
}
#include "Pic32.h"
#include "Pic32JTAG.h"
#include "Pic32JTAGDevice.h"
#include "MySerial.h"

void error(char *str) {
	printf(str);
}

int main(void)
{

	int i;
	/* Example use SysTick timer and read System core clock */
	SysTick_Config(72);  /* 1  ms if clock frequency 72 MHz */
	for(i=0;i<8;i++)
		//if(i!=4)
			STM_EVAL_LEDInit((Led_TypeDef)(LED3+i));
	int8_t buttonState=0;
	STM_EVAL_PBInit(BUTTON_USER,BUTTON_MODE_GPIO);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	while(true) {
		if(buttonState!=STM_EVAL_PBGetState(BUTTON_USER))
		{
			buttonState=!buttonState;
			if(buttonState)
				break;
		}
	}
	STM_EVAL_PBInit(BUTTON_USER,BUTTON_MODE_GPIO);
	SystemCoreClockUpdate();
	setOutDirect({bU,P0},0);

	{
		Pic32JTAGDevice pic32;
		uint32_t addr;
		bool exit = false;

		{
			char *name=pic32.GetDeviceName();
			int needsErase = pic32.NeedsErase();
			uint32_t id=pic32.GetDeviceID();
			int rowSize=pic32.GetRowSize();
			int pageSize=pic32.GetPageSize();
		}
	    pic32.SetReset(false);
	    delayMicroseconds(100000);
	    pic32.SetReset(true);

	    while(!pic32.IsConnected()) {
	    	if ( pic32.NeedsErase() )
			{
				error("need to erase first!");
			}
			else
			{
				pic32.EnterPgmMode();
				pic32.FlashOperation( NVMOP_NOP,  0x00000000, 0 );
			}
	    }

	    { //erase
	    	pic32.FlashOperation( NVMOP_NOP,  0x00000000, 0 );

			addr = pic32.GetBootFlashStart();
			while ( addr < pic32.GetBootFlashEnd() )
			{
				//Serial.print( F("Erasing: ") );
				//Serial.println( addr, HEX );
				pic32.FlashOperation( NVMOP_ERASE_PAGE, addr, 0 );
				pic32.FlashOperation( NVMOP_NOP, 0, 0 );

				addr += pic32.GetPageSize();
			}

			addr = pic32.GetProgramFlashStart();
			//Serial.print( F("Erasing: ") );
			//Serial.println( addr, HEX );
			pic32.FlashOperation( NVMOP_ERASE_PFM, addr, 0 );
			pic32.FlashOperation( NVMOP_NOP, 0, 0 );
	    }

	    {//program
	    	HexPgm( pic32, true, true );
	    }
	}
	return 0;
}
#if 0
void IRQHander()
{
	__asm__("BKPT");
}
void WWDG_IRQHandler()
{IRQHander();
}
                   /* Window WatchDog */
void PVD_IRQHandler()
{IRQHander();
}
                    /* PVD through EXTI Line detection */
void TAMPER_STAMP_IRQHandler()
{IRQHander();
}
           /* Tamper and TimeStamps through the EXTI line */
void RTC_WKUP_IRQHandler()
{IRQHander();
}
               /* RTC Wakeup through the EXTI line */
void FLASH_IRQHandler()
{IRQHander();
}
                  /* FLASH */
void RCC_IRQHandler()
{IRQHander();
}
                    /* RCC */
void EXTI0_IRQHandler()
{IRQHander();
}
                  /* EXTI Line0 */
void EXTI1_IRQHandler()
{IRQHander();
}
                  /* EXTI Line1 */
void EXTI2_TS_IRQHandler()
{IRQHander();
}
               /* EXTI Line2 and Touch Sense */
void EXTI3_IRQHandler()
{IRQHander();
}
                  /* EXTI Line3 */
void EXTI4_IRQHandler()
{IRQHander();
}
                  /* EXTI Line4 */
void DMA1_Channel1_IRQHandler()
{IRQHander();
}
          /* DMA1 Channel 1 */
void DMA1_Channel2_IRQHandler()
{IRQHander();
}
          /* DMA1 Channel 2 */
void DMA1_Channel3_IRQHandler()
{IRQHander();
}
          /* DMA1 Channel 3 */
void DMA1_Channel4_IRQHandler()
{IRQHander();
}
          /* DMA1 Channel 4 */
void DMA1_Channel5_IRQHandler()
{IRQHander();
}
          /* DMA1 Channel 5 */
void DMA1_Channel6_IRQHandler()
{IRQHander();
}
          /* DMA1 Channel 6 */
void DMA1_Channel7_IRQHandler()
{IRQHander();
}
          /* DMA1 Channel 7 */
void ADC1_2_IRQHandler()
{IRQHander();
}
                 /* ADC1 and ADC2 */
void USB_HP_CAN1_TX_IRQHandler()
{IRQHander();
}
         /* USB Device High Priority or CAN1 TX */
void USB_LP_CAN1_RX0_IRQHandler()
{IRQHander();
}
        /* USB Device Low Priority or CAN1 RX0 */
void CAN1_RX1_IRQHandler()
{IRQHander();
}
               /* CAN1 RX1 */
void CAN1_SCE_IRQHandler()
{IRQHander();
}
               /* CAN1 SCE */
void EXTI9_5_IRQHandler()
{IRQHander();
}
                /* External Line[9:5]s */
            /* TIM4 */
void I2C1_EV_IRQHandler()
{IRQHander();
}
                /* I2C1 Event */
void I2C1_ER_IRQHandler()
{IRQHander();
}
                /* I2C1 Error */
void I2C2_EV_IRQHandler()
{IRQHander();
}
                /* I2C2 Event */
void I2C2_ER_IRQHandler()
{IRQHander();
}
                /* I2C2 Error */
void SPI1_IRQHandler()
{IRQHander();
}
                   /* SPI1 */
void SPI2_IRQHandler()
{IRQHander();
}
                   /* SPI2 */
void USART1_IRQHandler()
{IRQHander();
}
                 /* USART1 */
void USART2_IRQHandler()
{IRQHander();
}
                 /* USART2 */
void USART3_IRQHandler()
{IRQHander();
}
                 /* USART3 */
void EXTI15_10_IRQHandler()
{IRQHander();
}
              /* External Line[15:10]s */
void RTC_Alarm_IRQHandler()
{IRQHander();
}
              /* RTC Alarm (A and B) through EXTI Line */
void USBWakeUp_IRQHandler()
{IRQHander();
}

void ADC3_IRQHandler()
{IRQHander();
}
                   /* ADC3 */

                                 /* Reserved */
void SPI3_IRQHandler()
{IRQHander();
}
                   /* SPI3 */
void UART4_IRQHandler()
{IRQHander();
}
                  /* UART4 */
void UART5_IRQHandler()
{IRQHander();
}

void DMA2_Channel1_IRQHandler()
{IRQHander();
}
          /* DMA2 Channel 1 */
void DMA2_Channel2_IRQHandler()
{IRQHander();
}
          /* DMA2 Channel 2 */
void DMA2_Channel3_IRQHandler()
{IRQHander();
}
          /* DMA2 Channel 3 */
void DMA2_Channel4_IRQHandler()
{IRQHander();
}
          /* DMA2 Channel 4 */
void DMA2_Channel5_IRQHandler()
{IRQHander();
}
          /* DMA2 Channel 5 */
void ADC4_IRQHandler()
{IRQHander();
}
                   /* ADC4 */
                         /* Reserved */
void COMP1_2_3_IRQHandler()
{IRQHander();
}
              /* COMP1, COMP2 and COMP3 */
void COMP4_5_6_IRQHandler()
{IRQHander();
}
              /* COMP4, COMP5 and COMP6 */
void COMP7_IRQHandler()
{IRQHander();
}
                  /* COMP7 */

                                 /* Reserved */
void USB_HP_IRQHandler()
{IRQHander();
}
                 /* USB High Priority remap */
void USB_LP_IRQHandler()
{IRQHander();
}
                 /* USB Low Priority remap */
void USBWakeUp_RMP_IRQHandler()
{IRQHander();
}

                                 /* Reserved */
void FPU_IRQHandler()
{IRQHander();
}
                    /* FPU */
void HardFault_Handler()
{IRQHander();
}void MemManage_Handler()
{IRQHander();
}void BusFault_Handler()
{IRQHander();
}void UsageFault_Handler()
{IRQHander();
}void NMI_Handler()
{IRQHander();
}


#endif
