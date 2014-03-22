#ifndef MONTGOMERY
#define MONTGOMERY

#include "uberzahl/uberzahl.h"
#include <iostream>


class Montgomery {
public:
	Montgomery(const uberzahl& num);

	// operators
	Montgomery operator+(const Montgomery& other) const;
	Montgomery operator-(const Montgomery& other) const;
	Montgomery operator-(int other) const;
	Montgomery operator*(const Montgomery& other) const;
	Montgomery operator%(const Montgomery& other) const;
	Montgomery operator%(int other) const;
	Montgomery operator>>(int nbits) const;

	// comparison
	bool operator==(int other) const;
	bool operator>(const Montgomery& other) const;
	bool operator<(const Montgomery& other) const;
	bool operator>(double other) const;
	bool operator<(double other) const;

	const Montgomery inverse(const Montgomery& other) const;

	// returns the Montgomery in uberzahl form
	const uberzahl& get_num() const;

private:
	uberzahl num;

};

inline std::ostream& operator<<(std::ostream& os, const Montgomery& num)
		{ return os << num.get_num(); }


#endif
