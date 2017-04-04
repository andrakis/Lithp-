/* 
 * File:   LithpString.cpp
 * Author: thatcherj
 * 
 * Created on 4 April 2017, 3:02 PM
 */

#include "LithpString.h"

LithpString::LithpString(String value) {
	this->value = value;
}

LithpString::LithpString(const LithpString& orig) {
}

LithpString::~LithpString() {
}

bool LithpString::operatorCompare(const LithpPrimitive &other) const {
	const LithpString *iOther = dynamic_cast<const LithpString*>(&other);
	return this->value == iOther->value;
}
