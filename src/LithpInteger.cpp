/* 
 * File:   LithpInteger.cpp
 * Author: thatcherj
 * 
 * Created on 4 April 2017, 12:26 PM
 */

#include "LithpInteger.h"

LithpInteger::LithpInteger(long long value) {
	this->value = value;
}

LithpInteger::LithpInteger(const LithpInteger& orig) {
}

LithpInteger::~LithpInteger() {
}

bool LithpInteger::operatorCompare(const LithpPrimitive &other) const {
	const LithpInteger *iOther = dynamic_cast<const LithpInteger*>(&other);
	return this->value == iOther->value;
}