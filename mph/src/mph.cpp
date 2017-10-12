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
#include <type_traits>
#include <chrono>

#include "Util.hpp"
#include "basic_string_view.hpp"
#include "NotNull.hpp"
#include "MFuncWHelper.hpp"
#include "Timer.hpp"

using namespace std;

void func(bool cancelled)
{
    cout<<cancelled<<endl;
}

int main()
{
    mph::Timer<chrono::steady_clock> timer(&func);
    timer.expiresFromNow( chrono::seconds(2) );
    timer.cancel();
	return 0;
}
