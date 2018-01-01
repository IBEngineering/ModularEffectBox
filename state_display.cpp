/*
 * state_display.cpp
 *
 *  Created on: 29 dec. 2017
 *      Author: borgert
 */

#include "state_display.h"

void DisplayState::setup()
{
	u8g2->drawStr(12, 12, "Display not supported");
}

void DisplayState::loop()
{
	if(PRESSEDP(encc1) > 0 || PRESSEDP(encc2) > 0 || PRESSEDP(encc3) > 0)
	{
		u8g2->clearBuffer();
		stateManager->setCurrentState(0);
	}
}
