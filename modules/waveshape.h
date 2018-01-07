/*
 * waveshape.h
 *
 *  Created on: 7 jan. 2018
 *      Author: MisterCavespider
 */

#ifndef WAVESHAPE_H_
#define WAVESHAPE_H_

#include "../model.h"

class WaveshapeModule: public Module {
public:
	WaveshapeModule(uint8_t id);

	const char *title();
	const char **names();
	uint8_t valueCount();
	uint8_t inputCount();
	uint8_t outputCount();
};

#endif /* WAVESHAPE_H_ */
