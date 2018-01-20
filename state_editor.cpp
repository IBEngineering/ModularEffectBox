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

	WRITEP(encc1, 0);
	WRITEP(encc2, 0);
	WRITEP(encc3, 0);

	mdd = new drawdata_t[getSize()];

	calculateModule(getModule(0), 32);

	currselect = -1;
	lastselect = -1;

	onZoomedOut();
}

void EditorState::loop()
{
	// FIXME: Why is this?
	if(m == NULL) m = getModule(0);	// Get first module to prevent npe

	// Go out
	if(PRESSEDP(encc1) > 0 || PRESSEDP(encc2) > 0)
	{
		u8g2->clearBuffer();
		stateManager->setCurrentState(0);
		return;
	}
	// Zoom
	else if(PRESSEDP(encc3) > 0 && currselect >= 0)
	{
		zoomed = !zoomed;
		if(zoomed)	onZoomedIn();
		else		onZoomedOut();
	}

	// Actual loop
	zoomed ? whileZoomedIn() : whileZoomedOut();
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
	u8g2->print(m->title());
	u8g2->setCursor(1, n+=5);
	u8g2->print("----");
	for(i = 0; i < m->valueCount(); i++)
	{
		u8g2->setCursor(1, n+=6);	// Give it an extra pixel for spacing
		u8g2->print(m->names()[i]);
		u8g2->setCursor(99, n);	//28 px should be enough
		u8g2->print(m->values()[i].value());
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
		if(lastselect >= 0 && lastselect < m->valueCount())
		{
			u8g2->drawBox(0, 10 + 6*lastselect, 128, 7);
		}

		// Set new select
		if(currselect >= 0 && currselect < m->valueCount())
		{
			u8g2->drawBox(0, 10 + 6*currselect, 128, 7);
		}
		u8g2->setDrawColor(1);
	}

	/*
	 * If the value is to be changed, erase
	 * letters and draw them again.
	 */

	if(currselect >= 0 && currselect < m->valueCount())	// is valid?
	{
		/*
		 * The first button does 1 step
		 */
		if(READP(encc1)/4 != 0)
		{
			// Set value
			m->values()[currselect] += READP(encc1)/4;
			encc1->r.write(0);

			// Erase area
//			u8g2->setDrawColor(1);
			u8g2->drawBox(99, 10 + 6*currselect, 28, 7);

			//Draw text in
			u8g2->setDrawColor(0);
			u8g2->setCursor(99, 16 + 6*currselect);	//28 px should be enough
			u8g2->print(m->values()[currselect].value());
			u8g2->setDrawColor(1);
		}

		/*
		 * The second button does 10 steps
		 */
		if(READP(encc2)/4 != 0)
		{
			// Set value
			m->values()[currselect] += READP(encc2)/4 * 10;
			encc2->r.write(0);

			// Erase area
//			u8g2->setDrawColor(1);
			u8g2->drawBox(99, 10 + 6*currselect, 28, 7);

			//Draw text in
			u8g2->setDrawColor(0);
			u8g2->setCursor(99, 16 + 6*currselect);	//28 px should be enough
			u8g2->print(m->values()[currselect].value());
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
	u8g2->clearBuffer();	// TODO: check if necessary
	for(uint8_t i = 0; i < getSize(); i++)
	{
		mdd[i].drawn = false;
	}

	Module *currentModule = getModule(0);	//TODO: hacky
	drawModule(currentModule);	// Recursive
}

void EditorState::whileZoomedOut()
{
	currselect = -1;	// Invalidate
	int32_t read = encc3->r.read()/4;
	if(read >= 0 && read < getSize())
	{
		currselect = read;
	}
	else if(read >= getSize())
	{
		encc3->r.write(getSize()-1);
	}
	else
	{
		encc3->r.write(0);
	}

	if(currselect != lastselect)
		{
			// Remove last select
			if(lastselect >= 0 && lastselect < getSize())
			{
				drawdata_t dd = mdd[lastselect];
				u8g2->setDrawColor(2);
				u8g2->drawBox(dd.x+1, dd.y-3, dd.w-2, 7);
				u8g2->setDrawColor(1);
			}

			// Set new select
			if(currselect >= 0 && currselect < getSize())
			{
				drawdata_t dd = mdd[currselect];
				u8g2->setDrawColor(2);
				u8g2->drawBox(dd.x+1, dd.y-3, dd.w-2, 7);
				u8g2->setDrawColor(1);
			}
		}

		char buf[40];
		sprintf(buf, "c:%d, l:%d", currselect, lastselect);
		u8g2->drawStr(32, 58, buf);
		lastselect = currselect;
}

uint8_t usedOutputs(Module *m)
{
	uint8_t c = 0;
	for(uint8_t i = 0; i < m->outputCount() * m->paralsCount(); i++)
	{
		if(m->outputs()[i] < getSize())
		{
			c++;	// Nice
		}
	}
	return c;
}

bool hasInput(Module *m, uint8_t t)
{
	for(uint8_t i = 0; i < m->inputCount(); i++)
	{
		if(m->inputs()[i] == t) return true;
	}
	return false;
}

/*
 * py is only used as a reference:
 * if all inputs have been calculated,
 * the box will be drawn in the middle.
 * if not, the box will be drawn where
 * advised by the previous box.
 *
 * Mutual recognition is assumed and irrelevant
 */
void EditorState::calculateModule(Module *m, uint8_t py)
{
	// Is this necessary?
	if(mdd[m->id()].calcd)	return;

	uint8_t w = u8g2->getStrWidth(m->title()) + 4;
	uint8_t maxX = 0;
	uint8_t sumY = 0;
	uint8_t ofy = 0;
	bool allCalc = true;
	for(uint8_t i = 0; i < m->inputCount(); i++)
	{
		if(m->inputs()[i] < getSize())
		{
			// Does it have all data?
			if(!mdd[m->inputs()[i]].calcd)	// inputs()[i] is the id in this case
			{
				calculateModule(getModule(m->inputs()[i]), 255);
				allCalc = false;
			}

			// Calculate
			if(mdd[m->inputs()[i]].x + mdd[m->inputs()[i]].w + 6 > maxX)
			{
				maxX = mdd[m->inputs()[i]].x + mdd[m->inputs()[i]].w + 6;
			}
			sumY += mdd[m->inputs()[i]].y;
			ofy++;
		}
	}

	// Write data
	if(allCalc && ofy > 0)
	{
		mdd[m->id()].x = maxX;
		mdd[m->id()].y = (ofy == 1)? py : sumY/ofy;
	}
	else
	{
		mdd[m->id()].x = 0;
		mdd[m->id()].y = py;
	}
	mdd[m->id()].w = w;
	mdd[m->id()].calcd = true;

	// Continue the recursion
	uint8_t usesCalculated = 0;
	uint8_t used = usedOutputs(m);
	for(uint8_t i = 0; i < m->outputCount() * m->paralsCount(); i++)
	{
		Module *t = getModule(m->outputs()[i]);
		if(t != NULL)
		{
			if(used == 1)	// Only one output? Put it to the right
			{
				calculateModule(t, mdd[m->id()].y);
			}
			else	// More outputs? Put them in a stack
			{
				uint8_t yoff = (used*9+used-1)/2-4 -10*usesCalculated;
				calculateModule(t, mdd[m->id()].y + yoff);
				usesCalculated++;
			}
		}
	}
}

/*
 * Mutual recognition is assumed
 */
void EditorState::drawModule(Module *m)
{
	// Is this necessary?
	if(mdd[m->id()].drawn)	return;

	// Shorter syntax = 3 bytes more RAM
	uint8_t x = mdd[m->id()].x + encc1->r.read() + encc2->r.read();
	uint8_t y = mdd[m->id()].y;
	uint8_t w = mdd[m->id()].w;

	// Draw the box
	u8g2->drawStr(x+2, y+3, m->title());
	u8g2->drawFrame(x, y-4, w, 9);

	// Draw lines away from it + Continue the recursion
	for(uint8_t i = 0; i < m->outputCount() * m->paralsCount(); i++)	// Everything it outputs to
	{
		if(m->outputs()[i] < getSize())
		{
			drawdata_t dd = mdd[m->outputs()[i]];
			u8g2->drawLine(x+w, y, dd.x + encc1->r.read() + encc2->r.read(), dd.y);
			drawModule(getModule(m->outputs()[i]));
		}
	}
	mdd[m->id()].drawn = true;
}
