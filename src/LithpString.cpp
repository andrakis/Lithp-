#include "LithpString.h"

LithpString::LithpString(String value) {
	this->value = value;
}

LithpString::LithpString(const LithpString& orig) {
}

LithpString::~LithpString() {
}

bool LithpString::operatorCompare(const LithpPrimitive &other) const {
	const LithpString *iOther = static_cast<const LithpString*>(&other);
	return this->value == iOther->value;
}
