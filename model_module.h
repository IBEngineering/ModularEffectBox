/*
 * model_module.h
 *
 *  Created on: 25 dec. 2017
 *      Author: MisterCavespider
 */

#ifndef MODEL_MODULE_H_
#define MODEL_MODULE_H_

#include "Audio.h"
#include "model_module_prototype.h"
#include "model_value.h"
#include <stdlib.h>
#include <stdint.h>

class Module
{
protected:
	uint8_t mId;
	BoundedValue *mValues;
	uint8_t* mInputs;		// An array of input ports, each with one link
	uint8_t* mOutputs;		// An array of input ports, each with several outputs,
							//   but used as a pseudo-multidimensional array because c++
public:
	// What should it be called?
	virtual const char *title() = 0;
	virtual const char **names() = 0;
	// How many variables to set?
	virtual uint8_t valueCount() = 0;
	// How many ports?
	virtual uint8_t inputCount() = 0;
	virtual uint8_t outputCount() = 0;
	virtual uint8_t paralsCount() = 0;

	// Audio
	virtual void createAudio(AudioStream *store) = 0;

	uint8_t id();
	BoundedValue *values();
	uint8_t *inputs();
	uint8_t *outputs();
};

#endif /* MODEL_MODULE_H_ */
