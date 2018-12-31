#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int FindMaximumSubarray(const vector<int>& A) {
	int minSum = 0, runningSum = 0, maxSum = 0;
	for (int i = 0; i < size(A); ++i) {
		runningSum += A[i];
		if (runningSum < minSum) {
			minSum = runningSum;
		}
		if (runningSum - minSum > maxSum) {
			maxSum = runningSum - minSum;
		}
	}
	return maxSum;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "max_sum_subarray.cc", "max_sum_subarray.tsv",
                         &FindMaximumSubarray, DefaultComparator{},
                         param_names);
}
