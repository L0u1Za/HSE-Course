#include "biginteger.h"

BigInteger::BigInteger(std::string n) {
	//created
	sign = true;
	if (!n.empty()) {
		if (n[0] == '-') {
			sign = false;
			n = n.substr(1, (long long)n.size() - 1);
		}
	}
	for (auto i = (long long)n.size();i > 0; i -= BigInteger::pw) {
        if (i - BigInteger::pw < 0) {
            num.push_back(std::stoll(n.substr(0, i + 1)));
        }
        else num.push_back(std::stoll(n.substr(i - BigInteger::pw, BigInteger::pw)));
    }
}
BigInteger::BigInteger(int n) {
	sign = true;
	if (n == 0) {
		this->num = {0};
	}
	else {
		if (n < 0) {
			sign = false;
			n = -n;
		}
		while (n) {
			this->num.push_back(n % BigInteger::base);
			n /= BigInteger::base;
		}
	}
}

BigInteger::BigInteger(const BigInteger& A) {
	this->sign = A.sign;
	this->num = A.num;
}
BigInteger::~BigInteger() {
	//deleted
}
void BigInteger::relx() {
	while(num.size() > 1 && num.back() == 0) num.pop_back();
	if (num.size() == 1 && num.back() == 0) sign = true;
}
void BigInteger::changeSign() {
	this->sign ^= 1;
}
bool BigInteger::getSign() {
	return this->sign;
}
std::string BigInteger::toString() {
	std::string out;
    for (auto &i : num) {
        long long cur = i;
        while (cur) {
            out += ('0' + (cur % 10));
            cur /= 10;
        }
    }
    if (!sign) out += '-';
    std::reverse(out.begin(), out.end());
	return out;
}

void swap(BigInteger& a, BigInteger& b) {
	std::swap(a.num, b.num);
	std::swap(a.sign, b.sign);
}
BigInteger abs(BigInteger a) {
	return (a.getSign() ? a : -a);
}
BigInteger BigInteger::operator+() const {
	return *this;
}
BigInteger BigInteger::operator-() const {
	BigInteger opposite = *this;
	opposite.changeSign();
	return opposite;
}

bool operator<(const BigInteger& a, const BigInteger& b) {
	if (a == b) return false;
	if (a.sign) {
		if (b.sign) {
			if (a.num.size() != b.num.size())
				return a.num.size() < b.num.size();
			else {
				for (int i = 0; i < a.num.size(); ++i) {
					if (a.num[i] != b.num[i]) return a.num[i] < b.num[i];
				}
			}
		}
		else {
			return false;
		}
	}
	else {
		if (b.sign) {
			return true;
		}
		else {
			if (a.num.size() != b.num.size())
				return a.num.size() > b.num.size();
			else {
				for (int i = 0; i < a.num.size(); ++i) {
					if (a.num[i] != b.num[i]) return a.num[i] > b.num[i];
				}
			}
		}
	}
}
bool operator>(const BigInteger& a, const BigInteger& b) {
	if (a == b) return false;
	if (a.sign) {
		if (b.sign) {
			if (a.num.size() != b.num.size())
				return a.num.size() > b.num.size();
			else {
				for (int i = 0; i < a.num.size(); ++i) {
					if (a.num[i] != b.num[i]) return a.num[i] > b.num[i];
				}
			}
		}
		else {
			return true;
		}
	}
	else {
		if (b.sign) {
			return false;
		}
		else {
			if (a.num.size() != b.num.size())
				return a.num.size() < b.num.size();
			else {
				for (int i = 0; i < a.num.size(); ++i) {
					if (a.num[i] != b.num[i]) return a.num[i] < b.num[i];
				}
			}
		}
	}
}
bool operator==(const BigInteger& a, const BigInteger& b) {
	return (a.sign == b.sign) && (a.num == b.num);
}
bool operator!=(const BigInteger& a, const BigInteger& b) {
	return !(a == b);
}
bool operator<=(const BigInteger& a, const BigInteger& b) {
	return ((a < b) || (a == b));
}
bool operator>=(const BigInteger& a, const BigInteger& b) {
	return ((a > b) || (a == b));
}
BigInteger operator+(const BigInteger& a, const BigInteger& b) {
	BigInteger res = a;
	res += b;
	return res;
}
BigInteger operator-(const BigInteger& a, const BigInteger& b) {
	BigInteger res = a;
	res -= b;
	return res;
}
BigInteger operator*(const BigInteger& a, const BigInteger& b) {
	BigInteger res;
	res.sign = !(a.sign ^ b.sign);
	res.num.resize(int(a.num.size()) + int(b.num.size()));

	int ost = 0;
	for (int i = 0; i < a.num.size() || ost; ++i) {
		for (int j = 0; j < b.num.size() || ost; ++j) {
			res.num[i + j] += (i < a.num.size() ? a.num[i] : 0) * (j < b.num.size() ? b.num[j] : 0) + ost;
			ost = 0;

			if (res.num[i + j] >= BigInteger::base) {
				ost = res.num[i + j] / BigInteger::base;
				res.num[i + j] %= BigInteger::base;
			}
		}
	}
	res.relx();
	return res;
}
BigInteger operator/(const BigInteger& a, const int& b) {
	BigInteger res;
	std::string cur = "";

	res.num.assign(a.num.size() + 1, 0);

	for (int i = a.num.size() - 1; i >= 0; i--) {
		cur += std::to_string(a.num[i]);
		int temp = std::stoll(cur);

		if (temp / b > 0) {
			res.num[i] = temp / b;
			cur = std::to_string(temp % b);
		}
	}
	res.relx();
	return res;
}

BigInteger operator/(const BigInteger& a, const BigInteger& b) {
	bool sgn = !(a.sign ^ b.sign);
	BigInteger l("0"), r = abs(a) + BigInteger("1");
	while (r - l > BigInteger("1")) {
		BigInteger m = (l + r) / 2;
		BigInteger res = m * abs(b);
		if (m * b <= abs(a)) {
			l = m;
		}
		else {
			r = m;
		}
	}
	l.sign = sgn;
	return l;
}
BigInteger operator%(const BigInteger& a,const BigInteger& b) {
	return a - a / b * b;
}
BigInteger& BigInteger::operator++() {
	*this += BigInteger("1");
	return *this;
}
BigInteger& BigInteger::operator--() {
	*this -= BigInteger("1");
	return *this;
}
BigInteger BigInteger::operator++(int id) {
	BigInteger t = *this;
	*this += BigInteger("1");
	return t;
}
BigInteger BigInteger::operator--(int id) {
	BigInteger t = *this;
	*this -= BigInteger("1");
	return t;
}
void calc(BigInteger& a, const BigInteger& b, bool minus) {
	int ost = 0;
	const bool isThisBigger = abs(a) > abs(b), isSubtraction = (!a.sign) ^ (!b.sign) ^ minus;

	if (!isThisBigger) {
		a.sign = !((!b.sign) ^ minus);
	}

	for (int i = 0; i < a.num.size() || i < b.num.size() || ost != 0; i++) {
		if (i >= a.num.size()) {
			a.num.push_back(0);
		}
		if (isSubtraction) {
			if (isThisBigger) {
				a.num[i] -= (i < b.num.size() ? b.num[i] : 0);
			}
			else {
				a.num[i] = (i < b.num.size() ? b.num[i] : 0) - (i < a.num.size() ? a.num[i] : 0);
			}
		}
		else {
			a.num[i] += (i < b.num.size() ? b.num[i] : 0);
		}

		a.num[i] += ost;
		ost = 0;

		if (a.num[i] >= BigInteger::base) {
			a.num[i] -= BigInteger::base;
			ost++;
		}
		else if (a.num[i] < 0) {
			a.num[i] += BigInteger::base;
			ost--;
		}
	}
	a.relx();
}
BigInteger BigInteger::operator+=(const BigInteger& b) {
	calc(*this, b, false);
	return *this;
}
BigInteger BigInteger::operator-=(const BigInteger& b) {
	calc(*this, b, true);
	return *this;
}
BigInteger BigInteger::operator*=(const BigInteger& b) {
	*this = *this * b;
	return *this;
}
BigInteger BigInteger::operator/=(const BigInteger& a) {
	*this = *this / a;
	return *this;
}
BigInteger BigInteger::operator%=(const BigInteger& b) {
	*this = *this % b;
	return *this;
}
std::istream& operator>>(std::istream& in, BigInteger& a) {
	std::string s; 
	in >> s;
	a = BigInteger(s);
	return in;
}
std::ostream& operator<<(std::ostream& out, BigInteger& a) {
	out << a.toString();
    return out;
}
BigInteger::operator bool() {
	return !(*this == BigInteger("0"));
}