/*
 * MFuncWrapper.hpp
 *
 *  Created on: Aug 27, 2017
 *      Author: butters
 */

#ifndef MFuncWrapper_HPP_HC256C0B0_3BC9_4293_A4DB_2923F4504182
#define MFuncWrapper_HPP_HC256C0B0_3BC9_4293_A4DB_2923F4504182

#include <utility>
#include <cstddef>
#include <stdexcept>

namespace mph
{

template<class F, F V>
    class MFuncWrapper;

    template<class R, class C, class ...ARGS, R(C::*V)(ARGS...) const>
    class MFuncWrapper<R(C::*)(ARGS...) const, V>
    {
    private:
        const C* mInstance;

    public:
        MFuncWrapper(std::nullptr_t) = delete;

        MFuncWrapper(const C* instance)
                :mInstance(instance)
        {
            if(!instance)
                throw std::invalid_argument("");
        }

        template<class ...INARGS>
        R operator()(INARGS&&... args)
        {
            return (mInstance->*V)(std::forward<INARGS>(args)...);
        }
    };

    template<class R, class C, class ...ARGS, R(C::*V)(ARGS...)>
    class MFuncWrapper<R(C::*)(ARGS...), V>
    {
    private:
        C* mInstance;

    public:
        MFuncWrapper(std::nullptr_t) = delete;

        MFuncWrapper(C* instance)
                :mInstance(instance)
        {
            if(!mInstance)
                throw std::invalid_argument("");
        }

        template<class ...INARGS>
        R operator()(INARGS&&... args)
        {
            return (mInstance->*V)(std::forward<INARGS>(args)...);
        }
    };

}


#endif /* MFuncWrapper_HPP_HC256C0B0_3BC9_4293_A4DB_2923F4504182 */
