/*
	This is the implementation for all the available simple data types
*/

#include "TaM_simpleTypes.h"

/****************************
	TaM_IntVector
*****************************/
TaM_IntVector::TaM_IntVector(int one, int two) {
	val1 = one;
	val2 = two;
}

TaM_IntVector::TaM_IntVector() {
	val1 = 0;
	val2 = 0;
}

bool TaM_IntVector::equalTo(TaM_IntVector oth) {
	if ((val1 == oth.val1) && (val2 == oth.val2)) {
		return true;
	}

	else {
		return false;
	}
}

TaM_IntVector TaM_IntVector::operator- (const TaM_IntVector &oth) {
	TaM_IntVector tempy;
	tempy.val1 = val1 - oth.val1;
	tempy.val2 = val2 - oth.val2;

	return tempy;
}

/****************************
	TaM_FloatVector
*****************************/
TaM_FloatVector::TaM_FloatVector(float one, float two) {
	val1 = one;
	val2 = two;
}

TaM_FloatVector::TaM_FloatVector() {
	val1 = 0.f;
	val2 = 0.f;
}