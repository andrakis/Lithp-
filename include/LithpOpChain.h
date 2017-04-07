#pragma once
#include "LithpPrimitive.h"
#include "LithpList.h"

// This is the subclass that all OpChainTypes must derive from
class LithpOpChainType :
	public LithpPrimitive
{
public:
	LithpOpChainType() { };
	virtual ~LithpOpChainType() {};
protected:
	virtual String toString() {
		return "stub::LithpOpChainType::toString()";
	}
};

typedef LithpList ListOpChainType;

class LithpOpChain :
	public LithpPrimitive
{
public:
	LithpOpChain();
	virtual ~LithpOpChain();
	ListOpChainType::iterator GetIterator() {
		return ops.begin();
	}
	void Push(LithpOpChainType *value) {
		ops.PushBack(value);
	}
protected:
	LithpPrimitiveEnum PrimitiveType() const {
		return OPCHAIN;
	}
	ListOpChainType ops;
};

