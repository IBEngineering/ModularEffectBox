/*
 * model_module.cpp
 *
 *  Created on: 25 dec. 2017
 *      Author: MisterCavespider
 */

#include "model_module.h"

Module::Module()
{
	id = -1;										// invalid
	values = new BoundedValue[1];					// one value
	inputs = new uint8_t[1];						// one port
	outputs = new uint8_t[OUTPUTCONNECTIONS];		// one port, OUTPUTCONNECTIONS connections
	proto = NULL;									// null pointer
}

Module::Module(ModuleProto *proto, uint8_t id)
{
	this->proto = proto;
	this->id = id;
	values = new BoundedValue[proto->valueCount];
	inputs = new uint8_t[proto->inputCount];
	outputs = new uint8_t[proto->inputCount * OUTPUTCONNECTIONS];
}

Module::Module(ModuleProto *proto, uint8_t id, BoundedValue *values, uint8_t* inputs, uint8_t* outputs)
{
	this->proto = proto;
	this->id = id;
	this->values = values;
	this->inputs = inputs;
	this->outputs = outputs;
}
