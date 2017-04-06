#pragma once
#include "LithpAtom.h"
#include "LithpOpChain.h"

#include <list>

class LithpFunctionCall :
	public LithpOpChainType
{
public:
	LithpFunctionCall(const LithpFunctionCall &orig)
		: name(orig.name), params(orig.params) {

	}
	LithpFunctionCall(LithpAtom name, ListOpChainType params)
		: name(name), params(params) {

	}
	virtual ~LithpFunctionCall();
	LithpAtom GetName() const {
		return name;
	}
	ListOpChainType GetParams() const {
		return params;
	}
	String ToString();
protected:
	LithpAtom name;
	ListOpChainType params;
};

