/*
 * model.h
 *
 *  Created on: 25 dec. 2017
 *      Author: MisterCavespider
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "Audio.h"
#include "model_module_prototype.h"
#include "model_module.h"
#include "model_value.h"
#include <string.h>
#include <stdint.h>

void allocateForModules(uint8_t size);

void addModule(Module *module);
Module *putModule(Module *module);
Module *getModule(int index);

void bakeModules();
bool containsInput(Module *m, uint8_t input);

uint8_t getSize();

#endif /* MODEL_H_ */
