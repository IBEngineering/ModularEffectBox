/*
 * model.h
 *
 *  Created on: 25 dec. 2017
 *      Author: MisterCavespider
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "model_module_prototype.h"
#include "model_module.h"
#include <string.h>
#include <stdint.h>

void allocateForProtos(uint8_t size);
void allocateForModules(uint8_t size);

int addProto(ModuleProto *proto);

void addModule(int protoIndex);
void addModule(Module *module);

Module *getModule(int index);

#endif /* MODEL_H_ */
