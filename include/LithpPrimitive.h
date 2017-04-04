/* 
 * File:   LithpPrimitive.h
 * Author: thatcherj
 *
 * Created on 4 April 2017, 12:15 PM
 */

#ifndef LITHPPRIMITIVE_H
#define	LITHPPRIMITIVE_H

#include <string>

typedef std::string String;

enum LithpPrimitiveEnum {
	NONE,
	ATOM,
	INTEGER,
	FLOAT,
	LIST,
	STRING,
	DICT
};

class LithpPrimitive {
public:
    LithpPrimitive();
    LithpPrimitive(const LithpPrimitive& orig);
    virtual ~LithpPrimitive();
	LithpPrimitiveEnum GetType() const {
		return PrimitiveType();
	}
	virtual std::string ToString() {
		return "stub::ToString()";
	}
	virtual LithpPrimitive *Cast(LithpPrimitiveEnum to);
	bool operator==(const LithpPrimitive &other) const {
		if (GetType() != other.GetType())
			return false;
		return operatorCompare(other);
	}
protected:
	virtual LithpPrimitiveEnum PrimitiveType() const {
		return NONE;
	}
	virtual bool operatorCompare(const LithpPrimitive &other) const {
		return false;
	}
};

#endif	/* LITHPPRIMITIVE_H */

