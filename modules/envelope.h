/*
 * envelope.h
 *
 *  Created on: 7 jan. 2018
 *      Author: MisterCavespider
 */

#ifndef ENVELOPE_H_
#define ENVELOPE_H_

#include "../model.h"

class EnvelopeModule: public Module {
public:
	EnvelopeModule(uint8_t id);

	const char *title();
	const char **names();
	uint8_t valueCount();
	uint8_t inputCount();
	uint8_t outputCount();
	void createAudio(AudioStream *store);
};

#endif /* ENVELOPE_H_ */
