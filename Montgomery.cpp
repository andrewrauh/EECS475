#include "Montgomery.h"
#include <gmpxx.h>
#include <algorithm>
using std::swap;


Montgomery::Montgomery() : Montgomery {mpz_class {0}} {}

// construct from mpz_class number
Montgomery::Montgomery(const mpz_class& num) : num {num}
{
	// TODO
}

Montgomery Montgomery::operator*(const Montgomery& other) const
{
	// TODO
	return Montgomery {num * other.num};
}

Montgomery Montgomery::operator%(const Montgomery& other) const
{
	// TODO
	return Montgomery {num % other.num};
}

Montgomery& Montgomery::operator%=(const Montgomery& other)
{
	// TODO
	num %= other.num;
	return *this;

}

bool Montgomery::operator==(const Montgomery& other)
{
	// TODO
	return num == other.num;
}
