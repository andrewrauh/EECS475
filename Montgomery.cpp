#include "Montgomery.h"
// #include "uberzahl/uberzahl.h"
#include <algorithm>
using std::swap;


Montgomery::Montgomery() : Montgomery {uberzahl {0}} {}

// construct from uberzahl number
Montgomery::Montgomery(const uberzahl& num) : num {num}
{
	// TODO
}

Montgomery Montgomery::operator+(const Montgomery& other) const
{
	// TODO
	return Montgomery {num + other.num};
}

Montgomery Montgomery::operator-(const Montgomery& other) const
{
	// TODO
	return Montgomery {num - other.num};
}

Montgomery Montgomery::operator-(int other) const
{
	// TODO
	return Montgomery {num - other};
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

Montgomery Montgomery::operator%(int other) const
{
	// TODO
	return Montgomery {num % other};
}

Montgomery& Montgomery::operator+=(const Montgomery& other)
{
	// TODO
	num += other.num;
	return *this;
}

Montgomery& Montgomery::operator%=(const Montgomery& other)
{
	// TODO
	num %= other.num;
	return *this;

}

bool Montgomery::operator==(int other) const
{
	// TODO
	return num == other;
}

bool Montgomery::operator>(const Montgomery& other) const
{
	return num > other.num;
}

bool Montgomery::operator<(const Montgomery& other) const
{
	return num < other.num;
}

bool Montgomery::operator>(double other) const
{
	// TODO
	return num > other;
}

bool Montgomery::operator<(double other) const
{
	// TODO
	return num < other;
}

// uberzahl Montgomery::get_num() const
// {
// 	// TODO
// 	return num;
// }

// mpz_srcptr Montgomery::get_mpz_t() const
// {
// 	mpz_srcptr srcptr = num.get_mpz_t();
// 	return srcptr;
// }

// mpz_ptr Montgomery::get_mpz_t()
// {
// 	mpz_ptr ptr = num.get_mpz_t();
// 	return ptr;
// }
