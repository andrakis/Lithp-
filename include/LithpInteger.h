#ifndef LITHPINTEGER_H
#define	LITHPINTEGER_H

#include <string>
#include <sstream>

#include "LithpPrimitive.h"

class LithpInteger : public LithpPrimitive {
public:
	LithpInteger(long long value);
	LithpInteger(const LithpInteger& orig) : value(orig.value) { }
	virtual ~LithpInteger();
	bool operatorCompare(const LithpPrimitive & other) const;
protected:
	String toString () {
		std::stringstream ss;
		ss << value;
		return ss.str();
	}
	LithpPrimitiveEnum PrimitiveType() const {
		return INTEGER;
	}
	long long value;
};

#endif	/* LITHPINTEGER_H */

