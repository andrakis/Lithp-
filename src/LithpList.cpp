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

String LithpList::toString() {
	String result = "";
	bool first = true;
	for(iterator it = this->begin();
		it != this->end(); ++it) {
			if(!first)
				result += " ";
			else
				first = false;
			LithpPrimitive *p = *it;
			result += this->toStringPrefix(p) + p->ToString() + this->toStringPostfix(p);
	}
	return result;
}

String LithpList::toStringPrefix(LithpPrimitive *prim)
{
	switch (prim->GetType()) {
	case STRING:
		return "\"";
	case LIST:
		return "[";
	case DICT:
		return "{";
	case ATOM:
		return "'";
	default:
		return "";
	}
}

String LithpList::toStringPostfix(LithpPrimitive *prim)
{
	switch (prim->GetType()) {
	case STRING:
		return "\"";
	case LIST:
		return "]";
	case DICT:
		return "}";
	case ATOM:
		return "'";
	default:
		return "";
	}
}
