/*
 * state.h
 *
 *  Created on: 29 dec. 2017
 *      Author: MisterCavespider
 */

#ifndef STATE_STATE_H_
#define STATE_STATE_H_

#include "enc.h"
#include <U8g2lib.h>
#include "state_manager.h"

class StateManager;

class ProgramState {
protected:
	EncoderCapsule *encc1;
	EncoderCapsule *encc2;
	EncoderCapsule *encc3;
	StateManager *stateManager;
	U8G2_ST7920_128X64_F_SW_SPI *u8g2;

public:
	const char *title;

	ProgramState();
	ProgramState(
			U8G2_ST7920_128X64_F_SW_SPI *u8g2,
			EncoderCapsule *encc1,
			EncoderCapsule *encc2,
			EncoderCapsule *encc3,
			StateManager *stateManager,
			const char *title);

	virtual void setup() =0;
	virtual void loop() =0;

	virtual ~ProgramState();
};

#endif /* STATE_STATE_H_ */
