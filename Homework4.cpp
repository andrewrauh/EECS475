#include "Homework4.h"
#include "Montgomery.h"
#include <cassert>
#include <iostream>
using std::cerr; using std::endl;


static uberzahl mont_reduction(const uberzahl& num, const uberzahl& R, smallType R_bitlength
	,const uberzahl& mod, const uberzahl& Mprime)
{
	static const uberzahl zero {"0"};
	uberzahl m=(num*Mprime)&(R-1);
	uberzahl t=(num+m*mod) >> R_bitlength;
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
	assert(p > q);
	uberzahl mod {p * q};
	uberzahl total {1};
	base = base % mod;
	static const uberzahl zero {"0"}; // don't reinitialize over and over
	while(exp > zero) {
		if(exp % 2 == 1)
			total = (total * base) % mod;
		exp = exp >> 1;
		base = (base * base) % mod;
	}
	return total;
}

uberzahl modexp_crt(uberzahl base, uberzahl exp, const uberzahl& p,
	const uberzahl& q)
{
	assert(p > q);
	uberzahl exp_p = exp % (p - 1);
	uberzahl exp_q = exp % (q - 1);
	uberzahl q_inv {q.inverse(p)};
	uberzahl m_1 = modexp(base, exp_p, p, uberzahl {1});
	uberzahl m_2 = modexp(base, exp_q, q, uberzahl {1});
	uberzahl h {"0"};
	if(m_1 < m_2) {
		h = (q_inv * (m_1 + p - m_2)) % p;
	} else {
		h = (q_inv * (m_1 - m_2)) % p;
	}
	return m_2 + h * q;
}

uberzahl modexp_mont(uberzahl base, uberzahl exp, const uberzahl& p,
	const uberzahl& q)
{
	assert(p > q);
	uberzahl mod {p * q};
	uberzahl R {1};
	int R_bitlength = 0;
	while(R<=mod){
		R=R*2;
		++R_bitlength;
	}
	uberzahl Mprime=(R*R.inverse(mod)-1)/mod;
	uberzahl baseHat=(base*(R-mod))%mod;
	uberzahl total {1};
	static const uberzahl zero {"0"}; // don't reinitialize over and over
	while(exp > zero) {
		if((exp & 1) == 1){
			total=mont_reduction(baseHat*total,R,R_bitlength,mod,Mprime);
		}
		exp = exp >> 1;
		baseHat=mont_reduction(baseHat*baseHat,R,R_bitlength,mod,Mprime);
	}
	return total;
}

uberzahl modexp_mont_crt(uberzahl base, uberzahl exp, const uberzahl& p,
	const uberzahl& q)
{	
	
	assert(p > q);
	uberzahl exp_p = exp % (p - 1);
	uberzahl exp_q = exp % (q - 1);
	uberzahl q_inv {q.inverse(p)};
	uberzahl m_1 = modexp_mont(base, exp_p, p, uberzahl {1});
	uberzahl m_2 = modexp_mont(base, exp_q, q, uberzahl {1});
	uberzahl h {"0"};
	if(m_1 < m_2) {
		h = (q_inv * (m_1 + p - m_2)) % p;
	} else {
		h = (q_inv * (m_1 - m_2)) % p;
	}
	return m_2 + h * q;
}
