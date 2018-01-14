/*
 * flange.h
 *
 *  Created on: 7 jan. 2018
 *      Author: MisterCavespider
 */

#ifndef FLANGE_H_
#define FLANGE_H_

#include "../model.h"

class FlangeModule : public Module {
public:
	FlangeModule(uint8_t id);

	const char *title();
	const char **names();
	uint8_t valueCount();
	uint8_t inputCount();
	uint8_t outputCount();
	uint8_t paralsCount();
	void createAudio(AudioStream *store);
};

#endif /* FLANGE_H_ */
