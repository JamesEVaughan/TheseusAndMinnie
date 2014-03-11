/*********************************
	This is the implementation file for TaM_GameManager.
**********************************/

#include "TaM_GameManager.h"

// Constructors, etc.
TaM_GameManager::TaM_GameManager() {
	curRules = new TaM_GameRules();
	curWnd = new TaM_Window();

	inputKey = 0;
}

TaM_GameManager::~TaM_GameManager() {
	delete curRules;
	delete curWnd;
}

// Initializer
int TaM_GameManager::init(string map) {
	// First things first, let's open up this map and see what happens
	int errCode = ALL_CLEAR;
	if (errCode = curRules->init(map)) {
		// Issue with map, might be recoverable, kick it upstream
		return errCode;
	}

	// Now, let's setup the window
	TaM_IntVector wndSz(TAM_WINDOW_X, TAM_WINDOW_Y);
	if (errCode = curWnd->init(wndSz, TAM_WINDOW_NAME)) {
		// Issue with the window, unlikely to be recoverable, kick it upstream
		return errCode;
	}
	GLFWwindow *actWnd = curWnd->getWnd(); // Pointer to the actual window

	// Link this instance with the window for the API callbacks
	if (glfwGetWindowUserPointer(actWnd)) {
		// Yeah, this shouldn't happen, return a general error
		return ERR_GEN;
	}
	glfwSetWindowUserPointer(actWnd, static_cast<void *>(this));

	// Everything's ok, load the map & characters to the viewer
	curWnd->addMap(curRules->getMap());
	curWnd->addActor(curRules->getTheseus());

	// Now that everything's loaded, refresh the window
	curWnd->refresh();

	return ALL_CLEAR;
}

// Interprets keyboard input 
int TaM_GameManager::kbInput(int key) {
	// Needs to be completed...

	return ALL_CLEAR;
}

// The main application loop, returns error code depending on exit status
int TaM_GameManager::mainLoop() {
	// Needs to be completed...

	return ALL_CLEAR;
}

// Returns a pointer to the application window, for establishing callbacks
GLFWwindow *TaM_GameManager::getWnd() {
	return curWnd->getWnd();
}