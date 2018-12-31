#include <vector>
#include <algorithm>
#include "test_framework/generic_test.h"
using std::vector;
using std::swap;

void directedPermutations(int i, vector<int> *A, vector<vector<int>> *result);

vector<vector<int>> Permutations(vector<int> A) {
	vector<vector<int>> result;
	directedPermutations(0, &A, &result);
	return result;
}

void directedPermutations(int i, vector<int> *A_ptr, vector<vector<int>> *result) {
	vector<int> &A = *A_ptr;
	if (i == size(A) - 1) {
		result->emplace_back(A);
		return;
	}

	for (int j = i; j < size(A); ++j) {
		swap(A[i], A[j]);
		directedPermutations(i + 1, A_ptr, result);
		swap(A[i], A[j]);
	}
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "permutations.cc", "permutations.tsv", &Permutations,
      &UnorderedComparator<vector<vector<int>>>, param_names);
}
