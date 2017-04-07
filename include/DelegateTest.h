#pragma once
#include <iostream>
#include "delegate.h"
#include "LithpAtom.h"
#include "LithpList.h"
#include "LithpLiteral.h"

typedef fd::delegate<LithpPrimitive& (LithpList &params, LithpOpChain &state)>
	LithpFunctionDelegate;

class DelegateTest
{
public:
	DelegateTest();
	virtual ~DelegateTest();
	LithpPrimitive& Print(LithpList &params, LithpOpChain &state) {
		LithpAtom *nnil = Atom("nil");
		LithpAtom &nil = reinterpret_cast<LithpAtom&>(nnil);
		bool first = true;
		for(LithpList::iterator it = params.begin();
			it != params.end(); ++it) {
				if (!first)
					std::cout << " ";
				else
					first = false;
				std::cout << (*it)->ToString();
		}
		std::cout << std::endl;
		return nil;
	}
};

void DoDelegateTest();
