#include "Homework4.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <algorithm>
#include <sys/time.h>
using std::cout; using std::endl;
using std::array;
using std::swap;
using std::fixed;


static void run_test(const mpz_class& base, const mpz_class& exp,
	const mpz_class& p, const mpz_class& q, int bit_length);


// TODO am I testing correctly?
int main(int argc, char* argv[])
{
	// testing parameters
	int low_bit_len {100};
	int high_bit_len {1000};
	int tests_per_len {3};
	if(argc == 4) {
		low_bit_len = atoi(argv[1]);
		high_bit_len = atoi(argv[2]);
		tests_per_len = atoi(argv[3]);
	}

	cout.precision(8);

    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(nullptr));

	for(int num_bits = low_bit_len; num_bits <= high_bit_len; ++num_bits) {
		for(int j = 0; j < tests_per_len; ++j) {
			// get base
			mpz_class base {};
			mpz_urandomb(base.get_mpz_t(), state, num_bits);

			// get mod
			mpz_class mod {};
			mpz_urandomb(mod.get_mpz_t(), state, num_bits);

			// get p
			mpz_class p {};
			mpz_urandomb(p.get_mpz_t(), state, num_bits / 2);
			mpz_nextprime(p.get_mpz_t(), p.get_mpz_t());

			// get q
			mpz_class q {};
			mpz_urandomb(q.get_mpz_t(), state, num_bits / 2);
			mpz_nextprime(q.get_mpz_t(), q.get_mpz_t());

			if(p == q) { // if we chose the same numbers, rerun test
				--j;
				continue;
			} else if(p < q) {
				swap(p, q);
			}

			run_test(base, mod, p, q, num_bits);
		}
	}

	// manual tests for correctness
	// run_test(2, 10, 3, 2, 10); // TODO this breaks crt. Why?
	// run_test(13, 1023, 883, 881, 10);
	// run_test(13, 1024, 883, 881, 10);
	// run_test(13, 1025, 883, 881, 10);

	return 0;
}

// outputs the runtime of each algorithm in the format:
// <bit length> <modexp runtime> <modexp_crt runtime> <modexp_mont runtime> <modexp_mont_crt runtime>
// Also tests whether all versions of modexp return the same value
static void run_test(const mpz_class& base, const mpz_class& exp,
	const mpz_class& p, const mpz_class& q, int bit_length)
{
	cout << bit_length;

	using modexp_t = mpz_class (*)(mpz_class, mpz_class, const mpz_class&, const mpz_class&);
	array<modexp_t, 4> funcs {modexp, modexp_crt, modexp_mont, modexp_mont_crt};
	for(modexp_t func : funcs) {
		timeval tim {};
		gettimeofday(&tim, nullptr);
		double init_time {tim.tv_sec + (tim.tv_usec / 1000000.0)};
		mpz_class result {func(base, exp, p, q)}; // TODO will the compiler optimize this out?. 99% sure no
		gettimeofday(&tim, nullptr);
		double finish_time {tim.tv_sec + (tim.tv_usec / 1000000.0)};
		cout << '\t' << fixed << finish_time - init_time;
	}

	cout << '\n';

	#ifdef DEBUG
	mpz_class t1 {modexp(base, exp, p, q)};
	mpz_class t2 {modexp_crt(base, exp, p, q)};
	mpz_class t3 {modexp_mont(base, exp, p, q)};
	mpz_class t4 {modexp_mont_crt(base, exp, p, q)};


	// human-readable output testing. Comment out in final tests
	mpz_class mod {p * q};
	mpz_class correct {};
	mpz_powm(correct.get_mpz_t(), base.get_mpz_t(), exp.get_mpz_t(), mod.get_mpz_t());
	if(!(t1 == t2 && t1 == t3 && t1 == t4)) {
		cout << "FAILURE: " << base << '^' << exp << " mod " << p << '*' << q
			<< "\n\tmpz_powm:\t" << correct
			<< "\n\tmodexp:\t\t" << t1
			<< "\n\tmodexp_crt:\t" << t2
			<< "\n\tmodexp_mont:\t" << t3
			<< "\n\tmodexp_mon_crt:\t" << t4 << '\n' << endl;
		exit(1);
	}
	#endif
}
