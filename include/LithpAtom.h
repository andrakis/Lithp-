#ifndef LITHPATOM_H
#define	LITHPATOM_H

#include "LithpInteger.h"
#include "LithpPrimitive.h"

typedef long long   AtomId;
typedef String      AtomName;

class LithpAtom: public LithpInteger {
public:
	LithpAtom(AtomId id, String name)
		: LithpInteger(id), name(name) {
	}
	LithpAtom(const LithpAtom &orig) : LithpInteger(orig.value), name(orig.name) {}
protected:
	String toString() {
		return "'" + this->name + "'";
	}
	LithpPrimitiveEnum PrimitiveType() const {
		return ATOM;
	}
	std::string name;
};

LithpAtom* Atom (String name);

#endif	/* LITHPATOM_H */

