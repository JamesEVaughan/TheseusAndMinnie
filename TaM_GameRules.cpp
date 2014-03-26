/*********************************
	This is the implementation file for TaM_GameRules
**********************************/
#include "TaM_GameRules.h"

TaM_GameRules::TaM_GameRules() {
	map = new TaM_Map();
	the = new TaM_Theseus();
	min = new TaM_Minnie();

	turn = TAM_TURN_END;
}

TaM_GameRules::~TaM_GameRules() {
	// Delete the pointers, this is where they were created
	delete map;
	delete the;
}

int TaM_GameRules::init(string mapName) {
	// First, see if the map is valid
	int err = map->init(mapName);
	if (err) {
		// Phooey!
		return err;
	}

	// Setup Theseus too
	the->init(map->getTheseus());

	// Setup Minnie when that's done...
	min->init(map->getMinnie());

	// Theseus is always first
	turn = TAM_TURN_THE;

	return ALL_CLEAR;
}

bool TaM_GameRules::moveThe(char dir) {
	char curPos = map->getSpaceInfo(the->getLoc());
	
	// Include only the wall info
	curPos &= WALL_MASK;

	if (dir & curPos) {
		// Invalid
		return false;
	}

	// Removed: Unnecessary protection
	//if (dir ^ TAM_MOVE_MASK) {
	//	// dir wasn't a valid direction
	//	return false;
	//}

	the->move(dir);

	setTurn();

	// It's all OK!
	return true;
}

bool TaM_GameRules::moveMin(char dir) {
	char curPos = map->getSpaceInfo(min->getLoc());
	
	// Include only the wall info
	curPos &= WALL_MASK;

	if (dir & curPos) {
		// Illegal move
		return false;
	}
	else if (dir == TAM_MOVE_STAY) {
		// Special case!
		// A command for Minnie to stay means no valid moves, short-circuit straight to Theseus's turn
		turn = TAM_TURN_THE;
		return true;
	}
	else {
		// Legal move, do it!
		min->move(dir);
		// Set next turn
		setTurn();

		// It's all OK!
		return true;
	}
}

void TaM_GameRules::restart() {
	// Put characters back to starting locations
	the->init(map->getTheseus());
	min->init(map->getMinnie());

	// Make it Theseus's turn
	turn = TAM_TURN_THE;
}


// Helpers
void TaM_GameRules::setTurn() {
	// Check game over statuses
	if (gameOver()) {
		turn = TAM_TURN_END;
	}
	else {
		turn++;
		if (turn > TAM_TURN_MIN_2) {
			// If it's greater than Minnie's second turn, make it Theseus's
			turn = TAM_TURN_THE;
		}
	}
}

bool TaM_GameRules::gameOver() {
	// Sanity check
	if (turn == TAM_TURN_END) {
		// We already did this!
		return true;
	}

	// Thesues has triumphed!
	if (the->getLoc().equalTo(map->getTheEnd())) {
		turn = TAM_TURN_END;
		return true;
	}

	// Minnie had a tasty snack!
	if (the->getLoc().equalTo(min->getLoc())) {
		// Yum yum, tasty adventurer! ^_^
		turn = TAM_TURN_END;
		return true;
	}

	// Was it any of those conditions? Then the game continues!
	return false;
}