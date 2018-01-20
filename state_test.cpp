/*
 * state_test.cpp
 *
 *  Created on: 1 jan. 2018
 *      Author: MisterCavespider
 */

#include "model.h"
#include "state_test.h"

void TestState::setup()
{

}

void TestState::loop()
{
	int32_t read = 0;

	if(PRESSEDP(encc1) > 0 || PRESSEDP(encc2) > 0 || PRESSEDP(encc3) > 0)
	{
		u8g2->clearBuffer();
		stateManager->setCurrentState(0);
		return;
	}

	read = READP(encc1)/4;
	if(read != 0)
	{
		bv += read;
		WRITEP(encc1,0);
	}
	read = encc2->r.read()/4;
	if(encc2->r.read()/4 != 0)
	{
		bv += encc2->r.read()/4;
		encc2->r.write(0);
	}
	read = encc3->r.read()/4;
	if(encc3->r.read()/4 != 0)
	{
		bv += encc3->r.read()/4;
		encc3->r.write(0);
	}

	u8g2->clearBuffer();
	char buf[64];
	sprintf(buf, "bv: [%0.1f:%0.1f:%0.1f]:%0.1f",
			getModule(1)->values()[0].minimum(), getModule(1)->values()[0].stepSize(),
			getModule(1)->values()[0].maximum(), getModule(1)->values()[0].value());

	u8g2->drawStr(0, 5, buf);
}

TestState::~TestState() {
}

