/*
 * Util.hpp
 *
 *  Created on: Aug 27, 2017
 *      Author: butters
 */

#ifndef Util_HPP_H98C550F2_67DB_494A_9EDD_F22225ECF124
#define Util_HPP_H98C550F2_67DB_494A_9EDD_F22225ECF124

#include <string>
#include <system_error>
#include <limits>
#include <memory>
#include <chrono>
#include <type_traits>

#include "MFuncWrapper.hpp"

namespace mph
{

namespace details
{
    template<class, class>
    struct MFuncWrapperTypeHelper;

    template<class R, class C, class ...ARGS>
    struct MFuncWrapperTypeHelper<std::function<R(ARGS...)>, C>
    {
        using Type=R(C::*)(ARGS...);
        using ConstType=R(C::*)(ARGS...) const;
    };

    template<class R, class C, class ...ARGS>
    struct MFuncWrapperTypeHelper<R(*)(ARGS...), C>
    {
        using Type=R(C::*)(ARGS...);
        using ConstType=R(C::*)(ARGS...) const;
    };

    template<class R, class C, class ...ARGS>
    struct MFuncWrapperTypeHelper<R(ARGS...), C>
    {
        using Type=R(C::*)(ARGS...);
        using ConstType=R(C::*)(ARGS...) const;
    };

    template<class R, class C2, class C, class ...ARGS>
    struct MFuncWrapperTypeHelper<R(C2::*)(ARGS...), C>
    {
        using Type=R(C::*)(ARGS...);
        using ConstType=R(C::*)(ARGS...) const;
    };

    template<class R, class C2, class C, class ...ARGS>
    struct MFuncWrapperTypeHelper<R(C2::*)(ARGS...) const, C>
    {
        using Type=R(C::*)(ARGS...);
        using ConstType=R(C::*)(ARGS...) const;
    };
    template<class T>
    struct MakeUniqueHelper
    {
        using Object=std::unique_ptr<T>;
    };

    template<class T>
    struct MakeUniqueHelper<T[]>
    {
        using Array=std::unique_ptr<T[]>;
    };

    template<class T, std::size_t N>
    struct MakeUniqueHelper<T[N]>
    {
        struct Invalid{};
    };
}//namespace detail

class Util
{
public:
    Util() = delete;

}; //class Util

template<class F, class C, typename details::MFuncWrapperTypeHelper<F,C>::Type V>
MFuncWrapper<typename details::MFuncWrapperTypeHelper<F, C>::Type, V>
bindMFunc(C* instance) noexcept
{
    return instance;
}

template<class F, class C, typename details::MFuncWrapperTypeHelper<F,C>::ConstType V>
MFuncWrapper<typename details::MFuncWrapperTypeHelper<F, C>::ConstType, V>
bindMFuncConst(const C* instance) noexcept
{
    return instance;
}

int stoi(int& value, const std::string& str, std::size_t* pos = 0, int base = 10) noexcept;

int stoi(int& value, const std::wstring& str, std::size_t* pos = 0, int base = 10) noexcept;

int stol(long & value, const std::string& str, std::size_t* pos = 0, int base = 10) noexcept;

int stol(long & value, const std::wstring& str, std::size_t* pos = 0, int base = 10) noexcept;

int stoll(long long & value, const std::string& str, std::size_t* pos = 0, int base = 10) noexcept;

int stoll(long long & value, const std::wstring& str, std::size_t* pos = 0, int base = 10) noexcept;

int stoui(unsigned int& value, const std::string& str, std::size_t* pos = 0, int base = 10) noexcept;

int stoui(unsigned int& value, const std::wstring& str, std::size_t* pos = 0, int base = 10) noexcept;

int stoul(unsigned long & value, const std::string& str, std::size_t* pos = 0, int base = 10) noexcept;

int stoul(unsigned long & value, const std::wstring& str, std::size_t* pos = 0, int base = 10) noexcept;

int stoull(unsigned long long & value, const std::string& str, std::size_t* pos = 0, int base = 10) noexcept;

int stoull(unsigned long long & value, const std::wstring& str, std::size_t* pos = 0, int base = 10)
        noexcept;

int stof(float& value, const std::string& str, std::size_t* pos = 0) noexcept;

int stof(float& value, const std::wstring& str, std::size_t* pos = 0) noexcept;

int stod(double& value, const std::string& str, std::size_t* pos = 0) noexcept;

int stod(double& value, const std::wstring& str, std::size_t* pos = 0) noexcept;

int stold(long double& value, const std::string& str, std::size_t* pos = 0) noexcept;

int stold(long double& value, const std::wstring& str, std::size_t* pos = 0) noexcept;

template<class T, class... Args>
typename details::MakeUniqueHelper<T>::Object
make_unique( Args&&... args )
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<class T>
typename details::MakeUniqueHelper<T>::Array
make_unique( std::size_t size )
{
    return std::unique_ptr<T>(new typename std::remove_extent<T>::type[size]());
}

template<class T, class ...ARGS>
typename details::MakeUniqueHelper<T>::Invalid
make_unique(ARGS&&...) = delete;

} /* namespace mph */

#endif /* Util_HPP_H98C550F2_67DB_494A_9EDD_F22225ECF124 */
