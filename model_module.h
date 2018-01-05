/*
 * model_module.h
 *
 *  Created on: 25 dec. 2017
 *      Author: MisterCavespider
 */

#ifndef MODEL_MODULE_H_
#define MODEL_MODULE_H_

#include "model_module_prototype.h"
#include "model_value.h"
#include <stdlib.h>
#include <stdint.h>

class Module
{
public:
	Module() {
		id = -1;	//impossible
		values = new BoundedValue[1];
		inputs = (uint8_t *)malloc(sizeof(uint8_t));
		outputs = (uint8_t **)malloc(sizeof(uint8_t));
		proto = 0;
	}

	Module(ModuleProto *proto, uint8_t id)
	{
		this->proto = proto;
		this->id = id;
		values = new BoundedValue[proto->valueCount];
		inputs = (uint8_t *)malloc(sizeof(uint8_t)*proto->inputCount);
		outputs = (uint8_t **)malloc(sizeof(uint8_t)*proto->outputCount);
	}

	Module(ModuleProto *proto, uint8_t id, BoundedValue *values, uint8_t* inputs, uint8_t** outputs);

	ModuleProto *proto;
	uint8_t id;
	BoundedValue *values;
	uint8_t* inputs;		// An array of input ports, each with one link
	uint8_t** outputs;		// An array of input ports, each with several outputs
};

#endif /* MODEL_MODULE_H_ */
