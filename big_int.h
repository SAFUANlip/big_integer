#pragma once
#include <iostream>
#include <vector>
#include <string>

// https://e-maxx.ru/algo/big_integer
// https://habr.com/ru/post/172285/?ysclid=l6ri45mh3v820500388
// https://github.com/ThiBsc/BigInteger/blob/master/src/header/biginteger.h

class big_int
{
	// empty num == 0
	// insignificant => will be not correct working
private:
	std::vector<int> num;
	bool minus = false;
	static const int base = 1000000000; // 1 000 000 000, limitation for int

public:
	// don't make explicit for operator == working not only with big_int, big_int 
	big_int() {};
	big_int(int);
	big_int(signed long long);
	big_int(unsigned long long);
	big_int(std::string);

	//big_int == const char * // work only if i macke big_int from const char* , construct with string don't make it
	big_int(const char* c) : big_int(static_cast<std::string>(c)) {};

	friend std::ostream& operator << (std::ostream&, const big_int&);
	bool operator == (const big_int&) const;
	//bool operator < (const)

};

