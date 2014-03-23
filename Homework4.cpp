#include "Homework4.h"
#include "Montgomery.h"
#include <cassert>
#include <iostream>
using std::cerr; using std::endl;


template<typename T>
static T generic_modexp(T base, T exp, const T& p, const T& q);
template<typename T>
static T generic_modexp_crt(T base, T exp, const T& p, const T& q);
template<typename T>
static T generic_mont_reduction(T num, T R, T mod, T Mprime);
template<typename T>
static T generic_modexp_mont(T base, T exp, const T& p, const T& q);
template<typename T>
static T generic_modexp_mont_crt(T base, T exp, const T& p, const T& q);

template<typename T>
static T generic_mont_reduction(T num, T R, T mod, T Mprime){
	static const T zero {"0"};
	T m=(num*Mprime)&(R-1);
	T t=(num+m*mod)/R;
	if(t>=mod){
		return t-mod;
	} else if(t>=zero){
		return t;
	} else {
		return t+mod;
	}
}


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
	return generic_modexp_mont(base, exp, p, q);
}

uberzahl modexp_mont_crt(uberzahl base, uberzahl exp, const uberzahl& p,
	const uberzahl& q)
{
	uberzahl a=1;
	return a;
	//return generic_modexp_mont_crt(base, exp, p, q);
}


// ************** helpers ************************************

template<typename T>
static T generic_modexp(T base, T exp, const T& p, const T& q)
{
	assert(p > q);
	T mod {p * q};
	T total {1};
	base = base % mod;
	static const T zero {"0"}; // don't reinitialize over and over
	while(exp > zero) {
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
	assert(p > q);
	T exp_p = exp % (p - 1);
	T exp_q = exp % (q - 1);
	T q_inv {q.inverse(p)};
	T m_1 = generic_modexp(base, exp_p, p, T {1});
	T m_2 = generic_modexp(base, exp_q, q, T {1});
	T h {"0"};
	if(m_1 < m_2) {
		h = (q_inv * (m_1 + p - m_2)) % p;
	} else {
		h = (q_inv * (m_1 - m_2)) % p;
	}
	static const T zero {"0"}; // don't reinitialize over and over
	// if(h < zero)
		// h = h + p;
	return m_2 + h * q;
}


template<typename T>
static T generic_modexp_mont(T base, T exp, const T& p, const T& q)
{
	assert(p > q);
	T mod {p * q};
	T R {1};
	while(R<=mod){
		R=R*2;
	}
	T Mprime=(R*R.inverse(mod)-1)/mod;
	T Rhat=((R-mod)*(R-mod))%mod;
	T baseHat=generic_mont_reduction(base*Rhat,R,mod,Mprime);
	T total {1};
	base = base % mod;
	static const T zero {"0"}; // don't reinitialize over and over
	while(exp > zero) {
		if(exp % 2 == 1){
			total=generic_mont_reduction(baseHat*total,R,mod,Mprime);
		}
		exp = exp >> 1;
		base=generic_mont_reduction(base*baseHat,R,mod,Mprime);
		baseHat=generic_mont_reduction(base*Rhat,R,mod,Mprime);
	}
	return total;
}


template<typename T>
static T generic_modexp_mont_crt(T base, T exp, const T& p, const T& q)
{
	assert(p > q);
	T exp_p = exp % (p - 1);
	T exp_q = exp % (q - 1);
	T q_inv {q.inverse(p)};
	T m_1 = generic_modexp_mont(base, exp_p, p, T {1});
	T m_2 = generic_modexp_mont(base, exp_q, q, T {1});
	T h {"0"};
	if(m_1 < m_2) {
		h = (q_inv * (m_1 + p - m_2)) % p;
	} else {
		h = (q_inv * (m_1 - m_2)) % p;
	}
	return m_2 + h * q;
}
