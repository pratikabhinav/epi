#include <memory>
#include <vector>
#include <queue>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

using std::queue;
using std::unique_ptr;
using std::vector;

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
	queue<BinaryTreeNode<int>*> processing_nodes;
	processing_nodes.emplace(tree.get());
	int num_nodes_to_process_at_current_level = processing_nodes.size();
	vector<vector<int>> result;
	vector<int> one_level;
	
	while (!processing_nodes.empty()) {
		auto curr = processing_nodes.front();
		processing_nodes.pop();
		--num_nodes_to_process_at_current_level;
		if (curr) {
			one_level.emplace_back(curr->data);
			processing_nodes.emplace(curr->left.get());
			processing_nodes.emplace(curr->right.get());
		}

		if (!num_nodes_to_process_at_current_level) {
			num_nodes_to_process_at_current_level = processing_nodes.size();
			if (!one_level.empty()) {
				result.emplace_back(move(one_level));
			}
		}
	}
	return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
