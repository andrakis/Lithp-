#if defined(_MSC_VER) && _MSC_VER <= 1200
#pragma warning(disable: 4786)  // identifier was truncated to 'number' characters in 
                                // the debug information
#endif  // #if defined(_MSC_VER) && _MSC_VER <= 1200

#include "test_delegate.h"
#include "../../include/allocator.hpp"

// ====================================================================================================

namespace fd
{
  template<int I> class arg
  {
  };

  template<int I> bool operator==(arg<I> const &, arg<I> const &)
  {
    return true;
  }
} // namespace fd

// ====================================================================================================

namespace
{
  static fd::arg<1> _1;
  static fd::arg<2> _2;
  static fd::arg<3> _3;
  static fd::arg<4> _4;
  static fd::arg<5> _5;
  static fd::arg<6> _6;
  static fd::arg<7> _7;
  static fd::arg<8> _8;
  static fd::arg<9> _9;

} // unnamed namespace

// ===========================================================================

int hello(int n) { cout << "int ::hello(int " << n << ")" << endl; return n; }

int hellohello(CDerived1 * pDerived1, int n) { cout << "int ::hellohello(pDerived, int " << n << ")" << endl; return n; }

// ------------------------------

void DoSomethingWithMyDelegate1(fd::delegate1<int, int> dg) { dg(999); }
void DoSomethingWithMyDelegate2(fd::delegate1<int, int> const & dg) { dg(888); }

// ------------------------------

int doSomethingFree0(int n) { cout << "int ::doSomethingFree0(int " << n << ")" << endl; return n; }
int doSomethingFree1(int n) { cout << "int ::doSomethingFree1(int " << n << ")" << endl; return n; }
int doSomethingFree2(int n) { cout << "int ::doSomethingFree2(int " << n << ")" << endl; return n; }

// ------------------------------

int doSomethingVolatile(int volatile * n) { cout << "doSomethingVolatile(int volatile " << *n << ")" << endl; return *n; }

// ------------------------------

int FD_STDCALL_ my_stdcall(int n) { cout << "int __stdcall my_stdcall(int " << n << ")" << endl; return n; }

// ===========================================================================

void test_delegate()
{

#if defined(FD_MS_VC6)
  typedef fd::delegate1<int, int>    MyDelegate;
#else
  typedef fd::delegate<int (int)>    MyDelegate;
#endif

  cout << "// ===========================================================================" << endl;
  cout << "// Basic Usage" << endl;
  cout << "// (three callable entities, function, member function and functor)" << endl;
  cout << "// ===========================================================================" << endl;
  
  { // 1) free (non-member) function / static member function
    cout << endl << "1) free (non-member) function / static member function" << endl;

    MyDelegate dg1(&::hello);
    MyDelegate dg2 = &CBase1::foobar;

    int r1 = dg1(123);
    int r2 = dg2(234);

    dg2 = MyDelegate(&CDerived1::foobar);
    dg1 = &CDerived1::foobar;

    int r3 = dg1(345);
    int r4 = dg2(456);
  }

  { // 2) member function
    cout << endl << "2) member function" << endl;

    CBase1 b1; CDerived1 d1("d1"), d2("d2");
    const CDerived1 cd1("cd1");

    // the second template paramter to specify callee type, it can be either pointer or reference
    fd::delegate2<int, CBase1 *, int> dg1(&CBase1::foo);
    fd::delegate2<int, CDerived1 &, int> dg2 = &CDerived1::foo;

    dg1(&b1, 123); // b1.foo(123);
    dg2(d1, 234);  // d1.foo(234);

    dg1(&d1, 123); // d1.CBase1::foo(123); implicit cast (casting from the derived class to the base class) is always safe
    d1.CBase1::foo(123);

    // dg2(b1, 234);  // compile error! '()' : cannot convert parameter 1 from 'class CBase1 *' to 'class CDerived1 *'
    // b1.CDerived::foo(234);  // compile error! 'CDerived' : is not a member of 'CBase1'

    dg1 = fd::delegate2<int, CBase1 *, int>(&CBase1::bar);
    // dg1 = fd::delegate2<int, CBase1 *, int>(&CBase1::foobar); // compile error! foobar is static member function

    dg1(&b1, 345);  // b1.bar(345);

    dg1(&d1, 345);  // d1.bar(345);
    d1.bar(345);

    dg2 = fd::delegate2<int, CDerived1 &, int>(&CDerived1::bar);  // compile error! delegate type mismatch
    // dg2 = fd::delegate2<int, CDerived1 *, int>(&CDerived1::bar);  // compile error! delegate type mismatch
    // dg2 = fd::delegate2<int, CDerived1 const &, int>(&CDerived1::bar);  // compile error! delegate type mismatch (const qualifier mismatch)

    dg2(d1, 456); // d1.bar(456);

    // --------------------------------------------------

    // a)
    fd::delegate2<int, CDerived1 *, int> dg3 = &CDerived1::virtual_not_overridden;
    // member function pointer 'CDerived1::virtual_not_overridden' is interpreted and treated as 'CBase1::virtual_not_overridden' internally,
    // also it should be noted that the template parameter is passed over as 'CBase1::virtual_not_overridden', not 'CDerived1::virtual_not_overridden'

    dg3(&d1, 567);  // d1.CBase1::virtual_not_overridden(567);
    // b)
    d1.CBase1::virtual_not_overridden(567);
    // c)
    d1.virtual_not_overridden(567);

    // --------------------------------------------------

    fd::delegate3<int, CDerived1 *, CDerived1 *, int> dg4 = &CDerived1::foofoobar;

    dg4(&d1, &d2, 789); // dg1.foofoobar(&d2, 678);

    dg4(&d2, &d1, 789); // dg2.foofoobar(&d1, 678);

    // --------------------------------------------------

    fd::delegate2<int, CDerived1 &, int> dg5_1(&CDerived1::bar);
    dg5_1(d1, 890);
    //  fd::delegate2<int, CDerived1 const &, int> dg5_2(&CDerived1::bar);
    fd::delegate2<int, CDerived1 &, int> dg5_3(&CDerived1::foo);
    dg5_3(d1, 890);
    //  dg5_3(cd1, 890);
    fd::delegate2<int, CDerived1 const &, int> dg5_4(&CDerived1::foo);
    dg5_4(d1, 890);
    dg5_4(cd1, 890);

    // --------------------------------------------------

    fd::delegate2<int, CDerived1 *, int> dg6_1(&CDerived1::bar);
    dg6_1(&d1, 901);
    //  fd::delegate2<int, CDerived1 const *, int> dg6_2(&CDerived1::bar);
    fd::delegate2<int, CDerived1 *, int> dg6_3(&CDerived1::foo);
    dg6_3(&d1, 901);
    //  dg6_3(&cd1, 901);
    fd::delegate2<int, CDerived1 const *, int> dg6_4(&CDerived1::foo);
    dg6_4(&d1, 901);
    dg6_4(&cd1, 901);

    // --------------------------------------------------
  }

  { // 3) functor
    cout << endl << "3) functor" << endl;

    Ftor1 f1;

    // MyDelegate dg1(f1); // compile error! do not support copy c'tor from a functor
    MyDelegate dg1(&f1, true);
    // MyDelegate dg2 = f2; // compile error! do not support copy c'tor from a functor
    MyDelegate dg2;

    // functor which has a matching signature can be assigned through the special assignment operator (=)
    dg1 <<= &f1;
    // dg1 <<= &f1;  // compile error! assignment is only allowed by reference not by pointer

    // I tried to use operator = () but there was found to be an overload function call ambiguity issue which I couldn't solve,
    // therefore I decided to supply operator >>= () for functor assignment.

    dg1(123);

    {
      // (note)
      // A functor is rather being referenced than being actually cloned when the functor assignment is applied,
      // This is a different behavior from what boost::function does, and boost::function with boost::ref or boost::cref to assign
      // a functor is more similar to how delegate assign a functor here.
      // if functor has a state (non stateless-functor), the caller must guarantee that the target functor is in a valid state
      // when the assigned delegate is being invoked.
      // As a benefit from referencing rather than cloning is apparently a big improvement in speed while copying delegate, 
      // which exactly corresponds to the initial design criteria of delegate.
      // (cloning functor can be achieved through heap memory allocation with typed cloning manager(?), which tend to be slow
      // operation to avoid when many copies of delegate are required. I think boost::function use typed cloning manager)

      Ftor2 f2("Ftor2");
      dg2 <<= &f2;

      // target functor 'f2' is in a valid state here
      dg2(234);
    }

    // target functor 'f2' is not in a valid state anymore, name field is displayed as blank in this call
    dg2(345);
    // compiler ok! and run ok without runtime error here, but it might cause an undefined behavior some time later by accessing invalid memory
    // which will be extremely hard to spot when it occurs.
                        
  }

  cout << endl << "push any key to continue" << endl; _getch(); 
  cout << "// ===========================================================================" << endl;
  cout << "// Member function argument binding" << endl;
  cout << "// ===========================================================================" << endl;
  {
    CBase2 b2("b2");
    CBase3 b3("b3");
    CDerived2 d2("d2");

    // argument binding alway takes a pointer form (not reference) for callee object to be bound
    MyDelegate dg1(&CBase2::foo, &b2);

    MyDelegate dg2;
    dg2.bind(&CBase3::foo, &b3);  // bind member function

    // fd::bind is supported for easy conversion from the existing codes that use boost::bind with placeholders
    // this seems working well but be reminded that placeholder in fd::bind is just a placeholder, thus ignored, and do not
    // perform as what boost::bind does
    fd::delegate1<int, int> dg3 = fd::bind(&CDerived2::foo, &d2, _1);
    // boost::function1<int, int> bfn = boost::bind(&CDerived2::foo, &d2, _1);

    dg1(123);
    dg2(234);
    dg3(345);

    // (note)
    // the callee object bound is stored as a reference and no cloning occurs internally so that the caller must guarantee
    // that the target callee object is in a valid state when the assigned delegate is being invoked.
    MyDelegate d4;
    {
      CDerived2 d2_2("d2_2");
      d4.bind(&CDerived2::bar, &d2_2);

      // callee object d2_2 is in a valid state
      d4(456);
    }

    // callee object d2_2 is not in a valid state anymore, name field is displayed as blank in this call
    d4(567);
    // compiler ok! and run ok without runtime error here, but it might cause an undefined behavior some time later by accessing invalid memory
    // which will be extremely hard to spot when it occurs.
  }

  cout << endl << "push any key to continue" << endl; _getch(); 
  cout << "// ===========================================================================" << endl;
  cout << "// Helper function - make_delegate()" << endl;
  cout << "// ===========================================================================" << endl;

  { // 1) to pass over to the input parameter of a function
    cout << endl << "1) to pass over to the input parameter of a function" << endl;

    // 1-a)
    DoSomethingWithMyDelegate1(&CBase1::foobar);
    // 1-a)
    DoSomethingWithMyDelegate1(MyDelegate(&CBase1::foobar));
    // 1-c)
    DoSomethingWithMyDelegate1(fd::make_delegate(&CBase1::foobar));
    
    // --------------------------------------------------
    
    // 2) member function argument binding
    //
    // 2-a)
    CBase1 b1; CDerived1 d1("d1");
    const CDerived1 cd1("cd1");

    MyDelegate dg1;
    dg1.bind(&CBase1::foo, &b1);
    DoSomethingWithMyDelegate2(dg1);
    // 2-b)
    DoSomethingWithMyDelegate2(MyDelegate(&CBase1::foo, &b1));
    // 2-c)
    DoSomethingWithMyDelegate2(fd::make_delegate(&CBase1::foo, &b1));
    // make_delegate() only takes a pointer (not reference) to callee object For argument binding
    
    // --------------------------------------------------
    
    // 3) member function adapter version of make_delegate()
    //
    // 3-a)
    fd::delegate2<int, CDerived1 *, int> dg2 = fd::make_delegate((CDerived1 *)0, &CDerived1::bar);
    // when using member function adapter version of make_delegate(), caller must specify callee object
    // type explicitly since there is some case where callee object is different from what was specified
    // in member function pointer. CDerived1::virtual_not_overridden explained above is a such an example.
    dg2(&d1, 123);

    //
    // int CDerived1::foo(int) const
    // 
    fd::delegate2<int, CDerived1 *, int> dg2_1 = fd::make_delegate((CDerived1 *)0, &CDerived1::foo);
    dg2_1(&d1, 123);
    //	dg2_1(&cd1, 123);

    fd::delegate2<int, CDerived1 const *, int> dg2_2 = fd::make_delegate((CDerived1 const *)0, &CDerived1::foo);
    dg2_2(&d1, 123);
    dg2_2(&cd1, 123);

    // 3-b)
    fd::delegate2<int, CBase1 *, int> dg3 = &CDerived1::virtual_not_overridden;
    fd::delegate2<int, CDerived1 *, int> dg4 = &CDerived1::virtual_not_overridden;
    fd::delegate2<int, CBase1 *, int> dg5 = fd::make_delegate((CBase1 *)0, &CDerived1::virtual_not_overridden);
    fd::delegate2<int, CDerived1 *, int> dg6 = fd::make_delegate((CDerived1 *)0, &CDerived1::virtual_not_overridden);
    // even though 'CDerived1::virtual_not_overridden' is specified as the second parameter for make_delegate()
    // the actual member function pointer of type 'int CBase1::virtual_not_overridden(int)' is being passed over
    // into make_delegate() (R := int, U := CBase1, T1 := int) therefore it is required to specify how is the actual
    // member function pointer given is supposed to be treated by providing the proper type null pointer as the first
    // argument to the make_delegate()
    
    dg3(&b1, 234);
    dg4(&d1, 345);
    dg5(&b1, 456);
    dg6(&d1, 567);
    
    // 3-c)
    // member function adapter version of make_delegate only takes a pointer to the callee object
    fd::delegate2<int, CDerived1 *, int> dg7(&CDerived1::bar);
    fd::delegate2<int, CDerived1 &, int> dg8(&CDerived1::bar);
    fd::delegate2<int, CDerived1 *, int> dg9 = fd::make_delegate((CDerived1 *)0, &CDerived1::bar);
    // fd::delegate2<int, CDerived1 &, int> dg10 = fd::make_delegate((CDerived1 *)0, &CDerived1::bar);	// compile error!
    
    dg7(&d1, 678);
    dg8(d1, 789);
    dg9(&d1, 890);
  }

  cout << endl << "push any key to continue" << endl; _getch(); 
  cout << "// ===========================================================================" << endl;
  cout << "// Comparisons and misc." << endl;
  cout << "// ===========================================================================" << endl;
  {
    CBase1 b1, b2;
    CDerived1 d1("d1");

    // ----------------------------------------------------------------------

    MyDelegate dg1(&CBase1::foo, &b1);
    MyDelegate dg2 = &::hello;

    if(dg1 == dg2)
      cout << "dg1 equals to dg2" << endl;
    else
      cout << "dg1 does not equal to dg2" << endl;

    if(dg1 > dg2)
    {
      cout << "dg1 is greater than dg2" << endl;
      dg1(123);
    }
    else if(dg1 < dg2)
    {
      cout << "dg2 is greater than dg1" << endl;
      dg2(234);
    }

    // ----------------------------------------------------------------------

    MyDelegate dg3 = dg1;
    MyDelegate dg4(&CBase1::foo, &b2);

    // both function pointer and its bound callee object pointer stored in dg1 is the same as those stored in dg3
    if(0 == dg1.compare(dg3)) // this test return true
    {
      dg3(345);
    }
    if(0 == dg1.compare(dg3, true)) // this test return true as well
    {
      dg3(456); 
    }

    // ----------------------------------------------------------------------

    // function pointer stored in dg1 is the same as that stored in dg4 but their bound callee object pointers are not the same
    if(0 == dg1.compare(dg4)) // this test return true
    {
      dg4(567);
    }
    if(0 == dg1.compare(dg4, true)) // this test return fail
    {
      dg4(678);
    }

    // ----------------------------------------------------------------------

    if(dg2 != 0)  // this test return true
    {
      cout << "dg2 is not empty" << endl;
    }

    if(dg2)  // this test return true
    {
      cout << "dg2 is not empty" << endl;
    }

    if(!!dg2)  // this test return true
    {
      cout << "dg2 is not empty" << endl;
    }

    if(!dg2.empty())  // this test return true
    {
      cout << "dg2 is not empty" << endl;
    }

    // ----------------------------------------------------------------------

    dg1.swap(dg2);

    MyDelegate(dg2).swap(dg1);  // dg1 = dg2;

    MyDelegate().swap(dg1); // dg1.clear();

    dg2.clear();

    dg3 = 0;

    // ----------------------------------------------------------------------

    if(dg3.empty())
    {
      try
      {
        dg3(789);
      }
      catch(std::exception & e) { cout << e.what() << endl; } // 'call to empty delegate' exception
    }

    // ----------------------------------------------------------------------

    CBase1 * pBase = 0;
#if !defined(FD_MS_VC6)
    dg3.bind(&CBase1::foo, pBase);  // binding null callee object on purpose
#else

    // dg3.bind(&CBase1::foo, pBase);  // binding null callee object on purpose

    //
    // VC6 bug, can't use pointer to the bound object
    // error C2667: 'bind' : none of 2 overload have a best conversion
    // error C2668: 'bind' : ambiguous call to overloaded function
    //

    // Workaround: use template<typename T> T * fd::get_pointer(T *);
    dg3.bind(&CBase1::foo, fd::get_pointer(pBase));  // binding null callee object on purpose

#endif
    try
    {
      FD_ASSERT( !dg3.empty() );
      dg3(890);
    }
    catch(std::exception & e) { cout << e.what() << endl; } // 'member function call on no object' exception


    // ----------------------------------------------------------------------

#if !defined(FD_MS_VC6)
    {
      
      // Mixing portable syntax and preferred syntax is just fine as they are the same
      
      typedef fd::delegate1<int, int> PortableSyntax;
      typedef fd::delegate<int (int)> PreferredSyntax;

      CBase2 b2("b2"); CDerived2 d2("d2");
      
      PortableSyntax dg1(&CBase2::foo, &b2);
      PreferredSyntax dg2 = dg1;

      if(dg1 == dg2)  // this test return true
      {
        dg1(123);
      }

      PortableSyntax dg3;

      dg3.swap(dg2);

      FD_ASSERT( dg2.empty() );

      PortableSyntax dg4 = fd::make_delegate(&CDerived2::bar, &d2);
      PreferredSyntax dg5 = fd::make_delegate(&CDerived2::bar, &d2);

      FD_ASSERT( dg4 == dg5 );

      dg4(234);
      dg5(345);
        
    }
#endif  // #if !defined(FD_MS_VC6)

  }

  cout << endl << "push any key to continue" << endl; _getch(); 
  cout << "// ===========================================================================" << endl;
  cout << "// Use delegate in STL containers & algorithms" << endl;
  cout << "// ===========================================================================" << endl;
  {
    // std::unary_function compatible
    typedef fd::delegate1<float, long> my_unary_delegate;
    my_unary_delegate my_udg; my_udg;
    enum
    {
      value1 = fd::util::Is_same_type<float, my_unary_delegate::result_type>::value,
      value2 = fd::util::Is_same_type<long, my_unary_delegate::argument_type>::value
    };

    FD_ASSERT( value1 );  // ok
    FD_ASSERT( value2 );  // ok

    // std::binary_function compatible
    typedef fd::delegate2<double, char *, int []> my_binary_delegate;
    my_binary_delegate my_bdg; my_bdg;
    enum
    {
      value3 = fd::util::Is_same_type<double, my_binary_delegate::result_type>::value,
      value4 = fd::util::Is_same_type<char *, my_binary_delegate::first_argument_type>::value,
      value5 = fd::util::Is_same_type<int [], my_binary_delegate::second_argument_type>::value,
    };

    FD_ASSERT( value3 );  // ok
    FD_ASSERT( value4 );  // ok
    FD_ASSERT( value5 );  // ok

    // --------------------------------------------------

    CManyFunctions cmf;
    vector<MyDelegate> vecMyDelegate;

    fd::delegate1<int, int> ttt;
    const fd::delegate1<int, int> ttt2;
    ttt = ttt2;
    vecMyDelegate.push_back(fd::make_delegate(&CManyFunctions::doSomething2, &cmf));
    vecMyDelegate.push_back(fd::make_delegate(&CManyFunctions::doSomething4, &cmf));
    vecMyDelegate.push_back(fd::make_delegate(&CManyFunctions::doSomething5, &cmf));
    vecMyDelegate.push_back(fd::make_delegate(&CManyFunctions::doSomething6, &cmf));
    vecMyDelegate.push_back(fd::make_delegate(&CManyFunctions::doSomething7, &cmf));
    vecMyDelegate.push_back(fd::make_delegate(&CManyFunctions::doSomething0, &cmf));
    vecMyDelegate.push_back(fd::make_delegate(&CManyFunctions::doSomething1, &cmf));
    vecMyDelegate.push_back(fd::make_delegate(&CManyFunctions::doSomething3, &cmf));
    vecMyDelegate.push_back(fd::make_delegate(&CManyFunctions::doSomething8, &cmf));
    vecMyDelegate.push_back(fd::make_delegate(&CManyFunctions::doSomething9, &cmf));
    vecMyDelegate.push_back(fd::make_delegate(&::doSomethingFree0));
    vecMyDelegate.push_back(fd::make_delegate(&::doSomethingFree1));
    vecMyDelegate.push_back(fd::make_delegate(&::doSomethingFree2));
    vecMyDelegate.push_back(fd::make_delegate(&CManyFunctions::doSomethingStatic0));
    vecMyDelegate.push_back(fd::make_delegate(&CManyFunctions::doSomethingStatic1));
    vecMyDelegate.push_back(fd::make_delegate(&CManyFunctions::doSomethingStatic2));

    cout << endl << "Before meaningless sorting" << endl;
    for_each(vecMyDelegate.begin(), vecMyDelegate.end(), invoker_ii(123));

    // meaning-less sorting
    // - sorted by comparing two memory locations, using ::memcmp(), which are pointed by each function pointers
    // if FD_COPARE_WITH_ENDIANESS_CORRECT is defined, before including, directly or indirectly, "delegate.h"
    // (and link incrementally option is off in case of VC), functions will be sorted as they are declared, but
    // it doesn't really mean anything so that I disable it by default.
    sort(vecMyDelegate.begin(), vecMyDelegate.end(), std::greater<MyDelegate>());

    cout << endl << "After meaningless sorting" << endl;
    for_each(vecMyDelegate.begin(), vecMyDelegate.end(), invoker_ii(123));

  // --------------------------------------------------

    CMyWindow myWin;
    
    myWin.RegisterMessageHandler(UWM_MESSAGE1, &CMyWindow::OnMessageHandler1);
    myWin.RegisterMessageHandler(UWM_MESSAGE2, &CMyWindow::OnMessageHandler2);
    myWin.RegisterMessageHandler(UWM_MESSAGE3, CMyWindow::MessageHandlerType(&CMyWindow::OnMessageHandler3));
    myWin.RegisterMessageHandler(UWM_MESSAGE4, fd::make_delegate((CMyWindow *)0, &CMyWindow::OnMessageHandler4));
    myWin.RegisterMessageHandler(UWM_MESSAGE5, &CMyWindow::OnMessageHandler5);
    myWin.RegisterMessageHandler(UWM_MESSAGE6, &CMyWindow::OnMessageHandlerStatic1);
    myWin.RegisterMessageHandler(UWM_MESSAGE7, CMyWindow::MessageHandlerType(&CMyWindow::OnMessageHandlerStatic2));
    myWin.RegisterMessageHandler(UWM_MESSAGE8, fd::make_delegate(&CMyWindow::OnMessageHandlerStatic3));

    LRESULT res = 0;
    res = myWin.SendMessage(UWM_MESSAGE3, (WPARAM)123, (LPARAM)234);

    // to change message handler dynamically at run-time
    myWin.RegisterMessageHandler(UWM_MESSAGE3, &CMyWindow::OnMessageHandlerStatic2);

    res = myWin.SendMessage(UWM_MESSAGE3, (WPARAM)567, (LPARAM)678);
  }

  cout << endl << "push any key to continue" << endl; _getch(); 
  cout << "// ===========================================================================" << endl;
  cout << "// Speed Benchmarks" << endl;
  cout << "// ===========================================================================" << endl;
  {
    {
      //
      // invocation
      //

      cout << "Invocation test" << endl;

      CBase1 b1;
      fd::delegate0<void> dg1(&CBase1::dummy, &b1);
      fd::delegate0<void> dg2(&CBase1::static_dummy);
      // boost::function0<void> dg2(&CBase1::static_dummy);

      enum { loop = 12345678 };
      cout << endl << "member function 'void CBase1::dummy()' invocation" << endl;
      {
        lres_timer t2("member function");
        for(long i = 0; i < loop; ++i)
        {
          volatile int no_loop_opt = 1;
          b1.dummy();
        }
      }

      cout << endl << "member function delegate 'dg1(&CBase1::dummy, b1)' invocation" << endl;
      {
        lres_timer t2("member function delegate");
        for(long i = 0; i < loop; ++i)
        {
          volatile int no_loop_opt = 1;
          dg1();
        }
      }

      cout << endl << "static member function 'void CBase1::static_dummy()' invocation" << endl;
      {
        lres_timer t2("static member function");
        for(long i = 0; i < loop; ++i)
        {
          volatile int no_loop_opt = 1;
          CBase1::static_dummy();
        }
      }

      cout << endl << "static member function delegate 'dg2(&CBase1::static_dummy())' invocation" << endl;
      {
        lres_timer t2("static member function delegate");
        for(long i = 0; i < loop; ++i)
        {
          volatile int no_loop_opt = 1;
          dg2();
        }
      }
    }

    {
      //
      // copying
      //

      cout << "Copying test" << endl;

      CDerived2 d2("d2");

      typedef std::allocator<void> Allocator;
      // typedef fd::util::std_allocator<void> Allocator;
      // typedef fd::util::fixed_allocator<void> Allocator;
      
      typedef fd::delegate1<int, int, Allocator, 1> MyDelegateBufSize4;  // 4 * 1 = 4
      typedef fd::delegate1<int, int, Allocator, 4> MyDelegateBufSize16; // 4 * 4 = 16
      
      cout << "sizeof(MyDelegateBufSize4) = " << sizeof(MyDelegateBufSize4) << " & buffer size = 4" << endl;    // 12 + 4 + alpha
      cout << "sizeof(MyDelegateBufSize16) = " << sizeof(MyDelegateBufSize16) << " & buffer size = 16" << endl;  // 12 + 16 + 0
      
      cout << "sizeof(&CDerived2::bar) = " << sizeof(&CDerived2::bar) << endl;
      
      MyDelegateBufSize4 dg1(&CDerived2::bar, &d2), dg2;
      MyDelegateBufSize16 dg3(&CDerived2::bar, &d2), dg4;
      
      FD_ASSERT(sizeof(&CDerived2::bar) > 4);   // dg1 & dg2 use heap allocation memory to store function pointer
      FD_ASSERT(sizeof(&CDerived2::bar) < 16);  // dg3 & dg4 use internal buffer (no heap allocation)

      enum { loop = 12345678 };

      cout << endl << "raw member function pointer" << endl;
      { // raw member function pointer

        typedef int (CDerived2::*TMFn)(int);

        TMFn volatile mfn1 = &CDerived2::bar;
        CDerived2 volatile * obj_ptr1 = &d2;

        TMFn volatile mfn2 = 0;
        CDerived2 volatile * obj_ptr2 = 0;

        lres_timer t("#0");

        for(long i = 0; i < loop; ++i)
        {
          mfn2 = mfn1;
          obj_ptr2 = obj_ptr1;

          mfn2 = 0;
          obj_ptr2 = 0;
        }
      }

      cout << endl << "member function pointer in the internal buffer" << endl;
      cout << "& storing pointer to bound object" << endl;
      { // member function pointer stored in the internal buffer (no heap allocation)
        lres_timer t("#1");
        
        for(long i = 0; i < loop; ++i)
        {
          dg4 = dg3;
          dg4.clear();
        }
      }
      
      cout << endl << "member function pointer in the heap memory allocated" << endl;
      cout << "& storing pointer to bound object" << endl;
      { // member function pointer stored in the allocated heap memory
        lres_timer t("#2");
        
        for(long i = 0; i < loop; ++i)
        {
          dg2 = dg1;
          dg2.clear();
        }
      }

#if !defined(FD_DISABLE_CLONE_BOUND_OBJECT)

      MyDelegateBufSize4 dg5(&CDerived2::bar, d2), dg6;
      MyDelegateBufSize16 dg7(&CDerived2::bar, d2), dg8;

      cout << endl << "member function pointer in the internal buffer" << endl;
      cout << "& cloning bound object" << endl;
      { // member function pointer stored in the internal buffer (no heap allocation)
        lres_timer t("#3");
        
        for(long i = 0; i < loop; ++i)
        {
          dg8 = dg7;
          dg8.clear();
        }
      }
      
      cout << endl << "member function pointer in the heap memory allocated" << endl;
      cout << "& cloning bound object" << endl;
      { // member function pointer stored in the allocated heap memory
        lres_timer t("#4");
        
        for(long i = 0; i < loop; ++i)
        {
          dg6 = dg5;
          dg6.clear();
        }
      }

#endif  // #if !defined(FD_DISABLE_CLONE_BOUND_OBJECT)

    }
  }

  cout << endl << "push any key to continue" << endl; _getch(); 
  cout << "// ===========================================================================" << endl;
  cout << "// Cv-qualifiers" << endl;
  cout << "// ===========================================================================" << endl;
  {
    // --------------------------------------------------
    // const
    // --------------------------------------------------

    CBase1 b1;
    CBase1 const cb1;

    {
      // --------------------------------------------------
      // argument binding
      
      MyDelegate dg1(&CBase1::foo, &b1);
      MyDelegate dg2(&CBase1::foo, &cb1);
      MyDelegate dg3(&CBase1::bar, &b1);
      // MyDelegate dg4(&CBase1::bar, &cb1); // compile error! const member function can not be called on non-const object
      
      dg1(123);
      dg2(234);
      dg3(345);
      
      // --------------------------------------------------
      // member function adapter
      
      fd::delegate2<int, CBase1 *, int> dg4(&CBase1::foo);
      fd::delegate2<int, CBase1 *, int> dg5(&CBase1::bar);
      fd::delegate2<int, CBase1 const *, int> dg6(&CBase1::foo);
      // fd::delegate2<int, CBase1 const *, int> dg7(&CBase1::bar);  // compile error! non-const member function can not be used for const member function adapter
      
      dg4(&b1, 456);
      // dg4(&cb1, 456); // compile error! const object cannot be used non-const member function adpater
      dg5(&b1, 567);
      // dg5(&cb1, 567); // compile error! const object cannot be used non-const member function adpater
      dg6(&b1, 678);
      dg6(&cb1, 678);
    }

    // --------------------------------------------------
    // volatile
    // - volatile is not supported at all
    // --------------------------------------------------

    CBase1 volatile vb1;
    CBase1 const volatile cvb1;
    {
      // --------------------------------------------------
      // argument binding (volatile object can not be bound to delegate at all)

      // MyDelegate dg1(&CBase1::foo, &vb1);  // compile error! volatile object can not be bound
      // MyDelegate dg2(&CBase1::foo, &cvb1); // compile error! volatile object can not be bound
      // MyDelegate dg3(&CBase1::bar, &vb1);  // compile error! volatile object can not be bound
      // MyDelegate dg4(&CBase1::bar, &cvb1); // compile error! volatile object can not be bound

      // --------------------------------------------------
      // member function adapter (volatile object can not be used as member function adapter at all)

      // fd::delegate2<int, CBase1 volatile *, int> dg5(&CBase1::foo);       // compile error! 
      // fd::delegate2<int, CBase1 const volatile *, int> dg6(&CBase1::foo); // compile error! 
      // fd::delegate2<int, CBase1 volatile *, int> dg5(&CBase1::bar);       // compile error! 
      // fd::delegate2<int, CBase1 const volatile *, int> dg6(&CBase1::bar); // compile error! 
    }

    fd::delegate1<int, int volatile *> dg6(&::doSomethingVolatile);
    int volatile vn = 10;
    dg6(&vn);

  }

  cout << endl << "push any key to continue" << endl; _getch(); 
  cout << "// ===========================================================================" << endl;
  cout << "// Platform specific calling convention" << endl;
  cout << "// ===========================================================================" << endl;
  {
    // FD_FN_ENABLE_STDCALL macro is defined before including "delegate.h"
    // to support __stdcall free function
    MyDelegate dg1(&::my_stdcall);

    dg1(123);

    // --------------------------------------------------

    CFastCallClass fcc;

    // FD_MEM_FN_ENABLE_FASTCALL macro is defined before including "delegate.h"
    // to support __fastcall member function
    MyDelegate dg2(&CFastCallClass::foo, &fcc);
    
    dg2(234);

    // --------------------------------------------------

    // FD_MEM_FN_ENABLE_CDECL macro is defined before include "delegate.h"
    // to support __cdecl member function
    fd::delegate2<int, CFastCallClass *, int> dg3(&CFastCallClass::bar);

    dg3(&fcc, 345);

  }

#if !defined(FD_DISABLE_TYPE_RELAXATION)

  cout << endl << "push any key to continue" << endl; _getch(); 
  cout << "// ===========================================================================" << endl;
  cout << "// Type Relaxation" << endl;
  cout << "// ===========================================================================" << endl;
  {
    {
      // Template parameter types passed over to delegate are very strictly checked but this could be too much in real life.
      // there might be a situation we want to treat bunch of int (*)(int) functions and int (*)(long) functions together,
      // when these functions are assigned into delegate1<int, int>, compiler will emits errors for int (*)(long)
      // functions saying that it can't not be assigned since 'int' and 'long' are different type.
      //
      // By defining FD_TYPE_RELAXATION macro before including "delegate.h", type-check relaxation can be enabled.
      // IOW, a function (free function, member function or functor) can be assigned or binded to fd::delegate whenever
      // the following three conditions are met,
      //
      //    a) the number of argument matches,
      //    b) each matching argument can be trivially converted (from delegate's argument to target function's argument) by compiler,
      //    c) return type can be trivially converted (from delegate's return type to target function's return type "and vice versa") by compiler.
      //
      // if any of above conditions can not be met, compiler will complain about it (compile-time warning and/or error messages)
      // 
      
      CBase1 b1;
      //
      // int CBase1::foo(int) const;
      // int CBase1::bar(int);
      //

      fd::delegate1<int, long> dg1(&CBase1::foo, &b1);
      //
      // the above delegate definition is theoretically equivalent to the following definition
      // 
      // CBase1 b1;
      // int fd_delegate1_dg1(long l)
      // {
      //   return b1.foo(l);
      // }
      //
      // the above example show why three conditions is required to be fulfilled for fd::delegate to work in type-check relaxation mode
      //
      dg1(123);
      
      // --------------------------------------------------
      
      fd::delegate1<float, long> dg2(&CBase1::bar, &b1); // compile warning! : 'return' : conversion from '' to '', possible loss of data
      // 'int' result type to 'float' result type can be converted seamlessly,
      // but 'float' return type to 'int' return type can cause a possible loss of data
      //
      // float fd_delegate1_dg2(long l)
      // {
      //   return b1.bar(l);  // compile warning! : possible loss of data
      // }
      //
      dg2(234);
      
      // --------------------------------------------------
      
      // fd::delegate1<int, char *> dg3(&CBase1::foo, &b1); // compile error! : cannot convert parameter 3 from 'char *' to 'int'
      //
      // int fd_delegate1_dg3(char * ch)
      // {
      //   return b1.foo(ch);  // compile error! : cannot convert parameter 'ch' from 'char *' to 'int'
      // }

      // --------------------------------------------------
      fd::delegate1<int, long> dg4(&::hello);
      dg4(456);

      // --------------------------------------------------

      CDerived1 d1("d1");
      //
      // class CDerived1 : public CBase1 { };
      //
      fd::delegate2<int, CDerived1 *, long> dg5(&CBase1::bar);
      //
      // int fd_delegate2_dg5(CDerived1 * pd1, long l)
      // {
      //   return pd1->bar(l);
      // }
      //
      // Upcasting from 'CDerived1 *' to 'CBase1 *' is always safe and can be converted trivially.
      //
      //
      dg5(&d1, 567);

    }

    // ====================================================================================================
    // FD_TYPE_RELAXATION & make_delegate()
    // ====================================================================================================
    {
      //
      // (remark)
      // fd::bind() does not support FD_TYPE_RELAXATION, while fd::make_delegate() does support it as will be shown below
      //

      // typedef fd::delegate1<int, int> MyDelegate;
      typedef fd::delegate1<int, long> MyDelegateIntLong;
      CBase1 b1;

      // --------------------------------------------------

      MyDelegate dg1 = fd::make_delegate(&CBase1::foo, &b1);
      dg1(123);

      MyDelegate dg2 = fd::make_delegate(&::hello);
      dg2(234);

      fd::delegate2<int, CBase1 *, int> dg3 = fd::make_delegate((CBase1 *)0, &CBase1::bar);
      dg3(&b1, 345);

      // --------------------------------------------------

      // [obsolete]
      // type-check relaxation version of make_delegate take a null type as the first extra argument to
      // retrieve the function type information (return type, parameters type and callee class type)

//#if !defined(FD_MS_VC6)
//      //
//      // VC6 cannot distinguish the different version of make_delegate()s when FD_TYPE_RELAXATION is enabled
//      // and emits "fatal error C1001: INTERNAL COMPILER ERROR", sigh~~~
//      //
//
//      MyDelegateIntLong dg4 = fd::make_delegate((MyDelegateIntLong *)0, &CBase1::foo, &b1);
//      dg4(456);
//
//      MyDelegateIntLong dg5 = fd::make_delegate((MyDelegateIntLong *)0, ::hello); // free function & type-check relaxation
//      dg5(567);
//
//      typedef fd::delegate2<int, CBase1 *, long> MyDelegateAdapterIntLong1;
//      typedef fd::delegate<int (CBase1 *, long)> MyDelegateAdapterIntLong2;
//
//      MyDelegateAdapterIntLong1 dg6_1 = fd::make_delegate((MyDelegateAdapterIntLong1 *)0, &CBase1::bar); // member function adapter & type-check relaxation
//      dg6_1(&b1, 678);
//
//      MyDelegateAdapterIntLong1 dg6_2 = fd::make_delegate((MyDelegateAdapterIntLong2 *)0, &CBase1::bar); // member function adapter & type-check relaxation
//      dg6_2(&b1, 789);
//
//      MyDelegateAdapterIntLong2 dg7_1 = fd::make_delegate((MyDelegateAdapterIntLong1 *)0, (CBase1 *)0, &CBase1::bar);  // member function adapter & type-check relaxation
//      // the second argument is redundant as that type information can be retrieved from the first argument
//      // but I left this version of make_delegate() to be coincident with other versions
//      dg7_1(&b1, 890);
//
//      MyDelegateAdapterIntLong2 dg7_2 = fd::make_delegate((MyDelegateAdapterIntLong2 *)0, (CBase1 *)0, &CBase1::bar);  // member function adapter & type-check relaxation
//      // the second argument is redundant as that type information can be retrieved from the first argument
//      // but I left this version of make_delegate() to be coincident with other versions
//      dg7_2(&b1, 901);
//
//#endif  // #if !defined(FD_MS_VC6)

      // --------------------------------------------------

    }
  }

#endif  // #if !defined(FD_DISABLE_TYPE_RELAXATION)

  cout << endl << "push any key to end" << endl; _getch(); 
}
