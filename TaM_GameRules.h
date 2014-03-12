/*********************************
	This is the header file for TaM_GameRules class. GameRules manages the 
	activity and changes to the game's state. It is the main interface that the
	[Controller] uses to effect the game.
**********************************/
#ifndef TAM_GAMERULES
#define TAM_GAMERULES

#include "TaM_defHeaders.h"

#include "TaM_Map.h"
#include "TaM_Theseus.h"
#include "TaM_Minnie.h"

class TaM_GameRules {
private:
	TaM_Map *map;  // Current map
	TaM_Theseus *the; // Theseus, the player character
	TaM_Minnie *min; // Minnie, the horrible monster

	int turn;

	// Helpers
	void setTurn();

	// Checks all game ending conditions, returns true if one has been achieved
	bool gameOver();

public:
	// Constructors/destructors
	TaM_GameRules();
	~TaM_GameRules();

	// Initializer, returns error code
	int init(string mapName);

	//***** Controller access *****
	// Movement
	bool moveThe(char dir);  // Attempts to move Theseus, returns true if successful
	bool moveMin(char dir);  // Attempts to move Minnie, returns true if successful

	// Map
	void restart();  // Restarts game using the same map

	// Returns current turn
	int curTurn() {return turn;}

	// Accessors, pass map, etc. for view components
	TaM_Map *getMap() {return map;}
	TaM_Theseus *getTheseus() {return the;}
	TaM_Minnie *getMinnie() {return min;}
};

#endif