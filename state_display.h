/*
 * state_display.h
 *
 *  Created on: 29 dec. 2017
 *      Author: MisterCavespider
 */

#ifndef STATE_DISPLAY_H_
#define STATE_DISPLAY_H_

#include "Audio.h"
#include "state_state.h"

class DisplayState : public ProgramState {
private:
	AudioAnalyzeRMS *rms;
	float currentRMS, lastRMS;
	uint16_t ticks = 1;
public:
	DisplayState(
			U8G2_ST7920_128X64_F_SW_SPI *u8g2,
			AudioAnalyzeRMS *rms,
			EncoderCapsule *encc1,
			EncoderCapsule *encc2,
			EncoderCapsule *encc3,
			StateManager *states)
			:ProgramState(u8g2, encc1, encc2, encc3, states, "DISPLAY") {this->rms = rms;}
	void setup();
	void loop();
	virtual ~DisplayState() {}
};

#endif /* STATE_DISPLAY_H_ */
