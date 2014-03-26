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
	curWnd->addActor(curRules->getMinnie());

	// Now that everything's loaded, refresh the window
	curWnd->refresh();

	return ALL_CLEAR;
}

// Interprets keyboard input 
void TaM_GameManager::kbInput(int key) {
	// Log the input if it's something we're looking for
	switch (key) {
	case TAM_EXIT:
	case TAM_NEW_MAP:
	case TAM_RESTART:
	case TAM_UP:
	case TAM_RIGHT:
	case TAM_DOWN:
	case TAM_LEFT:
	case TAM_STAY:
		inputKey = key;
		break;
	}
}

// The main application loop, returns error code depending on exit status
int TaM_GameManager::mainLoop() {
	int turn;
	// Game runs until it's set to close, use the glfw to check this. For now...
	while (!glfwWindowShouldClose(glfwWndPtr)) {
		curWnd->refresh();
		// Check up on the GLFW events
		glfwPollEvents();
		turn = curRules->curTurn();

		// Is it a command that can always be done?
		switch (inputKey) {
		case TAM_EXIT:	
			// Then quit the program
			glfwSetWindowShouldClose(glfwWndPtr, GL_TRUE);
			continue;
		case TAM_NEW_MAP:
			// Begin loading a new map
			// TO DO: Add map loading when this is available, for now, drop down to restart
		case TAM_RESTART:
			// Restart the map
			curRules->restart();
			// Refresh window to show change
			curWnd->refresh();
			continue;
		}

		// The following checks handle Game Over and game delay statuses
		if (turn == TAM_TURN_END) {
			// First and foremost, if the game is over, just idle
			continue;
		}
		if (turn != TAM_TURN_THE) {
			// It's not the player's turn. Flush input
			inputKey = -1;
		}

		if (!canAct()) {
			// Also, flush input if the delay hasn't passed
			inputKey = -1;
			continue;
		}
		
		if (turn == TAM_TURN_THE) {
			// It's the players turn, see if it's valid input
			switch (inputKey) {
			case TAM_STAY:
				inputKey = TAM_MOVE_STAY;
				break;
			case TAM_UP:
				inputKey = TAM_MOVE_NORTH;
				break;
			case TAM_RIGHT:
				inputKey = TAM_MOVE_EAST;
				break;
			case TAM_DOWN:
				inputKey = TAM_MOVE_SOUTH;
				break;
			case TAM_LEFT:
				inputKey = TAM_MOVE_WEST;
				break;
			default:
				// If it's not valid input, flush it
				inputKey = -1;
				continue;
			}

			// Attempt the move
			if (!curRules->moveThe((char)(inputKey))) {
				// Invalid move, flush it
				inputKey = -1;
				// TO DO: Add illegal move message
				continue;
			}

			// An action was completed, reset the clock
			setNextAction();

			// Game state has been changed, refresh the window
			curWnd->refresh();
		}
		else if (turn == TAM_TURN_MIN_1 || turn == TAM_TURN_MIN_2) {
			// It's Minnie's turn, and she attacks!
			minnieAttacks();

			// An action was completed, reset the clock
			setNextAction();

			// Game state has been changed, refresh the window
			curWnd->refresh();
		}
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
	// this is a placeholder, use no input delay for now
}

// Finds the next move for Minnie base on current game state
void TaM_GameManager::minnieAttacks() {
	// First, grab the direction vector for Minnie to reach Theseus
	TaM_IntVector toTheseus = curRules->getTheseus()->getLoc() - curRules->getMinnie()->getLoc();

	char moveDir = TAM_MOVE_STAY; // Sentinel value

	// Horizontal check
	if (toTheseus.get1() != 0) {
		// If Minnie can get closer by moving in the x-axis
		moveDir = (toTheseus.get1() > 0) ? TAM_MOVE_EAST : TAM_MOVE_WEST;

		if (curRules->moveMin(moveDir)) {
			// Yay! Move was successful
			return;
		}
		else {
			// Reset to sentinel
			moveDir = TAM_MOVE_STAY;
		}
	}
	// Maybe going vertical is the way?
	if (toTheseus.get2() != 0) {
		moveDir = (toTheseus.get2() > 0) ? TAM_MOVE_SOUTH : TAM_MOVE_NORTH;

		if (curRules->moveMin(moveDir)) {
			// Yay! Move was successful
			return;
		}
		else {
			// Reset to sentinel
			moveDir = TAM_MOVE_STAY;
		}
	}

	// If neither work, use the sentinel value to flip over to Theseus's turn
	curRules->moveMin(TAM_MOVE_STAY);
}