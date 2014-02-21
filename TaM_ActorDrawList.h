/*********************************
	This is the header file for the TaM_ActorDrawList class. A DrawList is a singly-
	linked list of Drawables used to handle redraw events.
**********************************/
#ifndef TAM_ACTORDRAWLIST
#define TAM_ACTORDRAWLIST

#include "TaM_defHeaders.h"
#include "TaM_Actor.h"

class TaM_ActorDrawNode;

class TaM_ActorDrawList {
private:
	TaM_ActorDrawNode *head;
	TaM_ActorDrawNode *tail;

public:
	// Constructors/destructors
	TaM_ActorDrawList() {head = tail = NULL;}
	~TaM_ActorDrawList();

	// Adds a Actor object to the list
	void addActor(TaM_Actor *act, TaM_FloatVector tlCoord);

	// Draws everything in the list
	void drawAll();
};

// Nested class node
class TaM_ActorDrawNode {
private:
	TaM_Actor *act;
	TaM_ActorDrawNode *next;
	
	// Transformation matrix
	GLfloat trans[16];

	friend class TaM_ActorDrawList;

public:
	TaM_ActorDrawNode(TaM_Actor *ptrDraw) {
		act = ptrDraw;
		next = NULL;
	}
	
	// Calls the act's draw()
	void draw() {act->draw();}

	// Accesses act's getLoc()
	TaM_IntVector loc() {return act->getLoc();}
};


#endif