/*
 * reverb.h
 *
 *  Created on: 7 jan. 2018
 *      Author: MisterCavespider
 */

#ifndef REVERB_H_
#define REVERB_H_

#include "../model.h"

class ReverbModule: public Module {
public:
	ReverbModule(uint8_t id);

	const char *title();
	const char **names();
	uint8_t valueCount();
	uint8_t inputCount();
	uint8_t outputCount();
	void createAudio(AudioStream *store);
};

#endif /* REVERB_H_ */
