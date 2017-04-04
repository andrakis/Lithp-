/* 
 * File:   LithpList.cpp
 * Author: thatcherj
 * 
 * Created on 4 April 2017, 3:47 PM
 */

#include <list>
#include <string>
#include <sstream>

#include "LithpList.h"

LithpList::LithpList() {
}

LithpList::LithpList(const LithpList& orig) {
}

LithpList::~LithpList() {
}

String LithpList::ToString () {
	String result = "[";
	bool first = true;
	for(std::list<LithpPrimitive*>::iterator it = this->value.begin();
		it != this->value.end(); ++it) {
			if(!first)
				result += " ";
			else
				first = false;
			result += (*it)->ToString();
	}
	result += "]";
	return result;
}