#include <string>
#include "LithpDict.h"

LithpDict::LithpDict() {
}

LithpDict::LithpDict(const LithpDict& orig) : dict(orig.dict) {
}

LithpDict::~LithpDict() {
}

String LithpDict::toString() {
	String result = "{";
	bool first = true;
	for(iterator it = dict.begin();
		it != dict.end(); ++it) {
			if(!first)
				result += " ";
			else
				first = false;
			result += it->first + ": " +
				this->toStringPrefix(it->second) +
				it->second->ToString() +
				this->toStringPostfix(it->second);
	}
	result += "}";
	return result;
}

String LithpDict::toStringPrefix(LithpPrimitive *prim)
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

String LithpDict::toStringPostfix(LithpPrimitive *prim)
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
