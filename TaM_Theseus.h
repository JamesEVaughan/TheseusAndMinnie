/*********************************
	This is the header file for TaM_Theseus. This class represents our player
	character.
**********************************/
#ifndef TAM_THESEUS
#define TAM_THESEUS

#include "TaM_defHeaders.h"
#include "TaM_Actor.h"

class TaM_Theseus : public TaM_Actor {
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


	// Actor functions
	virtual TaM_IntVector getLoc() {return *pos;}
	virtual void move(char dir);

	// Drawable functions
	virtual void draw();
};

#endif