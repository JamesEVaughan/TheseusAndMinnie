/*********************************
	This is the implementation file for TaM_GameDisplay.
**********************************/

#include "TaM_GameDisplay.h"

TaM_GameDisplay::TaM_GameDisplay() {
	actMap = NULL;
	actors = new TaM_ActorDrawList();
}

TaM_GameDisplay::TaM_GameDisplay(TaM_IntVector coord, TaM_IntVector dimens) {
	actMap = NULL;
	actors = new TaM_ActorDrawList();

	vpOrigin.set1(coord.get1());
	vpOrigin.set2(coord.get2());

	vpDim.set1(dimens.get1());
	vpDim.set2(dimens.get2());
}

TaM_GameDisplay::~TaM_GameDisplay() {
	delete actors;
}

void TaM_GameDisplay::redrawDisplay() {
	// First things first, setup the viewport
	glViewport(vpOrigin.get1(), vpOrigin.get2(), vpDim.get1(), vpDim.get2());

	// Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// We only bother drawing if there's a map
	if (!actMap) {
		return;
	}

	actMap->draw();
	actors->drawAll();
}