/*********************************
	This is the header file for TaM_GameRules class. GameRules manages the activity
	and changes to the game's state. Also handles control of Minnie. It is the main 
	interface that the [Controller] uses to effect the game.
**********************************/
#ifndef TAM_GAMERULES
#define TAM_GAMERULES

#include "TaM_defHeaders.h"

#include "TaM_Map.h"
#include "TaM_Theseus.h"

class TaM_GameRules {
private:
	TaM_Map *map;  // Current map
	TaM_Theseus *the; // Theseus, the player character

	enum {THESEUS, MINNIE, GAME_END} turn;

public:
	// Constructors/destructors
	TaM_GameRules();
	~TaM_GameRules();

	// Initializer, returns error code
	int init(string mapName);

	//***** Controller access *****
	// Character
	bool moveThe(char dir);  // Returns true move was valid, false if not

	// Map
	void restart();  // Restarts game using the same map

	// Accessors, pass map, etc. for view components
	TaM_Map *getMap() {return map;}
	TaM_Theseus *getTheseus() {return the;}
};

#endif