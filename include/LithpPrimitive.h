#ifndef LITHPPRIMITIVE_H
#define	LITHPPRIMITIVE_H

#include <string>

typedef std::string String;
typedef long long   Integer;
typedef double      Float;

enum LithpPrimitiveEnum {
	NONE,
	ATOM,
	INTEGER,
	FLOAT,
	LIST,
	STRING,
	DICT,
	OBJECT,
	OPCHAIN
};

class LithpPrimitive {
public:
    LithpPrimitive();
    LithpPrimitive(const LithpPrimitive& orig);
    virtual ~LithpPrimitive();
	LithpPrimitiveEnum GetType() const {
		return PrimitiveType();
	}
	virtual LithpPrimitive *Cast(LithpPrimitiveEnum to);
	bool operator==(const LithpPrimitive &other) const {
		if (GetType() != other.GetType())
			return false;
		return operatorCompare(other);
	}
	String ToString() {
		return toString();
	}
protected:
	virtual String toString() {
		return "stub::ToString()";
	}
	virtual LithpPrimitiveEnum PrimitiveType() const {
		return NONE;
	}
	virtual bool operatorCompare(const LithpPrimitive &other) const {
		return false;
	}
};

#endif	/* LITHPPRIMITIVE_H */

