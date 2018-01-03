/*
 * model_value.cpp
 *
 *  Created on: 1 jan. 2018
 *      Author: MisterCavespider
 */

#include "model_value.h"

BoundedValue::BoundedValue()
{
	this->min = -1.0;
	this->step = 0.1;
	this->max = 1.0;
	this->val = 0.0;
}

BoundedValue::BoundedValue(float min, float step, float max)
{
	this->min = min;
	this->step = step;
	this->max = max;
	this->val = 0.0;
}

BoundedValue::BoundedValue(float min, float step, float max, float val)
{
	this->min = min;
	this->step = step;
	this->max = max;
	this->val = val;
}
float BoundedValue::minimum()	{return this->min;}
float BoundedValue::stepSize()	{return this->step;}
float BoundedValue::maximum()	{return this->max;}
float BoundedValue::value()		{return this->val;}

BoundedValue BoundedValue::operator=(float f)
{
	this->val = f;

	if(this->val > max) this->val = max;
	if(this->val < min) this->val = min;

	return *this;
}

BoundedValue BoundedValue::operator+=(float val)
{
	this->val += val;

	if(this->val > max) this->val = max;
	if(this->val < min) this->val = min;

	return *this;
}

BoundedValue BoundedValue::operator+=(int32_t steps)
{
	if(steps == 0) return *this;

	val += step * steps;

	if(this->val > max) this->val = max;
	if(this->val < min) this->val = min;

	return *this;
}

bool BoundedValue::operator==(float f)	{return f == val;}
bool BoundedValue::operator!=(float f)	{return f != val;}
bool BoundedValue::operator>(float f)	{return f > val;}
bool BoundedValue::operator>=(float f)	{return f >= val;}
bool BoundedValue::operator<(float f)	{return f < val;}
bool BoundedValue::operator<=(float f)	{return f <= val;}

BoundedValue::~BoundedValue()
{
	// TODO Auto-generated destructor stub
}

