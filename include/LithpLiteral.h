#pragma once
#include "LithpPrimitive.h"
#include "LithpOpChain.h"

class LithpLiteral :
	public LithpOpChainType
{
public:
	LithpLiteral(LithpPrimitive value);
	LithpLiteral(const LithpLiteral &orig)
		: value(value)
	{

	}
	~LithpLiteral();
	LithpPrimitive *GetValue() const {
		return value;
	}
protected:
	virtual LithpPrimitiveEnum PrimitiveType() const {
		return value->GetType();
	}
	virtual bool operatorCompare(const LithpPrimitive &other) const {
		return *value == other;
	}
	LithpPrimitive *value;
};

