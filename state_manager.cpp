/*
 * state_manager.cpp
 *
 *  Created on: 29 dec. 2017
 *      Author: MisterCavespider
 */

#include "state_manager.h"

//StateManager::StateManager(uint8_t)
//{
//	this->states = new ProgramState[3];
//	this->currentState = states; //actually &states[0], but thats longer
//}

StateManager::StateManager(ProgramState **states)
{
	this->states = states;
	this->currentState = states[0]; //actually &states[0], but thats longer
}
void StateManager::setCurrentState(uint8_t state)
{
	currentState = states[state];
	currentState->setup();
}

void StateManager::setup()
{
	currentState->setup();
}

void StateManager::loop()
{
	currentState->loop();
}

StateManager::~StateManager() {}

