#if defined(_MSC_VER) && _MSC_VER <= 1200
#pragma warning(disable: 4786)  // identifier was truncated to 'number' characters in 
                                // the debug information
#endif  // #if defined(_MSC_VER) && _MSC_VER <= 1200

#include "test_delegate.h"
#include "test_delegate2.h"

// ***
// uncomment below to test boost compatiblity
// ***
//#define TEST_BOOST_COMPATIBLE

#ifdef TEST_BOOST_COMPATIBLE
#include <boost/shared_ptr.hpp>
#include <boost/mem_fn.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#endif // #ifdef TEST_BOOST_COMPATIBLE

#if defined(TEST_BOOST_COMPATIBLE) && defined(FD_MS_VC6)
// Even thogh get_pointer is defined in boost/shared_ptr.hpp, VC6 doesn't seem to
// implement Koenig Lookup (argument dependent lookup) thus can't find the definition,
// So we define get_pointer explicitly in fd namesapce to help the poor compiler
namespace fd
{
  template<class T>
    T * get_pointer(boost::shared_ptr<T> const & p)
  {
    return p.get();
  }
}
#endif  // #if defined(TEST_BOOST_COMPATIBLE) && defined(FD_MS_VC6)

void test_delegate2()
{

#if !defined(FD_DISABLE_CLONE_BOUND_OBJECT)

#if defined(FD_MS_VC6)
  typedef fd::delegate1<int, int>    MyDelegate;
#else
  typedef fd::delegate<int (int)>    MyDelegate;
#endif

  //
  // smart pointer recognition/support
  //
  std::auto_ptr<CBase1> spb1(new CBase1);
  fd::delegate1<int, int> dg1;
  dg1.bind(&CBase1::foo, spb1);
  dg1(123);

  //
  // boost::compatible
  //
#ifdef TEST_BOOST_COMPATIBLE

  CBase1 b1;
  //
  // int CBase1::foo(int) const;
  // int CBase1::bar(int);
  //

  //
  // boost smart pointer recognition/support
  //
  boost::shared_ptr<CBase1> spb2(new CBase1);
  fd::delegate1<int, int> dg2(&CBase1::foo, spb2);
  dg2(234);

  // ----------------------------------------------------------------------

  fd::delegate2<int, CBase1 const &, int> dg3;
  dg3 <<= boost::mem_fn(&CBase1::foo);
  dg3(*spb2.get(), 345);

  // ----------------------------------------------------------------------

  boost::function1<int, int> bfn1 = dg1;
  bfn1(456);

  boost::function1<int, int> bfn2;
  bfn2 = dg2;
  bfn2(567);

  boost::function2<int, CBase1 const &, int> bfn3(dg3);
  bfn3(*spb2.get(), 678);

  // ----------------------------------------------------------------------
  // boost function also support type-check relaxation mode

  boost::function1<int, float> bfn4_1 = boost::bind(&CBase1::foo, &b1, _1);
  bfn4_1(789);

  // Compile warning: conversion from 'float' to 'int', possible loss of data
  boost::function2<int, CBase1 *, float> bfn4_2(&CBase1::foo);
  bfn4_2(&b1, 780);

  // Compile error: cannot convert parameter 2 from 'int' to 'char *'
  // boost::function2<int, CBase1 *, char *> bfn4_3(&CBase1::foo);
  // bfn4_3(&b1, 780);

  typedef fd::delegate1<int, long> MyDelegateIntLong;

#if !defined(FD_NO_CONST_OVERLOADING)
  boost::function1<int, long> bfn4_4(MyDelegateIntLong(&CBase1::foo, &b1));
#else
  boost::function1<int, long> bfn4_4(MyDelegateIntLong(&CBase1::foo, const_cast<CBase1 const *>(&b1)));
#endif
  bfn4_4(781);

  const MyDelegateIntLong dg5(&CBase1::bar, &b1);

  boost::function1<int, long> bfn5(boost::cref(dg5));
  bfn5(890);

  // [obsolete]

//#if !defined(FD_MS_VC6)
//
//  boost::function1<int, long> bfn6(fd::make_delegate((MyDelegateIntLong *)0, &CBase1::foo, &b1));
//  bfn6(901);
//
//#endif  // #if !defined(FD_MS_VC6)

  // ----------------------------------------------------------------------

#endif  // #ifdef TEST_BOOST_COMPATIBLE

#endif  // #if !defined(FD_DISABLE_CLONE_BOUND_OBJECT)

  cout << endl << "push any key to end" << endl; _getch(); 

}
