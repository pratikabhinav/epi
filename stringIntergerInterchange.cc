#include <string>
#include <numeric>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
	bool is_negative = false;
	if (x < 0) {
		x = -x, is_negative = true;
	}

	string s;
	do {
		s += '0' + abs(x % 10);
		x /= 10;
	} while (x);

	if (is_negative) {
		s += '-';
	}
	reverse(s.begin(), s.end());
	return s;
}


int StringToInt(const string& s) {
	bool is_negative = s[0] == '-';
	int result = 0;
	for (int i = s[0] == '-' ? 1 : 0; i < s.size(); ++i) {
		int digit = s[i] - '0';
		result = result * 10 + digit;
	}
	return is_negative ? -result : result;
}
void Wrapper(int x, const string& s) {
  if (IntToString(x) != s) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
