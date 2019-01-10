#include <vector>
#include <deque>
#include "test_framework/generic_test.h"
using std::vector;
using std::deque;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n) {
	vector<int> primes;
	deque<bool> isPrime(n + 1, true);
	isPrime[0] = isPrime[1] = 0;
	for (int p = 2; p <= n; p++) {
		if (isPrime[p]) {
			primes.emplace_back(p);
			for (int i = p; i <= n; i += p) {
				isPrime[i] = 0;
			}
		}
	}
	return primes;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
