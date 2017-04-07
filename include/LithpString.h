#ifndef LITHPSTRING_H
#define	LITHPSTRING_H

#include <string>
#include <sstream>

#include "LithpPrimitive.h"

class LithpString: public LithpPrimitive {
public:
	LithpString(String value);
	LithpString(const LithpString& orig);
	virtual ~LithpString();
	bool operatorCompare(const LithpPrimitive & other) const;
protected:
	String toString () {
		return value;
	}
	LithpPrimitiveEnum PrimitiveType() const {
		return STRING;
	}
private:
	String value;
};

#endif	/* LITHPSTRING_H */

