/*********************************
	This is the header file for the TaM_Window class. Window handles the window
	and everything displayed within. This class forms the root of our Viewer
	component.
**********************************/

#ifndef TAM_WINDOW
#define TAM_WINDOW

#include "TaM_defHeaders.h"
#include "TaM_Definitions.h"

// All the display classes
#include "TaM_GameDisplay.h"

class TaM_Window {
private:
	GLFWwindow *mainWnd;  // Pointer to the application's window
	TaM_GameDisplay *disp;  // The viewer to the game world

	/* TO DO:
		* Menu system for entry & exit
		* Informational displays
	*/

	TaM_IntVector wndSize;  // Size, in pixels, of application window

	// Helper functions
public:
	// Constructors/destructors
	TaM_Window();
	~TaM_Window();

	// Initializer, returns error code
	int init(TaM_IntVector sz, string name);

	// Refreshes entire window
	void refresh();

	// disp accessors
	void addMap(TaM_Map *m) {disp->addMap(m);}
	void addActor(TaM_Actor *act) {disp->addActor(act);}

	// Returns the active window
	GLFWwindow *getWnd() {return mainWnd;}

};

#endif