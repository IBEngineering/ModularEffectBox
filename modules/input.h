/*
 * input.h
 *
 *  Created on: 6 jan. 2018
 *      Author: MisterCavespider
 */

#ifndef INPUT_H_
#define INPUT_H_

#include "../model.h"

class InputModule: public Module {
public:
	InputModule(uint8_t id);

	const char *title();
	const char **names();
	uint8_t valueCount();
	uint8_t inputCount();
	uint8_t outputCount();
};

#endif /* INPUT_H_ */
