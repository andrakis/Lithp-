#if !defined(__TEST_DELEGATE_H__INCLUDED__)
#define __TEST_DELEGATE_H__INCLUDED__

// ===========================================================================

// #define FD_MEM_FN_ENABLE_STDCALL
#define FD_MEM_FN_ENABLE_FASTCALL
#define FD_MEM_FN_ENABLE_CDECL
#define FD_FN_ENABLE_STDCALL
#define FD_ENABLE_BIND_HELPER_FUNCTION
// #define FD_FN_ENABLE_FASTCALL
// #define FD_DISABLE_TYPE_RELAXATION
// #define FD_DISABLE_CLONE_BOUND_OBJECT
#include "../../include/delegate.h"

#include <iostream>
#include <conio.h>
#include <ctime>

#if !defined(FD_MS_VC) && !defined(FD_MS_VC6)
using std::clock_t;
using std::clock;
#endif

#include <algorithm>
#include <functional>

using std::cout;
using std::endl;
using std::sort;
using std::greater;
using std::for_each;

#if defined(_MSC_VER) && _MSC_VER <= 1200

#pragma warning(push)
#include <yvals.h>              // warning numbers get enabled in yvals.h 
#pragma warning(disable: 4018)  // signed/unsigned mismatch
#pragma warning(disable: 4100)  // unreferenced formal parameter
#pragma warning(disable: 4245)  // conversion from 'type1' to 'type2', 
                                // signed/unsigned mismatch
#pragma warning(disable: 4512)  // 'class' : assignment operator could not be generated
#pragma warning(disable: 4663)  // C++ language change: to explicitly specialize 
                                // class template 'vector'
#pragma warning(disable: 4710)  // 'function' : function not inlined
#pragma warning(disable: 4786)  // identifier was truncated to 'number' characters in 
                                // the debug information
#include <vector>
#include <map>
#include <string>
#pragma warning(pop)

#else // #if defined(_MSC_VER) && _MSC_VER <= 1200

#include <vector>
#include <map>
#include <string>

#endif  // #if defined(_MSC_VER) && _MSC_VER <= 1200

using std::vector;
using std::map;
using std::string;

// ===========================================================================

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

// ------------------------------

// stateless functor
struct Ftor1
{
  int operator () (int n) { cout << "int Ftor1::operator () (int " << n << ")" << endl; return n; }

};

// functor with state
struct Ftor2
{
  string name_;

  explicit Ftor2(char * name) : name_(name) { }

  int operator () (int n) { cout << "int Ftor1::operator () (int " << n << ") - name: " << name_ << endl; return n; }

};


// ===========================================================================

class CRoot
{
  string name_;

public:
  CRoot(char * name) : name_(name) { }

public:
  const string name() const { return name_; }

};

// ------------------------------

class CBase2 : virtual public CRoot
{
public:
  CBase2(char * name) : CRoot(name) { }

public:
  int foo(int n) const { cout << "int CBase2::foo(int " << n << ")" << endl; return n; }
  virtual int bar(int n) { cout << "virtual int CBase2::bar(int " << n << ") - name: " << name() << endl; return n; }
  static int foobar(int n) { cout << "int CBase2::foobar(int " << n << ")" << endl; return n; }
  int foofoobar(CBase2 * pOther, int n) { cout << "int CBase2::foofoobar(pOther(" << pOther->name() <<"), int " << n << ") - name: " << name() << endl; return n; }

};

// ------------------------------

class CBase3 : virtual public CRoot
{
public:
  CBase3(char * name) : CRoot(name) { }

public:
  int foo(int n) const { cout << "int CBase3::foo(int " << n << ") - name: " << name() << endl; return n; }
  virtual int bar(int n) { cout << "virtual int CBase3::bar(int " << n << ") - name: " << name() << endl; return n; }
  static int foobar(int n) { cout << "int CBase3::foobar(int " << n << ")" << endl; return n; }
  int foofoobar(CBase3 * pOther, int n) { cout << "int CBase3::foofoobar(pOther(" << pOther->name() <<"), int " << n << ") - name: " << name() << endl; return n; }

};

// ------------------------------

class CDerived2 : public CBase2, public CBase3
{
public:
  CDerived2(char * name) : CBase2(name), CBase3(name), CRoot(name) { }

public:
  int foo(int n) const { cout << "int CDerived2::foo(int " << n << ") - name: " << name() << endl; return n; }
  virtual int bar(int n) { cout << "virtual int CDerived2::bar(int " << n << ") - name: " << name() << endl; return n; }
  static int foobar(int n) { cout << "int CDerived2::foobar(int " << n << ")" << endl; return n; }
  int foofoobar(CDerived2 * pOther, int n) { cout << "int CDerived2::foofoobar(pOther(" << pOther->name() <<"), int " << n << ") - name: " << name() << endl; return n; }

};

// ===========================================================================

class CManyFunctions
{
public:
  int doSomething0(int n) { cout << "int CManyFunctions::doSomething0(int " << n << ")" << endl; return n; }
  int doSomething1(int n) { cout << "int CManyFunctions::doSomething1(int " << n << ")" << endl; return n; }
  int doSomething2(int n) { cout << "int CManyFunctions::doSomething2(int " << n << ")" << endl; return n; }
  int doSomething3(int n) { cout << "int CManyFunctions::doSomething3(int " << n << ")" << endl; return n; }
  int doSomething4(int n) { cout << "int CManyFunctions::doSomething4(int " << n << ")" << endl; return n; }
  int doSomething5(int n) { cout << "int CManyFunctions::doSomething5(int " << n << ")" << endl; return n; }
  int doSomething6(int n) { cout << "int CManyFunctions::doSomething6(int " << n << ")" << endl; return n; }
  int doSomething7(int n) { cout << "int CManyFunctions::doSomething7(int " << n << ")" << endl; return n; }
  int doSomething8(int n) { cout << "int CManyFunctions::doSomething8(int " << n << ")" << endl; return n; }
  int doSomething9(int n) { cout << "int CManyFunctions::doSomething9(int " << n << ")" << endl; return n; }

  static int doSomethingStatic0(int n) { cout << "static int CManyFunctions::doSomethingStatic0(int " << n << ")" << endl; return n; }
  static int doSomethingStatic1(int n) { cout << "static int CManyFunctions::doSomethingStatic1(int " << n << ")" << endl; return n; }
  static int doSomethingStatic2(int n) { cout << "static int CManyFunctions::doSomethingStatic2(int " << n << ")" << endl; return n; }

};

// ------------------------------

struct invoker_ii
{
  int n_;

  explicit invoker_ii(int n) : n_(n) { }

  template<class T>
  int operator () (T const & t)
  {
    return t(n_);
  }

};

// ===========================================================================

typedef long LRESULT, LPARAM;
typedef unsigned int UINT, WPARAM;

template<class T>
class CMyWindowBase
{
public:
  typedef fd::delegate4<LRESULT, T *, UINT, WPARAM, LPARAM> MessageHandlerType;
  typedef std::map<UINT, MessageHandlerType> MessageMap;

private:
  MessageMap message_map_;

public:
  bool RegisterMessageHandler(UINT uMsg, LRESULT (T::*mfn_msg_handler)(UINT, WPARAM, LPARAM))
  {
    message_map_[uMsg] = fd::make_delegate((T *)0, mfn_msg_handler);
    return true;
  }

  bool RegisterMessageHandler(UINT uMsg, LRESULT (*fn_msg_handler)(T *, UINT, WPARAM, LPARAM))
  {
    message_map_[uMsg] = fd::make_delegate(fn_msg_handler);
    return true;
  }

  bool RegisterMessageHandler(UINT uMsg, MessageHandlerType const & dg_msg_handler)
  {
    message_map_[uMsg] = dg_msg_handler;
    return true;
  }

  LRESULT SendMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    typename MessageMap::iterator it_f = message_map_.find(uMsg);
    if(it_f != message_map_.end())
    {
      T * pT = static_cast<T *>(this);
      return (it_f->second)(pT, uMsg, wParam, lParam);
    }

    return -1;
  }
  
};

class CMyWindow : public CMyWindowBase<CMyWindow>
{
public:

  typedef CMyWindowBase<CMyWindow>::MessageHandlerType MessageHandlerType;

  LRESULT OnMessageHandler1(UINT uMsg, WPARAM wParam, LPARAM lParam) { cout << "CMyWindow::OnMessageHandler1(UINT(" << uMsg << "), WPARAM(" << wParam << "), LPARAM(" << lParam << ")" << endl; return lParam; }
  LRESULT OnMessageHandler2(UINT uMsg, WPARAM wParam, LPARAM lParam) { cout << "CMyWindow::OnMessageHandler2(UINT(" << uMsg << "), WPARAM(" << wParam << "), LPARAM(" << lParam << ")" << endl; return lParam; }
  LRESULT OnMessageHandler3(UINT uMsg, WPARAM wParam, LPARAM lParam) { cout << "CMyWindow::OnMessageHandler3(UINT(" << uMsg << "), WPARAM(" << wParam << "), LPARAM(" << lParam << ")" << endl; return lParam; }
  LRESULT OnMessageHandler4(UINT uMsg, WPARAM wParam, LPARAM lParam) { cout << "CMyWindow::OnMessageHandler4(UINT(" << uMsg << "), WPARAM(" << wParam << "), LPARAM(" << lParam << ")" << endl; return lParam; }
  LRESULT OnMessageHandler5(UINT uMsg, WPARAM wParam, LPARAM lParam) { cout << "CMyWindow::OnMessageHandler5(UINT(" << uMsg << "), WPARAM(" << wParam << "), LPARAM(" << lParam << ")" << endl; return lParam; }

  static LRESULT OnMessageHandlerStatic1(CMyWindow * pThis, UINT uMsg, WPARAM wParam, LPARAM lParam) { cout << "CMyWindow::OnMessageHandlerStatic1(UINT(" << uMsg << "), WPARAM(" << wParam << "), LPARAM(" << lParam << ")" << endl; return lParam; }
  static LRESULT OnMessageHandlerStatic2(CMyWindow * pThis, UINT uMsg, WPARAM wParam, LPARAM lParam) { cout << "CMyWindow::OnMessageHandlerStatic1(UINT(" << uMsg << "), WPARAM(" << wParam << "), LPARAM(" << lParam << ")" << endl; return lParam; }
  static LRESULT OnMessageHandlerStatic3(CMyWindow * pThis, UINT uMsg, WPARAM wParam, LPARAM lParam) { cout << "CMyWindow::OnMessageHandlerStatic1(UINT(" << uMsg << "), WPARAM(" << wParam << "), LPARAM(" << lParam << ")" << endl; return lParam; }

};

#define UWM_MESSAGE1 1001
#define UWM_MESSAGE2 1002
#define UWM_MESSAGE3 1003
#define UWM_MESSAGE4 1004
#define UWM_MESSAGE5 1005
#define UWM_MESSAGE6 1006
#define UWM_MESSAGE7 1007
#define UWM_MESSAGE8 1008
#define UWM_MESSAGE9 1009

// ===========================================================================

struct lres_timer
{
  string title_;
  clock_t t_begin_, t_end_;

  lres_timer(char * title) : title_(title), t_end_(0)
  {
    cout << "// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "// - Beg_Timer: " << title_ << endl;

    t_begin_ = clock();
  }
  ~lres_timer()
  {
    t_end_ = clock();

    cout << "// - End_Timer: " << title_ << " - " << (t_end_ - t_begin_) << " clocks" << endl;
    cout << "// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
  }
};

// ===========================================================================

class CFastCallClass
{
public:
  int FD_FASTCALL_ foo(int n) { cout << "int __fastcall CFastCallClass::foo(int " << n << ")" << endl; return n; }
  int FD_CDECL_ bar(int n) { cout << "int __cdecl CFastCallClass::bar(int " << n << ")" << endl; return n; }

};

// ===========================================================================

void test_delegate();

#endif  // #if !defined(__TEST_DELEGATE_H__INCLUDED__)
