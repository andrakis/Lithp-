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
	std::list<LithpPrimitive*>::iterator GetIterator() {
		return value.begin();
	}

	typedef typename std::list<LithpPrimitive*>::iterator iterator;

	String ToString ();
protected:
	std::list<LithpPrimitive*> value;
	LithpPrimitiveEnum PrimitiveType() const {
		return LIST;
	}
private:
	
};

#endif	/* LITHPLIST_H */

