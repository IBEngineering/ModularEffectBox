/*
 * gui.h
 *
 *  Created on: 17 jan. 2018
 *      Author: MisterCavespider
 */

#ifndef GUI_H_
#define GUI_H_

#define GUI_SELECTOR_TYPE uint8_t

typedef struct selector	selector_t;

struct selector
{
	GUI_SELECTOR_TYPE curr;
	GUI_SELECTOR_TYPE last;
};


#endif /* GUI_H_ */
