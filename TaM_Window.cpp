/*********************************
	The implementation file for TaM_Window
**********************************/

#include "TaM_Window.h"

TaM_Window::TaM_Window() {
	mainWnd = NULL;
	//disp = NULL;
}

TaM_Window::~TaM_Window() {
	// Clean up mainWnd
	glfwDestroyWindow(mainWnd);

	// Delete disp
	//delete disp;
}

int TaM_Window::init(TaM_IntVector sz, string name) {
	// Build the window
	mainWnd = glfwCreateWindow(sz.get1(), sz.get2(), name.c_str(), NULL, NULL);
	if (!mainWnd) {
		// Window broke :<
		return ERR_WND_OPEN;
	}

	wndSize = sz;

	TaM_IntVector viewStart(TAM_DISP_OFF, TAM_DISP_OFF);
	TaM_IntVector viewSz(wndSize.get1() - viewStart.get1(), wndSize.get1() - viewStart.get2());

	disp = new TaM_GameDisplay(viewStart, viewSz);

	glfwMakeContextCurrent(mainWnd);  // Makes the current window the current context

	glViewport(0, 0, wndSize.get1(), wndSize.get2());
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(mainWnd);

	return ALL_CLEAR;
}

void TaM_Window::refresh() {
	// Run the redraw functions in order
	disp->redrawDisplay();

	// Swap buffers
	glfwSwapBuffers(mainWnd);
}