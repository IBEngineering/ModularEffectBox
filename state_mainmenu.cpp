/*
 * state_mainmenu.cpp
 *
 *  Created on: 29 dec. 2017
 *      Author: MisterCavespider
 */

#include "state_mainmenu.h"

bool logo = true;

void MainMenuState::setup()
{
	if(logo)
	{

	}
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

