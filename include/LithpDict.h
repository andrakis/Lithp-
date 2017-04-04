/* 
 * File:   LithpDict.h
 * Author: thatcherj
 *
 * Created on 4 April 2017, 12:13 PM
 */

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
	std::map<String,LithpPrimitive*>::iterator Iterator () {
		return dict.begin();
	}
	String ToString();
protected:
	LithpPrimitiveEnum PrimitiveType() const {
		return DICT;
	}
private:
	std::map<String,LithpPrimitive*> dict;
};

#endif	/* LITHPDICT_H */

