// The official start for Theseus and Minnie. Initializes app and yield control to TaM_Master.

#include "TaM_defHeaders.h"
#include "TaM_main.h"
#include "TaM_GameManager.h"


// Debugging
#include "TaM_Map.h"
#include "TaM_Theseus.h"
#include "TaM_ActorDrawList.h"
#include "TaM_GameDisplay.h"
#include "TaM_Window.h"

#include <ctime>

using namespace std;


int main(int argc, char *args[]) {
	// The following section will be pruned and rewritten as major features develop
	// Initialize library
	if (!glfwInit()) {
		// Well that sucks, bye
		TaM_error(ERR_GLFW);
		return 0;
	}

	int err = ALL_CLEAR;
	TaM_GameManager ctrl;

	err = ctrl.init((string)(MAP_DIR) + "Map1.tam");
	if (err) {
		// This is a non-recoverable error
		TaM_error(err);

		return 0; // No reason to freak out the system over this crappy little game
	} 

	GLFWwindow *wnd = ctrl.getWnd();
	// First and foremost, link this instance of GameRules with the window
	// Establish callbacks like:
	// Keyboard!
	if (glfwSetKeyCallback(wnd, TaM_kbCallback)) {
		// Uh oh
		TaM_error(ERR_GLFW);

		return 0;
	}

	// Let's see what it looks like...
	ctrl.mainLoop();


	glfwTerminate();
	return 0;
}

// Helper function implementation!
// Error function
void TaM_error(int errCode) {
	// Unload the GLFW library
	glfwTerminate();

	cout << endl << endl;
	cout << "Error code: " << errCode << " occurred." << endl;
	cout << "Theseus and Minnie will now end." << endl;
	system("PAUSE");
}

// Keyboard callback
void TaM_kbCallback(GLFWwindow *wnd, int key, int sCode, int act, int mod) {
	TaM_GameManager *ctrl = static_cast<TaM_GameManager *>(glfwGetWindowUserPointer(wnd));
	if (!ctrl) {
		// Not good, just break for now...
		return;
	}

	// We only care about keys that have been pressed
	if (act == GLFW_PRESS) {
		ctrl->kbInput(key);
	}
}

GLFWwindow *TaM_viewInit_direct() {
	GLFWwindow *ptrW = glfwCreateWindow(TAM_WINDOW_X, TAM_WINDOW_Y, "Theseus and the Minotaur - Tempy", NULL, NULL);
	if (!ptrW) {
		return NULL;
	}

	glfwSetKeyCallback(ptrW, TaM_kbCallback_direct);

	glfwMakeContextCurrent(ptrW);

	// Setup a black background
	int width, height;
	glfwGetFramebufferSize(ptrW, &width, &height);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(ptrW);
	

	// Everything go well? Groovy!
	return ptrW;
}

void TaM_viewDestroy_direct(GLFWwindow *ptrW) {
	glfwDestroyWindow(ptrW);
}

static void TaM_kbCallback_direct(GLFWwindow *ptrW, int key, int sCode, int act, int mods) {
	if (act == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(ptrW, GL_TRUE);
			break;
		}
	}
}

void TaM_mainloop_direct(GLFWwindow *ptrW) {
	/*
	TaM_LineList *tempy = new TaM_LineList(1.f, 0.f, 0.f);

	// Add some lines
	tempy->addLine(0.8f, 0.8f, -0.8f, -0.8f);
	tempy->addLine(-0.8f, 0.8f, 0.8f, -0.8f);

	tempy->addLine(0.8f, 0.8f, 0.8f, -0.8f);
	tempy->addLine(0.8f, -0.8f, -0.8f, -0.8f);
	tempy->addLine(-0.8f, -0.8f, -0.8f, 0.8f);
	tempy->addLine(-0.8f, 0.8f, 0.8f, 0.8f);
	// Setup the viewport
	int width, height;
	glfwGetFramebufferSize(ptrW, &width, &height);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	// It should be an X!
	tempy->drawLines();
	// Swap those buffers!
	glfwSwapBuffers(ptrW);
	*/
	while(!glfwWindowShouldClose(ptrW)) {

		glfwPollEvents();
	}
}

void TaM_draw_direct(GLFWwindow *ptrW, TaM_Drawable *drawThis) {
	// Return if the object is bad
	if (!drawThis) {
		return;
	}
	// Setup the viewport
	// The dimensions of the drawing window
	int gameSpaceWidth = 560;
	int gameSpaceHeight = 560;
	// The coordinates of the lower left corner of the drawing window
	int gameSpaceX = 40;
	int gameSpaceY = 40;

	glViewport(gameSpaceX, gameSpaceY, gameSpaceWidth, gameSpaceHeight);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	// Draw viewport border
	glBegin(GL_LINE_LOOP);
		glColor3f(TAM_COLOR_END);
		glVertex2f(-1.f, 1.f);
		glVertex2f(1.f, 1.f);
		glVertex2f(1.f, -1.f);
		glVertex2f(-1.f, -1.f);
	glEnd();
	drawThis->draw();
}

void TaM_prepTheseus_direct(TaM_Map *curMap, TaM_Theseus *curThe) {
	glPushMatrix();
	glLoadIdentity();
	TaM_IntVector mapSz = curMap->getSize();

	// Move him from the origin to square 0, 0
	GLfloat mapSqX = ((TAM_GRID_SIZE - mapSz.get1())/2) * TAM_SQUARE_SIZE - 1;
	GLfloat mapSqY = 1 - ((TAM_GRID_SIZE - mapSz.get1())/2 * TAM_SQUARE_SIZE);

	mapSqX += TAM_SQUARE_SIZE/2;
	mapSqY -= TAM_SQUARE_SIZE/2;

	glTranslatef(mapSqX, mapSqY, 0);
	
	// Scale him to size
	glScalef(TAM_SQUARE_SIZE, TAM_SQUARE_SIZE, 1);

	mapSqX = (float)curThe->getLoc().get1();
	mapSqY = (float)-curThe->getLoc().get2();

	glTranslatef(mapSqX, mapSqY, 0.f);
}