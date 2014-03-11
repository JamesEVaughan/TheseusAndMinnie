/*********************************
	This is the implementation file for TaM_GameManager.
**********************************/

#include "TaM_GameManager.h"

// Constructors, etc.
TaM_GameManager::TaM_GameManager() {
	curRules = new TaM_GameRules();
	curWnd = new TaM_Window();

	inputKey = 0;
	nextAction = clock();
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
	glfwWndPtr = curWnd->getWnd(); // Pointer to the actual window

	// Link this instance with the window for the API callbacks
	if (glfwGetWindowUserPointer(glfwWndPtr)) {
		// Yeah, this shouldn't happen, return a general error
		return ERR_GEN;
	}
	glfwSetWindowUserPointer(glfwWndPtr, static_cast<void *>(this));

	// Everything's ok, load the map & characters to the viewer
	curWnd->addMap(curRules->getMap());
	curWnd->addActor(curRules->getTheseus());

	// Now that everything's loaded, refresh the window
	curWnd->refresh();

	return ALL_CLEAR;
}

// Interprets keyboard input 
void TaM_GameManager::kbInput(int key) {
	char act = 0;

	// The player can always exit, restart, or change the map
	switch (key) {
	case TAM_EXIT:
		glfwSetWindowShouldClose(glfwWndPtr, GL_TRUE);
		act = -1;
		break;
	case TAM_RESTART:
		curRules->restart();
		act = -1;
		break;
	case TAM_NEW_MAP:
		// TO DO: Implement map choosing
		// For now, treat it like a restart
		curRules->restart();
		act = -1;
		break;
	}
	// First, is it the players turn?
	if (curRules->curTurn() != TAM_TURN_THE) {
		// Flush input
		return;
	}


	// Debugging, output the commands given...
	if (act >= 0) {
		switch(key) {
		case TAM_UP:
			act = TAM_MOVE_NORTH;
			break;
		case TAM_RIGHT:
			act = TAM_MOVE_EAST;
			break;
		case TAM_DOWN:
			act = TAM_MOVE_SOUTH;
			break;
		case TAM_LEFT:
			act = TAM_MOVE_WEST;
			break;
		case TAM_STAY:
			act = TAM_MOVE_STAY;
			break;
		}
	}

	// If we're here, that means it was a move for Theseus!
	// Try the move!
	if (curRules->moveThe(act)) {
		// Yeah, he moved!
	}

	else {
		// He didn't move? D: Tell the player
	}

	curWnd->refresh();
}

// The main application loop, returns error code depending on exit status
int TaM_GameManager::mainLoop() {
	// Dirty hack
	while (!glfwWindowShouldClose(glfwWndPtr)) {
		glfwPollEvents();
	}

	return ALL_CLEAR;
}

// Helpers
bool TaM_GameManager::canAct() {
	if (nextAction < clock()) {
		return true;
	}
	else {
		return false;
	}
}

void TaM_GameManager::setNextAction() {
	nextAction = clock() + (clock_t)(CLOCKS_PER_SEC * 0.5f);
}