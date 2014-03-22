#include "Montgomery.h"
#include <algorithm>
using std::swap;


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

Montgomery Montgomery::operator>>(int nbits) const
{
	// TODO
	return Montgomery {num >> nbits};
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

const Montgomery Montgomery::inverse(const Montgomery& other) const
{
	// TODO
	return num.inverse(other.get_num());
}

const uberzahl& Montgomery::get_num() const
{
	// TODO
	return num;
}
