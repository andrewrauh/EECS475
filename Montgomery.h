#ifndef MONTGOMERY
#define MONTGOMERY

#include <gmpxx.h>


class Montgomery {
public:
	Montgomery();

	// construct from mpz_class number
	explicit Montgomery(const mpz_class& num);

	Montgomery operator*(const Montgomery& other) const;
	Montgomery operator%(const Montgomery& other) const;
	Montgomery& operator%=(const Montgomery& other);
	bool operator==(const Montgomery& other);

private:
	mpz_class num;

};


#endif
