#include "DelegateTest.h"

#include "LithpList.h"
#include "LithpOpChain.h"
#include "LithpString.h"


DelegateTest::DelegateTest()
{
}


DelegateTest::~DelegateTest()
{
}

void DoDelegateTest() {
	DelegateTest builtins;
	//LithpFunctionDelegate print;
	//print.bind(&DelegateTest::Print, builtins);
	auto print = dlgt::make_delegate(&DelegateTest::Print, builtins);
	LithpList params;
	params.PushBack(new LithpString("Hello, world!"));
	LithpOpChain chain; // just for passing
	print(params, chain);
}