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
#include <functional>

#include "Util.hpp"
#include "basic_string_view.hpp"


using namespace std;

class Clazz
{
public:
    void pp1()
    {
        cout<<1<<endl;
    }

    void pp1() const
    {
        cout<<2<<endl;
    }
};

int main()
{
    Clazz clazz;
    auto f1=mph::bindMFuncConst<
            void(),
            Clazz,
            &Clazz::pp1>(&clazz);

    Clazz* p1=&clazz;
    const Clazz* p2=p1;
    f1();
	return 0;
}
