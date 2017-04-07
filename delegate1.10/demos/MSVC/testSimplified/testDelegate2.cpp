// testDelegate2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cassert>

#include <boost/shared_ptr.hpp>

using std::cout;
using std::endl;
using std::string;

#include "../Howto_ExtractSimplified/delegate1.h"

class CBase1
{
public:
  int foo(int n) const { cout << "int CBase1::foo(int " << n << ")" << endl; return n; }
  virtual int bar(int n) { cout << "virtual int CBase1::bar(int " << n << ")" << endl; return n; }
  static int foobar(int n) { cout << "int CBase1::foobar(int " << n << ")" << endl; return n; }

  virtual int virtual_not_overridden(int n)  { cout << "virtual int CBase1::virtual_not_overridden(int " << n << ")" << endl; return n; }

  void dummy() { };
  static void static_dummy() { };
};

// ------------------------------

class CDerived1 : public CBase1
{
  string name_;

public:
  explicit CDerived1(char * name) : name_(name) { }
  string const name() const { return name_; }

public:
  int foo(int n) const { cout << "int CDerived1::foo(int " << n << ") - name: " << name() << endl; return n; }
  virtual int bar(int n) { cout << "virtual int CDerived1::bar(int " << n << ") - name: " << name() << endl; return n; }
  static int foobar(int n) { cout << "int CDerived1::foobar(int " << n << ")" << endl; return n; }

  int foofoobar(CDerived1 * pOther, int n) { cout << "int CDerived1::foofoobar(pOther - name: " << pOther->name() << ", int " << n << ") - name: " << name() << endl; return n; }

};

#if _MSC_VER < 1300
// VC6 does not implemented koenig lookup
namespace fd
{
  template<class T> inline
    T * get_pointer(boost::shared_ptr<T> const & p)
  {
    return p.get();
  }
} // namespace fd
#endif  // #if _MSC_VER < 1300

struct foo
{
  int operator()(int n) const { cout << "int foo::operator()(int " << n << ") const" << endl; return n; }

};

struct bar
{
  int operator()(int n) { cout << "int bar::operator()(int " << n << ")" << endl; return n; }

};

// ====================================================================================================

int main(int argc, char* argv[])
{
  // ====================================================================================================

  //
  // argument bindings and const correctness
  //
  {
    //
    // argument binding for the const member function
    //
    {
      // ----------------------------------------------------------------------
      CBase1 b1;
      const CBase1 cb1;
      // ----------------------------------------------------------------------
      CBase1 * pb1 = &b1;
      CBase1 const * pcb1 = &cb1;
      // ----------------------------------------------------------------------
      CBase1 & rb1 = b1;
      CBase1 const & rcb1 = cb1;
      // ----------------------------------------------------------------------
      std::auto_ptr<CBase1> apb1(new CBase1());
      const std::auto_ptr<CBase1> apcb1(new CBase1());
      // ----------------------------------------------------------------------
#if defined(_MSC_VER) && _MSC_VER > 1300
      // VC6 does not allow to delete const pointer
      // Compile Error: error C2665: 'delete' : none of the 2 overloads can convert parameter 1 from type 'const class T *'
      std::auto_ptr<CBase1 const> capb1(new CBase1());
      const std::auto_ptr<CBase1 const> capcb1(new CBase1());
#endif  // #if defined(_MSC_VER) && _MSC_VER > 1300
      // ----------------------------------------------------------------------
      boost::shared_ptr<CBase1> spb1(new CBase1());
      const boost::shared_ptr<CBase1> spcb1(new CBase1());
      // ----------------------------------------------------------------------
      boost::shared_ptr<CBase1 const> cspb1(new CBase1());
      const boost::shared_ptr<CBase1 const> cspcb1(new CBase1());
      // ----------------------------------------------------------------------

      //
      // int CBase1::foo(int) const;
      //

      // ----------------------------------------------------------------------
      // reference to the bound object
      fd::delegate1<int, int> dg11(&CBase1::foo, b1);
      dg11(11);
      fd::delegate1<int, int> dg12(&CBase1::foo, cb1);
      dg12(12);
      // ----------------------------------------------------------------------
      // address of the bound object
      fd::delegate1<int, int> dg13(&CBase1::foo, &b1);
      dg13(13);
      fd::delegate1<int, int> dg14(&CBase1::foo, &cb1);
      dg14(14);
      // ----------------------------------------------------------------------
      // pointer variable to the bound object
#if defined(_MSC_VER) && _MSC_VER > 1300
      // VC6 bug can resolve overloads when pointer variable which point to the bound object is given
      fd::delegate1<int, int> dg15(&CBase1::foo, pb1);
      dg15(15);
      fd::delegate1<int, int> dg16(&CBase1::foo, pcb1);
      dg16(16);
#endif  // #if defined(_MSC_VER) && _MSC_VER > 1300
      // workaround for VC6
      fd::delegate1<int, int> dg15_1(&CBase1::foo, fd::get_pointer(pb1));
      dg15_1(15);
      fd::delegate1<int, int> dg16_1(&CBase1::foo, fd::get_pointer(pcb1));
      dg16_1(16);
      // ----------------------------------------------------------------------
      // dereference of the pointer variable to the bound object
      fd::delegate1<int, int> dg17(&CBase1::foo, *pb1);
      dg17(17);
      fd::delegate1<int, int> dg18(&CBase1::foo, *pcb1);
      dg18(18);
      // ----------------------------------------------------------------------    
      // reference variable to the bound object
      fd::delegate1<int, int> dg19(&CBase1::foo, rb1);
      dg19(19);
      fd::delegate1<int, int> dg20(&CBase1::foo, rcb1);
      dg20(20);
      // ----------------------------------------------------------------------
      // address of the reference variable to the bound object
      fd::delegate1<int, int> dg21(&CBase1::foo, &rb1);
      dg21(21);
      fd::delegate1<int, int> dg22(&CBase1::foo, &rcb1);
      dg22(22);
      // ----------------------------------------------------------------------
      // std::auto_ptr<T>
      fd::delegate1<int, int> dg23(&CBase1::foo, apb1);
      dg23(23);
      // it is not allowed to take the ownership of const version of std::auto_ptr<T>
      //    fd::delegate1<int, int> dg24(&CBase1::foo, apcb1);
      //    dg24(24);
      // ----------------------------------------------------------------------
#if defined(_MSC_VER) && _MSC_VER > 1300
      // VC6 does not allow to delete const pointer
      // std::auto_ptr<T const>
      fd::delegate1<int, int> dg25(&CBase1::foo, capb1);
      dg25(25);
      // it is not allowed to take the ownership of const version of std::auto_ptr<T>
      //    fd::delegate1<int, int> dg26(&CBase1::foo, capcb1);
      //    dg26(26);
#endif  // #if defined(_MSC_VER) && _MSC_VER > 1300
      // ----------------------------------------------------------------------
      // boost::shared_ptr<T>
      fd::delegate1<int, int> dg27(&CBase1::foo, spb1);
      dg27(27);
      fd::delegate1<int, int> dg28(&CBase1::foo, spcb1);
      dg28(28);
      // ----------------------------------------------------------------------
      // boost::shared_ptr<T const>
      fd::delegate1<int, int> dg29(&CBase1::foo, cspb1);
      dg29(29);
      fd::delegate1<int, int> dg30(&CBase1::foo, cspcb1);
      dg30(30);
      // ----------------------------------------------------------------------
    }

    // ====================================================================================================

    //
    // argument binding for the non-const member function
    //

    {
      // ----------------------------------------------------------------------
      CBase1 b1;
      const CBase1 cb1;
      // ----------------------------------------------------------------------
      CBase1 * pb1 = &b1;
      CBase1 const * pcb1 = &cb1;
      // ----------------------------------------------------------------------
      CBase1 & rb1 = b1;
      CBase1 const & rcb1 = cb1;
      // ----------------------------------------------------------------------
      std::auto_ptr<CBase1> apb1(new CBase1());
      const std::auto_ptr<CBase1> apcb1(new CBase1());
      // ----------------------------------------------------------------------
#if defined(_MSC_VER) && _MSC_VER > 1300
      // VC6 does not allow to delete const pointer
      // Compile Error: error C2665: 'delete' : none of the 2 overloads can convert parameter 1 from type 'const class T *'
      std::auto_ptr<CBase1 const> capb1(new CBase1());
      const std::auto_ptr<CBase1 const> capcb1(new CBase1());
#endif  // #if defined(_MSC_VER) && _MSC_VER > 1300
      // ----------------------------------------------------------------------
      boost::shared_ptr<CBase1> spb1(new CBase1());
      const boost::shared_ptr<CBase1> spcb1(new CBase1());
      // ----------------------------------------------------------------------
      boost::shared_ptr<CBase1 const> cspb1(new CBase1());
      const boost::shared_ptr<CBase1 const> cspcb1(new CBase1());
      // ----------------------------------------------------------------------

      //
      // virtual int CBase1::bar(int);
      //

      // ----------------------------------------------------------------------
      // reference to the bound object
      fd::delegate1<int, int> dg11(&CBase1::bar, b1);
      dg11(11);
      //    fd::delegate1<int, int> dg12(&CBase1::bar, cb1);
      //    dg12(12);
      // ----------------------------------------------------------------------
      // address of the bound object
      fd::delegate1<int, int> dg13(&CBase1::bar, &b1);
      dg13(13);
      //    fd::delegate1<int, int> dg14(&CBase1::bar, &cb1);
      //    dg14(14);
      // ----------------------------------------------------------------------
      // pointer variable to the bound object
#if defined(_MSC_VER) && _MSC_VER > 1300
      // VC6 bug can resolve overloads when pointer variable which point to the bound object is given
      fd::delegate1<int, int> dg15(&CBase1::bar, pb1);
      dg15(15);
      //    fd::delegate1<int, int> dg16(&CBase1::bar, pcb1);
      //    dg16(16);
#endif  // #if defined(_MSC_VER) && _MSC_VER > 1300
      // workaround for VC6
      fd::delegate1<int, int> dg15_1(&CBase1::bar, fd::get_pointer(pb1));
      dg15_1(15);
      //    fd::delegate1<int, int> dg16_1(&CBase1::bar, fd::get_pointer(pcb1));
      //    dg16_1(16);
      // ----------------------------------------------------------------------
      // dereference of the pointer variable to the bound object
      fd::delegate1<int, int> dg17(&CBase1::bar, *pb1);
      dg17(17);
      //    fd::delegate1<int, int> dg18(&CBase1::bar, *pcb1);
      //    dg18(18);
      // ----------------------------------------------------------------------    
      // reference variable to the bound object
      fd::delegate1<int, int> dg19(&CBase1::bar, rb1);
      dg19(19);
      //    fd::delegate1<int, int> dg20(&CBase1::bar, rcb1);
      //    dg20(20);
      // ----------------------------------------------------------------------
      // address of the reference variable to the bound object
      fd::delegate1<int, int> dg21(&CBase1::bar, &rb1);
      dg21(21);
      //    fd::delegate1<int, int> dg22(&CBase1::bar, &rcb1);
      //    dg22(22);
      // ----------------------------------------------------------------------
      // std::auto_ptr<T>
      fd::delegate1<int, int> dg23(&CBase1::bar, apb1);
      dg23(23);
      // it is not allowed to take the ownership of const version of std::auto_ptr<T>
      //    fd::delegate1<int, int> dg24(&CBase1::bar, apcb1);
      //    dg24(24);
      // ----------------------------------------------------------------------
#if defined(_MSC_VER) && _MSC_VER > 1300
      // VC6 does not allow to delete const pointer
      // std::auto_ptr<T const>
      //    fd::delegate1<int, int> dg25(&CBase1::bar, capb1);
      //    dg25(25);
      // it is not allowed to take the ownership of const version of std::auto_ptr<T>
      //    fd::delegate1<int, int> dg26(&CBase1::bar, capcb1);
      //    dg26(26);
#endif  // #if defined(_MSC_VER) && _MSC_VER > 1300
      // ----------------------------------------------------------------------
      // boost::shared_ptr<T>
      fd::delegate1<int, int> dg27(&CBase1::bar, spb1);
      dg27(27);
      //    fd::delegate1<int, int> dg28(&CBase1::bar, spcb1);
      //    dg28(28);
      // ----------------------------------------------------------------------
      // boost::shared_ptr<T const>
      //    fd::delegate1<int, int> dg29(&CBase1::bar, cspb1);
      //    dg29(29);
      //    fd::delegate1<int, int> dg30(&CBase1::bar, cspcb1);
      //    dg30(30);
      // ----------------------------------------------------------------------
    }

    // ====================================================================================================

    //
    // argument binding for the special case
    //
    // CDerived1::virtual_not_overridden is passed as template argument of CBase1::virtual_not_overridden type
    // since virtual_not_overridden is not overridden in the derived class (CDerived1).
    //

    {
      // ----------------------------------------------------------------------
      CDerived1 d1("d1");
      const CDerived1 cd1("d1");
      // ----------------------------------------------------------------------
      CDerived1 * pd1 = &d1;
      CDerived1 const * pcd1 = &cd1;
      // ----------------------------------------------------------------------
      CDerived1 & rd1 = d1;
      CDerived1 const & rcd1 = cd1;
      // ----------------------------------------------------------------------
      std::auto_ptr<CDerived1> apd1(new CDerived1("d1"));
      const std::auto_ptr<CDerived1> apcd1(new CDerived1("d1"));
      // ----------------------------------------------------------------------
#if defined(_MSC_VER) && _MSC_VER > 1300
      // VC6 does not allow to delete const pointer
      // Compile Error: error C2665: 'delete' : none of the 2 overloads can convert parameter 1 from type 'const class T *'
      std::auto_ptr<CDerived1 const> capd1(new CDerived1("d1"));
      const std::auto_ptr<CDerived1 const> capcd1(new CDerived1("d1"));
#endif  // #if defined(_MSC_VER) && _MSC_VER > 1300
      // ----------------------------------------------------------------------
      boost::shared_ptr<CDerived1> spd1(new CDerived1("d1"));
      const boost::shared_ptr<CDerived1> spcd1(new CDerived1("d1"));
      // ----------------------------------------------------------------------
      boost::shared_ptr<CDerived1 const> cspd1(new CDerived1("d1"));
      const boost::shared_ptr<CDerived1 const> cspcd1(new CDerived1("d1"));
      // ----------------------------------------------------------------------

      //
      // class CDerived1 : public CBase1 { };
      //
      // virtual int CDerived1::virtual_not_overridden(int);
      //

      // ----------------------------------------------------------------------
      // reference to the bound object
      fd::delegate1<int, int> dg11(&CDerived1::virtual_not_overridden, d1);
      dg11(11);
      //    fd::delegate1<int, int> dg12(&CDerived1::virtual_not_overridden, cd1);
      //    dg12(12);
      // ----------------------------------------------------------------------
      // address of the bound object
      fd::delegate1<int, int> dg13(&CDerived1::virtual_not_overridden, &d1);
      dg13(13);
      //    fd::delegate1<int, int> dg14(&CDerived1::virtual_not_overridden, &cd1);
      //    dg14(14);
      // ----------------------------------------------------------------------
      // pointer variable to the bound object
#if defined(_MSC_VER) && _MSC_VER > 1300
      // VC6 bug can resolve overloads when pointer variable which point to the bound object is given
      fd::delegate1<int, int> dg15(&CDerived1::virtual_not_overridden, pd1);
      dg15(15);
      //    fd::delegate1<int, int> dg16(&CDerived1::virtual_not_overridden, pcd1);
      //    dg16(16);
#endif  // #if defined(_MSC_VER) && _MSC_VER > 1300
      // workaround for VC6
      fd::delegate1<int, int> dg15_1(&CDerived1::virtual_not_overridden, fd::get_pointer(pd1));
      dg15_1(15);
      //    fd::delegate1<int, int> dg16_1(&CDerived1::virtual_not_overridden, fd::get_pointer(pcd1));
      //    dg16_1(16);
      // ----------------------------------------------------------------------
      // dereference of the pointer variable to the bound object
      fd::delegate1<int, int> dg17(&CDerived1::virtual_not_overridden, *pd1);
      dg17(17);
      //    fd::delegate1<int, int> dg18(&CDerived1::virtual_not_overridden, *pcd1);
      //    dg18(18);
      // ----------------------------------------------------------------------    
      // reference variable to the bound object
      fd::delegate1<int, int> dg19(&CDerived1::virtual_not_overridden, rd1);
      dg19(19);
      //    fd::delegate1<int, int> dg20(&CDerived1::virtual_not_overridden, rcd1);
      //    dg20(20);
      // ----------------------------------------------------------------------
      // address of the reference variable to the bound object
      fd::delegate1<int, int> dg21(&CDerived1::virtual_not_overridden, &rd1);
      dg21(21);
      //    fd::delegate1<int, int> dg22(&CDerived1::virtual_not_overridden, &rcd1);
      //    dg22(22);
      // ----------------------------------------------------------------------
      // std::auto_ptr<T>
      fd::delegate1<int, int> dg23(&CDerived1::virtual_not_overridden, apd1);
      dg23(23);
      // it is not allowed to take the ownership of const version of std::auto_ptr<T>
      //    fd::delegate1<int, int> dg24(&CDerived1::virtual_not_overridden, apcd1);
      //    dg24(24);
      // ----------------------------------------------------------------------
#if defined(_MSC_VER) && _MSC_VER > 1300
      // VC6 does not allow to delete const pointer
      // std::auto_ptr<T const>
      //    fd::delegate1<int, int> dg25(&CDerived1::virtual_not_overridden, capd1);
      //    dg25(25);
      // it is not allowed to take the ownership of const version of std::auto_ptr<T>
      //    fd::delegate1<int, int> dg26(&CDerived1::virtual_not_overridden, capcd1);
      //    dg26(26);
#endif  // #if defined(_MSC_VER) && _MSC_VER > 1300
      // ----------------------------------------------------------------------
      // boost::shared_ptr<T>
      fd::delegate1<int, int> dg27(&CDerived1::virtual_not_overridden, spd1);
      dg27(27);
      //    fd::delegate1<int, int> dg28(&CDerived1::virtual_not_overridden, spcd1);
      //    dg28(28);
      // ----------------------------------------------------------------------
      // boost::shared_ptr<T const>
      //    fd::delegate1<int, int> dg29(&CDerived1::virtual_not_overridden, cspd1);
      //    dg29(29);
      //    fd::delegate1<int, int> dg30(&CDerived1::virtual_not_overridden, cspcd1);
      //    dg30(30);
      // ----------------------------------------------------------------------
    }
  }

  // ====================================================================================================

  {
    // ----------------------------------------------------------------------
    foo ff1;
    const foo cff1;
    // ----------------------------------------------------------------------
    foo * pff1 = &ff1;
    foo const * pcff1 = &cff1;
    // ----------------------------------------------------------------------
    foo & rff1 = ff1;
    foo const & rcff1 = cff1;
    // ----------------------------------------------------------------------
    
    //
    // int foo::operator()(int) const;
    //
    
    // ----------------------------------------------------------------------
    // reference to the bound object
    fd::delegate1<int, int> dg11;
    dg11 <<= ff1;
    dg11(11);
    fd::delegate1<int, int> dg12;
    dg12 <<= cff1;
    dg12(12);
    // ----------------------------------------------------------------------
    // address of the bound object
    fd::delegate1<int, int> dg13;
    dg13 <<= &ff1;
    dg13(13);
    fd::delegate1<int, int> dg14;
    dg14 <<= &cff1;
    dg14(14);
    // ----------------------------------------------------------------------
    // pointer variable to the bound object
#if defined(_MSC_VER) && _MSC_VER > 1300
    // VC6 bug can resolve overloads when pointer variable which point to the bound object is given
    fd::delegate1<int, int> dg15;
    dg15 <<= pff1;
    dg15(15);
    fd::delegate1<int, int> dg16;
    dg16 <<= pcff1;
    dg16(16);
#endif  // #if defined(_MSC_VER) && _MSC_VER > 1300
    // workaround for VC6
    fd::delegate1<int, int> dg15_1;
    dg15_1 <<= fd::get_pointer(pff1);
    dg15_1(15);
    fd::delegate1<int, int> dg16_1;
    dg16_1 <<= fd::get_pointer(pcff1);
    dg16_1(16);
    // ----------------------------------------------------------------------
    // dereference of the pointer variable to the bound object
    fd::delegate1<int, int> dg17;
    dg17 <<= *pff1;
    dg17(17);
    fd::delegate1<int, int> dg18;
    dg18 <<= *pcff1;
    dg18(18);
    // ----------------------------------------------------------------------    
    // reference variable to the bound object
    fd::delegate1<int, int> dg19;
    dg19 <<= rff1;
    dg19(19);
    fd::delegate1<int, int> dg20;
    dg20 <<= rcff1;
    dg20(20);
    // ----------------------------------------------------------------------
    // address of the reference variable to the bound object
    fd::delegate1<int, int> dg21;
    dg21 <<= &rff1;
    dg21(21);
    fd::delegate1<int, int> dg22;
    dg22 <<= &rcff1;
    dg22(22);
    // ----------------------------------------------------------------------
  }

  // ====================================================================================================

  {
    // ----------------------------------------------------------------------
    bar fb1;
    const bar cfb1;
    // ----------------------------------------------------------------------
    bar * pfb1 = &fb1;
    bar const * pcfb1 = &cfb1;
    // ----------------------------------------------------------------------
    bar & rfb1 = fb1;
    bar const & rcfb1 = cfb1;
    // ----------------------------------------------------------------------
    
    //
    // int bar::operator()(int) const;
    //
    
    // ----------------------------------------------------------------------
    // reference to the bound object
    fd::delegate1<int, int> dg11;
    dg11 <<= fb1;
    dg11(11);
//    fd::delegate1<int, int> dg12;
//    dg12 <<= cfb1;
//    dg12(12);
    // ----------------------------------------------------------------------
    // address of the bound object
    fd::delegate1<int, int> dg13;
    dg13 <<= &fb1;
    dg13(13);
//    fd::delegate1<int, int> dg14;
//    dg14 <<= &cfb1;
//    dg14(14);
    // ----------------------------------------------------------------------
    // pointer variable to the bound object
#if defined(_MSC_VER) && _MSC_VER > 1300
    // VC6 bug can resolve overloads when pointer variable which point to the bound object is given
    fd::delegate1<int, int> dg15;
    dg15 <<= pfb1;
    dg15(15);
//    fd::delegate1<int, int> dg16;
//    dg16 <<= pcfb1;
//    dg16(16);
#endif  // #if defined(_MSC_VER) && _MSC_VER > 1300
    // workaround for VC6
    fd::delegate1<int, int> dg15_1;
    dg15_1 <<= fd::get_pointer(pfb1);
    dg15_1(15);
//    fd::delegate1<int, int> dg16_1;
//    dg16_1 <<= fd::get_pointer(pcfb1);
//    dg16_1(16);
    // ----------------------------------------------------------------------
    // dereference of the pointer variable to the bound object
    fd::delegate1<int, int> dg17;
    dg17 <<= *pfb1;
    dg17(17);
//    fd::delegate1<int, int> dg18;
//    dg18 <<= *pcfb1;
//    dg18(18);
    // ----------------------------------------------------------------------    
    // reference variable to the bound object
    fd::delegate1<int, int> dg19;
    dg19 <<= rfb1;
    dg19(19);
//    fd::delegate1<int, int> dg20;
//    dg20 <<= rcfb1;
//    dg20(20);
    // ----------------------------------------------------------------------
    // address of the reference variable to the bound object
    fd::delegate1<int, int> dg21;
    dg21 <<= &rfb1;
    dg21(21);
//    fd::delegate1<int, int> dg22;
//    dg22 <<= &rcfb1;
//    dg22(22);
    // ----------------------------------------------------------------------
  }

  // ====================================================================================================

  //
  // clearing fd::delegate by assigning 0
  //
  {
    fd::delegate1<int, int> dg_null1(0);
    // fd::delegate1<int, int> dg_null1(123);  // compile error
    fd::delegate1<int, int> dg_null2 = 0;
    dg_null1 = 0;
    // dg_null1 = 123; // compiler error
  }

  // ====================================================================================================

  //
  // ownership transferring of std::auto_ptr is applied to fd::delegate when std::auto_ptr is being cloned into it
  //
  {
    std::auto_ptr<CBase1> apb1(new CBase1);
    fd::delegate1<int, int> dg11(&CBase1::foo, apb1);
    dg11(11);

    // ownership of the bound object is being transfered from dg11 to dg12
    fd::delegate1<int, int> dg12 = dg11;
    dg12(12);

    try
    {
      // dg11 does not have the ownership of the bound object
      dg11(11);

      //
      // VC6 std::auto_ptr bug
      //
      // VC6 implementation of std::auto_ptr does not clear the pointer to the object and simply set the ownership flag to false
      // so it did not cause an exception here but it is definitely against the design criteria of std::auto_ptr
    }
    catch(std::exception & e) { cout << e.what() << endl; } // 'member function call on no object' exception
  }

  // ====================================================================================================

	printf("Hello World!\n");
	return 0;
}

