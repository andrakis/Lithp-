#include <map>
#include <string>

#include "LithpAtom.h"

std::map<AtomId,LithpAtom*> atomsById;
std::map<AtomName,LithpAtom*> atomsByName;

LithpAtom* Atom (String name) {
	if(atomsByName.find(name) == atomsByName.end()) {
		AtomId id = atomsByName.size();
		LithpAtom* atom = new LithpAtom(id, name);
		atomsByName[name] = atom;
		atomsById[id] = atom;
	}
	return atomsByName[name];
}

