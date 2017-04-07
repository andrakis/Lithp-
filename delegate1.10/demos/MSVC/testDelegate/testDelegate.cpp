// testDelegate.cpp : Defines the entry point for the console application.

#include "../../common/test_delegate.h"
#include "../../common/test_delegate2.h"

//
// Visual Leak Detector - Enhanced Memory Leak Detection for Visual C++ By Dan Moulding 
// ( http://codeproject.com/tools/visualleakdetector.asp )
//
//	#include <vld.h>

int main(int argc, char* argv[])
{
  test_delegate();

  test_delegate2();

  return 0;
}
