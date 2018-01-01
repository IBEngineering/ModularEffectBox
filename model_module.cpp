/*
 * model_module.cpp
 *
 *  Created on: 25 dec. 2017
 *      Author: borgert
 */

#include "model_module.h"

Module::Module(ModuleProto *proto, uint8_t id, float *values, uint8_t* inputs, uint8_t* outputs)
{
	this->proto = proto;
	this->id = id;
	this->values = values;
	this->inputs = inputs;
	this->outputs = outputs;
}
