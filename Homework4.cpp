#include "Homework4.h"
#include <cassert>


mpz_class modexp(mpz_class base, mpz_class exp, const mpz_class& p, const mpz_class& q)
{
	assert(p > q);
	mpz_class mod {p * q};
	mpz_class total {1};
	base %= mod;
	while(exp > 0) {
		if(exp % 2 == 1)
			total = (total * base) % mod;
		mpz_fdiv_q_2exp(exp.get_mpz_t(), exp.get_mpz_t(), 1);
		base = (base * base) % mod;
	}
	return total;
}

mpz_class modexp_crt(mpz_class base, mpz_class exp, const mpz_class& p,
	const mpz_class& q)
{
	assert(p > q);
	mpz_class exp_p = exp % (p - 1);
	mpz_class exp_q = exp % (q - 1);
	mpz_class q_inv {};
	mpz_invert(q_inv.get_mpz_t(), q.get_mpz_t(), p.get_mpz_t());
	mpz_class m_1 = modexp(base, exp_p, p, 1);
	mpz_class m_2 = modexp(base, exp_q, q, 1);
	mpz_class h = (q_inv * (m_1 - m_2)) % p;
	if(h < 0)
		h += p;
	return m_2 + h * q;
}

// TODO
mpz_class modexp_mont(mpz_class base, mpz_class exp, const mpz_class& p,
	const mpz_class& q)
{
	return modexp(base, exp, p, q);
}

// TODO
mpz_class modexp_mont_crt(mpz_class base, mpz_class exp, const mpz_class& p,
	const mpz_class& q)
{
	return modexp(base, exp, p, q);
}


