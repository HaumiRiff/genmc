// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___MEMORY_SHARED_PTR_H
#define _LIBCPP___MEMORY_SHARED_PTR_H

#define _LIBCPP_INLINE_VISIBILITY __attribute__((visibility("inline")))

#define _LIBCPP_BEGIN_NAMESPACE_STD namespace std {
#define _LIBCPP_END_NAMESPACE_STD   }

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif
_LIBCPP_BEGIN_NAMESPACE_STD

template <class _ValueType>
inline _LIBCPP_INLINE_VISIBILITY
_ValueType __libcpp_relaxed_load(_ValueType const* __value) {
#if !defined(_LIBCPP_HAS_NO_THREADS) && \
    defined(__ATOMIC_RELAXED) &&        \
    (__has_builtin(__atomic_load_n) || defined(_LIBCPP_COMPILER_GCC))
    return __atomic_load_n(__value, __ATOMIC_RELAXED);
#else
    return *__value;
#endif
}


template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _Tp
__libcpp_atomic_refcount_increment(_Tp& __t) _NOEXCEPT
{
#if defined(_LIBCPP_HAS_BUILTIN_ATOMIC_SUPPORT) && !defined(_LIBCPP_HAS_NO_THREADS)
    return __atomic_add_fetch(&__t, 1, __ATOMIC_RELAXED);
#else
    return __t += 1;
#endif
}

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _Tp
__libcpp_atomic_refcount_decrement(_Tp& __t) _NOEXCEPT
{
#if defined(_LIBCPP_HAS_BUILTIN_ATOMIC_SUPPORT) && !defined(_LIBCPP_HAS_NO_THREADS)
    return __atomic_add_fetch(&__t, -1, __ATOMIC_ACQ_REL);
#else
    return __t -= 1;
#endif
}

template<class _Tp> class _LIBCPP_TEMPLATE_VIS weak_ptr;

class _LIBCPP_TYPE_VIS __shared_count
{
    __shared_count(const __shared_count&);
    __shared_count& operator=(const __shared_count&);

protected:
    long __shared_owners_;
    virtual ~__shared_count();
private:
    virtual void __on_zero_shared() _NOEXCEPT = 0;

public:
    _LIBCPP_INLINE_VISIBILITY
    explicit __shared_count(long __refs = 0) _NOEXCEPT
        : __shared_owners_(__refs) {}

#if defined(_LIBCPP_BUILDING_LIBRARY) && \
    defined(_LIBCPP_DEPRECATED_ABI_LEGACY_LIBRARY_DEFINITIONS_FOR_INLINE_FUNCTIONS)
    void __add_shared() _NOEXCEPT;
    bool __release_shared() _NOEXCEPT;
#else
    _LIBCPP_INLINE_VISIBILITY
    void __add_shared() _NOEXCEPT {
      __libcpp_atomic_refcount_increment(__shared_owners_);
    }
    _LIBCPP_INLINE_VISIBILITY
    bool __release_shared() _NOEXCEPT {
      if (__libcpp_atomic_refcount_decrement(__shared_owners_) == -1) {
        __on_zero_shared();
        return true;
      }
      return false;
    }
#endif
    _LIBCPP_INLINE_VISIBILITY
    long use_count() const _NOEXCEPT {
        return __libcpp_relaxed_load(&__shared_owners_) + 1;
    }
};



_LIBCPP_END_NAMESPACE_STD

#endif //_LIBCPP___MEMORY_SHARED_PTR_H
