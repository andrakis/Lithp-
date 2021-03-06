#ifndef LITHPLIST_H
#define	LITHPLIST_H

#include <list>
#include <string>

#include "LithpPrimitive.h"

class LithpList: public LithpPrimitive {
public:
	LithpList();
	LithpList(const LithpList& orig);
	virtual ~LithpList();
	void PushFront (LithpPrimitive* value) {
		this->value.push_front(value);
	}
	LithpPrimitive* PopFront () {
		LithpPrimitive *p = this->value.front();
		this->value.pop_front();
		return p;
	}

	void PushBack (LithpPrimitive* value) {
		this->value.push_back(value);
	}
	LithpPrimitive* PopBack () {
		LithpPrimitive *p = this->value.back();
		this->value.pop_back();
		return p;
	}

	typedef typename std::list<LithpPrimitive*>::iterator iterator;

	iterator begin() {
		return value.begin();
	}
	iterator end() {
		return value.end();
	}

protected:
	String toString () ;
	String toStringPrefix(LithpPrimitive * prim);
	String toStringPostfix(LithpPrimitive * prim);
	std::list<LithpPrimitive*> value;
	LithpPrimitiveEnum PrimitiveType() const {
		return LIST;
	}
private:
	
};

#endif	/* LITHPLIST_H */

