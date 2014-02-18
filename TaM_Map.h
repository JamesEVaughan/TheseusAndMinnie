/****************************
This is the header for the Map class.

Map handles the actual map that play is conducted on. It knows the game space
and walls. 
*****************************/

#ifndef TAM_MAP
#define TAM_MAP

#include "TaM_defHeaders.h"
#include "TaM_Definitions.h"
#include "TaM_Drawable.h"
#include "TaM_LineList.h"

using namespace std;

class TaM_Map : public TaM_Drawable {
private:
	TaM_IntVector *sizeSq;	// Size of the map in spaces
	char *spaces;			// Only use SPC_ functs to interact! Explanation for each space
	TaM_LineList *wallHelper;
	string name;

	// Important positions on the map
	TaM_IntVector *startTheseus;
	TaM_IntVector *startMinnie;
	TaM_IntVector *theEnd;

	// Helper functions for *spaces so I don't fuck it up
	void SPC_create(TaM_IntVector dim) {spaces = new char[dim.get1() * dim.get2()];}
	char SPC_getSpace(int x, int y) {return spaces[(x + y * sizeSq->get2())];}
	void SPC_setSpace(int x, int y, char val) {spaces[x + y * sizeSq->get1()] = val;}
	void SPC_delete() {delete[] spaces;}

	// Builds lines from map data
	void buildLines();

	// Loads map file, name, into memory
	int loadMap(string name);

	// Finds the start and end points, returns error if all three aren't found
	int findPoints();
public:
	// Constructors/Destructors, make private?
	TaM_Map();	// Basic constructor
	~TaM_Map();	// Basic destructor

	// Initializer, builds map and populates data from map file at mapName
	int init(string mapName);

	// TaM_Drawable functions
	virtual void draw();

	// Debugging
	void writeToConsole();

	// Accessors for the key spaces
	TaM_IntVector getTheseus();
	TaM_IntVector getMinnie();
	TaM_IntVector getTheEnd();
	TaM_IntVector getSize();
};

#endif