#include <memory>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::numeric_limits;

bool areKeysInRange(const unique_ptr<BinaryTreeNode<int>> &tree, int low, int high);

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
	return areKeysInRange(tree, numeric_limits<int>::min(), numeric_limits<int>::max());
}

bool areKeysInRange(const unique_ptr<BinaryTreeNode<int>> &tree, int low, int high) {
	if (tree == nullptr) {
		return true;
	}
	else if (tree->data < low || tree->data > high) {
		return false;
	}
	return areKeysInRange(tree->left, low, tree->data) && areKeysInRange(tree->right, tree->data, high);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
