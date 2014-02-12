/****************************
	This is the implementation file for TaM_LineList.
*****************************/
/*
#ifndef TAM_GLFW
#define TAM_GLFW
#include <GLFW\glfw3.h>
#endif
*/
#include "TaM_LineList.h"

/***********************
	Constructors & Destructors
	Building shit up just to tear it down.
************************/
TaM_LineList::TaM_LineList(GLfloat red, GLfloat green, GLfloat blue) {
	head = tail = NULL;

	color[0] = red;
	color[1] = green;
	color[2] = blue;
}
TaM_LineList::~TaM_LineList() {
	// Sanity checks
	if (head == NULL) {
		if (tail != NULL) {
			delete tail;
		}
		return;
	}

	while (head != NULL) {
		TaM_LineNode *deathRow = head;
		head = head->next;
		delete deathRow;
	}
}

/***********************
	addLine()
	Adds a new line to the list
************************/
void TaM_LineList::addLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
	TaM_LineNode *tempy = new TaM_LineNode(x1, y1, x2, y2);
	if (head == NULL) {
		// Special case: first line
		head = tail = tempy;
	}
	else {
		tail->next = tempy;
		tail = tempy;
	}
}

/***********************
	drawLines()
	Finally! The whole reason we built this class in the first place.
************************/
void TaM_LineList::drawLines() {
	TaM_LineNode *cur = head;
	
	// Let's start the lines!
	glBegin(GL_LINES);
		// Set current color
		glColor3f(color[0], color[1], color[2]);

		while (cur != NULL) {
			// Draw the line
			glVertex2f(cur->start[0], cur->start[1]);
			glVertex2f(cur->end[0], cur->end[1]);
			cur = cur->next;
		}

	// Done!
	glEnd();
}