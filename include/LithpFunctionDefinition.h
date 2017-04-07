#pragma once

#include "LithpPrimitive.h"
#include "LithpOpChain.h"

class LithpFunctionDefinition
{
public:

	LithpFunctionDefinition()
	{
	}

	virtual ~LithpFunctionDefinition()
	{
	}
protected:
	String fn_name;
	std::list<String> fn_params;

};

