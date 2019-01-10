#include <vector>
#include <algorithm>
#include "test_framework/generic_test.h"
using std::vector;
using std::swap;

void ApplyPermutation(vector<int>* perm_ptr, vector<int>* A_ptr) {
	vector<int> &perm = *perm_ptr, &A = *A_ptr;
	for (int i = 0; i < size(A); ++i) {
		int next = i;
		while (perm[next] >= 0) {
			swap(A[i], A[perm[next]]);
			int temp = perm[next];
			perm[next] -= size(perm);
			next = temp;
		}
	}
}
vector<int> ApplyPermutationWrapper(vector<int> perm, vector<int> A) {
  ApplyPermutation(&perm, &A);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm", "A"};
  return GenericTestMain(args, "apply_permutation.cc", "apply_permutation.tsv",
                         &ApplyPermutationWrapper, DefaultComparator{},
                         param_names);
}
