/*
 * io.c
 *
 *  Created on: Jul 16, 2014
 *      Author: zacaj
 */

#include <stdint.h>
#include "stm32f30x.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_conf.h"
#include "stm32f3_discovery.h"
#include <stdio.h>
#include "io.h"
#include <string.h>
#include <stdlib.h>

#define _GPIO_WriteBit(b,p,v) \
	if(!v) ((b))->BRR = ((p)); \
else ((b))->BSRR = ((p));
#define _writeHigh(b) \
		((b)).bank->BSRR = ((b)).pin
#define _writeLow(b) \
		((b)).bank->BRR = ((b)).pin

#define _GPIO_ReadInputDataBit(b,p) \
	(( ( ((b))->IDR & ((p)) ) != 0 ))


void initInput(IOPin pin, GPIOPuPd_TypeDef def) {
	if (pin.bank == bU)
		return;
	if ((int) pin.bank < 11)
		return;
	GPIO_InitTypeDef init;
	init.GPIO_Mode = GPIO_Mode_IN;
	init.GPIO_OType = GPIO_OType_PP;
	init.GPIO_Pin = pin.pin;
	init.GPIO_PuPd = PULL_DOWN;

	GPIO_Init(pin.bank, &init);
}

void initOutput(IOPin pin) {
	if (pin.bank == bU)
		return;
	if ((int) pin.bank < 11)
		return;
	GPIO_InitTypeDef init;
	init.GPIO_Mode = GPIO_Mode_OUT;
	init.GPIO_OType = GPIO_OType_PP;
	init.GPIO_Pin = pin.pin;
	init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(pin.bank, &init);
}

void setOutDirect(IOPin pin, uint32_t value) {
	if (pin.bank == bU)
		return;
	_GPIO_WriteBit(pin.bank, pin.pin, value);
}

void setOut(IOPin pin, uint32_t value) {
	if (pin.bank == bU)
		return;
	_GPIO_WriteBit(pin.bank, pin.pin, value);
}

uint8_t getInDirect(IOPin pin) {
	if (pin.bank == bU)
		return 0;
	return _GPIO_ReadInputDataBit(pin.bank, pin.pin);
}

uint8_t getIn(IOPin pin) {
	return _GPIO_ReadInputDataBit(pin.bank, pin.pin);
}
