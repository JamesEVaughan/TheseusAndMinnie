/*********************************
	This is the implementation file for TaM_GameRules
**********************************/
#include "TaM_GameRules.h"

TaM_GameRules::TaM_GameRules() {
	map = new TaM_Map();
	the = new TaM_Theseus();
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

	// Theseus is always first
	turn = TAM_TURN_THE;

	return ALL_CLEAR;
}

bool TaM_GameRules::moveThe(char dir) {
	char curPos = map->getSpaceInfo(the->getLoc());

	if (!dir) {
		// Theseus isn't moving
		return true;
	}

	// Include only the wall info
	curPos &= WALL_MASK;

	if (dir & curPos) {
		// Invalid
		return false;
	}

	if (dir ^ WALL_MASK) {
		// dir wasn't a valid direction
		return false;
	}

	the->move(dir);

	// It's all OK!
	return true;
}

void TaM_GameRules::restart() {
	// Put characters back to starting locations
	the->init(map->getTheseus());
}