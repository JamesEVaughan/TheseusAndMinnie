// The official start for Theseus and Minnie. Initializes app and yield control to TaM_Master.

#include "TaM_defHeaders.h"
#include "TaM_main.h"


// Debugging
#include "TaM_Map.h"
#include "TaM_Theseus.h"
#include "TaM_ActorDrawList.h"
#include "TaM_GameDisplay.h"
#include <ctime>

using namespace std;

#define	TaM_WINDOW_X	640
#define TaM_WINDOW_Y	640


int main(int argc, char *args[]) {
	// The following section will be pruned and rewritten as major features develop
	// Initialize library
	if (!glfwInit()) {
		// Well that sucks, bye
		return 0;
	}

	GLFWwindow *theWnd = TaM_viewInit_direct(); 
	if (!theWnd) {
		// Just quietly crash, we can debug for faults
		return 0;
	}

	// Test of TaM_Map
	TaM_Map testaroni;
	TaM_Theseus player;
	TaM_IntVector coord(40, 40);
	TaM_IntVector dims(560, 560);
	TaM_GameDisplay disp(coord, dims);
	int err = testaroni.init("Maps\\Map1.tam");
	if (err) {
		cout << "Error code: " << err << " produced.\n";
	}
	else {
		// Initialize Theseus
		player.init(testaroni.getTheseus());

		// Load the game elements
		disp.addMap(&testaroni);
		disp.addActor(&player);
		
		// Let's see what it looks like...
		disp.redrawDisplay();

		glfwSwapBuffers(theWnd);
	}

	// Let's test the moving stuff
	for (int i = 0; i < 7; i++) {
		double wait = 3.0; // Wait 3 seconds
		clock_t beg = clock();

		while(wait > (clock() - beg)/CLOCKS_PER_SEC) {
			// Wait
		}

		if (i % 2) {
			player.move(TAM_MOVE_NORTH);
		}
		else {
			player.move(TAM_MOVE_SOUTH);
		}

		disp.redrawDisplay();
		glfwSwapBuffers(theWnd);
	}
	
	TaM_mainloop_direct(theWnd);
	

	// Again, the following section will be pruned of the _direct functions
	TaM_viewDestroy_direct(theWnd);

	glfwTerminate();
	return 0;
}

GLFWwindow *TaM_viewInit_direct() {
	GLFWwindow *ptrW = glfwCreateWindow(TaM_WINDOW_X, TaM_WINDOW_Y, "Theseus and the Minotaur - Tempy", NULL, NULL);
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