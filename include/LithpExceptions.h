/* 
 * File:   LithpCastException.h
 * Author: thatcherj
 *
 * Created on 4 April 2017, 2:56 PM
 */

#ifndef LITHPCASTEXCEPTION_H
#define	LITHPCASTEXCEPTION_H

#include <exception>

#include "LithpPrimitive.h"

class LithpCastException: public std::exception {
public:
	LithpCastException(LithpPrimitiveEnum from, LithpPrimitiveEnum to);
	LithpCastException(const LithpCastException& orig);
	virtual const char* what() const throw()
	{
		return "Unable to cast to requested type";
	}
private:
	LithpPrimitiveEnum from, to;
};

#endif	/* LITHPCASTEXCEPTION_H */

