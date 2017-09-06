//============================================================================
// Name        : mph.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <memory>
#include <utility>

#include "Util.hpp"
#include "FixedThreadPool.hpp"

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

template<class T, class... Args>
typename MakeUniqueHelper<T>::Object
make_unique( Args&&... args )
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<class T>
typename MakeUniqueHelper<T>::Array
make_unique( std::size_t size )
{
    return std::unique_ptr<T>(new typename std::remove_extent<T>::type[size]());
}

template<class T, class ...ARGS>
typename MakeUniqueHelper<T>::Invalid
make_unique(ARGS&&...) = delete;

using namespace std;

int main()
{
	return 0;
}
