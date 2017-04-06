#include <string>
#include "LithpDict.h"

LithpDict::LithpDict() {
}

LithpDict::LithpDict(const LithpDict& orig) : dict(orig.dict) {
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