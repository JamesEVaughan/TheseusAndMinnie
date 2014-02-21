/*********************************
	This is the header file for the TaM_GameDisplay class. GameDisplay handles
	the drawing of all aspects of the game world onto the screen.
**********************************/
#ifndef TAM_GAMEDISPLAY
#define TAM_GAMEDISPLAY

#include "TaM_defHeaders.h"

// Objects to draw
#include "TaM_Map.h"
#include "TaM_ActorDrawList.h"

class TaM_GameDisplay {
private:
	// What we need to draw
	TaM_Map *actMap;			// The active map
	TaM_ActorDrawList *actors;	// The actors on screen

	// Viewport definitions
	TaM_IntVector vpOrigin;		// The origin (in the active window) of the viewport alloted to GameDisplay
	TaM_IntVector vpDim;		// The dimensions of the viewport alloted to GameDisplay

public:
	// Constructors/destructors
	TaM_GameDisplay(TaM_IntVector coord, TaM_IntVector dimens); // Takes the view port coordinates and dimensions
	TaM_GameDisplay();
	~TaM_GameDisplay();

	// Update parts
	void addMap(TaM_Map *m) {actMap = m;}
	void addActor(TaM_Actor *act) {actors->addActor(act, actMap->getTopLeft());}

	// Most important function!!!!
	void redrawDisplay();
};


#endif