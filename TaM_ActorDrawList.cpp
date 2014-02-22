/*********************************
	The implementation file for the TaM_ActorDrawList class.
**********************************/

#include "TaM_defHeaders.h"
#include "TaM_ActorDrawList.h"

TaM_ActorDrawList::~TaM_ActorDrawList() {
	while (head != NULL) {
		TaM_ActorDrawNode *deathRow = head;
		head = head->next;
		delete deathRow;
	}
}

/***********************
	addDrawable()
	Adds a new Actor-type object to the list, with translation and scale factors
************************/
void TaM_ActorDrawList::addActor(TaM_Actor *act, TaM_FloatVector tlCoord) {
	// Sanity check
	if (!act) {
		// No object, break
		return;
	}

	TaM_ActorDrawNode *tempy = new TaM_ActorDrawNode(act);

	// Zero out the matrix
	for (int i = 0; i < 16; i++) {
		tempy->trans[i] = 0.f;
	}

	// Setup scale transformation...
	tempy->trans[0] = TAM_SQUARE_SIZE;  // Scale in x-axis
	tempy->trans[5] = TAM_SQUARE_SIZE;  // Scale in y-axis

	// ...translate to center of map coordinates (0, 0)...
	tempy->trans[12] = tlCoord.get1() + TAM_SQUARE_SIZE/2.f;  // Translation in x-axis
	tempy->trans[13] = tlCoord.get2() - TAM_SQUARE_SIZE/2.f;  // Translation in y-axis

	// ...and retain the homogeneous value
	tempy->trans[15] = 1.f;

	if (head == NULL) {
		head = tempy;
		tail = head;
	}
	else {
		tail->next = tempy;
		tail = tempy;
	}
}

void TaM_ActorDrawList::drawAll() {
	TaM_ActorDrawNode *tempy = head;
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	while (tempy) {
		TaM_IntVector help = tempy->loc();
		glLoadMatrixf(tempy->trans);
		glTranslatef((float)help.get1(), -(float)help.get2(), 0.f);
		tempy->draw();

		tempy = tempy->next;
	}

	glPopMatrix();
}