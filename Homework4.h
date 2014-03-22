#ifndef HOMEWORK_4
#define HOMEWORK_4

#include "uberzahl/uberzahl.h"


// "classic" modular exponentiation
uberzahl modexp(uberzahl base, uberzahl exp, const uberzahl& p, const uberzahl& q);

// modexp using the chinese remainder theorem
uberzahl modexp_crt(uberzahl base, uberzahl exp, const uberzahl& p,
	const uberzahl& q);

// modexp using montgomery multiplication
uberzahl modexp_mont(uberzahl base, uberzahl exp, const uberzahl& p,
	const uberzahl& q);

// modexp using chinese remainder theorem and montgomery multiplication
uberzahl modexp_mont_crt(uberzahl base, uberzahl exp, const uberzahl& p,
	const uberzahl& q);


#endif
