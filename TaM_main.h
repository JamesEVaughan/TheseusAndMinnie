// Header for the start of Theseus and Minne. May or may not ever be needed...

#ifndef	TAM_MAIN
#define	TAM_MAIN

#include "TaM_defHeaders.h"
#include "TaM_Drawable.h"
#include "TaM_Map.h"
#include "TaM_Theseus.h"

// Helper functions


/***** TaM_viewInit_direct
	* Initializes the view window for the entire app.
	* For initial baby builds only.
	* Replace with: to be determined

	*** Parameters:

	*** Returns:
	A pointer to the application window or NULL if creation failed

*/
GLFWwindow *TaM_viewInit_direct();

/***** TaM_viewDestroy_direct
	* Cleans up after GLFWwindow to close app.
	* For initial baby builds only.
	* Replace with: to be determined

	*** Parameters:
	* ptrW	- pointer to a GLFWwindow	

*/
void TaM_viewDestroy_direct(GLFWwindow *ptrW);

/***** TaM_kbCallback_direct()
	* Keyboard callback
	* Replace with: to be determined

	*** Parameters:
	* ptrW	- pointer to GLFWwindow to be linked with
	* key	- key pressed
	* sCode	- scancode
	* act	- action
	* mods	- mods, dunno

	*** Returns:
	
*/
static void TaM_kbCallback_direct(GLFWwindow *ptrW, int key, int sCode, int act, int mods);

/***** TaM_mainloop_direct()
	* The mainloop for TaM
	* Replace with: to be determined

	*** Parameters:

	*** Returns:
	
*/
void TaM_mainloop_direct(GLFWwindow *ptrW);

/***********************
	TaM_drawer_direct()
	* Directly draws the game elements
	* Replace with: to be determined
************************/
void TaM_draw_direct(GLFWwindow *ptrW, TaM_Drawable *drawThis);

/***********************
	TaM_drawTheseus_direct
	* Pushes current matrix and directly sets up the matrix for Theseus
	* Replace with: to be determined
************************/
void TaM_prepTheseus_direct(TaM_Map *curMap, TaM_Theseus *curThe);

#endif