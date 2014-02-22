/*********************************
	This is the header for the TaM_Actor class. Actor is an abstract base class
	for any object that is drawn and stores it's position relative to a map.
**********************************/

#ifndef	TAM_ACTOR
#define	TAM_ACTOR

#include "TaM_defHeaders.h"
#include "TaM_Drawable.h"

class TaM_Actor : public TaM_Drawable {
public:
	virtual TaM_IntVector getLoc() = 0; // Returns location on map as an IntVector
	virtual void move(char dir) = 0; // Moves actor one space in dir
};

#endif