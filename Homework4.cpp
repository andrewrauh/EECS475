#include "Homework4.h"
#include "Montgomery.h"
#include <cassert>
#include <iostream>
using std::cerr; using std::endl;


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
	Montgomery result {generic_modexp(Montgomery {base}
		, Montgomery {exp}
		, Montgomery {p}
		, Montgomery {q})};
	return result.get_num();
}

uberzahl modexp_mont_crt(uberzahl base, uberzahl exp, const uberzahl& p,
	const uberzahl& q)
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
	cerr << "entered generic_modexp\n";
	assert(p > q);
	T mod {p * q};
	T total {1};
	base = base % mod;
	static const T zero {"0"}; // don't reinitialize over and over
	while(exp > zero) {
		cerr << exp << endl;
		if(exp % 2 == 1)
			total = (total * base) % mod;
		exp = exp >> 1;
		base = (base * base) % mod;
	}
	return total;
}

// TODO this fails for small values. Why?
template<typename T>
static T generic_modexp_crt(T base, T exp, const T& p, const T& q)
{
	cerr << "entered generic_modexp\n";
	assert(p > q);
	T exp_p = exp % (p - 1);
	T exp_q = exp % (q - 1);
	T q_inv {q.inverse(p)};
	T m_1 = generic_modexp(base, exp_p, p, T {1});
	T m_2 = generic_modexp(base, exp_q, q, T {1});
	T h = (q_inv * (m_1 - m_2)) % p;
	static const T zero {"0"}; // don't reinitialize over and over
	if(h < zero)
		h = h + p;
	return m_2 + h * q;
}
