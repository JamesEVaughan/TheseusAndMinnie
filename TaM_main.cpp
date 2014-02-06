// The official start for Theseus and Minnie. Initializes app and yield control to TaM_Master.

#include "TaM_defHeaders.h"
#include "TaM_main.h"

#include "TaM_Map.h"

using namespace std;

#define	TaM_WINDOW_X	640
#define TaM_WINDOW_Y	480


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
	int err = testaroni.init("Maps\\Map1.tam");
	if (err) {
		cout << "Error code: " << err << " produced.\n";
	}
	else {
		testaroni.writeToConsole();
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
	while(!glfwWindowShouldClose(ptrW)) {

		glfwPollEvents();
	}
}