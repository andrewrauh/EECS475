#ifndef MONTGOMERY
#define MONTGOMERY

#include "uberzahl/uberzahl.h"


class Montgomery {
public:
	Montgomery();

	// construct a Montgomery number from uberzahl number
	Montgomery(const uberzahl& num);

	// operators
	Montgomery operator+(const Montgomery& other) const;
	Montgomery operator-(const Montgomery& other) const;
	Montgomery operator-(int other) const;
	Montgomery operator*(const Montgomery& other) const;
	Montgomery operator%(const Montgomery& other) const;
	Montgomery operator%(int other) const;

	// modifying operators
	Montgomery& operator+=(const Montgomery& other);
	Montgomery& operator%=(const Montgomery& other);

	// comparison operators
	bool operator==(int other) const;
	bool operator>(const Montgomery& other) const;
	bool operator<(const Montgomery& other) const;
	bool operator>(double other) const;
	bool operator<(double other) const;

	// returns the number translated from Montgomery to uberzahl
	// uberzahl get_num() const;

	// returns num.get_mpz_t(). const/non-const versions both necessary
	// mpz_srcptr get_mpz_t() const;
	// mpz_ptr get_mpz_t();

private:
	uberzahl num;

};


#endif
