/****************************
	This is the header for TaM_LineList. This class manages a group of 
	independent lines to be drawn on screen. Mainly used as a helper for 
	objects extending TaM_Drawable. All lines will be drawn of the same color, so
	use other LineList's for different colors. Don't like it? Tough nuggie!
*****************************/
#ifndef TAM_LINE_LIST
#define TAM_LINE_LIST

#ifndef TAM_GLFW
#define TAM_GLFW
#include <GLFW\glfw3.h>
#endif

#include "TaM_defHeaders.h"

// I'm honestly not sure if this is good practice or not...
class TaM_LineNode;

class TaM_LineList {
private:
	TaM_LineNode *head;
	TaM_LineNode *tail;
	GLfloat color[3];

public:
	TaM_LineList(GLfloat red, GLfloat green, GLfloat blue);
	~TaM_LineList();

	// Adds a line to the list
	void addLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);

	// Draws the lines to the established context
	void drawLines();
};

class TaM_LineNode {
private:
	GLfloat start[2];
	GLfloat end[2];
	TaM_LineNode *next;
	friend class TaM_LineList;

public:
	TaM_LineNode(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
		start[0] = x1; start[1] = y1;
		end[0] = x2; end[1] = y2;
		next = NULL;
	}
};


#endif