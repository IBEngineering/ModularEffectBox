/*
 * state_mainmenu.cpp
 *
 *  Created on: 29 dec. 2017
 *      Author: MisterCavespider
 */

#include "state_mainmenu.h"

void MainMenuState::setup()
{
	u8g2->setFont(u8g2_font_6x10_mr);

	u8g2->drawBox(0, 13, 4, 3);
	u8g2->drawStr(5, 17, "Graph");

	u8g2->drawBox(0, 48, 4, 3);
	u8g2->drawStr(5, 52, "Editor");
}

void MainMenuState::loop()
{
	if(PRESSEDP(encc1) > 0)
	{
		u8g2->clearBuffer();
		stateManager->setCurrentState(1);
	} else if(PRESSEDP(encc2) > 0) {
		u8g2->clearBuffer();
		stateManager->setCurrentState(2);
	}
}

MainMenuState::~MainMenuState()
{
}

