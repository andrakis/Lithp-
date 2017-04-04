/* 
 * File:   main.cpp
 * Author: thatcherj
 *
 * Created on 4 April 2017, 12:11 PM
 */

#include <iostream>
#include <map>

#include "LithpAtom.h"
#include "LithpDict.h"
#include "LithpExceptions.h"
#include "LithpInteger.h"
#include "LithpList.h"
#include "LithpPrimitive.h"
#include "LithpString.h"

void testDict() {
	LithpDict d;
	LithpList l;
	l.PushFront(new LithpInteger(2));
	l.PushFront(new LithpString("Dooot"));
	l.PushBack(Atom("test-atom"));
	d.Put("test", new LithpInteger(1));
	d.Put("foo", new LithpString("bar"));
	d.Put("list", &l);
	std::cout << "Dict: " << d.ToString() << std::endl;
}

void testCompare() {
	LithpInteger one(1);
	LithpInteger two(2);
	LithpInteger oneTwo(1);

	bool testA = one == two;
	bool testB = one == oneTwo;

	if (!testA) std::cout << "TestA pass" << std::endl;
	if (testB)  std::cout << "TestB pass" << std::endl;

	LithpAtom atomTest = Atom("test");
	LithpAtom atomTest2 = Atom("test");
	bool testC = atomTest == atomTest2;
	if (testC) std::cout << "TestC pass" << std::endl;

	LithpString string1("test");
	LithpString string2("foo");
	LithpString string3("test");
	bool testD = string1 == string2;
	bool testE = string1 == string3;

	if (!testD) std::cout << "TestD pass" << std::endl;
	if (testE)  std::cout << "TestE pass" << std::endl;
}

/*
 * Lithp++ entry point
 */
int main(int argc, char** argv) {
	testDict();
	testCompare();

	std::cout << "Tests finished. Hit enter to finish." << std::endl;
	std::string s;
	std::getline(std::cin, s);
    return 0;
}

