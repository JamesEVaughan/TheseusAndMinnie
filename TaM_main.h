// Header for the start of Theseus and Minne. May or may not ever be needed...

#include "TaM_defHeaders.h"

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