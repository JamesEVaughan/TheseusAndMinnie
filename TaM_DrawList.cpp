/*********************************
	The implementation file for the TaM_DrawList class.
**********************************/

#include "TaM_defHeaders.h"
#include "TaM_DrawList.h"

TaM_DrawList::~TaM_DrawList() {
	while (head != NULL) {
		TaM_DrawNode *deathRow = head;
		head = head->next;
		delete deathRow;
	}
}

// Finish later
void TaM_DrawList::addDrawable(TaM_Drawable *dr, GLfloat transX, GLfloat transY, GLfloat scaleX, GLfloat scaleY) {
}

void TaM_DrawList::transNode(TaM_Drawable *dr, GLfloat transX, GLfloat transY) {
}

void TaM_DrawList::redraw() {
}