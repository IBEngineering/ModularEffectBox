/*
 * model_value.h
 *
 *  Created on: 1 jan. 2018
 *      Author: MisterCavespider
 */

#ifndef MODEL_VALUE_H_
#define MODEL_VALUE_H_

#include <stdint.h>

class BoundedValue {
public:
	BoundedValue();
	BoundedValue(float min, float step, float max);
	BoundedValue(float min, float step, float max, float val);

	float minimum();
	float stepSize();
	float maximum();
	float value();

	BoundedValue operator=(float f);

	BoundedValue operator+=(float f);
	BoundedValue operator+=(int32_t steps);

	bool operator==(float f);
	bool operator!=(float f);
	bool operator>(float f);
	bool operator>=(float f);
	bool operator<(float f);
	bool operator<=(float f);

	virtual ~BoundedValue();
private:
	float min, step, max, val;
};

#endif /* MODEL_VALUE_H_ */
