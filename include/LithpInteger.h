/* 
 * File:   LithpInteger.h
 * Author: thatcherj
 *
 * Created on 4 April 2017, 12:26 PM
 */

#ifndef LITHPINTEGER_H
#define	LITHPINTEGER_H

#include <string>
#include <sstream>

#include "LithpPrimitive.h"

class LithpInteger : public LithpPrimitive {
public:
	LithpInteger(long long value);
	LithpInteger(const LithpInteger& orig);
	virtual ~LithpInteger();
	bool operatorCompare(const LithpPrimitive & other) const;
	String ToString () {
		std::stringstream ss;
		ss << value;
		return ss.str();
	}
protected:
	LithpPrimitiveEnum PrimitiveType() const {
		return INTEGER;
	}
	long long value;
};

#endif	/* LITHPINTEGER_H */

