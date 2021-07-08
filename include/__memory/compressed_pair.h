// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___MEMORY_COMPRESSED_PAIR_H
#define _LIBCPP___MEMORY_COMPRESSED_PAIR_H

#define _LIBCPP_BEGIN_NAMESPACE_STD namespace std {
#define _LIBCPP_END_NAMESPACE_STD   }

#define _NOEXCEPT noexcept
#define _LIBCPP_CONSTEXPR constexpr


#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_CXX14_CONSTEXPR)
#  define _LIBCPP_CONSTEXPR_AFTER_CXX14 constexpr
#else
#  define _LIBCPP_CONSTEXPR_AFTER_CXX14
#endif

//#include <__utility/forward.h>
#include <_tuple> // needed in c++03 for some constructors
#include <type_traits>
#include <utility>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif


_LIBCPP_BEGIN_NAMESPACE_STD
    template<class _Tp, bool>
    struct _LIBCPP_TEMPLATE_VIS __dependent_type
    : public _Tp {};

template<class _Tp>
struct _LIBCPP_TEMPLATE_VIS
        __libcpp_is_final
: public integral_constant<bool, __is_final(_Tp)> {
};

struct __default_init_tag {
};
struct __value_init_tag {
};

template<class _Tp, int _Idx,
        bool _CanBeEmptyBase =
        is_empty<_Tp>::value && !__libcpp_is_final<_Tp>::value>
struct __compressed_pair_elem {
    typedef _Tp _ParamT;
    typedef _Tp &reference;
    typedef const _Tp &const_reference;

    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    __compressed_pair_elem(__default_init_tag) {}

    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    __compressed_pair_elem(__value_init_tag) : __value_() {}

    template<class _Up, class = typename enable_if<
            !is_same<__compressed_pair_elem, typename decay<_Up>::type>::value
    >::type>
    _LIBCPP_INLINE_VISIBILITY
    _LIBCPP_CONSTEXPR explicit
    __compressed_pair_elem(_Up &&__u)
            : __value_(_VSTD::forward<_Up>(__u)) {
    }


#ifndef _LIBCPP_CXX03_LANG

    template<class... _Args, size_t... _Indexes>
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
    __compressed_pair_elem(piecewise_construct_t, tuple<_Args...> __args,
                           __tuple_indices<_Indexes...>)
            : __value_(_VSTD::forward<_Args>(_VSTD::get<_Indexes>(__args))...) {}

#endif


    _LIBCPP_INLINE_VISIBILITY reference

    __get() _NOEXCEPT { return __value_; }

    _LIBCPP_INLINE_VISIBILITY
            const_reference

    __get() const _NOEXCEPT { return __value_; }

private:
    _Tp __value_;
};

template<class _T1, class _T2>
class __compressed_pair : private __compressed_pair_elem<_T1, 0>,
                          private __compressed_pair_elem<_T2, 1> {
public:
    // NOTE: This static assert should never fire because __compressed_pair
    // is *almost never* used in a scenario where it's possible for T1 == T2.
    // (The exception is std::function where it is possible that the function
    //  object and the allocator have the same type).
    static_assert((!is_same<_T1, _T2>::value),
                  "__compressed_pair cannot be instantiated when T1 and T2 are the same type; "
                  "The current implementation is NOT ABI-compatible with the previous "
                  "implementation for this configuration");

    typedef _LIBCPP_NODEBUG_TYPE __compressed_pair_elem
    <_T1, 0> _Base1;
    typedef _LIBCPP_NODEBUG_TYPE __compressed_pair_elem
    <_T2, 1> _Base2;

    template<bool _Dummy = true,
            class = typename enable_if<
                    __dependent_type < is_default_constructible < _T1>, _Dummy> ::value &&
            __dependent_type<is_default_constructible < _T2>, _Dummy
    >::value
    >::type
    >

    _LIBCPP_INLINE_VISIBILITY
    _LIBCPP_CONSTEXPR __compressed_pair() : _Base1(__value_init_tag()), _Base2(__value_init_tag()) {}

    template<class _U1, class _U2>
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    __compressed_pair(_U1 &&__t1, _U2 &&__t2)
            : _Base1(_VSTD::forward<_U1>(__t1)), _Base2(_VSTD::forward<_U2>(__t2)) {}

#ifndef _LIBCPP_CXX03_LANG

    template<class... _Args1, class... _Args2>
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
    __compressed_pair(piecewise_construct_t __pc, tuple<_Args1...> __first_args,
                      tuple<_Args2...> __second_args)
            : _Base1(__pc, _VSTD::move(__first_args),
                     typename __make_tuple_indices<sizeof...(_Args1)>::type()),
              _Base2(__pc, _VSTD::move(__second_args),
                     typename __make_tuple_indices<sizeof...(_Args2)>::type()) {}

#endif

    _LIBCPP_INLINE_VISIBILITY
    typename _Base1::reference

    first() _NOEXCEPT {
        return static_cast<_Base1 &>(*this).__get();
    }

    _LIBCPP_INLINE_VISIBILITY
    typename _Base1::const_reference

    first() const _NOEXCEPT {
        return static_cast<_Base1 const &>(*this).__get();
    }

    _LIBCPP_INLINE_VISIBILITY
    typename _Base2::reference

    second() _NOEXCEPT {
        return static_cast<_Base2 &>(*this).__get();
    }

    _LIBCPP_INLINE_VISIBILITY
    typename _Base2::const_reference

    second() const _NOEXCEPT {
        return static_cast<_Base2 const &>(*this).__get();
    }

    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    static _Base1
    *
    __get_first_base(__compressed_pair
    * __pair) _NOEXCEPT {
        return static_cast<_Base1 *>(__pair);
    }
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    static _Base2
    *
    __get_second_base(__compressed_pair
    * __pair) _NOEXCEPT {
        return static_cast<_Base2 *>(__pair);
    }
};

_LIBCPP_END_NAMESPACE_STD;

#endif // _LIBCPP___MEMORY_COMPRESSED_PAIR_H
