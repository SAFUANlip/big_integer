#pragma once
#include <iostream>
#include <vector>
#include <string>

// https://e-maxx.ru/algo/big_integer
// https://habr.com/ru/post/172285/?ysclid=l6ri45mh3v820500388
// https://github.com/ThiBsc/BigInteger/blob/master/src/header/biginteger.h
// https://e-maxx.ru/algo/binary_pow

class big_int
{
	// empty num == 0
	// insignificant => will be not correct working
private:
	std::vector<int> num;
	bool minus = false;
	static const int BASE = 1000000000; // 1 000 000 000, limitation for int

	void remove_leading_zeros();
	void shift_right();
	
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
	bool operator < (const big_int&) const;
	
	const big_int operator +() const;
	const big_int operator -() const;
	big_int& operator += (const big_int&);
	big_int& operator -= (const big_int&);
	big_int& operator ++();
	const big_int operator ++(int);
	big_int& operator --();
	const big_int operator --(int);
	big_int& operator *= (const big_int&);
	big_int& operator /= (const big_int&);
	big_int& operator %= (const big_int&);

	const big_int pow(big_int n) const;
	/*auto operator <=>(const big_int& other, const big_int&) { // still dont know how to make it
		return;
	}*/
};



template<typename T>
bool operator == (const T& l, const big_int& r) {
	return (big_int(l) == r);
}

template<typename T>
bool operator < (const T& l, const big_int& r) {
	return (big_int(l) < r);
}

bool operator != (const big_int& l, const big_int& r);
bool operator <= (const big_int& l, const big_int& r);
bool operator > (const big_int& l, const big_int& r);
bool operator >= (const big_int& l, const big_int& r);

const big_int operator + (const big_int& l, const big_int& r);
const big_int operator - (const big_int& l, const big_int& r);
const big_int operator * (const big_int& l, const big_int& r);
const big_int operator / (const big_int& l, const big_int& r);
const big_int operator % (const big_int& l, const big_int& r);
