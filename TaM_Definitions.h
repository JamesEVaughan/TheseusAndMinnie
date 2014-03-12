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

#define WALL_MASK	WALL_NORTH | WALL_EAST | WALL_SOUTH | WALL_WEST

// Special squares
#define	START_THE	1 << 4	// Theseus start location
#define	START_MIN	1 << 5	// Minne start location
#define	THE_END		1 << 6	// The end
#define	NO_ACCESS	1 << 7

/***********************
	Movement
************************/
#define TAM_MOVE_STAY	0	// Don't move this round
#define	TAM_MOVE_NORTH	1
#define	TAM_MOVE_EAST	1 << 1
#define	TAM_MOVE_SOUTH	1 << 2
#define TAM_MOVE_WEST	1 << 3

#define TAM_MOVE_MASK	TAM_MOVE_NORTH | TAM_MOVE_EAST | TAM_MOVE_SOUTH | TAM_MOVE_WEST

/***********************
	File system
************************/
#define MAP_DIR		"Maps\\"

/***********************
	Draw aids
************************/
#define TAM_SQUARE_SIZE		0.125f	// The size of the side of one square in the mapspace
#define TAM_GRID_SIZE		16		// This is the maximum number of squares for a map (includes border)

// Colors in (R, G, B), floats, for use in glColr3f()
#define	TAM_COLOR_WALL	0.f, 0.9f, 0.f
#define	TAM_COLOR_THE	0.f, 0.f, 0.8f
#define	TAM_COLOR_MIN	0.9f, 0.15f, 0.6f	// Pink?
#define TAM_COLOR_END	0.9f, 0.f, 0.f
#define TAM_COLOR_BG	9.f, 9.f, 9.f	// Black

/***********************
	Actor
************************/
#define	TAM_MARKER_VERTS	20

/***********************
	Windows
************************/
#define TAM_WINDOW_NAME	"Theseus & Minnie"
#define	TAM_WINDOW_X	640
#define TAM_WINDOW_Y	640

#define TAM_DISP_OFF	40	// Border around the game viewer

/***********************
	Error codes
************************/
#define	ALL_CLEAR		0
#define	ERR_GEN			1	// Generic or unknown error
#define ERR_MAP			2	// General map error
#define	ERR_MAP_OPEN	3	// Map file not openable
#define ERR_MAP_BAD		4	// Bad map file
#define ERR_MAP_EOF		5	// Unexpected end of file
#define ERR_WND			6	// General window error
#define ERR_WND_OPEN	7	// Window didn't open
#define ERR_GLFW		8	// General GLFW error

/***********************
	GLFW Key Codes
************************/
// Player controls
#define TAM_UP		GLFW_KEY_UP
#define TAM_DOWN	GLFW_KEY_DOWN
#define TAM_LEFT	GLFW_KEY_LEFT
#define TAM_RIGHT	GLFW_KEY_RIGHT
#define TAM_STAY	GLFW_KEY_S

// Options
#define TAM_EXIT	GLFW_KEY_ESCAPE
#define TAM_RESTART	GLFW_KEY_R
#define TAM_NEW_MAP	GLFW_KEY_N

/***********************
	GameRules
************************/
// Turns
#define TAM_TURN_END	0
#define TAM_TURN_THE	1
#define TAM_TURN_MIN_1	2
#define TAM_TURN_MIN_2	3

#endif