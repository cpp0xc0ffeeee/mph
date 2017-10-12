/*
 * NotNull.hpp
 *
 *  Created on: Sep 22, 2017
 *      Author: butters
 */

#ifndef NotNull_HPP_H0C128560_6635_4638_9064_76F6EE635CFA
#define NotNull_HPP_H0C128560_6635_4638_9064_76F6EE635CFA

#include <type_traits>
#include <stdexcept>
#include <utility>
#include <cstddef>

namespace mph
{

template<class T>
class NotNull
{

static_assert(
        std::is_pointer<T>::value ||
        std::is_member_pointer<T>::value,
        "T is not a pointer");

private:
    T mPointer;

public:

    NotNull(T p)
            :mPointer( p )
    {
        if(mPointer==nullptr)
            throw std::invalid_argument("");
    }

    template<class U>
    constexpr NotNull(const NotNull<U>& u) noexcept
            :mPointer( u.mValue )
    {}

    NotNull(std::nullptr_t) = delete;

    NotNull& operator=(T p)
    {
        if(p==nullptr)
            throw std::invalid_argument("");
        mPointer = p;
        return *this;
    }

    template<class U>
    NotNull& operator=(const NotNull<U>& u) noexcept
    {
        mPointer = u.mValue;
        return *this;
    }

    NotNull& operator=(std::nullptr_t) = delete;

    constexpr operator T () const noexcept
    {
        return mPointer;
    }

    constexpr T get() const noexcept
    {
        return mPointer;
    }

};//class NotNull

} /* namespace mph */

#endif /* NotNull_HPP_H0C128560_6635_4638_9064_76F6EE635CFA */
