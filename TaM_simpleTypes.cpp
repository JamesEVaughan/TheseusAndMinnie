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