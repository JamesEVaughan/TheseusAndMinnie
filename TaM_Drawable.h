/**************************** 
This is the header for the TaM_Drawable class. It is an abstract base class for 
any object that is to be drawn onscreen.

*****************************/
#ifndef TAM_DRAWABLE
#define TAM_DRAWABLE

#include "TaM_simpleTypes.h"

class TaM_Drawable
{
public:
	// Draws from object space. Matrix setup is user defined.
	virtual void draw() = 0;

	/* Sets size of draw space to (x, y). Object will be scaled, if 
		isScaled is true. Only portion drawn if false. */
	// Removed, no reason for this to exist.
	//virtual void setSize(TaM_IntVector newSize, bool isScaled) = 0;

	// Returns how big (in pixels) the object is
	virtual TaM_IntVector getSize() = 0;
};

#endif

