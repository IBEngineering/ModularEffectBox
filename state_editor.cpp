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
	if(m == NULL) m = getModule(0);	// Get first module to prevent npe

	currselect = -1;	//Impossible
	int32_t read = encc3->r.read()/4;
	if(read >= 0 && read <= 16)	// Currently hardcoded to 16
	{
		currselect = read;
	}

	if(PRESSEDP(encc1) > 0 || PRESSEDP(encc2) > 0)
	{
		u8g2->clearBuffer();
		stateManager->setCurrentState(0);
		return;
	}
	else if(PRESSEDP(encc3) > 0 && currselect >= 0)
	{
		zoomed = !zoomed;
		if(zoomed)	onZoomedIn();
		else		onZoomedOut();
	}

	if(zoomed)
	{
		whileZoomedIn();
	}
	else
	{
		u8g2->clearBuffer();
		uint8_t x,y,w;

		Module *currentModule = getModule(0);	//TODO: hacky
		x = 0 - encc1->r.read()/4 - encc2->r.read()/4;
		y = 32;	//Middle

		w = drawModule(x,y,currentModule,true);
		if(currentModule->id == currselect)
		{
			u8g2->setDrawColor(2);
			u8g2->drawBox(x+1, y-3, w+1, 7);
			u8g2->setDrawColor(1);
		}

		currentModule = getModule(currentModule->outputs[0][0]);
		x = x+2+w+8;
		y = 32;

		w = drawModule(x,y,currentModule,true);
		if(currentModule->id == currselect)
		{
			u8g2->setDrawColor(2);
			u8g2->drawBox(x+1, y-3, w+1, 7);
			u8g2->setDrawColor(1);
		}

		currentModule = getModule(currentModule->outputs[0][0]);
		x = x+2+w+8;
		y = 32;

		w = drawModule(x,y,currentModule,true);
		if(currentModule->id == currselect)
		{
			u8g2->setDrawColor(2);
			u8g2->drawBox(x+1, y-3, w+1, 7);
			u8g2->setDrawColor(1);
		}

		currentModule = getModule(currentModule->outputs[0][0]);
		x = x+2+w+8;
		y = 32;

		w = drawModule(x,y,currentModule,false);
		if(currentModule->id == currselect)
		{
			u8g2->setDrawColor(2);
			u8g2->drawBox(x+1, y-3, w+1, 7);
			u8g2->setDrawColor(1);
		}
	}

	lastselect = currselect;
}

void EditorState::onZoomedIn()
{
	// Update currently selected module
	// Also 'locks' it
	m = getModule(currselect);

	uint8_t n = 0;	// cursor position
	uint8_t i = 0;	// iterated value

	u8g2->enableUTF8Print();
	u8g2->clearBuffer();
	u8g2->setCursor(1, n+=5);
	u8g2->print(m->proto->title);
	u8g2->setCursor(1, n+=5);
	u8g2->print("----");
	for(i = 0; i < m->proto->valueCount; i++)
	{
		u8g2->setCursor(1, n+=6);	// Give it an extra pixel for spacing
		u8g2->print(m->proto->names[i]);
		u8g2->setCursor(100, n);	//28 px should be enough
		u8g2->print(m->values[i].value());
	}

	encc3->r.write(0);

	// Make sure to have change
	currselect = 0;
	lastselect = -1;
}

void EditorState::whileZoomedIn()
{
	/*
	 * If there's a change in selection,
	 * deselect the last one and select
	 * the current one
	 */
	if(currselect != lastselect)
	{
		u8g2->setDrawColor(2);
		// Remove last select
		if(lastselect >= 0 && lastselect < m->proto->valueCount)
		{
			u8g2->drawBox(0, 10 + 6*lastselect, 128, 7);
		}

		// Set new select
		if(currselect >= 0 && currselect < m->proto->valueCount)
		{
			u8g2->drawBox(0, 10 + 6*currselect, 128, 7);
		}
		u8g2->setDrawColor(1);
	}

	/*
	 * If the value is to be changed, erase
	 * letters and draw them again.
	 */

	if(currselect >= 0 && currselect < m->proto->valueCount)	// is valid?
	{
		/*
		 * The first button does 1 step
		 */
		if(encc1->r.read()/4 != 0)
		{
			// Set value
			m->values[currselect] += encc1->r.read()/4;
			encc1->r.write(0);

			// Erase area
//			u8g2->setDrawColor(1);
			u8g2->drawBox(100, 10 + 6*currselect, 28, 7);

			//Draw text in
			u8g2->setDrawColor(0);
			u8g2->setCursor(100, 16 + 6*currselect);	//28 px should be enough
			u8g2->print(m->values[currselect].value());
			u8g2->setDrawColor(1);
		}

		/*
		 * The second button does 10 steps
		 */
		if(encc2->r.read()/4 != 0)
		{
			// Set value
			m->values[currselect] += encc2->r.read()/4 * 10;
			encc2->r.write(0);

			// Erase area
//			u8g2->setDrawColor(1);
			u8g2->drawBox(100, 10 + 6*currselect, 28, 7);

			//Draw text in
			u8g2->setDrawColor(0);
			u8g2->setCursor(100, 16 + 6*currselect);	//28 px should be enough
			u8g2->print(m->values[currselect].value());
			u8g2->setDrawColor(1);
		}
	}

	// Only clear a small area for debug
	u8g2->setDrawColor(0);
	u8g2->drawBox(0, 40, 128, 24);
	u8g2->setDrawColor(1);

	char buf[40];

	sprintf(buf, "c:%d, l:%d", currselect, lastselect);
	u8g2->drawStr(0, 58, buf);
}

void EditorState::onZoomedOut()
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

