#include "big_int.h"

big_int::big_int(int val) {
	minus = (val < 0);
	val = abs(val);
	while (val > 0) {
		num.push_back(val % base);
		val /= base;
	}
}

big_int::big_int(std::string str){
	if (str.size() != 0) {
		if (str.size() == 1 && str[0] == '0')
			return;
		if (str[0] == '-')
			str = str.substr(1), minus = true;
		for (long long i = str.size(); i > 0; i -= 9)
			num.push_back(atoi(str.substr(i >= 9 ? i-9 : 0, 9).c_str()));
	}
}

big_int::big_int(signed long long sll) {
	minus = (sll < 0);
	sll = abs(sll);
	while (sll > 0) {
		num.push_back(sll % base);
		sll /= base;
	}
}

big_int::big_int(unsigned long long ull) {
	while (ull > 0) {
		num.push_back(ull % base);
		ull /= base;
	}
}

std::ostream& operator << (std::ostream& out, const big_int& val) {
	if (val.num.empty())
		out << '0'; 
	else {
		if (val.minus)
			out << '-';
		for (auto it = val.num.end() - 1; it != val.num.begin(); --it)
			out << std::to_string(*it);
		out << std::to_string(*val.num.begin());
	}
	return out;
}

bool big_int::operator == (const big_int& r) const
{
	if (minus != r.minus) return false;
	if (num.empty() && r.num.empty()) return true;
	if (num.size() != r.num.size()) return false;
	for (auto i = 0; i < num.size(); ++i)
		if (num[i] != r.num[i])
			return false;
	return true;
}
