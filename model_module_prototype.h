/*
 * model_module_prototype.h
 *
 *  Created on: 25 dec. 2017
 *      Author: MisterCavespider
 */

#ifndef MODEL_MODULE_PROTOTYPE_H_
#define MODEL_MODULE_PROTOTYPE_H_

#include <stdint.h>
#include <string>
#include <initializer_list>
#include <vector>

class ModuleProto
{
public:
	ModuleProto(){}

	ModuleProto(const char* title, uint8_t valueSize, const char **names, uint8_t inputSize, uint8_t outputSize)
	{
		this->title = title;
		this->valueCount = valueSize;
		this->names = names;
		this->inputCount = inputSize;
		this->outputCount = outputSize;
	}

	const char* title;
	const char **names;
	uint8_t valueCount, inputCount, outputCount;
};

#endif /* MODEL_MODULE_PROTOTYPE_H_ */
