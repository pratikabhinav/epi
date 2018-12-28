#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"

using std::max;
using std::min;
using std::minmax;
using std::pair;
using std::tie;
using std::vector;

struct MinMax {
  int smallest, largest;
};

MinMax FindMinMax(const vector<int>& A) {
	if (size(A) <= 1) {
		return {A.front(), A.front()};
	}

	int globalMin, globalMax, localMin, localMax;
	tie(globalMin, globalMax) = minmax(A[0], A[1]);

	for (int i = 2; i + 1 < size(A); i += 2) {
		tie(localMin, localMax) = minmax(A[i], A[i+1]);
		globalMin = min(globalMin, localMin);
		globalMax = max(globalMax, localMax);
	}

	if (size(A) % 2) {
		globalMin = min(globalMin, A.back());
		globalMax = max(globalMax, A.back());
	}
	return { globalMin, globalMax };
}
template <>
struct SerializationTraits<MinMax> : UserSerTraits<MinMax, int, int> {};

bool operator==(const MinMax& lhs, const MinMax& rhs) {
  return std::tie(lhs.smallest, lhs.largest) ==
         std::tie(rhs.smallest, rhs.largest);
}

std::ostream& operator<<(std::ostream& out, const MinMax& x) {
  return out << "min: " << x.smallest << ", max: " << x.largest;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_for_min_max_in_array.cc",
                         "search_for_min_max_in_array.tsv", &FindMinMax,
                         DefaultComparator{}, param_names);
}
