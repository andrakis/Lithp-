
#include "LithpInteger.h"

LithpInteger::LithpInteger(long long value) {
	this->value = value;
}

LithpInteger::LithpInteger(const LithpInteger& orig) {
}

LithpInteger::~LithpInteger() {
}

bool LithpInteger::operatorCompare(const LithpPrimitive &other) const {
	const LithpInteger *iOther = static_cast<const LithpInteger*>(&other);
	return this->value == iOther->value;
}