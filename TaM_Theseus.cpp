/*********************************
	This is the implementation file for TaM_Theseus.
**********************************/
#include "TaM_Theseus.h"
#include <cmath>

TaM_Theseus::TaM_Theseus() {
	pos = NULL;

	buildMarker();
}

TaM_Theseus::~TaM_Theseus() {
	delete pos;
}

void TaM_Theseus::init(TaM_IntVector start) {
	pos = new TaM_IntVector(start.get1(), start.get2());
}

void TaM_Theseus::buildMarker() {
	// Builds a set of vertices for the marker
	GLfloat angleStep = (float) (2.f * M_PI / TAM_MARKER_VERTS);
	float r = 0.45f;  // Radius for the circle

	for (int i = 0; i < TAM_MARKER_VERTS; i++) {
		marker[i][0] = cos(angleStep * i) * r;
		marker[i][1] = sin(angleStep * i) * r;
	}
}

void TaM_Theseus::draw() {
	glColor3f(TAM_COLOR_THE);

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.f, 0.f);
		
		// Loop through all the vertices
		for (int i = 0; i < TAM_MARKER_VERTS; i++) {
			glVertex2fv(marker[i]);
		}

		// Add the first one back in to complete the circle
		glVertex2fv(marker[0]);
	glEnd();
}

void TaM_Theseus::move(unsigned char dir) {
	// Sanity check
	dir &= TAM_MOVE_MASK;
	if (dir) {
		switch (dir) {
		case TAM_MOVE_NORTH:
			pos->set2(pos->get2()-1);
			return;
		case TAM_MOVE_SOUTH:
			pos->set2(pos->get2()+1);
			return;
		case TAM_MOVE_WEST:
			pos->set1(pos->get1()+1);
			return;
		case TAM_MOVE_EAST:
			pos->set1(pos->get1()-1);
			return;
		}
	}
}