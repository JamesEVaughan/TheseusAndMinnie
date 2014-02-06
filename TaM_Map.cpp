/****************************
	This is the implementation file for the TaM_Map class. This class handles
	a single map for Theseus and Minnie.
*****************************/
#include "TaM_Map.h"

using namespace std;

// Constructors/destructors
TaM_Map::TaM_Map() {
	spaces = NULL;
	name = "";
	wallHelper = new TaM_LineList(COLOR_WALL);
}

TaM_Map::~TaM_Map() {
	// Destroy all dynamic memory
	if (spaces) {
		SPC_delete();
	}
}

int TaM_Map::init(string mapName) {
	char *mapData = NULL;
	int errCode = 0;

	// Load the map into mapData
	if (errCode = loadMap(mapName)) {
		return errCode;
	}

	// What's the size of this as a block of pixels?
	sizePx = new TaM_IntVector(sizeSq->get1() * SQUARE_SIZE, sizeSq->get2() * SQUARE_SIZE);

	// Build the lines
	buildLines();



	return ALL_CLEAR;
}

int TaM_Map::loadMap(string name) {
	ifstream ifMap(name, ios::in | ios::binary|ios::ate);
	int errCode = 0;
	if (!ifMap.is_open()) {
		// Map won't open, not our problem
		// Make all output pointers NULL
		spaces = NULL;
		return ERR_MAP_OPEN;
	}

	// First, let's find out how big the file is
	int szMap = (int)ifMap.tellg();
	szMap -= 2;  // The first two bytes tell us the map dimensions

	// Now, let's reset the reader and pop off the map size
	ifMap.seekg(0, ios::beg);
	int width = ifMap.get();
	sizeSq = new TaM_IntVector(width, ifMap.get());

	// Sanity check
	if (szMap < (sizeSq->get1() * sizeSq->get2())) {
		// Map is bad
		return ERR_MAP_BAD;
	}

	// Now, load the rest into data
	spaces = new char[szMap];
	ifMap.read(spaces, (szMap));
	if (!ifMap.good() && szMap != ifMap.gcount()) {
		// Problem with the file
		// Delete all new objects
		delete sizeSq;
		delete[] spaces;
		if (ifMap.eof()) {
			// The map file is too short
			return ERR_MAP_EOF;
		}
		else {
			// The map file is just bad
			return ERR_MAP_BAD;
		}
	}

	// Now close up shop
	ifMap.close();
	return ALL_CLEAR;
}

int TaM_Map::findPoints() {
	// Just scan the whole thing, looking for each point
	char tempy;
	for (int y = 0; y < sizeSq->get2(); y++) {
		for (int x = 0; x < sizeSq->get1(); x++) {
			tempy = SPC_getSpace(x, y);
			if (tempy & START_THE) {
				if (startTheseus) {
					// Bad map
					return ERR_MAP_BAD;
				}
				startTheseus = new TaM_IntVector(x, y); 
			}
			else if (tempy & START_MIN) {
				if (startMinnie) {
					// Bad map
					return ERR_MAP_BAD;
				}
				startMinnie = new TaM_IntVector(x, y);
			}
			else if (tempy & THE_END) {
				if (theEnd) {
					// Bad map
					return ERR_MAP_BAD;
				}
				theEnd = new TaM_IntVector(x, y);
			}
		}
	}

	if (startTheseus || startMinnie || theEnd) {
		// Bad map
		return ERR_MAP_BAD;
	}

	return ALL_CLEAR;
}

TaM_IntVector TaM_Map::getSize() {
	return *sizePx;
}

void TaM_Map::writeToConsole() {
	int x = sizeSq->get1();
	int y = sizeSq->get2();
	cout << "(" << x << ", " << y << ")" << endl;
	for (int i = 0; i < y; i++) {
		printf("%3X", (unsigned char)SPC_getSpace(0, i));
		for (int j = 1; j < x; j++) {
			printf(" %3X", (unsigned char)SPC_getSpace(j, i));
		}
		cout << endl;
	}
}
// Function to complete later:
void TaM_Map::buildLines() {
}

void TaM_Map::draw() {
}

