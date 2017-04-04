#include "LithpPrimitive.h"
#include "LithpExceptions.h"

LithpPrimitive::LithpPrimitive() {
}

LithpPrimitive::LithpPrimitive(const LithpPrimitive& orig) {
}

LithpPrimitive::~LithpPrimitive() {
}

LithpPrimitive* LithpPrimitive::Cast(LithpPrimitiveEnum to) {
	throw LithpCastException(PrimitiveType(), to);
}