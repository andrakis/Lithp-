#include <list>
#include <string>
#include <sstream>

#include "LithpList.h"

LithpList::LithpList() {
}

LithpList::LithpList(const LithpList& orig) : value(orig.value) {
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