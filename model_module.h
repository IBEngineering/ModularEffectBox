/*
 * model_module.h
 *
 *  Created on: 25 dec. 2017
 *      Author: borgert
 */

#ifndef MODEL_MODULE_H_
#define MODEL_MODULE_H_

#include "model_module_prototype.h"
#include <stdlib.h>
#include <stdint.h>

class Module
{
public:
	Module() {
		id = -1;	//impossible
		values = (float *)malloc(sizeof(float));
		inputs = (uint8_t *)malloc(sizeof(uint8_t));
		outputs = (uint8_t *)malloc(sizeof(uint8_t));
		proto = 0;
	}

	Module(ModuleProto *proto, uint8_t id)
	{
		this->proto = proto;
		this->id = id;
		values = (float *)malloc(sizeof(float)*proto->valueSize);
		inputs = (uint8_t *)malloc(sizeof(uint8_t)*proto->inputSize);
		outputs = (uint8_t *)malloc(sizeof(uint8_t)*proto->outputSize);
	}

	Module(ModuleProto *proto, uint8_t id, float *values, uint8_t* inputs, uint8_t* outputs);

	ModuleProto *proto;
	uint8_t id;
	float *values;
	uint8_t* inputs;
	uint8_t* outputs;
};

#endif /* MODEL_MODULE_H_ */
