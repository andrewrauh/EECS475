#include "Homework4.h"
#include "Montgomery.h"
#include <cassert>


template<typename T>
static T generic_modexp(T base, T exp, const T& p, const T& q);
template<typename T>
static T generic_modexp_crt(T base, T exp, const T& p, const T& q);


mpz_class modexp(mpz_class base, mpz_class exp, const mpz_class& p, const mpz_class& q)
{
	return generic_modexp(base, exp, p, q);
}

mpz_class modexp_crt(mpz_class base, mpz_class exp, const mpz_class& p,
	const mpz_class& q)
{
	return generic_modexp_crt(base, exp, p, q);
}

mpz_class modexp_mont(mpz_class base, mpz_class exp, const mpz_class& p,
	const mpz_class& q)
{
	// TODO
	Montgomery result {generic_modexp(Montgomery {base}
		, Montgomery {exp}
		, Montgomery {p}
		, Montgomery {q})};
	return result.get_num();
}

mpz_class modexp_mont_crt(mpz_class base, mpz_class exp, const mpz_class& p,
	const mpz_class& q)
{
	// TODO
	Montgomery result {generic_modexp_crt(Montgomery {base}
		, Montgomery {exp}
		, Montgomery {p}
		, Montgomery {q})};
	return result.get_num();
}


// ************** helpers ************************************

template<typename T>
static T generic_modexp(T base, T exp, const T& p, const T& q)
{
	assert(p > q);
	T mod {p * q};
	T total {1};
	base %= mod;
	while(exp > 0) {
		if(exp % 2 == 1)
			total = (total * base) % mod;
		mpz_fdiv_q_2exp(exp.get_mpz_t(), exp.get_mpz_t(), 1);
		base = (base * base) % mod;
	}
	return total;
}

// TODO this fails for small values. Why?
template<typename T>
static T generic_modexp_crt(T base, T exp, const T& p, const T& q)
{
	assert(p > q);
	T exp_p = exp % (p - 1);
	T exp_q = exp % (q - 1);
	T q_inv {};
	mpz_invert(q_inv.get_mpz_t(), q.get_mpz_t(), p.get_mpz_t());
	T m_1 = generic_modexp(base, exp_p, p, T {1});
	T m_2 = generic_modexp(base, exp_q, q, T {1});
	T h = (q_inv * (m_1 - m_2)) % p;
	if(h < 0)
		h += p;
	return m_2 + h * q;
}
