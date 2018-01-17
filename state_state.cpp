/*
 * state.cpp
 *
 *  Created on: 29 dec. 2017
 *      Author: MisterCavespider
 */

#include "state_state.h"

ProgramState::ProgramState()
{
	this->u8g2 = 0;
	this->encc1 = 0;
	this->encc2 = 0;
	this->encc3 = 0;
	this->stateManager = 0;
	this->title = 0;
}

ProgramState::ProgramState(
		U8G2_ST7920_128X64_F_HW_SPI *u8g2,
		EncoderCapsule *encc1,
		EncoderCapsule *encc2,
		EncoderCapsule *encc3,
		StateManager *stateManager,
		const char *title) {
	this->u8g2 = u8g2;
	this->encc1 = encc1;
	this->encc2 = encc2;
	this->encc3 = encc3;
	this->stateManager = stateManager;
	this->title = title;
}

/*
 * Empty defined virtual methods
 */

void ProgramState::setup() {}
void ProgramState::loop() {}
ProgramState::~ProgramState() {}
