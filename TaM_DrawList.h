/*********************************
	This is the header file for the TaM_DrawList class. A DrawList is a singly-
	linked list of Drawables used to handle redraw events.
**********************************/
#ifndef TAM_DRAWLIST
#define TAM_DRAWLIST

#include "TaM_defHeaders.h"
#include "TaM_Drawable.h"

class TaM_DrawList {
private:
	// Nested class node
	class TaM_DrawNode {
	private:
		TaM_Drawable *obj;
		TaM_DrawNode *next;
	
		// Transformation matrices
		GLfloat trans[2];
		GLfloat scale[2];

		friend class TaM_DrawList;

	public:
		TaM_DrawNode(TaM_Drawable *ptrDraw) {
			obj = ptrDraw;
			next = NULL;
		}
	};

	TaM_DrawNode *head;
	TaM_DrawNode *tail;

public:
	// Constructors/destructors
	TaM_DrawList() {head = tail = NULL;}
	~TaM_DrawList();

	// Adds a drawable object to the list
	void addDrawable(TaM_Drawable *dr, GLfloat transX, GLfloat transY, GLfloat scaleX, GLfloat scaleY);

	// Translates an object in list, does nothing if object is not in the list
	void transNode(TaM_Drawable *dr, GLfloat transX, GLfloat transY);

	// Draws everything in the list
	void redraw();
};



#endif