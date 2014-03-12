/*********************************
	This is the implementation file for TaM_Minnie.

	rawr >:-3
**********************************/
#include "TaM_Minnie.h"

// Constructors/destructors
TaM_Minnie::TaM_Minnie() {
	pos = NULL;

	buildMarker();
}

TaM_Minnie::~TaM_Minnie() {
	delete pos;
}

// Initializer
void TaM_Minnie::init(TaM_IntVector start) {
	pos = new TaM_IntVector(start.get1(), start.get2());
}

// Builds the Minnie's marker. Or token, if you will
void TaM_Minnie::buildMarker() {
	// The angle increases for each slice by this amount
	GLfloat angleStep = (float)(2.f * M_PI / TAM_MARKER_VERTS);
	GLfloat r = 0.5f;  // Radius of the circle, slightly larger than Theseus

	for (int i = 0; i < TAM_MARKER_VERTS; i++) {
		marker[i][0] = cos(angleStep * i) * r;
		marker[i][1] = sin(angleStep * i) * r;
	}
}

// To move Minnie...
void TaM_Minnie::move(char dir) {
	// Mask out everything but possible moves
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
			pos->set1(pos->get1()-1);
			return;
		case TAM_MOVE_EAST:
			pos->set1(pos->get1()+1);
			return;
		}
	}
}

// To draw Minnie...
void TaM_Minnie::draw() {
	// Add horns? Maybe later
	glColor3f(TAM_COLOR_MIN);

	// Draw the marker as a triangle fan
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.f, 0.f);  // The center is the origin

		// Loop through the outer vertices
		for (int i = 0; i < TAM_MARKER_VERTS; i++) {
			glVertex2fv(marker[i]);
		}

		glVertex2fv(marker[0]);  // The first one completes the circle
	glEnd();
}