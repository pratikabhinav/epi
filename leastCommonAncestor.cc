#include <memory>
#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;

struct status;
status LCAhelper(const unique_ptr<BinaryTreeNode<int>>& tree,
	const unique_ptr<BinaryTreeNode<int>>& node0,
	const unique_ptr<BinaryTreeNode<int>>& node1);

struct status{
	int numTargetNodes;
	BinaryTreeNode<int> *ancestor;
};

BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& tree,
                         const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  
  return LCAhelper(tree, node0, node1).ancestor;
}

status LCAhelper(const unique_ptr<BinaryTreeNode<int>>& tree,
	const unique_ptr<BinaryTreeNode<int>>& node0,
	const unique_ptr<BinaryTreeNode<int>>& node1) {

	if (tree == nullptr) {
		return { 0, nullptr };
	}

	auto leftResult = LCAhelper(tree->left, node0, node1);
	if (leftResult.numTargetNodes == 2) {
		return leftResult;
	}

	auto rightResult = LCAhelper(tree->right, node0, node1);
	if (rightResult.numTargetNodes == 2) {
		return rightResult;
	}

	int numTargetNodes = leftResult.numTargetNodes + rightResult.numTargetNodes + (tree == node0) + (tree == node1);

	return { numTargetNodes, numTargetNodes == 2 ? tree.get() : nullptr };

}

int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return LCA(tree, node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
