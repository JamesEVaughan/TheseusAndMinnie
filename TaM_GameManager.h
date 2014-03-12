/*********************************
	This is the header file for TaM_GameManager. GameManager is the main class
	for the	controller component. It mainly handles the central event handler 
	in its mainLoop(). After initialization, mainLoop runs until the program
	terminates.
**********************************/
#ifndef TAM_GAMEMANAGER
#define TAM_GAMEMANAGER

#include "TaM_defHeaders.h"

// GameManger act as the interface between the Game and the Display
#include "TaM_GameRules.h"
#include "TaM_Window.h"

using namespace std;

class TaM_GameManager {
private:
	TaM_GameRules *curRules;
	TaM_Window *curWnd;

	// Needed throughout
	GLFWwindow *glfwWndPtr;

	int inputKey;
	clock_t nextAction;

	// Helper functions
	// Return true only if clock() > nextAction
	bool canAct();

	// Sets nextAction to a new value after a completed action
	void setNextAction();

	// Minnie attempts to catch the pesky Theseus
	void minnieAttacks();

public:
	// Constructor/destructors
	TaM_GameManager();
	~TaM_GameManager();

	// Initializer, returns error codes
	int init(string map);

	// Keyboard handler
	void kbInput(int key);

	// The main loop, return error code
	int mainLoop();

	// Window accessor, returns pointer for callbacks, etc
	GLFWwindow *getWnd() {return glfwWndPtr;} 
};

#endif