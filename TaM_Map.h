/****************************
This is the header for the Map class.

Map handles the actual map that play is conducted on. It knows the game space
and walls. 
*/

#ifndef TAM_MAP
#define TAM_MAP

#include "TaM_Definitions.h"
#include "TaM_Drawable.h"


class TaM_Map : public TaM_Drawable {
private:
	TaM_IntVector size;
	char *spaces;		// Only use SPC_ functs to interact! Explanation for each space




	// Helper functions for *spaces so I don't fuck it up
	void SPC_create(TaM_IntVector dim) {spaces = new char[(dim.get1() * dim.get2()];}
	char SPC_getSpace(TaM_IntVector loc) {return spaces[(loc.get1() + (loc.get2() * size.get1))];}
	void SPC_setSpace(TaM_IntVector loc, char val) {spaces[(loc.get1() + (loc.get2() * size.get1))] = val;}
	void SPC_delete() {delete[] spaces;}
}

#endif