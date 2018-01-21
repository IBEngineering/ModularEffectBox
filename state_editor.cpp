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

	selI.curr = -1;
	selI.last = -1;
	selO.curr = 0;
	selO.last = 0;

	m = getModule(0);
	onZoomedOut();
}

void EditorState::loop()
{
	// Go out
	if(PRESSEDP(encc1) > 0 || PRESSEDP(encc2) > 0)
	{
		u8g2->clearBuffer();
		stateManager->setCurrentState(0);
		return;
	}

	// Actual loop
	zoomed ? whileZoomedIn() : whileZoomedOut();
}

void EditorState::onZoomedIn()
{
	// Update currently selected module (in zoomOut)
	// Also 'locks' it
//	m = getModule(selO.curr);

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
		u8g2->setCursor(1, n+=6);		// Give it an extra pixel for spacing
		u8g2->print(m->names()[i]);
		u8g2->setCursor(99, n);			//28 px should be enough
		u8g2->print(m->values()[i].value());
	}

	encc3->r.write(0);

	// Make sure it's (il)legal
	selI.curr = -1;
	selI.curr = -1;
}


/*
 * Order:
 * - read curr
 * - validate
 * - update highlight
 * - update value
 */
void EditorState::whileZoomedIn()
{
	if(PRESSEDP(encc3) > 0)
	{
		zoomed = !zoomed;
		if(zoomed)	onZoomedIn();
		else		onZoomedOut();
		return;
	}

	selI.curr = READP(encc3) / 4;
	if(selI.curr >= m->valueCount())
	{
		selI.curr = m->valueCount();
	}

	/*
	 * If there's a change in selection,
	 * deselect the last one and select
	 * the current one
	 */
	if(selI.curr != selI.last)
	{
		u8g2->setDrawColor(2);
		// Remove last select
		if(selI.last >= 0 && selI.last < m->valueCount())
		{
			u8g2->drawBox(0, 10 + 6*selI.last, 128, 7);
		}

		// Set new select
		if(selI.curr >= 0 && selI.curr < m->valueCount())
		{
			u8g2->drawBox(0, 10 + 6*selI.curr, 128, 7);
		}
		u8g2->setDrawColor(1);
	}

	/*
	 * If the value is to be changed, erase
	 * letters and draw them again.
	 */

	/*
	 * The first button does 1 step
	 */
	if(READP(encc1)/4 != 0)
	{
		// Set value
		m->values()[selI.curr] += READP(encc1)/4;
		encc1->r.write(0);

		// Erase area
//			u8g2->setDrawColor(1);
		u8g2->drawBox(99, 10 + 6*selI.curr, 28, 7);

		//Draw text in
		u8g2->setDrawColor(0);
		u8g2->setCursor(99, 16 + 6*selI.curr);	//28 px should be enough
		u8g2->print(m->values()[selI.curr].value());
		u8g2->setDrawColor(1);
	}

	/*
	 * The second button does 10 steps
	 */
	if(READP(encc2)/4 != 0)
	{
		// Set value
		m->values()[selI.curr] += READP(encc2)/4 * 10;
		encc2->r.write(0);

		// Erase area
//			u8g2->setDrawColor(1);
		u8g2->drawBox(99, 10 + 6*selI.curr, 28, 7);

		//Draw text in
		u8g2->setDrawColor(0);
		u8g2->setCursor(99, 16 + 6*selI.curr);	//28 px should be enough
		u8g2->print(m->values()[selI.curr].value());
		u8g2->setDrawColor(1);
	}

	// Only clear a small area for debug
	u8g2->setDrawColor(0);
	u8g2->drawBox(0, 40, 128, 24);
	u8g2->setDrawColor(1);

	char buf[40];

	sprintf(buf, "c:%d, l:%d", selI.curr, selI.last);
	u8g2->drawStr(0, 58, buf);

	selI.last = selI.curr;
}

void EditorState::onZoomedOut()
{
	u8g2->clearBuffer();	// TODO: check if necessary

//	m = getModule(0);
	drawModule(m);
	highlightModule(m);
}

void EditorState::whileZoomedOut()
{
	selO.curr = encc3->r.read()/4;

	if(PRESSEDP(encc3) > 0)
	{

		if(selO.curr < 0)
		{
			u8g2->clearBuffer();
			m = getModule(m->inputs()[-selO.curr-1]);
			drawModule(m);
			highlightModule(m);
			selO.curr = 0;
			selO.last = 0;
			WRITEP(encc3, 0);
		}
		else if(selO.curr > 0)
		{
			u8g2->clearBuffer();
			m = getModule(m->outputs()[selO.curr-1]);
			drawModule(m);
			highlightModule(m);
			selO.curr = 0;
			selO.last = 0;
			WRITEP(encc3, 0);
		}
		else if(selO.curr == 0) {
			zoomed = !zoomed;
			if(zoomed)	onZoomedIn();
			else		onZoomedOut();
			return;
		}
	}

	if(selO.curr != selO.last)
	{
		// Remove last select
		if(selO.last < 0)
		{
			highlightModule(getModule(m->inputs()[-selO.last-1]));
		}
		else if(selO.last == 0)
		{
			highlightModule(m);
		}
		else if(selO.last > 0)
		{
			highlightModule(getModule(m->outputs()[selO.last-1]));
		}

		// Set new select
		if(selO.curr < 0)
		{
			highlightModule(getModule(m->inputs()[-selO.curr-1]));
		}
		else if(selO.curr == 0)
		{
			highlightModule(m);
		}
		else if(selO.curr > 0)
		{
			highlightModule(getModule(m->outputs()[selO.curr-1]));
		}
	}

	char buf[40];
	sprintf(buf, "c:%d, l:%d", selO.curr, selO.last);
	u8g2->drawStr(32, 58, buf);
	selO.last = selO.curr;
}

void EditorState::highlightModule(Module *m)
{
	drawdata_t dd = mdd[m->id()];
	u8g2->setDrawColor(2);
	u8g2->drawBox(dd.x-1, dd.y-3, dd.w+2, 7);
	u8g2->setDrawColor(1);
}

uint8_t used(uint8_t *arr, uint8_t size)
{
	uint8_t c = 0;
	for(uint8_t i = 0; i < size; i++)
	{
		if(arr[i] < getSize())
		{
			c++;	// Nice
		}
	}
	return c;
}

void EditorState::drawModule(Module *m)
{
	// Draw the name in the middle

	drawdata_t ddm = mdd[m->id()];
	ddm.w = u8g2->getStrWidth(m->title());
	ddm.x = (128-ddm.w)/2;
	ddm.y = 32;
	mdd[m->id()] = ddm;
	uint8_t i = 0;

	/* USES BRACKETS SETTING */
	// *
	u8g2->drawStr(ddm.x, ddm.y+3, m->title());
	// [
	u8g2->drawHLine(ddm.x-2, ddm.y-4, 4);
	u8g2->drawVLine(ddm.x-2, ddm.y-3, 7);
	u8g2->drawHLine(ddm.x-2, ddm.y+4, 4);
	// ]
	u8g2->drawHLine(ddm.x+ddm.w-2, ddm.y-4, 4);
	u8g2->drawVLine(ddm.x+ddm.w+1, ddm.y-3, 7);
	u8g2->drawHLine(ddm.x+ddm.w-2, ddm.y+4, 4);

	// Draw the inputs
	uint8_t drawn = 0;
	uint8_t toDraw = used(m->inputs(), m->inputCount());
	for(i = 0; i < m->inputCount(); i++)
	{
		uint8_t tid = m->inputs()[i];
		if(tid < getSize())
		{
			Module *t = getModule(tid);
			drawdata_t ddt = mdd[tid];
			ddt.w = u8g2->getStrWidth(t->title());
			ddt.x = (128-ddm.w)/2 - (7+ddt.w);
			ddt.y = 32 + (toDraw*9+toDraw-1)/2-4 -10*drawn;
			mdd[tid] = ddt;

			/* USES BRACKETS SETTING */
			// *
			u8g2->drawStr(ddt.x, ddt.y+3, t->title());
			// ]
			u8g2->drawHLine(ddt.x+ddt.w-2, ddt.y-4, 4);
			u8g2->drawVLine(ddt.x+ddt.w+1, ddt.y-3, 7);
			u8g2->drawHLine(ddt.x+ddt.w-2, ddt.y+4, 4);

			drawn++;
		}
	}

	// Draw the outputs
	drawn = 0;
	toDraw = used(m->outputs(), m->outputCount() * m->paralsCount());
	for(i = 0; i < m->outputCount() * m->paralsCount(); i++)
	{
		uint8_t tid = m->outputs()[i];
		if(tid < getSize())
		{
			Module *t = getModule(tid);
			drawdata_t ddt = mdd[tid];
			ddt.w = u8g2->getStrWidth(t->title());
			ddt.x = (128-ddm.w)/2 + (7+ddm.w);
			ddt.y = 32 + (toDraw*9+toDraw-1)/2-4 -10*drawn;
			mdd[tid] = ddt;

			/* USES BRACKETS SETTING */
			// *
			u8g2->drawStr(ddt.x, ddt.y+3, t->title());
			// [
			u8g2->drawHLine(ddt.x-2, ddt.y-4, 4);
			u8g2->drawVLine(ddt.x-2, ddt.y-3, 7);
			u8g2->drawHLine(ddt.x-2, ddt.y+4, 4);

			drawn++;
		}
	}
}
