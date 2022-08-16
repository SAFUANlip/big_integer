#include "big_int.h"

big_int::big_int(int val) {
	minus = (val < 0);
	val = abs(val);
	while (val > 0) {
		num.push_back(val % BASE);
		val /= BASE;
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
		num.push_back(sll % BASE);
		sll /= BASE;
	}
}

big_int::big_int(unsigned long long ull) {
	while (ull > 0) {
		num.push_back(ull % BASE);
		ull /= BASE;
	}
}

void big_int::remove_leading_zeros() {
	while (num.size() > 0 && num.back() == 0)
		num.pop_back();
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


bool big_int::operator < (const big_int& r) const{
	if (minus && !r.minus) return true;
	if (r.minus && !minus) return false;
	if (num.size() < r.num.size()) return (!minus);
	if (num.size() > r.num.size()) return (minus);
	for (long long i = num.size() - 1; i >= 0 && !num.empty(); --i) {
		if (num[i] < r.num[i]) return (!minus);
		if (num[i] > r.num[i]) return (minus);
	}
	return false;
}

bool operator != (const big_int& l, const big_int& r) {
	return !(l == r);
}

bool operator <= (const big_int& l, const big_int& r) {
	return (l < r || l == r);
}

bool operator > (const big_int& l, const big_int& r) {
	return !(l <= r);
}

bool operator >= (const big_int& l, const big_int& r) {
	return !(l < r);
}

const big_int big_int::operator +() const{
	return big_int(*this);
}

const big_int big_int::operator -() const{
	if (num.size() != 0) {
		big_int copy(*this);
		copy.minus = !minus;
		return copy;
	}
	return *this;
}

big_int& big_int::operator += (const big_int& r){
	if (minus) {
		*this = -(*this);
		if (r.minus) {
			*this = -(*this += (-r));
			return *this;
		}
		else {
			big_int rr(r);
			*this = rr -= *this;
			return *this;
		}
	}
	else if (r.minus)
		return *this -=(-r);
	short buff = 0;
	for (auto i = 0; i < std::max(num.size(), r.num.size()) || buff != 0; ++i) {
		if (i == num.size()) num.push_back(0);
		num[i] += buff + (r.num.size() >= i ? r.num[i] : 0);
		buff = num[i] >= BASE;
		if (buff != 0)
			num[i] -= BASE;
	}

	return *this;
}

big_int& big_int::operator -= (const big_int& r) {
	if (r.minus) return *this += (-r);
	else if (minus) {
		big_int rr(r);
		*this = -(rr -= *this);
		return *this;
	}
	else if (*this < r) {
		big_int rr(r);
		*this = -(rr -= *this);
		return *this;
	}
	short buff = 0;
	for (auto i = 0; i < r.num.size() || buff != 0; ++i) {
		num[i] -= buff + (i < r.num.size() ? r.num[i] : 0);
		buff = num[i] < 0;
		if (buff != 0)
			num[i] += BASE;
	}
	this->remove_leading_zeros();
	return *this;
}

const big_int operator + (const big_int& l, const big_int& r) {
	big_int copy(l);
	copy += r;
	return copy;
}


const big_int operator - (const big_int& l, const big_int& r) {
	big_int copy(l);
	copy -= r;
	return copy;
}

big_int& big_int::operator ++() {
	return (*this += 1);
}

const big_int big_int::operator ++(int) {
	big_int copy(*this);
	*this += 1;
	return copy;
}

big_int& big_int::operator --() {
	return (*this -= 1);
}

const big_int big_int::operator --(int) {
	big_int copy(*this);
	*this -= 1;
	return copy;
}

big_int& big_int::operator *= (const big_int& r) {
	if (num.size() == 0) return *this;
	if (r.num.size() == 0) {
		*this = big_int();
		return *this;
	}

	big_int res;
	res.num.resize(num.size() + r.num.size());
	for (auto i = 0; i < num.size(); ++i) {
		int buff = 0;
		for (auto j = 0; j < r.num.size() || buff != 0; ++j) {
			long long cur = res.num[i + j] + num[i] * 1LL * (j < r.num.size() ? r.num[j] : 0) + buff;
			res.num[i + j] = static_cast<int>(cur % BASE);
			buff = static_cast<int>(cur / BASE);
		}
	}

	res.minus = minus != r.minus;
	res.remove_leading_zeros();
	*this = res;
	return *this;

}

const big_int operator * (const big_int& l, const big_int& r) {
	big_int copy(l);
	copy *= r;
	return copy; 
}

void big_int::shift_right() {
	if (num.size() == 0) {
		num.push_back(0);
		return;
	}

	num.push_back(num[num.size() - 1]);
	for (auto i = num.size() - 2; i > 0; num[i] = num[i - 1], --i) {}
	num[0] = 0;
	return;
}

// division by corner
big_int& big_int::operator/=(const big_int& r){
	if (num.empty()) return *this;
	try {
		if (r.num.empty()) throw std::exception("divide by zero");
	}
	catch (std::exception& e) {
		std::cout << e.what();
		return *this;
	}
	
	big_int r_abs = r;
	r_abs.minus = false;
	big_int res, remainder;
	res.num.resize(num.size());
	for (long long i = static_cast<long long>(num.size()) - 1; i >= 0; --i) {
		remainder.shift_right();
		remainder.num[0] = num[i];
		int x = 0, left = 0, right = BASE;
		while (left <= right) { // bin search of divider
			int mid = (left + right) / 2;
			big_int t = mid * r_abs;
			if (t <= remainder) {
				x = mid;
				left = mid + 1;
			}
			else right = mid - 1;
		}

		res.num[i] = x;
		remainder -= x * r_abs;
	}

	res.minus = minus != r.minus;
	res.remove_leading_zeros(); // if left < right
	*this = res;
	return *this;
}

const big_int operator / (const big_int& l, const big_int& r) {
	big_int copy = l;
	copy /= r;
	return copy;
}

big_int& big_int::operator %= (const big_int& r) {
	big_int r_abs = r.minus ? -r : r;
	big_int res = *this - (*this / r) * r;
	*this = res;
	return *this;
}
const big_int operator % (const big_int& l, const big_int& r) {
	big_int copy = l;
	copy %= r;
	return copy;
}

const big_int big_int::pow(big_int n) const{
	big_int res = 1, a = *this;
	while (!n.num.empty()) { // !- 0
		if (n.num[0] & 1) res *= a;
		a *= a;
		n /= 2;
	}
	return res;
}