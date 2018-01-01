/*
 * model_value.h
 *
 *  Created on: 1 jan. 2018
 *      Author: borgert
 */

#ifndef MODEL_VALUE_H_
#define MODEL_VALUE_H_

class BoundedValue {
public:
	BoundedValue();

	BoundedValue operator+(float f);

	virtual ~BoundedValue();
};

#endif /* MODEL_VALUE_H_ */
