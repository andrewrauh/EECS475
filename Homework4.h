#ifndef HOMEWORK_4
#define HOMEWORK_4

#include <gmpxx.h>


// "classic" modular exponentiation
mpz_class modexp(mpz_class base, mpz_class exp, const mpz_class& p, const mpz_class& q);

// modexp using the chinese remainder theorem
mpz_class modexp_crt(mpz_class base, mpz_class exp, const mpz_class& p,
	const mpz_class& q);

// modexp using montgomery multiplication
mpz_class modexp_mont(mpz_class base, mpz_class exp, const mpz_class& p,
	const mpz_class& q);

// modexp using chinese remainder theorem and montgomery multiplication
mpz_class modexp_mont_crt(mpz_class base, mpz_class exp, const mpz_class& p,
	const mpz_class& q);


#endif
