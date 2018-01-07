/*
 * state_display.cpp
 *
 *  Created on: 29 dec. 2017
 *      Author: MisterCavespider
 */

#include "state_display.h"

void DisplayState::setup()
{
//	u8g2->drawStr(12, 12, "Display not supported");
}

void DisplayState::loop()
{
	if(rms->available())
	{
		currentRMS = rms->read();

		u8g2->setDrawColor(0);
		u8g2->drawVLine((ticks+1) % 128, 0, 64);
		u8g2->setDrawColor(1);

		if(ticks % 128 == 0)	u8g2->drawPixel(0, 64 - currentRMS * 128);
		else	u8g2->drawLine((ticks-1) % 128, 64 - lastRMS * 128, ticks % 128, 64 - currentRMS * 128);

		lastRMS = currentRMS;
		ticks++;
	}
//	if(rms->available()) u8g2->drawPixel(ticks % 128, 64 - rms->read() * 64 * 4);

	if(PRESSEDP(encc1) > 0 || PRESSEDP(encc2) > 0 || PRESSEDP(encc3) > 0)
	{
		u8g2->clearBuffer();
		stateManager->setCurrentState(0);
	}


}
