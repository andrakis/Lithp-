/* 
 * File:   LithpDict.cpp
 * Author: thatcherj
 * 
 * Created on 4 April 2017, 12:13 PM
 */

#include <string>
#include "LithpDict.h"

LithpDict::LithpDict() {
}

LithpDict::LithpDict(const LithpDict& orig) {
}

LithpDict::~LithpDict() {
}

String LithpDict::ToString() {
	String result = "{";
	bool first = true;
	for(std::map<String,LithpPrimitive*>::iterator it = dict.begin();
		it != dict.end(); ++it) {
			if(!first)
				result += " ";
			else
				first = false;
			result += it->first + ": " + it->second->ToString();
	}
	result += "}";
	return result;
}