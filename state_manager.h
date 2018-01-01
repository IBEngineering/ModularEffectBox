/*
 * state_manager.h
 *
 *  Created on: 29 dec. 2017
 *      Author: MisterCavespider
 */

#ifndef STATE_MANAGER_H_
#define STATE_MANAGER_H_

#include "state_state.h"

class ProgramState;

class StateManager {
public:
	ProgramState **states;
	ProgramState *currentState;

//	StateManager(uint8_t size);
	StateManager(ProgramState **states);

	void setCurrentState(uint8_t state);
	void setup();
	void loop();

	virtual ~StateManager();
};

#endif /* STATE_MANAGER_H_ */
