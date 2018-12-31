#include <vector>
#include <algorithm>

#include "test_framework/generic_test.h"
using std::vector;

int HIndex(vector<int> citations) {
	sort(begin(citations), end(citations));
	const int n = size(citations);
	for (int i = 0; i < n; ++i) {
		if (citations[i] >= n - i) {
			return n - i;
		}
	}
	return 0;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"citations"};
  return GenericTestMain(args, "h_index.cc", "h_index.tsv", &HIndex,
                         DefaultComparator{}, param_names);
}
