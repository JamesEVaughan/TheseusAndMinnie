/****************************
	This is the main definition file for Theseus and Minnie.
*/

#ifndef TAM_DEFINITIONS
#define TAM_DEFINITIONS

/***********************
	Map
************************/
// Wall locations
#define	WALL_NONE	0
#define	WALL_NORTH	1
#define	WALL_EAST	1 << 1
#define	WALL_SOUTH	1 << 2
#define	WALL_WEST	1 << 3

// Special squares
#define	START_THE	1 << 4	// Theseus start location
#define	START_MIN	1 << 5	// Minne start location
#define	THE_END		1 << 6	// The end
#define	NO_ACCESS	-1

/***********************
	Movement
************************/
#define GO_STAY		0	// Don't move this round
#define	GO_NORTH	1
#define	GO_EAST		1 << 1
#define	GO_SOUTH	1 << 2
#define GO_WEST		1 << 3

#endif