/*
 * state_mainmenu.h
 *
 *  Created on: 29 dec. 2017
 *      Author: MisterCavespider
 */

#ifndef STATE_MAINMENU_H_
#define STATE_MAINMENU_H_

#include <elapsedMillis.h>
#include "state_state.h"

class MainMenuState: public ProgramState {
public:
	MainMenuState(
			U8G2_ST7920_128X64_F_SW_SPI *u8g2,
			EncoderCapsule *encc1,
			EncoderCapsule *encc2,
			EncoderCapsule *encc3,
			StateManager *states)
			:ProgramState(u8g2, encc1, encc2, encc3, states, "MENU") {}
	void setup();
	void loop();
	virtual ~MainMenuState();

private:
	elapsedMillis time;
	uint8_t lastselect=-1, currselect=-1;
};

#endif /* STATE_MAINMENU_H_ */
