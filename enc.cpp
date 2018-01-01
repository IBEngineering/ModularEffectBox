/*
 * enc.cpp
 *
 *  Created on: 29 dec. 2017
 *      Author: borgert
 */

#include "enc.h"

EncoderButton::EncoderButton(uint8_t pin)
{
	this->pin = pin;
	curr = 0;
	last = 0;
	delta = 0;
}


void EncoderButton::read()
{
	last = curr;				// update last
	curr = !digitalRead(pin);	// update current
	delta = curr - last;		// update delta
}

uint8_t	EncoderButton::currentread()
{
	return curr;
}

uint8_t EncoderButton::lastread()
{
	return last;
}

int8_t	EncoderButton::deltaread()
{
	return delta;
}

EncoderButton::~EncoderButton()
{
	// TODO Auto-generated destructor stub
}

