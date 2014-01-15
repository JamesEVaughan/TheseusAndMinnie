/****************************
The TaM_Actor abstract base class. This is for any drawn object that moves on 
the screen. Actor should know where it is in an 2d-coordinate system.
*****************************/
#ifndef TAM_ACTOR
#define TAM_ACTOR

#include "TaM_Drawable.h"

enum TaM_Directions {
	ad_Wait = 0,
	ad_North,
	ad_East,
	ad_South,
	ad_West,
	ad_END_LIST};

class TaM_Actor : public TaM_Drawable {
public:
	// Moves actor one space in the indicated direction
	virtual void move(TaM_Directions dir) = 0;

	// Actor needs to be moved, message to game state
	virtual bool needsMoved() = 0;

	// Current location
	virtual TaM_IntVector location() = 0;
};

#endif