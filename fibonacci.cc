#include "test_framework/generic_test.h"
int Fibonacci(int n) {
	if (n <= 1) {
		return n;
  }
	int fMinusOne = 1, fMinusTwo = 0;
	for (int i = 2; i <= n; ++i) {
		int f = fMinusTwo + fMinusOne;
		fMinusTwo = fMinusOne;
		fMinusOne = f;
	}

  return fMinusOne;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "fibonacci.cc", "fibonacci.tsv", &Fibonacci,
                         DefaultComparator{}, param_names);
}
