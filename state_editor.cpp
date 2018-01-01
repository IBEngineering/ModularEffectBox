/*
 * state_editor.cpp
 *
 *  Created on: 29 dec. 2017
 *      Author: MisterCavespider
 */

#include "state_editor.h"

void EditorState::setup()
{
	u8g2->setFont(u8g2_font_4x6_tr);

	encc1->r.write(0);
	encc2->r.write(0);
	encc3->r.write(0);
}

void EditorState::loop()
{
	int32_t select = encc3->r.read()/4;

	if(PRESSEDP(encc1) > 0 || PRESSEDP(encc2) > 0)
	{
		u8g2->clearBuffer();
		stateManager->setCurrentState(0);
	}
	else if(PRESSEDP(encc3) > 0 && select >= 0)
	{
		zoomed = !zoomed;
		onZoomedIn(select);
	}
	else if(zoomed)
	{
		whileZoomedIn(select);
	}
	else
	{
		u8g2->clearBuffer();
		uint8_t x,y,w;

		Module *currentModule = getModule(0);	//TODO: hacky
		x = 0 - encc1->r.read()/4 - encc2->r.read()/4;
		y = 32;	//Middle

		w = drawModule(x,y,currentModule,true);
		if(currentModule->id == select)
		{
			u8g2->setDrawColor(2);
			u8g2->drawBox(x+1, y-3, w+1, 7);
			u8g2->setDrawColor(1);
		}

		currentModule = getModule(currentModule->outputs[0]);
		x = x+2+w+8;
		y = 32;

		w = drawModule(x,y,currentModule,true);
		if(currentModule->id == select)
		{
			u8g2->setDrawColor(2);
			u8g2->drawBox(x+1, y-3, w+1, 7);
			u8g2->setDrawColor(1);
		}

		currentModule = getModule(currentModule->outputs[0]);
		x = x+2+w+8;
		y = 32;

		w = drawModule(x,y,currentModule,true);
		if(currentModule->id == select)
		{
			u8g2->setDrawColor(2);
			u8g2->drawBox(x+1, y-3, w+1, 7);
			u8g2->setDrawColor(1);
		}

		currentModule = getModule(currentModule->outputs[0]);
		x = x+2+w+8;
		y = 32;

		w = drawModule(x,y,currentModule,false);
		if(currentModule->id == select)
		{
			u8g2->setDrawColor(2);
			u8g2->drawBox(x+1, y-3, w+1, 7);
			u8g2->setDrawColor(1);
		}
	}
}

void EditorState::onZoomedIn(int32_t select)
{
//	uint8_t n = 0;
//	uint8_t i = 0;
//
//	u8g2->clearBuffer();
//	u8g2->setCursor(0, n+=5);
//	u8g2->print(getModule(select)->proto->title);
//	u8g2->setCursor(0, n+=5);
//	u8g2->print("----");
//	for(i = 0; i < getModule(select)->proto->valueSize; i++)
//	{
//		u8g2->setCursor(0, n+=6);	// Give it an extra pixel for spacing
//		u8g2->print(getModule(select)->proto->names[i]);
//		u8g2->setCursor(100, n);	//28 px should be enough
//		u8g2->print(getModule(select)->values[i]);
//	}
}

void EditorState::whileZoomedIn(int32_t select)
{
	uint8_t n = 0;
	uint8_t i = 0;

	u8g2->clearBuffer();
	u8g2->setCursor(0, n+=5);
	u8g2->print(getModule(select)->proto->title);
	u8g2->setCursor(0, n+=5);
	u8g2->print("----");
	for(i = 0; i < getModule(select)->proto->valueSize; i++)
	{
		u8g2->setCursor(0, n+=6);	// Give it an extra pixel for spacing
		u8g2->print(getModule(select)->proto->names[i]);
		u8g2->setCursor(100, n);	//28 px should be enough
		u8g2->print(getModule(select)->values[i]);
	}

	if(select > 0 && select < getModule(select)->proto->valueSize)
	{
		u8g2->setDrawColor(2);
		u8g2->drawBox(0, 10, 128, 7);
		u8g2->setDrawColor(1);
	}
}

void EditorState::onZoomedOut(int32_t select)
{

}

uint8_t EditorState::drawModule(int x, int y, Module *module, bool line)
{
	uint8_t w = u8g2->drawStr(x+2, y+3, module->proto->title);
	u8g2->drawFrame(x, y-4, w+3, 9);
	if(line) u8g2->drawLine(x+3+w, y, x+2+w+7, 32);
	return w;
}

EditorState::~EditorState()
{
	// TODO Auto-generated destructor stub
}

