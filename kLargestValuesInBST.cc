#include <memory>
#include <vector>
#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

void FindKLargestInBSTHelper(const unique_ptr<BstNode<int>> &tree, int k, vector<int> *kLargestElements);

vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
	vector<int> kLargestElements;
	FindKLargestInBSTHelper(tree, k, &kLargestElements);
  return kLargestElements;
}

void FindKLargestInBSTHelper(const unique_ptr<BstNode<int>> &tree, int k, vector<int> *kLargestElements) {
	if (tree && size(*kLargestElements) < k) {
		FindKLargestInBSTHelper(tree->right, k, kLargestElements);
		if (size(*kLargestElements) < k) {
			kLargestElements->emplace_back(tree->data);
			FindKLargestInBSTHelper(tree->left, k, kLargestElements);
		}
	}
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         &UnorderedComparator<std::vector<int>>, param_names);
}
