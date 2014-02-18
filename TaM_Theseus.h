/*********************************
	This is the header file for TaM_Theseus. This class represents our player
	character.
**********************************/
#ifndef TAM_THESEUS
#define TAM_THESEUS

#include "TaM_defHeaders.h"
#include "TaM_Drawable.h"

class TaM_Theseus : public TaM_Drawable {
private:
	TaM_IntVector *pos; // Grid position on the map
	GLfloat marker[TAM_MARKER_VERTS][2];  // An array of vertices

	// Builds the marker array
	void buildMarker();

public:
	// Constructors/destructors & initializers
	TaM_Theseus();
	~TaM_Theseus();

	void init(TaM_IntVector start);

	// Draw specific functions
	virtual void draw();

	// Accessors
	TaM_IntVector getLoc() {return *pos;}
};

#endif