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
	// Builds a set of vertices for a circle
	GLfloat angleStep = (float) (2.f * M_PI / TAM_MARKER_VERTS);

	for (int i = 0; i < TAM_MARKER_VERTS; i++) {
		marker[i][0] = cos(angleStep * i);
		marker[i][1] = sin(angleStep * i);
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