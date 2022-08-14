﻿#include <iostream>
#include "big_int.h"

int main()
{
    auto x = "123456789112233445566778899111222333444555666777888999";

    big_int a( "123456789112233445566778899111222333444555666777888999" );
    
    //big_int a (x);

    big_int b(9234567891129999999);

    big_int c("0");

    big_int d(-14442124000000195);
    const std::string s = "123456789112233445566778899111222333444555666777888999";
    std::cout << (9234567891129999999 == b) << std::endl;
    std::cout << (1 == 1);
    std::cout << c <<" " << b << " " << a << " " << d;
    
}
