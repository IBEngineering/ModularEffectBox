/*
 * filter.h
 *
 *  Created on: 7 jan. 2018
 *      Author: MisterCavespider
 */

#ifndef FILTER_H_
#define FILTER_H_

#include "../model.h"

class FilterModule : public Module {
public:
	FilterModule(uint8_t id);

	const char *title();
	const char **names();
	uint8_t valueCount();
	uint8_t inputCount();
	uint8_t outputCount();
	uint8_t paralsCount();
	void createAudio(AudioStream *store);
};

#endif /* FILTER_H_ */
