// This is header contains mainly system and library headers used throughout the application.
#ifndef TAM_DEF_HEADERS
#define	TAM_DEF_HEADERS

// GLFW is included first
#ifndef TAM_GLFW
#define TaM_GLFW	// Flags glfw.h as having been included for files that need to directly include glfw
#include <GLFW\glfw3.h>
#endif


// System files
/********		ALL CORE FILES ARE INCLUDED HERE!!!	***********/
#define _USE_MATH_DEFINES
#include <cmath>

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

// Super common TaM files
#include "TaM_Definitions.h"
#include "TaM_simpleTypes.h"
#endif