/*
 * legacymixer.h
 *
 *  Created on: 7 jan. 2018
 *      Author: MisterCavespider
 */

#ifndef LEGACYMIXER_H_
#define LEGACYMIXER_H_

#include "../model.h"

class LegacyMixerModule: public Module {
public:
	LegacyMixerModule(uint8_t id);

	const char *title();
	const char **names();
	uint8_t valueCount();
	uint8_t inputCount();
	uint8_t outputCount();
	uint8_t paralsCount();
	void createAudio(AudioStream *store);
};

#endif /* LEGACYMIXER_H_ */
