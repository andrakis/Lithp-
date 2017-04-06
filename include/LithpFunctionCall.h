#pragma once
#include "LithpAtom.h"
#include "LithpOpChain.h"

#include <list>

class LithpFunctionCall :
	public LithpOpChainType
{
public:
	LithpFunctionCall(const LithpFunctionCall &orig)
		//: name(orig.name), params(orig.params) {
	{
		this->name = orig.name;
		this->params = orig.params;

	}
	LithpFunctionCall(LithpAtom *name, ListOpChainType *params)
		//: name(name), params(params) {
	{
		this->name = name;
		this->params = params;

	}
	virtual ~LithpFunctionCall();
	LithpAtom GetName() const {
		return *name;
	}
	ListOpChainType GetParams() const {
		return *params;
	}
protected:
	String toString();
	LithpAtom *name;
	ListOpChainType *params;
};

