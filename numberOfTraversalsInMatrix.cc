#include <algorithm>
#include <memory>
#include <vector>
#include "test_framework/generic_test.h"

using std::make_unique;
using std::swap;
using std::vector;

int computeNumberOfWaystoXY(int x, int y, vector<vector<int>> *numberOfWaysPtr);

int NumberOfWays(int n, int m) {
	return computeNumberOfWaystoXY(n - 1, m - 1, make_unique<vector<vector<int>>>(n, vector<int>(m, 0)).get());
}
int computeNumberOfWaystoXY(int x, int y, vector<vector<int>> *numberOfWaysPtr) {
	if (x == 0 && y == 0) {
		return 1;
	}

	vector<vector<int>> &numberOfWays = *numberOfWaysPtr;
	if (numberOfWays[x][y] == 0) {
		int waysTop = x == 0 ? 0 : computeNumberOfWaystoXY(x - 1, y, numberOfWaysPtr);
		int waysLeft = y == 0 ? 0 : computeNumberOfWaystoXY(x, y - 1, numberOfWaysPtr);
		numberOfWays[x][y] = waysTop + waysLeft;
	}
	return numberOfWays[x][y];
}
int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "m"};
  return GenericTestMain(args, "number_of_traversals_matrix.cc",
                         "number_of_traversals_matrix.tsv", &NumberOfWays,
                         DefaultComparator{}, param_names);
}
