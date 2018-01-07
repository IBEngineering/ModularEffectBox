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

////Amount of connected modules per port
//#define OUTPUTCONNECTIONS	3
//
///**
// * What info is needed before allocation:
// * - prototype (for counts)
// *(- desired amount of connections per output): currently hardcoded
// *
// * The inputs array looks like this: {port, port, port}
// * The outputs array looks like this: {port0, port0, port0, port1, port1, port1, port2, ... }
// *   or: {{port0connections}, {port1connections}, {port2connections}}
// */
//class Module
//{
//public:
//	Module();
//	Module(ModuleProto *proto, uint8_t id);
//	Module(ModuleProto *proto, uint8_t id, BoundedValue *values, uint8_t* inputs, uint8_t* outputs);
//
//	ModuleProto *proto;
//	uint8_t id;
//	BoundedValue *values;
//	uint8_t* inputs;		// An array of input ports, each with one link
//	uint8_t* outputs;		// An array of input ports, each with several outputs,
//							//   but used as a pseudo-multidimensional array because c++
//};

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

	uint8_t id();
	BoundedValue *values();
	uint8_t *inputs();
	uint8_t *outputs();
};

#endif /* MODEL_MODULE_H_ */
