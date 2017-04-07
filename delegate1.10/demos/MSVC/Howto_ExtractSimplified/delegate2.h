// delegate_extract.h

// ====================================================================================================
// BEGIN extraction configuration
// ====================================================================================================

//#define NDEBUG

// #define FD_DISABLE_TYPE_RELAXATION
// #define FD_DISABLE_CLONE_BOUND_OBJECT

// #define FD_MEM_FN_ENABLE_STDCALL
// #define FD_MEM_FN_ENABLE_FASTCALL
// #define FD_MEM_FN_ENABLE_CDECL
// #define FD_FN_ENABLE_STDCALL
// #define FD_FN_ENABLE_FASTCALL
// #define FD_FN_ENABLE_PASCAL

// ====================================================================================================
// END extraction configuration
// ====================================================================================================

// ====================================================================================================

//#include <malloc.h>
//#include <algorithm>
//#include <stdexcept>

// --------------------------------------------------

// ====================================================================================================
// BEGIN of CONFIG
// ====================================================================================================

// ====================================================================================================

// ====================================================================================================

// internal buffer size of delegate in count of (void *)
// buf_size = countof_pvoid * sizeof(void *)

// ====================================================================================================

//
// to enable fd::bind helper function for easy conversion from boost::bind & boost::function to fd::delegate
// define FD_ENABLE_BIND_HELPER_FUNCTION macro before including, directly or indirectly, "delegate.h"
// 
// ====================================================================================================
// #define FD_ENABLE_BIND_HELPER_FUNCTION
// ====================================================================================================
//

// ====================================================================================================

// --------------------------------------------------
//
// to use delegate with __stdcall member functions,
// define FD_MEM_FN_ENABLE_STDCALL macro before including, directly or indirectly, "delegate.h"
//
// ====================================================================================================
// #define FD_MEM_FN_ENABLE_STDCALL
// ====================================================================================================
//
// --------------------------------------------------
//
// to use delegate with __fastcall member functions,
// define FD_MEM_FN_ENABLE_FASTCALL macro before including, directly or indirectly, "delegate.h"
//
// ====================================================================================================
// #define FD_MEM_FN_ENABLE_FASTCALL
// ====================================================================================================
//
// --------------------------------------------------
//
// to use delegate with __cdecl member functions,
// define FD_MEM_FN_ENABLE_CDECL macro before including, directly or indirectly, "delegate.h"
//
// ====================================================================================================
// #define FD_MEM_FN_ENABLE_CDECL
// ====================================================================================================
//
// --------------------------------------------------
//
// to use delegate with __stdcall functions,
// define FD_FN_ENABLE_STDCALL macro before including, directly or indirectly, "delegate.h"
//
// ====================================================================================================
// #define FD_FN_ENABLE_STDCALL
// ====================================================================================================
//
// --------------------------------------------------
//
// to use delegate with __stdcall functions,
// define FD_FN_ENABLE_FASTCALL macro before including, directly or indirectly, "delegate.h"
//
// ====================================================================================================
// #define FD_FN_ENABLE_FASTCALL
// ====================================================================================================
//
// --------------------------------------------------
//
// to use delegate with pascal functions,
// define FD_FN_ENABLE_PASCAL macro before including, directly or indirectly, "delegate.h"
//
// ====================================================================================================
// #define FD_FN_ENABLE_PASCAL
// ====================================================================================================
//
// --------------------------------------------------

// It is best to define these macros in the project options, via -D on the command line, or as the first
// line in the translation unit (.cpp file) where delegate is used. Not following this rule can lead to
// obscure errors when a header includes delegate.h before the macro has been defined.

// ====================================================================================================

//
// Less restrictive types (type-check relaxation)
//
// Callbacks in C++
// ( http://bpeers.com/articles/callback/ )
//
//
// to use this feature, DO NOT define FD_DISABLE_TYPE_RELAXATION macro so that a function is allowed to be assigned/binded
// to delegate as long as it does meet the follwing three conditions
//
//    a) the number of argument matches,
//    b) each matching argument can be trivially converted (from delegate's argument to target function's argument) by compiler,
//    c) return type can be trivaially converted (from delegate's return type to target function's return type "and vice versa") by compiler.
//
// ex)
//
// int foo(int n1, int n2) { };
// long bar(long n, float f) { };
//
// // #define FD_DISABLE_TYPE_RELAXATION
// #include "delegate.h"
//
// typedef fd::delegate<int (int)> MyDelegate;

// MyDelegate dg1 = &foo; // ok!
// MyDelegate dg2 = &bar; // ok! since the number of arguments (2 arguments) match
//                        // and long and floag can be trivially converted into int by compiler
//                        // but float > int conversion might cause a warning of 'possible loss of data'
//                        //
//                        // if FD_DISABLE_TYPE_RELAXATION were to be defined above, it causes errors here
//
// int result1 = dg1(123, 456); // ok!
// int result2 = dg2(345, 678); // ok!
//
// ====================================================================================================
// #define FD_DISABLE_TYPE_RELAXATION
// ====================================================================================================

//
// Cloning bound object
//

// Cloning bound object feature are added in v1.10. and there are several changes in public member function
// interfaces (member fucntion which related with argument binding,
// ex) delegate::bind(mfn, obj), delegate::operator <<= (ftor). fd::make_delegate(mfn, obj), fd::bind(mfn, obj, ...) )
//
// Unless otherwise FD_DISABLE_CLONE_BOUND_OBJECT is defined, the cloning bound object is enabled (default)
//

// ==============================
// argument binding
// ==============================

// CBase1 obj;
// smart_ptr<CBase1> sp(new CBase1);
//
// typedef int (CBase1::*TMFn)(int);
// TMFn mfn = &CBase1::foo;
//
// dg11.bind(mfn, &obj);
// dg12.bind(mfn, obj);
// dg13.bind(mfn, sp);
//
// delegate<> dg14(mfn, &obj);
// delegate<> dg15(mfn, obj);
// delegate<> dg16(mfn, sp);
//
// dg11(123); // (&obj)->foo(123);
// dg12(123); // (internal copy of obj).foo(123);
// dg13(123); // (internal copy of sp)->foo(123);
//
// dg14(123); // (&obj)->foo(123);
// dg15(123); // (internal copy of obj).foo(123);
// dg16(123); // (internal copy of sp)->foo(123);
//

// ==============================
// functor assignment
// ==============================

// struct bar { int operator()(int n) { return n; } };
//
// bar ftor;
//
// dg21 <<= &ftor;
// dg22 <<= ftor;
//
// // the second bool argument below is meaningless and provided just for the different function signature
// delegate<> dg23(&ftor, true); 
// delegate<> dg24(ftor, true);
//
// dg21(123); // (&ftor)->operator()(123);
// dg22(123); // (internal copy of ftor).operator()(123);
//
// dg23(123); // (&ftor)->operator()(123);
// dg24(123); // (internal copy of ftor).operator()(123);
//

//
// the reason I added cloning bound object feature is mostly to support any smart pointer
// (such as std::auto_ptr, boost::shared_ptr or loki::smartPtr)
// Though there are prerequisite/condition to be accomplished for a smart pointer to be recognized and supported
// by fd::delegate
//
//  a) T * get_pointer(smart_ptr (const) & p); is provided for the smart_ptr class and this function must
//     be seen in qualified namespace (including argument-dependent lookup)
//
//  b) smart_ptr class must expose public interface (typedef) of ' element_type ' that is the type of object at which
//     the smart_ptr points internally (std::auto_ptr, boost smart pointers and loki::smartPtr expose this
//     interface)
//
// If a smart_ptr class does not provide get_pointer() in its own namespace or your compiler poorly implemented the
// argument-dependent lookup (Koenig lookup) nor implemented it at all, then you can explicitly provide get_pointer
// for yourself in namespace fd
//
// namespace fd
// {
// #if defined(_MSC_VER) && _MSC_VER < 1300
// // get_pointer() for boost::shared_ptr is defined in boost namespace but VC6 did not implement koenig look-up
// // so it can't find the definition from namespace boost. therefore we can provide it in namespace fd for ourselves,
//   template<typename T> inline
//     T * get_pointer(boost::shared_ptr const & p)
//   {
//     return p.get();
//   }
// #endif // #if defined(_MSC_VER) && _MSC_VER < 1300
// } // namespace fd
//
// smart pointer will be copied internally which will transfer ownership or increase reference count and when
// the delegate is being destructed, the cloned smart pointer will be destructed, which will delete the object
// or decrease the reference count dependent on their implementation.
//
// Be aware that cloning the bound object involve heap memory allocation/deallocation using new/delete operator.
// The size of the object cloned (either it is bound object or smart pointer) is not known, therefore heap
// memory allocation/deallocation is inevitable. Since the idea of using fast delegate is avoiding
// heap memory allocation/deallocation but cloning object on the heap memory conflict with it. (though member
// function pointer will be still stored in the stack rather than heap). If speed is the only concern, do not use
// cloning bound object feature by defining FD_DISABLE_CLONE_BOUND_OBJECT macro then use reference version of
// bind() and relevant functions only. When FD_DISABLE_CLONE_BOUND_OBJECT is defined, extra 4 bytes space per delegate
// is saved as an additional bonus. (since obj_clone_man_ptr_ is not necessary any more)

// ====================================================================================================
// #define FD_DISABLE_CLONE_BOUND_OBJECT
// ====================================================================================================

// ====================================================================================================
// END of CONFIG
// ====================================================================================================

// --------------------------------------------------
//
// To recognize and support any smart pointer which supply the appropriate T * get_pointer() overloads
// ( http://boost.org/libs/bind/mem_fn.html )
//

/** @file get_pointer.hpp
 *
 *  @brief  get_pointer(p) extracts a ->* capable pointer from p
 *          excerpted from boost/get_pointer.hpp
 *
 * Copyright Peter Dimov and David Abrahams 2002. Permission to copy,
 * use, modify, sell and distribute this software is granted provided
 * this copyright notice appears in all copies of the source. This
 * software is provided "as is" without express or implied warranty,
 * and with no claim as to its suitability for any purpose.
 *
 */

namespace fd
{

template<class T> inline
T * get_pointer(T * p)
{
  return p;
}

template<class T> inline
T * get_pointer(std::auto_ptr<T> & p)
{
  return p.get();
}

}  // namespace fd

// --------------------------------------------------

// ====================================================================================================

#pragma warning(disable:4522) 

#pragma warning(disable:4786) 

// ====================================================================================================

// ====================================================================================================

// ====================================================================================================
// Calling conventions
// ====================================================================================================

//
// http://blogs.msdn.com/oldnewthing/archive/2004/01/02/47184.aspx
// http://blogs.msdn.com/oldnewthing/archive/2004/01/08/48616.aspx
// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vccore98/html/_core_results_of_calling_example.asp
//

// ====================================================================================================
// Platform specific workarounds
// ====================================================================================================

// VC71+

// VC6

// DEV-C++ 4.9.9.2 (Mingw/gcc 3.4.2))

// ====================================================================================================

//
// Repeater macro to generate template/function parameters/arguments
//
// AGM::LibReflection: A reflection library for C++.
// ( http://codeproject.com/library/libreflection.asp )
//

//various defs needed for parameters

// ----------------------------------------------------------------------

//
// example
//
// macro expansion for " __REPEAT(2, __TEMPLATE_PARAM__, __COMMA__) "
//
// __REPEAT(3, M, C)
// => __REPEAT3(M, C)
// => __REPEAT2(M, C) _##C M(3)
// => __REPEAT1(M, C) _##C M(2) _##C M(3)
// => M(1) _##C M(2) _##C M(3)
// => __TEMPLATE_PARAM__(1) __COMMA__ __TEMPLATE_PARAM__(2) __COMMA__ __TEMPLATE_PARAM__(3)
// => typename T1 , typename T2, typename T3
//
// macro expansion for " __REPEAT(3, __FUNCTION_ARG__, __COMMA__) "
//
// => M(1) _##C M(2) _##C M(3)
// => __FUNCTION_ARG__(1) __COMMA__ __FUNCTION_ARG__(2) __COMMA__ __FUNCTION_ARG__(3)
// => p1, p2, p3
//

// ====================================================================================================

// typename T1, typename T2, ... , typename Tn

// T1, T2, ... , Tn

// T1 p1, T2 p2, ... , Tn pn

// p1, p2, ... , pn

// typename U1, typename U2, ... , typename Un

// U1, U2, ... , Un

// U1 q1, U2 q2, ... , Un qn

// q1, q2, ... , qn

// ----------------------------------------------------------------------

//
// for member function call adapter
//

// typename T2, typename T3, ... , typename Tn

// T2, T3, ... , Tn

// T2 p2, T3 p3, ... , Tn pn

// p2, p3, ... , pn

// typename U2, typename U3, ... , typename Un

// U2, U3, ... , Un

// U2 q2, U3 q3, ... , Un qn

// q2, q3, ... , qn

// ====================================================================================================

// ====================================================================================================

namespace fd
{

namespace util
{

//
// for FD_STATIC_ASSERT()
//
// restricting constant template arguments
// ( http://cpptips.hyperformix.com/cpptips/restr_templ_args )
//
template<bool Condition> struct t_assert;
template<> struct t_assert<true>  { typedef bool assertion; };
template<> struct t_assert<false> { };

// ====================================================================================================

//
// A gentle introduction to Template Metaprogramming with C++ By moliate
// ( http://www.codeproject.com/cpp/crc_meta.asp )
//

template <bool t_condition, typename Then, typename Else>
struct If
{
  template<bool t_condition_inner> struct selector;
  template<> struct selector<true> { typedef Then Result; };
  template<> struct selector<false> { typedef Else Result; };

  typedef typename selector<t_condition>::Result Result;

};  // template <bool t_condition, typename Then, typename Else> If

// ====================================================================================================

template<typename T, typename U>
struct Is_pointer
{
  static U testee_;
  static int tester_(...);        // false condition
  static char tester_(T *);       // true condition, typename 'U' matches with typename 'T *' or 'T-derived *'

  enum { value = (sizeof(char) == sizeof(tester_(testee_))) };

};  // template<typename T, typename U> struct Is_pointer

template<typename T, typename U, typename Then, typename Else>
struct If_pointer
{
  // typename 'U' matches with typename 'T *', 'T const *', 'T-derived *' or 'T-derived const *'
  enum { Condition = Is_pointer<T, U>::value || Is_pointer<T const, U>::value };

  typedef typename If< Condition, Then, Else >::Result Result;

};  // template<typename T, typename U, typename Then, typename Else> struct If_pointer

// ====================================================================================================

template<typename T, typename U>
struct Is_reference
{
  static U testee_;
  static int tester_(...);        // false condition
  static char tester_(T &);       // true condition, typename 'U' matches with typename 'T &' or 'T-derived &'

  enum { value = (sizeof(char) == sizeof(tester_(testee_))) };

};  // template<typename T, typename U> struct Is_reference

template<typename T, typename U, typename Then, typename Else>
struct If_reference
{
  // typename 'U' matches with typename 'T &', 'T const &', 'T-derived &' or 'T-derived const &'
  enum { Condition = Is_reference<T, U>::value || Is_reference<T const, U>::value };

  typedef typename If< Condition, Then, Else >::Result Result;

};  // template<typename T, typename U, typename Then, typename Else> struct If_reference

// ====================================================================================================

template<typename T, typename U>
struct Is_pointer_or_reference
{
  // value is true, if typename 'U' matches with T' or 'T-derived' 's pointer or reference
  enum { value = Is_pointer<T, U>::value || Is_reference<T, U>::value };

};  // template<typename T, typename U> struct Is_pointer_or_reference

// ====================================================================================================

template<typename T, typename U>
struct Is_same_type
{
  template<typename R> struct selector { enum { value = false }; };
  template<> struct selector<T> { enum { value = true }; };

  enum { value = selector<U>::value };

};  // template<typename T, typename U> struct Is_same_type

// ====================================================================================================

template<typename T> struct Is_integral
{
  static T testee_;

  // false conditions
  static int tester_(...);
  static int tester_(void);
  static int tester_(float);
  static int tester_(double);
  static int tester_(long double);

  // true conditions
  static unsigned char tester_(signed char);
  static unsigned char tester_(signed short);
  static unsigned char tester_(signed int);
  static unsigned char tester_(signed long);
  static unsigned char tester_(unsigned char);
  static unsigned char tester_(unsigned short);
  static unsigned char tester_(unsigned int);
  static unsigned char tester_(unsigned long);

  enum { value = (sizeof(unsigned char) == sizeof(tester_(testee_))) };

};  // template<typename T> struct Is_integral

// ====================================================================================================

template<typename T> struct Is_floating
{
  static T testee_;

  // false conditions
  static int tester_(...);
  static int tester_(void);
  static int tester_(signed char);
  static int tester_(signed short);
  static int tester_(signed int);
  static int tester_(signed long);
  static int tester_(unsigned char);
  static int tester_(unsigned short);
  static int tester_(unsigned int);
  static int tester_(unsigned long);

  // true conditions
  static unsigned char tester_(float);
  static unsigned char tester_(double);
  static unsigned char tester_(long double);

  enum { value = (sizeof(unsigned char) == sizeof(tester_(testee_))) };

};  // template<typename T> struct Is_floating

// ====================================================================================================

} // namespace util

// ====================================================================================================

namespace detail
{

// ====================================================================================================

//
// DefaultVoid - a workaround for 'void' templates in VC6.
//
//  - VC6 and earlier do not allow you to return 'void' from a function
//    => return 'void const *' instead
//
// Member Function Pointers and the Fastest Possible C++ Delegates By Don Clugston
// ( http://codeproject.com/cpp/delegate.asp )
//
//

// VC6 workaround
typedef void const * DefaultVoid;

// Translate from 'void' into 'DefaultVoid'
// Everything else is unchanged
template <class T>
struct VoidToDefaultVoid { typedef T type; };

template <>
struct VoidToDefaultVoid<void> { typedef DefaultVoid type; };

// ====================================================================================================

//
// The Safe Bool Idiom by Bjorn Karlsson
// ( http://www.artima.com/cppsource/safebool.html )
//
class safe_bool_base
{
public:
  typedef void (safe_bool_base::*bool_type)() const;
  void this_type_does_not_support_comparisons() const {}

protected:
  safe_bool_base() {}
  safe_bool_base(const safe_bool_base &) {}
  safe_bool_base& operator=(const safe_bool_base &) {return *this;}
  ~safe_bool_base() {}

};  // class safe_bool_base

template<typename T>
class safe_bool : public safe_bool_base
{
public:
  operator bool_type() const
  {
    T const * pT = static_cast<T const *>(this); pT;
    return !pT->empty()
      ? &safe_bool_base::this_type_does_not_support_comparisons
      : 0;
  }
protected:
  ~safe_bool() {}

};  // template<typename T> class safe_bool : public safe_bool_base

template<typename T, typename U>
void operator == (const safe_bool<T> & lhs, const safe_bool<U> & rhs)
{
  lhs.this_type_does_not_support_comparisons();
  return false;
}

template<typename T,typename U>
void operator != (const safe_bool<T> & lhs,const safe_bool<U> & rhs)
{
  lhs.this_type_does_not_support_comparisons();
  return false;
}

// ====================================================================================================

//
// tag for template specialization for free function (non-member function)
//
struct free_fn_tag { };

// ====================================================================================================

// ====================================================================================================

template<typename TMFn, typename TMFn_const, typename TFtorOp> inline
void chk_functor(TMFn *, TMFn_const *, TFtorOp const & ftor_op)
{
  ftor_op;
  enum { value = util::Is_same_type<TMFn, TFtorOp>::value || util::Is_same_type<TMFn_const, TFtorOp>::value };
  typedef typename fd::util::t_assert<(bool)(value)>::assertion failed630;
}

template<typename TMFn_const, typename TFtorOp> inline
void chk_functor_const(TMFn_const *, TFtorOp const & ftor_op)
{
  ftor_op;
  enum { value = util::Is_same_type<TMFn_const, TFtorOp>::value };

  typedef typename fd::util::t_assert<(bool)(value)>::assertion failed639;  // functor do not have const version of operator ()
}

// ====================================================================================================

template<typename T>
struct self_ref_type_
{
  inline static T * get_pointer_(T const & obj)
  {
    return const_cast<T *>(&obj);
  }
};

template<typename T>
struct smart_ptr_type_
{
  inline static typename T::element_type * get_pointer_(T & obj)
  {
    return get_pointer(obj);
  }
};

template<typename T, typename U>
struct select_obj_type_
{
  enum { Condition = util::Is_reference<T, U>::value || util::Is_reference<U, T>::value };
  typedef self_ref_type_<T> Then;
  typedef smart_ptr_type_<T> Else;

  typedef typename util::If< Condition, Then, Else >::Result type;

};  // template<typename T, typename U> struct select_obj_type_

// ====================================================================================================

//
// Workaround : std::allocator in VC6 (Dinkumware) does not implemented rebinding
//

template<typename T>
class std_allocator_fixed : public std::allocator<T>
{
public:
  template<typename U> struct rebind { typedef std_allocator_fixed<U> other; };

};

template<typename Allocator>
struct fix_if_std_allocator
{
  enum { Condition = util::Is_same_type<std::allocator<Allocator::value_type>, Allocator>::value };

  typedef std_allocator_fixed<typename Allocator::value_type> Then;
  typedef Allocator Else;

  // if std::allocator then fix it
  typedef typename util::If< Condition, Then, Else >::Result type;

};

template<typename Allocator>
class allocator_base
{

  typedef typename fix_if_std_allocator<Allocator>::type alloc_;

public:

  inline static void * allocate_(size_t n, void const * pInitHint = 0)
  {
    static typename alloc_::template rebind<unsigned char>::other alloc;
    return alloc.allocate(n, pInitHint);
  }

  inline static void deallocate_(void * p, size_t n)
  {
    static typename alloc_::template rebind<unsigned char>::other alloc;
    alloc.deallocate(static_cast<unsigned char *>(p), n);
  }

};  // template<typename Allocator> class allocator_base

} // namespace detail

// ====================================================================================================

//
// The bad_member_function_call exception class is thrown when a delegate object is invoked
//
class bad_member_function_call : public std::runtime_error
{
public:
  bad_member_function_call() : std::runtime_error("member function call on no object") {}

};  // class bad_member_function_call : public std::runtime_error

class bad_function_call : public std::runtime_error
{
public:
  bad_function_call() : std::runtime_error("call to empty delegate") {}

};  // class bad_function_call : public std::runtime_error

// ====================================================================================================

enum { DefaultCountOfVoid = 2 };

// ====================================================================================================

template<typename T, typename Allocator = std::allocator<void> , size_t t_countof_pvoid = DefaultCountOfVoid>
class delegate; // no body

} // namespace fd

// ====================================================================================================

// Specializations

/** @file delegatetmpl.h
 *
 *  @brief  delegate interfaces (Preferred Syntax and Portable Syntax)
 *
 *
 *  @author JaeWook Choi
 *  @version 1.10
 *
 *  @history
 *    1.10 (03.12.2006) - added cloning bound object support for argument binding of member function
 *                          -> bind(mfn, obj)       : clone obj internally and invoke mfn on cloned object
 *                          -> bind(mfn, obj_ptr)   : store only the pointer to the obj (obj_ptr) and invoke
 *                                                    mfn on the pointed object
 *                          -> bind(mfn, smart_ptr) : clone smart_ptr internally and invoke mfn on the object
 *                                                    which is pointed by smart_ptr
 *                                                    (assuming T * get_pointer() is seen in the qualified
 *                                                    namespace and smart_ptr expose public interface element_type)
 *                        functor assignment operator (operator <<=) are changed to be coincident with bind()
 *                          -> operator <<= (ftor)      : clone functor internally and invoke operator () on the
 *                                                        cloned functor
 *                          -> operator <<= (ftor_ptr)  : store only the pointer to the functor (ftor_ptr) and
 *                                                        invoke operator () on the pointed fucntor
 *                        added copy c'tor for functor
 *                          -> delegateN(ftor, bool dummy)      : clone version copy c'tor for functor
 *                          -> delegateN(ftor_ptr, bool dummy)  : reference storing version copy c'tor for functor
 *                        macro definition are slightly changed and source codes are updated according to changes
 *                          -> FD_TYPE_RELAXATION changed to FD_DISABLE_TYPE_RELAXATION
 *                          -> FD_DISABLE_CLONING_BOUND_OBJECT added
 *                             if FD_DISABLE_CLONING_BOUND_OBJECT is not defined (default), cloning version of member
 *                             are enabled,
 *                             othereise, only reference storing version of member function are available but
 *                             4 bytes less per delegate in its size
 *                          -> therefore default is enabling both type-check relaxation mode and cloning bound object
 *                        added support for the custom allocator (the second last template argument)
 *    1.01 (03.10.2006) - seperated bind & make_delegate implementation into separate files
 *                        added supports for arbitary smart pointer whch supply T * get_pointer() overloads
 *                        ( copied from boost::mem_fn and, this version only recognize smart pointers
 *                          but do not trnasfer ownership nor increase refernce count )
 *                        removed the definition of fd::arg<> & fd::_1, fd::_2, ... fd::_9
 *                        removed make_delegate for type-check relaxation mode
 *    1.00 (03.01.2006) - Initial public release
 *
 *
 * This software is provided "as is" without express or implied warranty, and with
 * no claim as to its suitability for any purpose.
 *
 */

// Note: this header is a header template and must NOT have multiple-inclusion
// protection.

//
// --------------------------------------------------
// Preferred syntax
// --------------------------------------------------
// fd::delegate<R (T1, T2, ..., Tn), Allocator, t_countof_pvoid>;
//
// --------------------------------------------------
// Portable syntax
// --------------------------------------------------
// fd::delegateN<R, T1, T2, ... , Tn, Allocator, t_countof_pvoid>;
//
// --------------------------------------------------
// size of delegate
// --------------------------------------------------
// sizeof(delegate) = sizeof(delegateN) = t_countof_pvoid * 4 + 12 + alpha (bytes)
//                                      = 2 (default) * 4 + 12 = 20 + alpha (bytes)
//
// , where alpha is the size of the allocated memory if and only if it is required to be allocated
// , otherwise 0
//

/** @file delegatetmpl.hpp
 *
 *  @brief  delegate implementations
 *
 *
 *  @author JaeWook Choi
 *  @version 1.10
 *
 *  @history
 *    1.10 (03.12.2006) - see history of "delegateimpl.h"
 *    1.01 (03.10.2006) - member functions are renamed and rearranged
 *    1.00 (03.01.2006) - Initial public release
 *
 *
 * This software is provided "as is" without express or implied warranty, and with
 * no claim as to its suitability for any purpose.
 *
 */

// Note: this header is a header template and must NOT have multiple-inclusion
// protection.

namespace fd
{

namespace detail
{

template<typename R , typename T1 , typename T2, typename Allocator, size_t t_countof_pvoid>
struct delegateImpl2 : private detail::allocator_base<Allocator>
{
  typedef delegateImpl2<R , T1 , T2, Allocator, t_countof_pvoid> thisClass;
  typedef detail::allocator_base<Allocator> allocBase;

  // buffer size should be bigger than or matches with sizeof(void *)
  // IOW, t_countof_pvoid template parameter should be 1 or higher
  typedef typename fd::util::t_assert<(bool)(t_countof_pvoid > 0)>::assertion failed37;

  // DefaultVoid - a workaround for 'void' templates in VC6.

  typedef typename detail::VoidToDefaultVoid<R>::type  result_type;

  enum { size_buf = t_countof_pvoid * sizeof(void *) };

  // data members

  // ----------------------------------------------------------------------

  //
  // function pointer info.
  //
  typedef struct tag_fp_info
  {
    unsigned char sz_fp;              // byte 1 : size of the (member) function pointer
                                      //
    bool by_malloc;                   // byte 2 : whether or not the (member) function pointer is stored in the heap memory
                                      //          if true, a member function pointer is stored at *(TMFn *)(fn_ptr_)
                                      //          otherwise, a function pointer (either free function or member function)
                                      //          is stored at *((TFn *)buf_)
                                      //
    bool is_const;                    // byte 3 : cv-qualifier, whether or not the member function pointer is for const object
                                      //          ***note*** do not bind 'volatile' object with member function pointer
                                      //
    unsigned char calling_convention; // byte 4 : platform specific calling conventions, only enabled by explicit macro definition
                                      //          0 for none, 1 for FD_STDCALL_, 2 for FD_FASTCALL_, 3 for FD_CDECL_, 4 for FD_PASCAL_
  } fp_info;
  fp_info fp_info_;

  enum { fcc_none = 0, fcc_stdcall = 1, fcc_fastcall = 2, fcc_cdecl = 3, fcc_pascal = 4 };

  typedef typename fd::util::t_assert<(bool)(sizeof(void *) >= sizeof(fp_info))>::assertion failed74;

  // ----------------------------------------------------------------------

  //
  // to create a stub for type information restoring for member function invocation
  //
  // The Impossibly Fast C++ Delegates By Sergey Ryazanov
  // ( http://codeproject.com/cpp/ImpossiblyFastCppDelegate.asp )
  //
  typedef result_type (*stub_type)(thisClass const &, void * , T1 , T2);
  typedef result_type (*stub_const_type)(thisClass const &, void const * , T1 , T2);

  stub_type stub_ptr_;

  // ----------------------------------------------------------------------

  // to store the untyped object for the member function pointer, object's type information
  // will be restored in stub_type procedure (stub_ptr_ ) when delegate is being invoked
  void * obj_ptr_;

  typedef void * (*obj_clone_man_type)(thisClass &, void const *, bool);
  obj_clone_man_type obj_clone_man_ptr_;

  template<typename T, typename U>
  struct obj_clone_man_t
  {
    // if retrieve_obj_ptr_only is true, return the pointer to the existing cloned bound object only
    // otherwise,
    //   delete dg.obj_ptr_ then
    //     if untyped_obj_src is not 0, copy construct bound object (cloning) then
    //       return the pointer to the newly cloned bound object
    inline static void * typed_obj_manager_(thisClass & dg, void const * untyped_obj_src, bool retrieve_obj_ptr_only)
    {
      T * typed_obj_src =const_cast<T *>(static_cast<T const *>(untyped_obj_src)); typed_obj_src;

      if(!retrieve_obj_ptr_only)
      {
        if(dg.obj_ptr_)
        {
          T * typed_obj_this = static_cast<T *>(dg.obj_ptr_);
          typed_obj_this->~T();
          deallocate_(typed_obj_this, sizeof(T));
          // delete typed_obj_this;
          dg.obj_ptr_ = 0;
        }

        if(0 != typed_obj_src)
        {
          void * pv_new = allocate_(sizeof(T));
          T * obj_new = new (pv_new) T(*typed_obj_src);

          // T * obj_new = new T(*typed_obj_src);
          dg.obj_ptr_ = obj_new;
        }
      }

      T * typed_obj = static_cast<T *>(dg.obj_ptr_); typed_obj;
      return typed_obj ? (void *)detail::select_obj_type_<T, U>::type::get_pointer_(*typed_obj) : 0;
    }

  };  // template<typename T, typename U> struct obj_clone_man_t

  // ----------------------------------------------------------------------

  //
  // to avoid heap allocation for member function pointer
  //
  // Yet Another Generalized Functors Implementation in C++ By Aleksei Trunov
  // ( http://codeproject.com/cpp/genfunctors.asp )
  //
  union
  {
    void * fn_ptr_;
    unsigned char buf_[size_buf];
  };

  // ----------------------------------------------------------------------

  // to allow '0' as an argument of copy c'tor or assignment operator to indicate
  // 'clear of delegate'
  struct clear_type { };

  // ----------------------------------------------------------------------

  //
  // allocate/deallocate
  //
  inline static void * allocate_(size_t n, void const * pInitHint = 0)
  {
    return allocBase::allocate_(n, pInitHint);
  }

  inline static void deallocate_(void * p, size_t n)
  {
    allocBase::deallocate_(p, n);
  }
  
  // ====================================================================================================
  // implementations (template meta programming)
  // ====================================================================================================

  //
  // function pointer is stored in the internal buffer (buf_)
  //
  // *** No heap allocation ****
  //
  template<typename UR , typename U1 , typename U2>
  struct fp_by_value
  {
    // DefaultVoid - a workaround for 'void' templates in VC6.

    typedef typename detail::VoidToDefaultVoid<UR>::type  result_type2;

    template<typename U >
    struct callee_spec_
    {
      //
      // init_()
      //
      template<typename U>
        static void init_(thisClass & dg, UR (U::*mfn)(U1 , U2))
      {
        typedef UR (U::*TMFn)(U1 , U2);

        dg.fp_info_.sz_fp = sizeof(TMFn);
        dg.fp_info_.by_malloc = false;
        dg.fp_info_.is_const = false;
        dg.fp_info_.calling_convention = fcc_none;

        new (dg.buf_) TMFn(mfn);
      }

      template<typename U>
        static inline void init_(thisClass & dg, UR (U::*mfn)(U1 , U2) const)
      {
        typedef UR (U::*TMFn)(U1 , U2) const;

        dg.fp_info_.sz_fp = sizeof(TMFn);
        dg.fp_info_.by_malloc = false;
        dg.fp_info_.is_const = true;
        dg.fp_info_.calling_convention = fcc_none;

        new (dg.buf_) TMFn(mfn);
      }

      //
      // get_fp_() & get_const_fp_()
      //
      template<typename U>
        static inline result_type2 (U::* const get_fp_(thisClass const & dg, U *))(U1 , U2)
      {
        typedef result_type2 (U::*TMFn)(U1 , U2);
        return *reinterpret_cast<TMFn const *>(dg.buf_);
      }

      template<typename U>
        static inline result_type2 (U::* const get_const_fp_(thisClass const & dg, U const *))(U1 , U2) const
      {
        typedef result_type2 (U::*TMFn)(U1 , U2) const;
        return *reinterpret_cast<TMFn const *>(dg.buf_);
      }

      //
      // invoke_() & invoke_const_()
      //
      template<typename U>
        static inline result_type2 invoke_(thisClass const & dg, U * obj , U1 q1 , U2 q2)
      {
        if(0 == obj)
        {
          // member function call on no object
          throw bad_member_function_call();
        }

        if(false) { }

        else
        {
          typedef result_type2 (U::*TMFn)(U1 , U2);

          TMFn const mfn = get_fp_(dg, obj);

          return (obj->*mfn)(q1 , q2);
        }
      }

      template<typename U>
        static inline result_type2 invoke_const_(thisClass const & dg, U const * obj , U1 q1 , U2 q2)
      {
        if(0 == obj)
        {
          // member function call on no object
          throw bad_member_function_call();
        }

        if(false) { }

        else
        {
          typedef result_type2 (U::*TMFn)(U1 , U2) const;

          TMFn const mfn = get_const_fp_(dg, obj);

          return (obj->*mfn)(q1 , q2);
        }
      }

      // ====================================================================================================

      //
      // template specialization for member function adapter
      // a special provision is made for pointers to member functions.
      // a pointer to member function of the form R (X::*mf)(p1, p2, ..., pn) cv-quals
      // be adapted to a function object with the following function call operator overloads
      //
      // template<typename T>
      // R operator()(cv-quals T & x, T1 p1, T2 p2, ..., Tn pn) cv-quals
      // {
      //   return (*x).*mf(p1, p2, ..., pn);
      // }
      //
      struct mfn_adapter_
      {
        //
        // init_()
        //
        template<typename U>
          static inline void init_(thisClass & dg, UR (U::*mfn)(U2))
        {
          typedef UR (U::*TMFn)(U2);

          dg.fp_info_.sz_fp = sizeof(TMFn);
          dg.fp_info_.by_malloc = false;
          dg.fp_info_.is_const = false;
          dg.fp_info_.calling_convention = fcc_none;

          new (dg.buf_) TMFn(mfn);
        }

        template<typename U>
          static inline void init_(thisClass & dg, UR (U::*mfn)(U2) const)
        {
          typedef UR (U::*TMFn)(U2) const;

          dg.fp_info_.sz_fp = sizeof(TMFn);
          dg.fp_info_.by_malloc = false;
          dg.fp_info_.is_const = true;
          dg.fp_info_.calling_convention = fcc_none;

          new (dg.buf_) TMFn(mfn);
        }

        //
        // get_fp_() & get_const_fp_()
        //
        template<typename U>
          static inline result_type2 (U::* const get_fp_(thisClass const & dg, U *))(U2)
        {
          typedef result_type2 (U::*TMFn)(U2);
          return *reinterpret_cast<TMFn const *>(dg.buf_);
        }

        template<typename U>
          static inline result_type2 (U::* const get_const_fp_(thisClass const & dg, U const *))(U2) const
        {
          typedef result_type2 (U::*TMFn)(U2) const;
          return *reinterpret_cast<TMFn const *>(dg.buf_);
        }

        //
        // invoke_() & invoke_const_()
        //
        template<typename U>
          static inline result_type2 invoke_(thisClass const & dg, U * obj , U2 q2)
        {
          if(0 == obj)
          {
            // member function call on no object
            throw bad_member_function_call();
          }

          if(false) { }

          else
          {
            typedef result_type2 (U::*TMFn)(U2);

            TMFn const mfn = get_fp_(dg, obj);

            return (obj->*mfn)(q2);
          }
        }

        template<typename U>
          static inline result_type2 invoke_const_(thisClass const & dg, U const * obj , U2 q2)
        {
          if(0 == obj)
          {
            // member function call on no object
            throw bad_member_function_call();
          }

          if(false) { }

          else
          {
            typedef result_type2 (U::*TMFn)(U2) const;

            TMFn const mfn = get_const_fp_(dg, obj);

            return (obj->*mfn)(q2);
          }
        }

      };  // struct mfn_adapter_

      // ====================================================================================================

    };  // template<typename U> struct callee_spec_

    // ====================================================================================================

    //
    // template specialization for free function
    //
    template<>
    struct callee_spec_<free_fn_tag >
    {
      //
      // init_()
      //
      static inline void init_(thisClass & dg, UR (*fn)(U1 , U2))
      {
        typedef UR (*TFn)(U1 , U2);

        dg.fp_info_.sz_fp = sizeof(TFn);
        dg.fp_info_.by_malloc = false;
        dg.fp_info_.is_const = false;
        dg.fp_info_.calling_convention = fcc_none;

        new (dg.buf_) TFn(fn);
      }

      //
      // get_fp_()
      //
      static inline result_type2 (* const get_fp_(thisClass const & dg))(U1 , U2)
      {
        typedef result_type2 (*TFn)(U1 , U2);
        return *reinterpret_cast<TFn const *>(dg.buf_);
      }

      //
      // invoke_()
      //
      template<typename U>
        static inline result_type2 invoke_(thisClass const & dg, U * obj , U1 q1 , U2 q2)
      {
        assert(((void *)-1) == obj);

        if(false) { }

        else
        {
          typedef result_type2 (*TFn)(U1 , U2);

          TFn const fn = get_fp_(dg);

          return (*fn)(q1 , q2);
        }
      }

    };  // template<typename T FD_NESTED_PARTIAL_TPARM_MAIN(0)> struct callee_spec_

  };  // template<typename UR FD_COMMA FD_TPARMS2(N), FD_NESTED_PARTIAL_TPARM_MAIN(0)> struct fp_by_value

  // ====================================================================================================

  //
  // function pointer is stored in the heap memory allocated through ::malloc()
  // the internal buffer (buf_) is used to store the pointer to the memory allocated (to save 4 bytes)
  //
  template<typename UR , typename U1 , typename U2>
  struct fp_by_malloc
  {
    // DefaultVoid - a workaround for 'void' templates in VC6.

    typedef typename detail::VoidToDefaultVoid<UR>::type  result_type2;

    template<typename U>
    struct callee_spec_
    {
      //
      // init_()
      //
      template<typename U>
        static inline void init_(thisClass & dg, UR (U::*mfn)(U1 , U2))
      {
        typedef UR (U::*TMFn)(U1 , U2);

        enum { szTMFn = sizeof(TMFn) };

        dg.fp_info_.sz_fp = sizeof(TMFn);
        dg.fp_info_.by_malloc = true;
        dg.fp_info_.is_const = false;
        dg.fp_info_.calling_convention = fcc_none;

        dg.fn_ptr_ = allocate_(szTMFn, 0);
        new (dg.fn_ptr_) TMFn(mfn);
      }

      template<typename U>
        static inline void init_(thisClass & dg, UR (U::*mfn)(U1 , U2) const)
      {
        typedef UR (U::*TMFn)(U1 , U2) const;

        enum { szTMFn = sizeof(TMFn) };

        dg.fp_info_.sz_fp = sizeof(TMFn);
        dg.fp_info_.by_malloc = true;
        dg.fp_info_.is_const = true;
        dg.fp_info_.calling_convention = fcc_none;

        dg.fn_ptr_ = allocate_(szTMFn, 0);
        new (dg.fn_ptr_) TMFn(mfn);
      }

      //
      // get_fp_() & get_const_fp_()
      //
      template<typename U>
        static inline result_type2 (U::* const get_fp_(thisClass const & dg, U *))(U1 , U2)
      {
        typedef result_type2 (U::*TMFn)(U1 , U2);
        return *reinterpret_cast<TMFn const *>(dg.fn_ptr_);
      }

      template<typename U>
        static inline result_type2 (U::* const get_const_fp_(thisClass const & dg, U const *))(U1 , U2) const
      {
        typedef result_type2 (U::*TMFn)(U1 , U2) const;
        return *reinterpret_cast<TMFn const *>(dg.fn_ptr_);
      }

      //
      // invoke_() & invoke_const_()
      //
      template<typename U>
        static inline result_type2 invoke_(thisClass const & dg, U * obj , U1 q1 , U2 q2)
      {
        if(0 == obj)
        {
          // member function call on no object
          throw bad_member_function_call();
        }

        if(false) { }

        else
        {
          typedef result_type2 (U::*TMFn)(U1 , U2);

          TMFn const mfn = get_fp_(dg, obj);

          return (obj->*mfn)(q1 , q2);
        }
      }

      template<typename U>
        static inline result_type2 invoke_const_(thisClass const & dg, U const * obj , U1 q1 , U2 q2)
      {
        if(0 == obj)
        {
          // member function call on no object
          throw bad_member_function_call();
        }

        if(false) { }

        else
        {
          typedef result_type2 (U::*TMFn)(U1 , U2) const;

          TMFn const mfn = get_const_fp_(dg, obj);

          return (obj->*mfn)(q1 , q2);
        }
      }

      // ====================================================================================================

      struct mfn_adapter_
      {
        //
        // init_()
        //
        template<typename U>
          static inline void init_(thisClass & dg, UR (U::*mfn)(U2))
        {
          typedef UR (U::*TMFn)(U2);

          enum { szTMFn = sizeof(TMFn) };

          dg.fp_info_.sz_fp = sizeof(TMFn);
          dg.fp_info_.by_malloc = true;
          dg.fp_info_.is_const = false;
          dg.fp_info_.calling_convention = fcc_none;

          dg.fn_ptr_ = allocate_(szTMFn, 0);
          new (dg.fn_ptr_) TMFn(mfn);
        }

        template<typename U>
          static inline void init_(thisClass & dg, UR (U::*mfn)(U2) const)
        {
          typedef UR (U::*TMFn)(U2) const;

          enum { szTMFn = sizeof(TMFn) };

          dg.fp_info_.sz_fp = sizeof(TMFn);
          dg.fp_info_.by_malloc = true;
          dg.fp_info_.is_const = true;
          dg.fp_info_.calling_convention = fcc_none;

          dg.fn_ptr_ = allocate_(szTMFn, 0);
          new (dg.fn_ptr_) TMFn(mfn);
        }

        //
        // get_fp_() & get_const_fp_()
        //
        template<typename U>
          static inline result_type2 (U::* const get_fp_(thisClass const & dg, U *))(U2)
        {
          typedef result_type2 (U::*TMFn)(U2);
          return *reinterpret_cast<TMFn const *>(dg.fn_ptr_);
        }

        template<typename U>
          static inline result_type2 (U::* const get_const_fp_(thisClass const & dg, U const *))(U2) const
        {
          typedef result_type2 (U::*TMFn)(U2) const;
          return *reinterpret_cast<TMFn const *>(dg.fn_ptr_);
        }

        //
        // invoke_() & invoke_const_()
        //
        template<typename U>
          static inline result_type2 invoke_(thisClass const & dg, U * obj , U2 q2)
        {
          if(0 == obj)
          {
            // member function call on no object
            throw bad_member_function_call();
          }

          if(false) { }

          else
          {
            typedef result_type2 (U::*TMFn)(U2);

            TMFn const mfn = get_fp_(dg, obj);

            return (obj->*mfn)(q2);
          }
        }

        template<typename U>
          static inline result_type2 invoke_const_(thisClass const & dg, U const * obj , U2 q2)
        {
          if(0 == obj)
          {
            // member function call on no object
            throw bad_member_function_call();
          }

          if(false) { }

          else
          {
            typedef result_type2 (U::*TMFn)(U2) const;

            TMFn const mfn = get_const_fp_(dg, obj);

            return (obj->*mfn)(q2);
          }
        }

      };  // struct mfn_adapter_

      // ====================================================================================================

    };  // template<typename T> struct callee_spec_

  };  // template<typename UR FD_COMMA FD_TPARMS2(N)> // struct fp_by_malloc

  // ====================================================================================================

  //
  // select a proper function pointer info. according to function pointer type
  //
  template<typename UR , typename U1 , typename U2>
  struct select_fp_
  {
    template<typename U, bool t_binding >
    struct callee_bind_spec_
    {
      template<bool t_binding_inner > struct bind_spec_;

      // ====================================================================================================

      template<>
      struct bind_spec_<false >
      {
        struct normal_
        {
          // if the size of the member function is smaller than buffer size use buffer to store it,
          // otherwise use ::malloc to store it on the heap
          enum { Condition = sizeof(UR (U::*)(U1 , U2)) <= size_buf };

          typedef typename fp_by_value<UR , U1 , U2>::template callee_spec_<U>   Then;
          typedef typename fp_by_malloc<UR , U1 , U2>::template callee_spec_<U>  Else;

          typedef typename util::If< Condition, Then, Else >::Result type;

        };  // struct normal_

        struct mfn_adapter_
        {
          // typename T1 matches with typename U *
          // if the size of the member function is smaller than buffer size use buffer to store it,
          // otherwise use ::malloc to store it on the heap
          enum { Condition = sizeof(UR (U::*)(U2)) <= size_buf };

          typedef typename fp_by_value<UR , U1 , U2>::template callee_spec_<U>::mfn_adapter_   Then;
          typedef typename fp_by_malloc<UR , U1 , U2>::template callee_spec_<U>::mfn_adapter_  Else;

          typedef typename util::If< Condition, Then, Else >::Result type;

        };  // struct mfn_adapter_

        // if the typename 'T1' matches with typename 'U *', 'U const *', 'U &' or
        // 'U const &', treat it as a member function adapter
        enum { Condition = util::Is_pointer_or_reference<U, T1>::value || util::Is_pointer_or_reference<U const, T1>::value };

        typedef typename mfn_adapter_::type   Then;
        typedef typename normal_::type        Else;

        typedef typename util::If< Condition, Then, Else >::Result type;

      };

      // ====================================================================================================

      template<>
      struct bind_spec_<true >
      {
        // if the size of the member function is smaller than buffer size use buffer to store it,
        // otherwise use ::malloc to store it on the heap
        enum { Condition = sizeof(UR (U::*)(U1 , U2)) <= size_buf };

        typedef typename fp_by_value<UR , U1 , U2>::template callee_spec_<U>   Then;
        typedef typename fp_by_malloc<UR , U1 , U2>::template callee_spec_<U>  Else;

        typedef typename util::If< Condition, Then, Else >::Result type;

      };

      // ====================================================================================================

      typedef typename bind_spec_<t_binding>::type type;

    };  // template<typename T> struct callee_bind_spec_

    //
    // template specialization for free function
    //
    template<>
    struct callee_bind_spec_<free_fn_tag, false >
    {
      typedef typename fp_by_value<UR , U1 , U2>::template callee_spec_<free_fn_tag> type;

    };  // template<> struct callee_bind_spec_<free_fn_tag>

  };  // template<typename UR FD_COMMA FD_TPARMS2(N)> struct select_fp_

  // ====================================================================================================

  // ====================================================================================================

  //
  // function pointer selector
  //
  template<typename UR , typename U1 , typename U2>
  struct fp_selector_
  {
    // DefaultVoid - a workaround for 'void' templates in VC6.

    typedef typename detail::VoidToDefaultVoid<UR>::type  result_type2;

    template<typename U, bool t_binding >
    struct callee_bind_spec_
    {
      template<bool t_binding_inner > struct bind_spec_;

      // ====================================================================================================

      template<>
      struct bind_spec_<true >
      {
        template<typename U>
        static inline void init_(thisClass & dg, UR (U::*mfn)(U1 , U2))
        {
          select_fp_<UR , U1 , U2>::template callee_bind_spec_<U, true>::type::init_(dg, mfn);
        }
        template<typename U>
        static inline void init_(thisClass & dg, UR (U::*mfn)(U1 , U2) const)
        {
          select_fp_<UR , U1 , U2>::template callee_bind_spec_<U, true>::type::init_(dg, mfn);
        }

        template<typename U>
        static inline result_type2 invoke_(thisClass const & dg, U * obj , U1 q1 , U2 q2)
        {
          return select_fp_<UR , U1 , U2>::template callee_bind_spec_<U, true>::type::invoke_(dg, obj , q1 , q2);
        }
        template<typename U>
        static inline result_type2 invoke_const_(thisClass const & dg, U const * obj , U1 q1 , U2 q2)
        {
          return select_fp_<UR , U1 , U2>::template callee_bind_spec_<U, true>::type::invoke_const_(dg, obj , q1 , q2);
        }

      };  // template<> struct bind_spec_<true>

      // ====================================================================================================

      template<>
      struct bind_spec_<false >
      {
        //
        // specialization for member function call adapter
        //
        template<typename U>
        static inline void init_(thisClass & dg, UR (U::*mfn)(U2))
        {
          select_fp_<UR , U1 , U2>::template callee_bind_spec_<U, false>::type::init_(dg, mfn);
        }
        template<typename U>
        static inline void init_(thisClass & dg, UR (U::*mfn)(U2) const)
        {
          select_fp_<UR , U1 , U2>::template callee_bind_spec_<U, false>::type::init_(dg, mfn);
        }

        template<typename U>
        static inline result_type2 invoke_(thisClass const & dg, U * obj , U2 q2)
        {
          return select_fp_<UR , U1 , U2>::template callee_bind_spec_<U, false>::type::invoke_(dg, obj , q2);
        }
        template<typename U>
        static inline result_type2 invoke_const_(thisClass const & dg, U const * obj , U2 q2)
        {
          return select_fp_<UR , U1 , U2>::template callee_bind_spec_<U, false>::type::invoke_const_(dg, obj , q2);
        }

      };  // template<> struct bind_spec_<false>

      // ====================================================================================================

      typedef bind_spec_<t_binding> type;

    };  // template<typename T> struct callee_bind_spec_

    // ====================================================================================================

    //
    // template specialization for free function
    //
    template<>
    struct callee_bind_spec_<free_fn_tag, false >
    {
      static inline void init_(thisClass & dg, UR (*fn)(U1 , U2))
      {
        select_fp_<UR , U1 , U2>::template callee_bind_spec_<free_fn_tag, false>::type::init_(dg, fn);
      }

      template<typename U>
        static inline result_type2 invoke_(thisClass const & dg, U * obj , U1 q1 , U2 q2)
      {
        return select_fp_<UR , U1 , U2>::template callee_bind_spec_<free_fn_tag, false>::type::invoke_(dg, obj , q1 , q2);
      }

      typedef callee_bind_spec_<free_fn_tag, false> type;

    };  // template<> struct callee_bind_spec_<free_fn_tag>

  };  // template<typename UR FD_COMMA FD_TPARMS2(N)> struct fp_selector_

  // ====================================================================================================

  //
  // a stub for type information restoring for member function invocation
  //
  template<typename UR , typename U1 , typename U2>
  struct delegate_stub_t
  {
    // DefaultVoid - a workaround for 'void' templates in VC6.

    typedef typename detail::VoidToDefaultVoid<UR>::type  result_type2;

    template<typename U, bool t_binding>
    struct callee_bind_spec_
    {
      // ====================================================================================================
      //
      // RESTORE TYPE (the core of the entire delegate implementation)
      //
      // 1. the stored untyped object (callee) restores its type back here
      //
      // 2. the relaxed type relevant error/warning will occur here (when FD_ENABLE_TYPE_RELAXATION macro is defined)
      //
      //    ex) error C2664: 'delegate_stub_t<>::XXX::invoke_' : cannot convert parameter 3 from 'int' to 'char *' (MSVC)
      //    ex) warning C4244: 'argument' : conversion from 'int' to 'float', possible loss of data (MSVC)
      //    ex) 1760 delegatetmpl.hpp invalid conversion from `int' to `char*' (g++)
      //
      // ====================================================================================================
      static inline result_type typed_invoker_(thisClass const & dg, void * untyped_obj , T1 p1 , T2 p2)
      {

        void * untyped_obj_retrieved = dg.obj_clone_man_ptr_
          ? (*dg.obj_clone_man_ptr_)(const_cast<thisClass &>(dg), 0, true)
          : untyped_obj;
        U * typed_obj = static_cast<U *>(untyped_obj_retrieved); typed_obj;

        // if FD_ENABLE_TYPE_RELAXATION is defined, all warnings/errors message will be issued here
        // to indicate that type can be trivially converted by the compiler
        return select_stub_::type::invoke_(dg, typed_obj , p1 , p2);
      }

      static inline result_type typed_invoker_const_(thisClass const & dg, void const * untyped_const_obj , T1 p1 , T2 p2)
      {

        void const * untyped_const_obj_retrieved = dg.obj_clone_man_ptr_
          ? const_cast<void const *>((*dg.obj_clone_man_ptr_)(const_cast<thisClass &>(dg), 0, true))
          : untyped_const_obj;
        U const * typed_const_obj = static_cast<U const *>(untyped_const_obj_retrieved); typed_const_obj;

        // if FD_ENABLE_TYPE_RELAXATION is defined, all warnings/errors message will be issued here
        // to indicate that type can be trivially converted by the compiler
        return select_stub_::type::invoke_const_(dg, typed_const_obj , p1 , p2);
      }
      // ====================================================================================================
      //
      // ====================================================================================================

      struct select_stub_
      {
        template<bool t_binding_inner > struct bind_spec_;

        // ====================================================================================================

        template<>
        struct bind_spec_<false >
        {
          static inline result_type2 invoke_(thisClass const & dg, U * typed_obj , U1 q1 , U2 q2)
          {
            return fp_selector_<UR , U1 , U2>::template callee_bind_spec_<U, false>::type::invoke_(dg, typed_obj , q1 , q2);
          }

          static inline result_type2 invoke_const_(thisClass const & dg, U const * typed_obj , U1 q1 , U2 q2)
          {
            return fp_selector_<UR , U1 , U2>::template callee_bind_spec_<U, false>::type::invoke_const_(dg, typed_obj , q1 , q2);
          }

          // ====================================================================================================

          //
          // specialization for member function call adapter
          //
          struct mfn_ptr_adapter_
          {
            // typename T1 matches with typename U *
            static inline result_type2 invoke_(thisClass const & dg, U * /*typed_obj*/, U1 q1 , U2 q2)
            {
              U * typed_obj = q1;
              return fp_selector_<UR , U1 , U2>::template callee_bind_spec_<U, false>::type::invoke_(dg, typed_obj , q2);
            }

            // typename T1 matches with typename U const *
            static inline result_type2 invoke_const_(thisClass const & dg, U const * /*typed_obj*/, U1 q1 , U2 q2)
            {
              U const * typed_obj = q1;
              return fp_selector_<UR , U1 , U2>::template callee_bind_spec_<U, false>::type::invoke_const_(dg, typed_obj , q2);
            }

          };  // struct mfn_ptr_adapter_

          struct mfn_ref_adapter_
          {
            // typename T1 matches with typename U &
            static inline result_type2 invoke_(thisClass const & dg, U * /*typed_obj*/, U1 q1 , U2 q2)
            {
              U * typed_obj = &q1;
              return fp_selector_<UR , U1 , U2>::template callee_bind_spec_<U, false>::type::invoke_(dg, typed_obj , q2);
            }

            // typename T1 matches with typename U const &
            static inline result_type2 invoke_const_(thisClass const & dg, U const * /*typed_obj*/, U1 q1 , U2 q2)
            {
              U const * typed_obj = &q1;
              return fp_selector_<UR , U1 , U2>::template callee_bind_spec_<U, false>::type::invoke_const_(dg, typed_obj , q2);
            }

          };  // struct mfn_ref_adapter_

          // if the typename 'T1' matches with typename 'U *', 'U const *', 'U &' or 'U const &',
          // treat it as a member function adapter
          enum {
            Condition1 = util::Is_pointer<U, T1>::value || util::Is_pointer<U const, T1>::value,
            Condition2 = util::Is_reference<U, T1>::value || util::Is_reference<U const, T1>::value
          };

          typedef mfn_ptr_adapter_       Then1;
          typedef bind_spec_<false>      Else1;

          typedef mfn_ref_adapter_       Then2;
          typedef typename util::If< Condition1, Then1, Else1 >::Result Else2;

          typedef typename util::If< Condition2, Then2, Else2 >::Result type;

          // ====================================================================================================

        };  // template<bool t_binding> struct bind_spec_

        // ====================================================================================================

        template<>
        struct bind_spec_<true >
        {
          static inline result_type2 invoke_(thisClass const & dg, U * typed_obj , U1 q1 , U2 q2)
          {
            return fp_selector_<UR , U1 , U2>::template callee_bind_spec_<U, true>::type::invoke_(dg, typed_obj , q1 , q2);
          }

          static inline result_type2 invoke_const_(thisClass const & dg, U const * typed_obj , U1 q1 , U2 q2)
          {
            return fp_selector_<UR , U1 , U2>::template callee_bind_spec_<U, true>::type::invoke_const_(dg, typed_obj , q1 , q2);
          }

        }; // template<> struct bind_spec_<true>

        // ====================================================================================================

        typedef bind_spec_<true>                  Then;
        typedef typename bind_spec_<false>::type  Else;

        typedef typename util::If< t_binding, Then, Else >::Result type;

      };  // struct select_stub_

    };  // template<typename U, bool t_binding> struct callee_bind_spec_

  };  // template<typename UR FD_COMMA FD_TPARMS2(N)> struct delegate_stub_t

  // ====================================================================================================
  // c'tors and d'tor
  // ====================================================================================================

  //
  // default c'tor
  //
  delegateImpl2() : stub_ptr_(0), obj_ptr_(0)

    , obj_clone_man_ptr_(0)

  {
    ::memset(&fp_info_, 0, sizeof(fp_info));
    ::memset(buf_, 0, size_buf);  // zero buffer
  }

  //
  // copy c'tor
  //
  delegateImpl2(thisClass const & other)
    : fp_info_(other.fp_info_), stub_ptr_(other.stub_ptr_), obj_ptr_(other.obj_ptr_)

    , obj_clone_man_ptr_(other.obj_clone_man_ptr_)

  {
    ::memset(buf_, 0, size_buf);  // zero buffer

    if(!other.empty_())
    {
      // to copy the function pointer from other

      if(other.fp_info_.by_malloc)
      {
        // function pointer is stored in the heap memory, so allocate a heap memory and deep copy
        fn_ptr_ = allocate_(other.fp_info_.sz_fp, 0);

        // copy function pointer
        ::memcpy(fn_ptr_, other.fn_ptr_, other.fp_info_.sz_fp);
      }
      else
      {
        // direct copy from other.buf_ to buf_
        ::memcpy(buf_, other.buf_, size_buf);
      }
    }

    if(obj_clone_man_ptr_)
    {
      obj_ptr_ = 0;
      (*obj_clone_man_ptr_)(*this, other.obj_ptr_, false);
    }

  }

  //
  // copy c'tor with member function argument binding
  //

  template<typename UR , typename U1 , typename U2, typename U, typename T>
    delegateImpl2(UR (U::*mfn)(U1 , U2), T & obj)
    : stub_ptr_(0), obj_ptr_(0)
    , obj_clone_man_ptr_(0)
  {
    ::memset(&fp_info_, 0, sizeof(fp_info));
    ::memset(buf_, 0, size_buf);  // zero buffer

    bind_obj_cloned_(mfn, obj, false);
  }

  template<typename UR , typename U1 , typename U2, typename U, typename T>
    delegateImpl2(UR (U::*mfn)(U1 , U2) const, T const & obj)
    : stub_ptr_(0), obj_ptr_(0), obj_clone_man_ptr_(0)
  {
    ::memset(&fp_info_, 0, sizeof(fp_info));
    ::memset(buf_, 0, size_buf);  // zero buffer

    bind_obj_cloned_(mfn, obj, false);
  }

  template<typename UR , typename U1 , typename U2, typename U, typename T>
    delegateImpl2(UR (U::*mfn)(U1 , U2), T * obj)
    : stub_ptr_(0), obj_ptr_(0)

    , obj_clone_man_ptr_(0)

  {
    ::memset(&fp_info_, 0, sizeof(fp_info));
    ::memset(buf_, 0, size_buf);  // zero buffer

    bind_obj_ptr_(mfn, obj, false);
  }

  template<typename UR , typename U1 , typename U2, typename U, typename T>
    delegateImpl2(UR (U::*mfn)(U1 , U2) const, T const * obj)
    : stub_ptr_(0), obj_ptr_(0)

    , obj_clone_man_ptr_(0)

  {
    ::memset(&fp_info_, 0, sizeof(fp_info));
    ::memset(buf_, 0, size_buf);  // zero buffer

    bind_obj_ptr_(mfn, obj, false);
  }

  // copy c'tor
  template<typename UR , typename U1 , typename U2>
  delegateImpl2(UR (*fn)(U1 , U2))
    : stub_ptr_(0), obj_ptr_(0)

    , obj_clone_man_ptr_(0)

  {
    ::memset(&fp_info_, 0, sizeof(fp_info));
    ::memset(buf_, 0, size_buf);  // zero buffer

    typedef UR (*TFn)(U1 , U2);
    // size of free function pointer is smaller than size_buf
    typedef typename fd::util::t_assert<(bool)(size_buf >= sizeof(TFn))>::assertion failed2279;

    assign_(fn, false);
  }

  // copy c'tor
  // specialization for member function call adapter
  template<typename UR , typename U2, typename U>
    delegateImpl2(UR (U::*mfn)(U2 q2))
    : stub_ptr_(0), obj_ptr_(0)

    , obj_clone_man_ptr_(0)

  {
    ::memset(&fp_info_, 0, sizeof(fp_info));
    ::memset(buf_, 0, size_buf);  // zero buffer

    assign_(mfn, false);
  }

  template<typename UR , typename U2, typename U>
    delegateImpl2(UR (U::*mfn)(U2 q2) const)
    : stub_ptr_(0), obj_ptr_(0)

    , obj_clone_man_ptr_(0)

  {
    ::memset(&fp_info_, 0, sizeof(fp_info));
    ::memset(buf_, 0, size_buf);  // zero buffer

    assign_(mfn, false);
  }

  // d'tor
  ~delegateImpl2()
  {
    free_fp_malloc_();

    if(obj_clone_man_ptr_)
    {
      assert(obj_ptr_);
      (*obj_clone_man_ptr_)(*this, 0, false);
    }

  }

  // ====================================================================================================
  // operations
  // ====================================================================================================

  //
  // swap_()
  //
  inline void swap_(thisClass & other)
  {
    std::swap(fp_info_, other.fp_info_);
    std::swap(stub_ptr_, other.stub_ptr_);
    std::swap(obj_ptr_, other.obj_ptr_);

    std::swap(obj_clone_man_ptr_, other.obj_clone_man_ptr_);

    unsigned char buf_temp[size_buf];
    ::memcpy(buf_temp,    buf_,       size_buf);
    ::memcpy(buf_,        other.buf_, size_buf);
    ::memcpy(other.buf_,  buf_temp,   size_buf);
  }

  // ====================================================================================================

  //
  // reset_()
  //
  inline void reset_()
  {
    thisClass().swap_(*this);
  }

  // ====================================================================================================

  //
  // empty_()
  //
  inline bool empty_() const
  {
    return 0 == fp_info_.sz_fp;
  }

  // ====================================================================================================

  //
  // assign_()
  //
  inline thisClass & assign_(thisClass const & other)
  {
    if(&other == this)
      return *this;

    thisClass(other).swap_(*this);

    return *this;
  }

  template<typename UR , typename U1 , typename U2>
    inline thisClass & assign_(UR (*fn)(U1 , U2), bool reset = true)
  {
    typedef UR (*TFn)(U1 , U2);
    // size of free function pointer is smaller than size_buf
    typedef typename fd::util::t_assert<(bool)(size_buf >= sizeof(TFn))>::assertion failed2549;

    if(reset) reset_();

    enum { bind_spec = false };

    fp_selector_<UR , U1 , U2>::template callee_bind_spec_<free_fn_tag, bind_spec>::init_(*this, fn);
    stub_ptr_ = &delegate_stub_t<UR , U1 , U2>::template callee_bind_spec_<free_fn_tag, bind_spec>::typed_invoker_;

    obj_ptr_ = ((void *)-1);

    return *this;
  }

  // specialization for member function call adapter
  template<typename UR , typename U2, typename U>
    inline thisClass & assign_(UR (U::*mfn)(U2 q2), bool reset = true)
  {
    if(reset) reset_();

    enum { bind_spec = false };

    fp_selector_<UR, T1 , U2>::template callee_bind_spec_<U, bind_spec>::type::init_(*this, mfn);
    stub_ptr_ = &delegate_stub_t<UR, T1 , U2>::template callee_bind_spec_<U, bind_spec>::typed_invoker_;

    return *this;
  }

  template<typename UR , typename U2, typename U>
    inline thisClass & assign_(UR (U::*mfn)(U2 q2) const, bool reset = true)
  {
    if(reset) reset_();

    enum { bind_spec = false };

    fp_selector_<UR, T1 , U2>::template callee_bind_spec_<U, bind_spec>::type::init_(*this, mfn);
    stub_ptr_ = reinterpret_cast<stub_type>(&delegate_stub_t<UR, T1 , U2>::template callee_bind_spec_<U, bind_spec>::typed_invoker_const_);

    return *this;
  }

  // ====================================================================================================

  //
  // functor assignment
  //

  template<typename F>
    inline thisClass & assign_ftor_cloned_ (F & functor, bool reset = true)
  {
    bind_obj_cloned_(&F::operator(), functor, reset);

    return *this;
  }

  template<typename F>
    inline thisClass & assign_ftor_ptr_(F * functor, bool reset = true)
  {
    bind_obj_ptr_(&F::operator(), functor, reset);

    return *this;
  }

  // ====================================================================================================

  //
  // bind_obj_ptr_() & bind_obj_cloned_()
  //

  //
  // member function argument binding
  //

  template<typename UR , typename U1 , typename U2, typename U, typename T>
    inline thisClass & bind_obj_cloned_(UR (U::*mfn)(U1 , U2), T & obj, bool reset = true)
  {
    if(reset) reset_();

    enum { bind_spec = true };

    fp_selector_<UR , U1 , U2>::template callee_bind_spec_<U, bind_spec>::type::init_(*this, mfn);
    stub_ptr_ = &delegate_stub_t<UR , U1 , U2>::template callee_bind_spec_<U, bind_spec>::typed_invoker_;

    obj_ptr_ = new T(obj);
    obj_clone_man_ptr_ = &obj_clone_man_t<T, U>::typed_obj_manager_;

    return *this;
  }

  template<typename UR , typename U1 , typename U2, typename U, typename T>
    inline thisClass & bind_obj_cloned_(UR (U::*mfn)(U1 , U2) const, T const & obj, bool reset = true)
  {
    if(reset) reset_();

    enum { bind_spec = true };

    fp_selector_<UR , U1 , U2>::template callee_bind_spec_<U, bind_spec>::type::init_(*this, mfn);
    stub_ptr_ = reinterpret_cast<stub_type>(&delegate_stub_t<UR , U1 , U2>::template callee_bind_spec_<U, bind_spec>::typed_invoker_const_);

    obj_ptr_ = new T(const_cast<T &>(obj));
    obj_clone_man_ptr_ = &obj_clone_man_t<T, U>::typed_obj_manager_;

    return *this;
  }

  template<typename UR , typename U1 , typename U2, typename U, typename T>
    inline thisClass & bind_obj_ptr_(UR (U::*mfn)(U1 , U2), T * obj, bool reset = true)
  {
    if(reset) reset_();

    enum { bind_spec = true };

    fp_selector_<UR , U1 , U2>::template callee_bind_spec_<U, bind_spec>::type::init_(*this, mfn);
    stub_ptr_ = &delegate_stub_t<UR , U1 , U2>::template callee_bind_spec_<U, bind_spec>::typed_invoker_;

    obj_ptr_ = obj;

    return *this;
  }

  template<typename UR , typename U1 , typename U2, typename U, typename T>
    inline thisClass & bind_obj_ptr_(UR (U::*mfn)(U1 , U2) const, T const * obj, bool reset = true)
  {
    if(reset) reset_();

    enum { bind_spec = true };

    fp_selector_<UR , U1 , U2>::template callee_bind_spec_<U, bind_spec>::type::init_(*this, mfn);
    stub_ptr_ = reinterpret_cast<stub_type>(&delegate_stub_t<UR , U1 , U2>::template callee_bind_spec_<U, bind_spec>::typed_invoker_const_);

    obj_ptr_ = const_cast<T *>(obj);

    return *this;
  }

  //
  // function call operator
  //
  inline result_type operator () (T1 p1 , T2 p2) const
  {
    if(empty_())
      throw bad_function_call();

    if(((void *)-1) == obj_ptr_)
    {
      enum { bind_spec = false };

      // free function call

      return (*stub_ptr_)(*this, ((void *)-1) , p1 , p2);

    }
    else
    {
      if(!fp_info_.is_const)
      {
        // bound member function call or mfn_adapter_ call
        return (*stub_ptr_)(*this, obj_ptr_ , p1 , p2);
      }
      else
      {
        // bound const member function call or const mfn_adapter_ call
        stub_const_type stub_const_ptr = reinterpret_cast<stub_const_type>(stub_ptr_);
        void const * obj_const_ptr = const_cast<void const *>(obj_ptr_);
        return (*stub_const_ptr)(*this, obj_const_ptr , p1 , p2);
      }
    }
  }

  // ====================================================================================================

  inline int fpcmp_(void const * fp1, void const * fp2, size_t count) const
  {
    return ::memcmp(fp1, fp2, count);
  }

  //
  // compare_()
  //
  inline int compare_(thisClass const & other, bool check_bound_object = false) const
  {
    if(fp_info_.sz_fp == other.fp_info_.sz_fp)
    {
      if(0 == fp_info_.sz_fp)
        return 0;  // empty delegates

      void const * this_fp = fp_info_.by_malloc ? fn_ptr_ : reinterpret_cast<void const *>(buf_);
      void const * other_fp = other.fp_info_.by_malloc ? other.fn_ptr_ : reinterpret_cast<void const *>(other.buf_);

      int cmp_result = fpcmp_(this_fp, other_fp, fp_info_.sz_fp);
      if(!check_bound_object || 0 != cmp_result)
        return cmp_result;

      // function pointers are the same and check_bound_object is set as true

      void * this_obj_ptr = obj_clone_man_ptr_ ? (*obj_clone_man_ptr_)(const_cast<thisClass &>(*this), 0, true) : obj_ptr_;
      void * other_obj_ptr = other.obj_clone_man_ptr_ ? (*other.obj_clone_man_ptr_)(const_cast<thisClass &>(other), 0, true) : other.obj_ptr_;

      return (reinterpret_cast<void **>(this_obj_ptr) - reinterpret_cast<void **>(other_obj_ptr));
    }
    else
    {
      if(0 == fp_info_.sz_fp)
        return -1;

      if(0 == other.fp_info_.sz_fp)
        return 1;

      size_t min_sz_fp = (fp_info_.sz_fp <= other.fp_info_.sz_fp)
        ? fp_info_.sz_fp
        : other.fp_info_.sz_fp;

      void const * this_fp = fp_info_.by_malloc ? fn_ptr_ : reinterpret_cast<void const *>(buf_);
      void const * other_fp = other.fp_info_.by_malloc ? other.fn_ptr_ : reinterpret_cast<void const *>(other.buf_);

      int cmp_result = fpcmp_(this_fp, other_fp, min_sz_fp);
      if(0 != cmp_result)
        return cmp_result;

      if(fp_info_.sz_fp <= other.fp_info_.sz_fp)
        return -1;
      else
        return 1;
    }
  }

  // ====================================================================================================

  //
  // comparison operators
  //
  inline bool operator == (thisClass const & other) const
  {
    return 0 == compare_(other, false);
  }
  inline bool operator != (thisClass const & other) const
  {
    return 0 != compare_(other, false);
  }
  inline bool operator <=  (thisClass const & other) const
  {
    return 0 >= compare_(other, false);
  }
  inline bool operator < (thisClass const & other) const
  {
    return 0 > compare_(other, false);
  }
  inline bool operator > (thisClass const & other) const
  {
    return 0 < compare_(other, false);
  }
  inline bool operator >= (thisClass const & other) const
  {
    return 0 <= compare_(other, false);
  }

  // ====================================================================================================

  // implementations

  inline void free_fp_malloc_()
  {
    if(fp_info_.by_malloc)
    {
      fp_info_.by_malloc = false;
      deallocate_(fn_ptr_, fp_info_.sz_fp);
      fn_ptr_ = 0;
    }
  }

}; // template<typename R FD_COMMA FD_TPARMS(N), size_t t_countof_pvoid> struct FD_JOIN(delegateImpl,N)

} // namespace detail

} // namespace fd

namespace fd
{

// ====================================================================================================
//
// ====================================================================================================
//
// Portable syntax
//
// class delegateN<R, T1, T2, ..., Tn, Allocator, t_countof_pvoid>;
//
// ====================================================================================================
//
// ====================================================================================================
template<typename R , typename T1 , typename T2, typename Allocator = std::allocator<void> , size_t t_countof_pvoid = DefaultCountOfVoid>
class delegate2
  : public detail::safe_bool<delegate2<R , T1 , T2, Allocator, t_countof_pvoid> >
{
  typedef delegate2<R , T1 , T2, Allocator, t_countof_pvoid> thisClass;

  // ====================================================================================================
  // data members
  // ====================================================================================================
private:

  typedef detail::delegateImpl2<R , T1 , T2, Allocator, t_countof_pvoid> implClass;
  implClass impl_;

public:

  typedef typename implClass::result_type result_type;

  // std::binary_function compatible
  typedef T1 first_argument_type;
  typedef T2  second_argument_type;

  struct friend__
  {
    static implClass &
      impl_of_(delegate2<R , T1 , T2, Allocator, t_countof_pvoid> & friend_delegate)
    {
      return friend_delegate.impl_;
    }
    static const implClass &
      impl_of_(delegate2<R , T1 , T2, Allocator, t_countof_pvoid> const & friend_delegate)
    {
      return friend_delegate.impl_;
    }

  };  // friend__
  friend struct friend__;

  // ====================================================================================================
  // c'tors & d'tor
  // ====================================================================================================
public:

  // default c'tor
  delegate2()
    : impl_()
  {
  }

  // to allow zero delegate constructions
  //
  // fd::delegate1<void, int> dg1(0);           // ok
  // fd::delegate<int (float, double)> dg2 = 0; // ok
  // fd::delegate0<void> dg3(1234);             // error
  // fd::delegate<int (int, int)> dg4 = 3456;   // error
  //
  delegate2(typename implClass::clear_type const *)
    : impl_()
  {
  }

  // copy c'tor
  delegate2(thisClass const & other)
    : impl_(other.impl_)
  {
  }

  //
  // copy c'tor with member function argument binding
  //

  template<typename UR , typename U1 , typename U2, typename U, typename T>
    delegate2(UR (U::*mfn)(U1 , U2), T & obj)

    : impl_(mfn, obj)
  {
    // to prevent non-const member function call on const object
    U * param_chk = detail::select_obj_type_<T, U>::type::get_pointer_(obj); param_chk;
  }

  template<typename UR , typename U1 , typename U2, typename U, typename T>
    delegate2(UR (U::*mfn)(U1 , U2) const, T & obj)

    : impl_(mfn, const_cast<T const &>(obj))
  {
    // to prevent non-const member function call on const object
    U const * param_chk = detail::select_obj_type_<T, U>::type::get_pointer_(obj); param_chk;
  }

  template<typename UR , typename U1 , typename U2, typename U, typename T>
    delegate2(UR (U::*mfn)(U1 , U2), T * obj)

    : impl_(mfn, get_pointer(obj))
  {
    // to prevent non-const member function call on const object
    U * param_chk = obj; param_chk;
  }

  template<typename UR , typename U1 , typename U2, typename U, typename T>
    delegate2(UR (U::*mfn)(U1 , U2) const, T * obj)

    : impl_(mfn, const_cast<T const *>(get_pointer(obj)))
  {
    // to prevent non-const member function call on const object
    U const * param_chk = obj; param_chk;
  }

  // ----------------------------------------------------------------------

  template<typename UR , typename U1 , typename U2>
    delegate2(UR (*fn)(U1 , U2))
    : impl_(fn)
  {

  }

  // copy c'tor
  // specialization for member function call adapter

  template<typename UR , typename U2, typename U>
    delegate2(UR (U::*mfn)(U2 q2))

    : impl_(mfn)
  {
    // typename 'T1' should match with typename 'U *' or typename 'U &'
    enum { value = util::Is_pointer_or_reference<U, T1>::value };
    typedef typename fd::util::t_assert<(bool)(value)>::assertion failed1752;
  }

  // specialization for member function call adapter

  template<typename UR , typename U2, typename U>
    delegate2(UR (U::*mfn)(U2 q2) const)

    : impl_(mfn)
  {
    // typename 'T1' should match with typename 'U const *' or typename 'U const &'
    enum { value = util::Is_pointer_or_reference<U const, T1>::value };
    typedef typename fd::util::t_assert<(bool)(value)>::assertion failed1767;
  }

  template<typename F>
    delegate2(F & functor, bool/* dummy*/)
    : impl_()
  {

    impl_.assign_ftor_cloned_(functor, false);
  }

  template<typename F>
    delegate2(F * functor, bool/* dummy*/)
    : impl_()
  {

    impl_.assign_ftor_ptr_(functor, false);
  }

  // d'tor
  ~delegate2() { }

  // ====================================================================================================
  // operations
  // ====================================================================================================
public:

  //
  // swap()
  //
  inline void swap(thisClass & other)
  {
    impl_.swap_(other.impl_);
  }

  // ====================================================================================================

  //
  // clear()
  //
  inline void clear()
  {
    impl_.reset_();
  }

  // ====================================================================================================

  //
  // empty()
  //
  inline bool empty() const
  {
    return impl_.empty_();
  }

  // ====================================================================================================

  //
  // assignment operators
  //

  // ----------------------------------------------------------------------

  template<typename F>
    inline thisClass & operator <<= (F & functor)
  {

    impl_.assign_ftor_cloned_(functor);

    return *this;
  }

  template<typename F>
    inline thisClass & operator <<= (F * functor)
  {

    impl_.assign_ftor_ptr_(functor);

    return *this;
  }

  // ----------------------------------------------------------------------
  
  inline thisClass & operator = (thisClass const & other)
  {
    if(&this->impl_ == &other.impl_)
      return *this;

    impl_.assign_(other.impl_);

    return *this;
  }

  // ----------------------------------------------------------------------

  // to allow the zero assignment to clear delegate
  //
  // fd::delegate1<void, int> dg1;
  // dg1 = 0;     // ok
  // dg1 = 1234;  // error
  //
  inline thisClass & operator = (typename implClass::clear_type const *)
  {
    impl_.reset_();
    return *this;
  }

  // ----------------------------------------------------------------------

  template<typename UR , typename U1 , typename U2>
    inline thisClass & operator = (UR (*fn)(U1 , U2))
  {

    impl_.assign_(fn);
    return *this;
  }

  // specialization for member function call adapter

  template<typename UR , typename U2, typename U>
    inline thisClass & operator = (UR (U::*mfn)(U2 q2))

  {
    // typename 'T1' should match with typename 'U *' or typename 'U &'
    enum { value = util::Is_pointer_or_reference<U, T1>::value };
    typedef typename fd::util::t_assert<(bool)(value)>::assertion failed2104;

    impl_.assign_(mfn);
    return *this;
  }

  template<typename UR , typename U2, typename U>
    inline thisClass & operator = (UR (U::*mfn)(U2 q2) const)

  {
    // typename 'T1' should match with typename 'U const *' or typename 'U const &'
    enum { value = util::Is_pointer_or_reference<U const, T1>::value };
    typedef typename fd::util::t_assert<(bool)(value)>::assertion failed2120;

    impl_.assign_(mfn);
    return *this;
  }

  // ====================================================================================================

  //
  // bind()
  //

  //
  // member function argument binding
  //

  template<typename UR , typename U1 , typename U2, typename U, typename T>
    inline thisClass & bind(UR (U::*mfn)(U1 q1 , U2 q2), T & obj)

  {
    // to prevent non-const member function call on const object
    U * param_chk = detail::select_obj_type_<T, U>::type::get_pointer_(obj); param_chk;

    impl_.bind_obj_cloned_(mfn, obj);

    return *this;
  }

  template<typename UR , typename U1 , typename U2, typename U, typename T>
    inline thisClass & bind(UR (U::*mfn)(U1 q1 , U2 q2) const, T & obj)

  {
    // to prevent non-const member function call on const object
    U const * param_chk = detail::select_obj_type_<T, U>::type::get_pointer_(obj); param_chk;

    impl_.bind_obj_cloned_(mfn, const_cast<T const &>(obj));

    return *this;
  }

  template<typename UR , typename U1 , typename U2, typename U, typename T>
    inline thisClass & bind(UR (U::*mfn)(U1 q1 , U2 q2), T * obj)

  {
    // to prevent non-const member function call on const object
    U * param_chk = obj; param_chk;

    impl_.bind_obj_ptr_(mfn, obj);

    return *this;
  }

  template<typename UR , typename U1 , typename U2, typename U, typename T>
    inline thisClass & bind(UR (U::*mfn)(U1 q1 , U2 q2) const, T * obj)

  {
    // to prevent non-const member function call on const object
    U const * param_chk = obj; param_chk;

    impl_.bind_obj_ptr_(mfn, const_cast<T const *>(obj));

    return *this;
  }

  // ====================================================================================================

  //
  // function call operator
  //
  inline result_type operator () (T1 p1 , T2 p2) const
  {
    return impl_.operator () (p1 , p2);
  }

  // ====================================================================================================

  //
  // compare()
  //
  inline int compare(thisClass const & other, bool check_bound_object = false) const
  {
    return impl_.compare_(other.impl_, check_bound_object);
  }

  // ====================================================================================================

  //
  // comparison operators
  //

  // to allow to compare to 0
  inline bool operator == (typename implClass::clear_type const *) const
  {
    return impl_.empty_();
  }
  inline bool operator != (typename implClass::clear_type const *) const
  {
    return !impl_.empty_();
  }

  // ------------------------------------------------------------

  inline bool operator == (thisClass const & other) const
  {
    return impl_.operator == (other.impl_);
  }
  inline bool operator != (thisClass const & other) const
  {
    return impl_.operator != (other.impl_);
  }
  inline bool operator <= (thisClass const & other) const
  {
    return impl_.operator <= (other.impl_);
  }
  inline bool operator < (thisClass const & other) const
  {
    return impl_.operator < (other.impl_);
  }
  inline bool operator > (thisClass const & other) const
  {
    return impl_.operator > (other.impl_);
  }
  inline bool operator >= (thisClass const & other) const
  {
    return impl_.operator >= (other.impl_);
  }

};  // template<typename R, typename T, size_t t_countof_pvoid> class FD_JOIN(delegate,N)

} // namespace fd

/** @file bindtmpl.h
 *
 *  @brief  helper functions (fd::make_delegate)
 *
 *
 *  @author JaeWook Choi
 *  @version 1.10
 *
 *  @history
 *    1.10 (03.12.2006) - see history of "delegateimpl.h"
 *    1.01 (03.10.2006) - make_delegate implementation is separated from delegatetmpl.h
 *                        removed type-check relaxation version of make_delegate
 *                        (make_delegate is automatic type deduction function and it is not
 *                         useful at all in type-check relaxation mode)
 *
 *
 * This software is provided "as is" without express or implied warranty, and with
 * no claim as to its suitability for any purpose.
 *
 */

// Note: this header is a header template and must NOT have multiple-inclusion
// protection.

namespace fd
{

template<typename R , typename T1 , typename T2> inline
delegate2<R , T1 , T2>
make_delegate(R (*fn)(T1 , T2))
{
  return delegate2<R , T1 , T2>(fn);
}

// ====================================================================================================
// member function argument binding
// ====================================================================================================

template<typename R , typename T1 , typename T2, typename U, typename T> inline
delegate2<R , T1 , T2>
make_delegate(R (U::*mfn)(T1 p1 , T2 p2), T & obj)
{
  // to prevent non-const member function call on const object
  U * param_chk = detail::select_obj_type_<T, U>::type::get_pointer_(obj); param_chk;

  return delegate2<R , T1 , T2>(mfn, obj);
}

template<typename R , typename T1 , typename T2, typename U, typename T> inline
delegate2<R , T1 , T2>
make_delegate(R (U::*mfn)(T1 p1 , T2 p2) const, T & obj)
{
  // to prevent non-const member function call on const object
  U const * param_chk = detail::select_obj_type_<T, U>::type::get_pointer_(obj); param_chk;

  return delegate2<R , T1 , T2>(mfn, obj);
}

template<typename R , typename T1 , typename T2, typename U, typename T> inline
delegate2<R , T1 , T2>
make_delegate(R (U::*mfn)(T1 p1 , T2 p2), T * obj)
{
  // to prevent non-const member function call on const object
  U * param_chk = obj; param_chk;

  return delegate2<R , T1 , T2>(mfn, get_pointer(obj));
}

template<typename R , typename T1 , typename T2, typename U, typename T> inline
delegate2<R , T1 , T2>
make_delegate(R (U::*mfn)(T1 p1 , T2 p2) const, T * obj)
{
  // to prevent non-const member function call on const object
  U const * param_chk = obj; param_chk;

  return delegate2<R , T1 , T2>(mfn, get_pointer(obj));
}

// ====================================================================================================

//
// make_delegate_adpater() for member function adapter
//
// When using make_delegate() helper function for member function adapter,
// it is impossible to tell whether member function adapter is used in the
// pointer form (1) or in the reference form (2), therefore only pointer form (1)
// of make_delegate() for member function adapter will be enabled
//

// ----------------------------------------------------------------------
//
// 1)
// template<typename T>
// R operator()(cv-quals T * px, T1 p1, T2 p2, ..., Tn pn) cv-quals
// {
//   return px->.*mf(p1, p2, ..., pn);
// }
//
// (NOTE)
//
// the first argument of the pointer to object is only used for providing explicit type
// information about the member function which is being stored
//
// (why?)
//
// class Base
// {
// public:
//   virtual int foo(int);
// };
// class Derived : public Base
// {
// };
// template<typename T>
// void bar(int (T::*mfn)(int))
// {
//   enum { assertion = fd::util::Is_same<T, Derived>::value };
//   FD_STATIC_ASSERT(assertion);
// }
// int main()
// {
//   bar(&Derived::foo);  // cause FD_STATIC_ASSERT() in bar() at compile time !!!
// }
//
// In the code snippet shown above, typename 'T' is found to be 'Base' not 'Derived'
// even though member function pointer was specified as &Derived::foo when calling bar().
// therefore, to make make_delegate() to work as the user intended, explicit type info.
// should be passed over into make_delegate() call, something like,
//
// fd::delegate2<int, Derived *, int> dg = make_delegate((Derived *)0, &Derived::foo);
//
// If explicit type info. is passed over into make_delegate() as the second argument instead,
// it will confuse the compiler as its signature become exactly same as
// the member function with binging object version of make_delegate(), So type info.
// passed over into make_delegate() as the first argument to distinguish b/w them.
//
// It isn't really nice, but I don't see any better solution for this
//

template<typename R , typename T2, typename U, typename T> inline
delegate2<R, T * , T2>
make_delegate(T *, R (U::*mfn)(T2 p2))
{
  // to prevent non-const member function call on const object
  U * param_chk = (T *)0; param_chk;

  return delegate2<R, T * , T2>(mfn);
}

template<typename R , typename T2, typename U, typename T> inline
delegate2<R, T * , T2>
make_delegate(T *, R (U::*mfn)(T2 p2) const)
{
  U const * param_chk = (T *)0; param_chk;

  return delegate2<R, T * , T2>(mfn);
}

}  // namespace fd

/** @file bindtmpl.h
 *
 *  @brief  fd::bind
 *
 *  (note)
 *  [obsolete] bind do not support FD_ENABLE_TYPE_RELAXATION, use make_delegate() instead
 *             make_delegate do not support FD_TYPE_REXATION neither from version 1.01
 *
 *
 *  @author JaeWook Choi
 *  @version 1.10
 *
 *  @history
 *    1.10 (03.12.2006) - see history of "delegateimpl.h"
 *    1.01 (03.10.2006) - bind implementation is separated from delegatetmpl.h
 *
 * copied from FastDelegateBind.h (http://www.codeproject.com/cpp/FastDelegate.asp)
 * Original author: Jody Hagins
 *
 * This software is provided "as is" without express or implied warranty, and with
 * no claim as to its suitability for any purpose.
 *
 */

// Note: this header is a header template and must NOT have multiple-inclusion
// protection.

namespace fd
{

template<typename R , typename T1 , typename T2, typename U, typename T> inline
delegate2<R , T1 , T2>
bind(R (U::*mfn)(T1 , T2), T & obj, ...)
{
  // to prevent non-const member function call on const object
  U * param_chk = detail::select_obj_type_<T, U>::type::get_pointer_(obj); param_chk;

  return delegate2<R , T1 , T2>(mfn, obj);
}

template<typename R , typename T1 , typename T2, typename U, typename T> inline
delegate2<R , T1 , T2>
bind(R (U::*mfn)(T1 , T2) const, T & obj, ...)
{
  // to prevent non-const member function call on const object
  U const * param_chk = detail::select_obj_type_<T, U>::type::get_pointer_(obj); param_chk;

  return delegate2<R , T1 , T2>(mfn, obj);
}

template<typename R , typename T1 , typename T2, typename U, typename T> inline
delegate2<R , T1 , T2>
bind(R (U::*mfn)(T1 , T2), T * obj, ...)
{
  // to prevent non-const member function call on const object
  U * param_chk = obj; param_chk;

  return delegate2<R , T1 , T2>(mfn, get_pointer(obj));
}

template<typename R , typename T1 , typename T2, typename U, typename T> inline
delegate2<R , T1 , T2>
bind(R (U::*mfn)(T1 , T2) const, T * obj, ...)
{
  // to prevent non-const member function call on const object
  U const * param_chk = obj; param_chk;

  return delegate2<R , T1 , T2>(mfn, get_pointer(obj));
}

}  // namespace fd
