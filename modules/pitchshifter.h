/*
 * pitchshifter.h
 *
 *  Created on: 20 jan. 2018
 *      Author: MisterCavespider
 */

#ifndef PITCHSHIFTER_H_
#define PITCHSHIFTER_H_

#include "../model.h"

class PitchShifterModule: public Module {
public:
	PitchShifterModule(uint8_t id);

	const char *title();
	const char **names();
	uint8_t valueCount();
	uint8_t inputCount();
	uint8_t outputCount();
	uint8_t paralsCount();
	void createAudio(AudioStream *store);
};

#endif /* PITCHSHIFTER_H_ */
