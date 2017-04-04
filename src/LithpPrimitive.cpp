/* 
 * File:   LithpPrimitive.cpp
 * Author: thatcherj
 * 
 * Created on 4 April 2017, 12:15 PM
 */

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