/*********************************
	This is the header file for TaM_Minnie. Minnie is the loveable minotaur 
	trapped in the labyrinth with Theseus. Isn't she just just the cutest! ^_^
**********************************/
#ifndef TAM_MINNIE
#define TAM_MINNIE

#include "TaM_defHeaders.h"

#include "TaM_Actor.h"

class TaM_Minnie : public TaM_Actor {
private:
	TaM_IntVector *pos;  // Current position on the map
	GLfloat marker[TAM_MARKER_VERTS][2];  // An array for the marker vers


	// Helper functs
	void buildMarker();  // Builds the marker

public:
	// constructors/destructors & initializers
	TaM_Minnie();
	~TaM_Minnie();

	void init(TaM_IntVector start);

	// Actor functs
	virtual TaM_IntVector getLoc() {return *pos;}
	virtual void move(char dir);

	// Drawable functs
	virtual void draw();
};

#endif