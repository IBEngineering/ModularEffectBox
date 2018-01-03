/*
 * state_test.h
 *
 *  Created on: 1 jan. 2018
 *      Author: MisterCavespider
 */

#ifndef STATE_TEST_H_
#define STATE_TEST_H_

#include "model_value.h"
#include "state_state.h"

class TestState : public ProgramState {
public:
	TestState(
				U8G2_ST7920_128X64_F_SW_SPI *u8g2,
				EncoderCapsule *encc1,
				EncoderCapsule *encc2,
				EncoderCapsule *encc3,
				StateManager *states)
				:ProgramState(u8g2, encc1, encc2, encc3, states, "TEST") {bv = BoundedValue(0.0, 0.1, 5.0);}

	void setup();
	void loop();

	virtual ~TestState();
private:
	BoundedValue bv;
};

#endif /* STATE_TEST_H_ */
