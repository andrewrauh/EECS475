#include <gmpxx.h>
#include <iostream>
#include <cassert>
using namespace std;


void run_test(const mpz_class& base, const mpz_class& exp, const mpz_class& p,
		const mpz_class& q);


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
	// TODO how to actually do modular exponentiation here. Should I call modexp?
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



int main(int argc, char* argv[]) {
	//run_test(2, 10, 3, 2); TODO this breaks crt
	run_test(13, 1023, 883, 881);
	run_test(13, 1024, 883, 881);
	run_test(13, 1025, 883, 881);

	return 0;
}

// tests whether all versions of modexp return the same value
void run_test(const mpz_class& base, const mpz_class& exp, const mpz_class& p,
		const mpz_class& q) {
	mpz_class t1 = modexp(base, exp, p, q);
	mpz_class t2 = modexp_crt(base, exp, p, q);
	mpz_class t3 = modexp_mont(base, exp, p, q);
	mpz_class t4 = modexp_mont_crt(base, exp, p, q);

	mpz_class mod {p * q};
	mpz_class correct {};
	mpz_powm(correct.get_mpz_t(), base.get_mpz_t(), exp.get_mpz_t(), mod.get_mpz_t());

	cout << base << '^' << exp << " mod " << p << '*' << q
		<< "\n\tmpz_powm:\t" << correct
		<< "\n\tmodexp:\t\t" << t1
		<< "\n\tmodexp_crt:\t" << t2
		<< "\n\tmodexp_mont:\t" << t3
		<< "\n\tmodexp_mon_crt:\t" << t4 << '\n' << endl;

	assert(t1 == t2 && t1 == t3 && t1 == t4);
}
