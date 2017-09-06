/*
 * MFuncWrapperTypeHelper.hpp
 *
 *  Created on: Aug 27, 2017
 *      Author: butters
 */

#ifndef MFuncWrapperTypeHelper_HPP_H8D0C9E81_7676_4A32_AB53_EF9F6AB0DD0E
#define MFuncWrapperTypeHelper_HPP_H8D0C9E81_7676_4A32_AB53_EF9F6AB0DD0E

#include <functional>

namespace mph
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

}


#endif /* MFuncWrapperTypeHelper_HPP_H8D0C9E81_7676_4A32_AB53_EF9F6AB0DD0E */
