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
	wallHelper = new TaM_LineList(TAM_COLOR_WALL);
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
	return *sizeSq;
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

/***********************
	buildLines()
	takes the information from *spaces and constructs all the lines that they imply
************************/
void TaM_Map::buildLines() {
	GLfloat horiStart[2] = {6.f, 6.f};	// Start of the horizontal line
	GLfloat horiEnd[2] = {6.f, 6.f};	// End of the horizontal line

	GLfloat vertStart[2] = {6.f, 6.f};	// Start of the vertical line
	GLfloat vertEnd[2] = {6.f, 6.f};	// End of the vertical line

	// Set up the offsets in both directions to center the map
	// NOTE: With an odd number of squares, the extra square will be on the right and below, respectively
	GLfloat xOffset = ((MAX_GRID_SIZE - sizeSq->get1()) / 2.f) * SQUARE_SIZE;
	GLfloat yOffset = ((MAX_GRID_SIZE - sizeSq->get2()) / 2.f) * SQUARE_SIZE;

	/*********
		The algorithm evaluates each value in spaces to find the horizontal and 
		vertical lines. The main nested-for's test the north and west border for 
		each space. The for immediately folowing handles the southern and 
	**********/
	// Puposefully skip the 0th row and column, will never have a valid wall
	for (int y = 1; y < sizeSq->get2() - 1; y++) {
		for (int x = 1; x < sizeSq->get1() - 1; x++) {
			char spc = SPC_getSpace(x, y);
			// Special case:
			if (!(spc & NO_ACCESS) || !(spc & THE_END))  {
				// Short circuit and continue to the next space
				continue;
			}
			else if (!(spc & THE_END)) {
				// Walls are built differently, continue to next square
				continue;
			}
			/*
			I'm dumb, these are already done
			// Special cases. It should be obvious, but these spaces can't be duped
			if (!(spc & THE_END)) {
				// Mark the location
				theEnd = new TaM_IntVector(x, y);
				// The walls are built diferently for this one, continue
				continue;
			}
			else if (!(spc & START_THE)) {
				// Mark the space
				startTheseus = new TaM_IntVector(x, y);
			}
			else if (!(spc & START_MIN)) {
				// Mark the space
				startMinnie = new TaM_IntVector(x, y);
			}
			*/

			// Zero out all bits that aren't wall bits
			spc &= WALL_MASK;

			if (!(spc & WALL_NORTH)) {
				// Start of a new line?
				if (horiStart[0] > 1.f) {
					horiStart[0] = xOffset + (SQUARE_SIZE * x);
					horiStart[1] = yOffset + (SQUARE_SIZE * y);
				}
			}
			else {
				// End of the line?
				if (!(horiStart[0] > 1.f)) {
					horiEnd[0] = xOffset + (SQUARE_SIZE * x);
					horiEnd[1] = yOffset + (SQUARE_SIZE * y);

					wallHelper->addLine(horiStart[0], horiStart[1], horiEnd[0], horiEnd[1]);
					horiStart[0] = horiStart[1] = horiEnd[0] = horiEnd[1] = 6.f;
				}
			}
			if (!(spc & WALL_WEST)) {
				// Start of a new line?
				if (vertStart[0] > 1.f) {
					vertStart[0] = xOffset + (SQUARE_SIZE * x);
					vertStart[1] = yOffset + (SQUARE_SIZE * y);
				}
			}
			else {
				// End of the line?
				if (!(vertStart[0] > 1.f)) {
					vertEnd[0] = xOffset + (SQUARE_SIZE * x);
					vertEnd[1] = yOffset + (SQUARE_SIZE * y);

					wallHelper->addLine(vertStart[0], vertStart[1], vertEnd[0], vertEnd[1]);
					vertStart[0] = vertStart[1] = vertEnd[0] = vertEnd[1] = 6.f;
				}
			}
		}
	}
}
// Function to complete later:

void TaM_Map::draw() {
}

