#include "LithpExceptions.h"

LithpCastException::LithpCastException(LithpPrimitiveEnum from, LithpPrimitiveEnum to) {
	this->from = from;
	this->to = to;
}

LithpCastException::LithpCastException(const LithpCastException& orig) {
}

