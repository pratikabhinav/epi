#include <string>
#include "test_framework/generic_test.h"
using std::string;

string ConvertBase(const string& s, int b1, int b2) {
	bool is_negative = s.front() == '-';
	int x = 0;
	for (size_t i = (is_negative == true ? 1 : 0); i < s.size(); ++i) {
		x *= b1;
		x += isdigit(s[i]) ? s[i]-'0':s[i]-'A' + 10;
	}

	string result;
	do {
		int remainder = x % b2;
		result.push_back(remainder >= 10 ? 'A' + remainder - 10: '0' + remainder);
		x /= b2;
	} while (x);
	
	if (is_negative) {
		result.push_back('-');
	}
	
	reverse(result.begin(), result.end());
	return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
