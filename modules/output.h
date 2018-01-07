/*
 * output.h
 *
 *  Created on: 7 jan. 2018
 *      Author: MisterCavespider
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "../model.h"

class OutputModule: public Module {
public:
	OutputModule(uint8_t id);

	const char *title();
	const char **names();
	uint8_t valueCount();
	uint8_t inputCount();
	uint8_t outputCount();
};

#endif /* OUTPUT_H_ */
