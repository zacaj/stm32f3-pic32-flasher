/*
 * io.h
 *
 *  Created on: Jul 16, 2014
 *      Author: zacaj
 */

#ifndef IO_H_
#define IO_H_
#include "stm32f30x.h"
#include "stm32f3_discovery.h"
#include "stm32f30x_conf.h"
#include <stdio.h>
#include <stdint.h>

typedef struct
{
	GPIO_TypeDef* const bank;
	const uint32_t pin;
} IOPin;
#define NO_PULL GPIO_PuPd_NOPULL
#define PULL_DOWN GPIO_PuPd_DOWN
#define PULL_UP GPIO_PuPd_UP
#define bA GPIOA
#define bB GPIOB
#define bC GPIOC
#define bD GPIOD
#define bE GPIOE
#define bF GPIOF
#define bmA (GPIO_TypeDef*)1
#define bmB (GPIO_TypeDef*)2
#define bmC (GPIO_TypeDef*)3
#define bmD (GPIO_TypeDef*)4
#define bU (GPIO_TypeDef*)100
#define P0 GPIO_Pin_0
#define P1 GPIO_Pin_1
#define P2 GPIO_Pin_2
#define P3 GPIO_Pin_3
#define P4 GPIO_Pin_4
#define P5 GPIO_Pin_5
#define P6 GPIO_Pin_6
#define P7 GPIO_Pin_7
#define P8 GPIO_Pin_8
#define P9 GPIO_Pin_9
#define P10 GPIO_Pin_10
#define P11 GPIO_Pin_11
#define P12 GPIO_Pin_12
#define P13 GPIO_Pin_13
#define P14 GPIO_Pin_14
#define P15 GPIO_Pin_15

void initInput(IOPin pin, GPIOPuPd_TypeDef def);
void initOutput(IOPin pin);
void setOut(IOPin pin, uint32_t value);
void setOutDirect(IOPin pin, uint32_t value);
uint8_t getIn(IOPin pin);
#endif /* IO_H_ */
