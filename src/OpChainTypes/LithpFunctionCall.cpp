#include "LithpFunctionCall.h"


LithpFunctionCall::~LithpFunctionCall()
{
}

String LithpFunctionCall::ToString() {
	String result = "FunctionCall(";
	result += this->name.ToString();
	result += ", ";
	result += this->params.ToString();
	result += ")";
	return result;
}
