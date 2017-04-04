/* 
 * File:   LithpCastException.cpp
 * Author: thatcherj
 * 
 * Created on 4 April 2017, 2:56 PM
 */

#include "LithpExceptions.h"

LithpCastException::LithpCastException(LithpPrimitiveEnum from, LithpPrimitiveEnum to) {
	this->from = from;
	this->to = to;
}

LithpCastException::LithpCastException(const LithpCastException& orig) {
}

