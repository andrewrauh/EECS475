#include "Homework4.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <algorithm>
#include <sys/time.h>
using std::cout; using std::cerr; using std::endl;
using std::array;
using std::swap;
using std::fixed;


static void run_test(const uberzahl& base, const uberzahl& exp,
	const uberzahl& p, const uberzahl& q, int bit_length);


// TODO am I testing correctly?
int main(int argc, char* argv[])
{
	uberzahl a=23;
	uberzahl b=11;
	uberzahl p=7;
	uberzahl q=5;
	uberzahl test1=modexp(a,b,p,q);
	uberzahl test2=modexp_crt(a,b,p,q);
	uberzahl test3=modexp_mont(a,b,p,q);
	uberzahl test4=modexp_mont_crt(a,b,p,q);
	cout << test1 << " " << test2 << " " << test3 << " " << test4 << endl;

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

    srand(time(nullptr));

	for(int num_bits = 32; num_bits <= 2048; num_bits = num_bits << 1) {
		for(int j = 0; j < tests_per_len; ++j) {
			uberzahl base {};
			base.random(num_bits);

			uberzahl exp {};
			exp.random(num_bits);

			uberzahl p {};
			p.random(num_bits / 2);
			p = nextprime(p, 50);

			// get q
			uberzahl q {};
			q.random(num_bits / 2);
			q = nextprime(q, 50);

			if(p == q) { // if we chose the same numbers, rerun test
				--j;
				continue;
			} else if(p < q) {
				swap(p, q);
			}

			run_test(base, exp, p, q, num_bits);
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
static void run_test(const uberzahl& base, const uberzahl& exp,
	const uberzahl& p, const uberzahl& q, int bit_length)
{
	cout << bit_length;

	using modexp_t = uberzahl (*)(uberzahl, uberzahl, const uberzahl&, const uberzahl&);	
	array<modexp_t, 4> funcs {modexp, modexp_crt, modexp_mont, modexp_mont_crt};
	for(modexp_t func : funcs) {
		timeval tim {};
		gettimeofday(&tim, nullptr);
		double init_time {tim.tv_sec + (tim.tv_usec / 1000000.0)};
		uberzahl result {func(base, exp, p, q)}; // TODO will the compiler optimize this out?. 99% sure no
		gettimeofday(&tim, nullptr);
		double finish_time {tim.tv_sec + (tim.tv_usec / 1000000.0)};
		cout << '\t' << fixed << finish_time - init_time;
	}

	cout << '\n';

	#ifdef DEBUG
	uberzahl t1 {modexp(base, exp, p, q)};
	uberzahl t2 {modexp_crt(base, exp, p, q)};
	uberzahl t3 {modexp_mont(base, exp, p, q)};
	uberzahl t4 {modexp_mont_crt(base, exp, p, q)};


	// human-readable output testing. Comment out in final tests
	uberzahl mod {p * q};
	uberzahl correct {base};
	correct = correct.expm(exp, mod);
	if(!(t1 == t2 && t1 == t3 && t1 == t4)) {
		cout << "FAILURE: " << base << '^' << exp << " mod " << p << '*' << q
			<< "\n\tpowm:\t\t" << correct
			<< "\n\tmodexp:\t\t" << t1
			<< "\n\tmodexp_crt:\t" << t2
			<< "\n\tmodexp_mont:\t" << t3
			<< "\n\tmodexp_mon_crt:\t" << t4 << '\n' << endl;
		abort();
	}
	#endif
}
