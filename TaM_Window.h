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
#include "TaM_ActorDrawList.h"

class TaM_Window {
private:
	GLFWwindow *pMainWnd;


};

#endif