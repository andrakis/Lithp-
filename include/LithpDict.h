#ifndef LITHPDICT_H
#define	LITHPDICT_H

#include "LithpPrimitive.h"

#include <map>

class LithpDict : public LithpPrimitive {
public:
    LithpDict();
    LithpDict(const LithpDict& orig);
    virtual ~LithpDict();
	LithpPrimitive* Get (String key) {
		return dict[key];
	}
	void Put (String key, LithpPrimitive *p) {
		dict.insert(std::pair<String,LithpPrimitive*>(key, p));
	}
	void Update (String key, LithpPrimitive *p) {
		dict[key] = p;
	}
	void Remove (String key) {
		dict.erase(key);
	}
	bool Present (String key) {
		return dict.find(key) != dict.end();
	}
	typedef typename std::map<String, LithpPrimitive*>::iterator iterator;
	iterator GetIterator () {
		return dict.begin();
	}
protected:
	String toString();
	LithpPrimitiveEnum PrimitiveType() const {
		return DICT;
	}
	std::map<String,LithpPrimitive*> dict;
private:
};

#endif	/* LITHPDICT_H */

