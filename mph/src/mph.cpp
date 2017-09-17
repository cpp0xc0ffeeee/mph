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
#include "basic_string_view.hpp"


using namespace std;

int main()
{
    mph::string_view ss{"123"};
    mph::string_view sss("123456789");
    using namespace mph::literals;
    auto str="abc\0\0der"_sv;
    cout<<str;
	return 0;
}
