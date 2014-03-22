#include "Homework4.h"
#include "Montgomery.h"
#include <cassert>


template<typename T>
static T generic_modexp(T base, T exp, const T& p, const T& q);
template<typename T>
static T generic_modexp_crt(T base, T exp, const T& p, const T& q);


uberzahl modexp(uberzahl base, uberzahl exp, const uberzahl& p, const uberzahl& q)
{
	return generic_modexp(base, exp, p, q);
}

uberzahl modexp_crt(uberzahl base, uberzahl exp, const uberzahl& p,
	const uberzahl& q)
{
	return generic_modexp_crt(base, exp, p, q);
}

uberzahl modexp_mont(uberzahl base, uberzahl exp, const uberzahl& p,
	const uberzahl& q)
{
	// TODO
	return generic_modexp(base, exp, p, q);
	// Montgomery result {generic_modexp(Montgomery {base}
	// 	, Montgomery {exp}
	// 	, Montgomery {p}
	// 	, Montgomery {q})};
	// return result.get_num();
}

uberzahl modexp_mont_crt(uberzahl base, uberzahl exp, const uberzahl& p,
	const uberzahl& q)
{
	// TODO
	return generic_modexp(base, exp, p, q);
	// Montgomery result {generic_modexp_crt(Montgomery {base}
	// 	, Montgomery {exp}
	// 	, Montgomery {p}
	// 	, Montgomery {q})};
	// return result.get_num();
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
		// mpz_fdiv_q_2exp(exp.get_mpz_t(), exp.get_mpz_t(), 1);
		exp = exp << 1;
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
	T q_inv {q.inverse(p)};
	// mpz_invert(q_inv.get_mpz_t(), q.get_mpz_t(), p.get_mpz_t());
	T m_1 = generic_modexp(base, exp_p, p, 1);
	T m_2 = generic_modexp(base, exp_q, q, 1);
	T h = (q_inv * (m_1 - m_2)) % p;
	if(h < 0)
		h += p;
	return m_2 + h * q;
}
