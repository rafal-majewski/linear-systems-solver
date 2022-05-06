#include "./BigInt.h"


BigInt::BigInt() {
	sign = 0;
}

BigInt::BigInt(int a_number) {
	if (a_number == 0) {
		sign = 0;
		return;
	}
	int number = a_number;
	if (number < 0) {
		sign = -1;
		number = -number;
	} else {
		sign = 1;
	}
	digits = BigIntDigits(number);
}

BigInt::BigInt(const BigInt& other) {
	sign = other.sign;
	digits = other.digits;
}



// BigInt::operator std::string() const {
// 	std::vector<char> digitsDecimal;
// 	std::vector<char> digitsMultiplier = {1};
// 	for (int i = 0; i < digits.size(); ++i) {
// 		if (digits[i] == 1) {
// 			digitsDecimal = addDigits(digitsDecimal, digitsMultiplier, 10);
// 		}
// 		digitsMultiplier = addDigits(digitsMultiplier, digitsMultiplier, 10);
// 	}
// 	if (digitsDecimal.size() == 0) {
// 		digitsDecimal.push_back(0);
// 	}
// 	for (int i = 0; i < digitsDecimal.size(); ++i) {
// 		digitsDecimal[i] += '0';
// 	}
// 	if (sign == -1) {
// 		digitsDecimal.push_back('-');
// 	}
// 	std::reverse(digitsDecimal.begin(), digitsDecimal.end());
// 	std::string result(digitsDecimal.begin(), digitsDecimal.end());
// 	return result;
// }


BigInt::operator std::string() const {
	return (sign == -1 ? "-" : "") + std::string(digits);
}

BigInt operator+(const BigInt& bigint1, const BigInt& bigint2) {
	BigInt result(bigint1);
	result += bigint2;
	return result;
}

bool operator>=(const BigInt& bigint1, const BigInt& bigint2) {
	if (bigint1.sign == -1 && bigint2.sign == 1) {
		return false;
	}
	if (bigint1.sign == 1 && bigint2.sign == -1) {
		return true;
	}
	if (bigint1.sign == -1 && bigint2.sign == -1) {
		return bigint1.digits <= bigint2.digits;
	}
	if (bigint1.sign == 1 && bigint2.sign == 1) {
		return bigint1.digits >= bigint2.digits;
	}
	if (bigint1.sign == 0 && bigint2.sign == 1) {
		return false;
	}
	if (bigint1.sign == 1 && bigint2.sign == 0) {
		return true;
	}
	if (bigint1.sign == -1 && bigint2.sign == 0) {
		return false;
	}
	if (bigint1.sign == 0 && bigint2.sign == -1) {
		return true;
	}
	// if (bigint1.sign == 0 && bigint2.sign == 0) {
		return true;
	// }
}

bool operator<(const BigInt& bigint1, const BigInt& bigint2) {
	if (bigint1.sign == -1 && bigint2.sign == 1) {
		return true;
	}
	if (bigint1.sign == 1 && bigint2.sign == -1) {
		return false;
	}
	if (bigint1.sign == -1 && bigint2.sign == -1) {
		return bigint1.digits > bigint2.digits;
	}
	if (bigint1.sign == 1 && bigint2.sign == 1) {
		return bigint1.digits < bigint2.digits;
	}
	if (bigint1.sign == 0 && bigint2.sign == 1) {
		return true;
	}
	if (bigint1.sign == 1 && bigint2.sign == 0) {
		return false;
	}
	if (bigint1.sign == -1 && bigint2.sign == 0) {
		return true;
	}
	if (bigint1.sign == 0 && bigint2.sign == -1) {
		return false;
	}
	// if (bigint1.sign == 0 && bigint2.sign == 0) {
		return false;
	// }
}


BigInt& BigInt::operator+=(const BigInt rhs) {
	if (sign == 0) {
		sign = rhs.sign;
		digits = rhs.digits;
		return *this;
	}
	if (rhs.sign == 0) {
		return *this;
	}
	if (sign == rhs.sign) {
		digits += rhs.digits;
		return *this;
	}
	char digitsComparisonResult = digits.compare(rhs.digits);
	if (digitsComparisonResult == 0) {
		sign = 0;
		digits.zero();
		return *this;
	}
	sign *= digitsComparisonResult;
	digits -= rhs.digits;
	return *this;

}

BigInt& BigInt::operator-=(const BigInt rhs) {
	if (rhs.sign == 0) {
		return *this;
	}
	if (sign == 0) {
		sign = -rhs.sign;
		digits = rhs.digits;
		return *this;
	}
	if (sign != rhs.sign) {
		digits += rhs.digits;
		return *this;
	}
	char digitsComparisonResult = digits.compare(rhs.digits);
	if (digitsComparisonResult == 0) {
		sign = 0;
		digits.zero();
		return *this;
	}
	sign *= digitsComparisonResult;
	digits -= rhs.digits;
	return *this;
}

// BigInt& BigInt::operator+=(const BigInt& rhs) {
// 	if (rhs.sign == 0) {
// 		return *this;
// 	}
// 	if (sign == 0) {
// 		sign = rhs.sign;
// 		digits = rhs.digits;
// 		return *this;
// 	}
// 	if (sign == rhs.sign) {
// 		digits += rhs.digits;
// 		return *this;
// 	}
// 	char digitsComparisonResult = digits.compare(rhs.digits);
// 	if (digitsComparisonResult == 0) {
// 		sign = 0;
// 		digits.zero();
// 		return *this;
// 	}
// 	sign *= digitsComparisonResult;
// 	digits -= rhs.digits;
// 	return *this;
// }

bool operator==(const BigInt& lhs, const BigInt& rhs) {
	return lhs.sign == rhs.sign && lhs.digits == rhs.digits;
}

bool operator!=(const BigInt& lhs, const BigInt& rhs) {
	return !(lhs == rhs);
}

BigInt& BigInt::operator*=(const BigInt rhs) {
	if (sign == 0 || rhs.sign == 0) {
		sign = 0;
		digits.zero();
		return *this;
	}
	sign *= rhs.sign;
	digits *= rhs.digits;
	return *this;
}

BigInt& BigInt::operator/=(const BigInt rhs) {
	digits /= rhs.digits;
	if (digits.size() == 0) {
		sign = 0;
	} else {
		sign *= rhs.sign;
	}
	// sign *= bool(digits.size()) * rhs.sign;
	return *this;
}

BigInt& BigInt::operator%=(const BigInt rhs) {
	digits %= rhs.digits;

	if (digits.size() == 0) {
		sign = 0;
		return *this;
	}
	if (sign == -rhs.sign) {
		digits -= rhs.digits;
		sign = rhs.sign;
	}
	return *this;
}


// bool operator!=(const BigInt& bigint1, const BigInt& bigint2) {
// 	if (bigint1.sign != bigint2.sign) {
// 		return true;
// 	}
// 	if (bigint1.digits.size() != bigint2.digits.size()) {
// 		return true;
// 	}
// 	for (int i = 0; i < bigint1.digits.size(); ++i) {
// 		if (bigint1.digits[i] != bigint2.digits[i]) {
// 			return true;
// 		}
// 	}
// 	return false;
// }

std::ostream& operator<<(std::ostream& os, const BigInt& bigint) {
	os << std::string(bigint);
	return os;
}

BigInt operator-(const BigInt& bigint1, const BigInt& bigint2) {
	BigInt result(bigint1);
	result -= bigint2;
	return result;
}

BigInt operator*(const BigInt& bigint1, const BigInt& bigint2) {
	BigInt result(bigint1);
	result *= bigint2;
	return result;
}

BigInt operator/(const BigInt& bigint1, const BigInt& bigint2) {
	BigInt result(bigint1);
	result /= bigint2;
	return result;
}

BigInt operator%(const BigInt& bigint1, const BigInt& bigint2) {
	BigInt result(bigint1);
	result %= bigint2;
	return result;
}


BigInt BigInt::operator-() const {
	BigInt result(*this);
	result.sign *= -1;
	return result;
}

#include <iostream>

BigInt::BigInt(std::string str) {
	if (str[0] == '-') {
		sign = -1;
	} else {
		sign = 1;
	}
	digits = BigIntDigits(
		str.substr(str[0] == '-' ? 1 : 0)
	);
	if (digits.size() == 0) {
		sign = 0;
	}
}


BigInt BigInt::gcd(const BigInt& bigint) const {
	BigInt a(*this);
	BigInt b(bigint);
	while (b.sign != 0) {
		BigInt temp(b);
		b = a % b;
		a = temp;
	}
	return a;
}
