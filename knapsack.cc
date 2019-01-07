#include <vector>
#include <memory>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;
using std::max;
using std::make_unique;


struct Item;
int knapsack(const vector<Item> &items, int k, int avlCapacity, vector<vector<int>> *vPtr);

struct Item {
  int weight, value;
};

int OptimumSubjectToCapacity(const vector<Item>& items, int capacity) {
	return knapsack(items, size(items) - 1, capacity, make_unique<vector<vector<int>>>(size(items), vector<int>(capacity + 1, -1)).get());
}

int knapsack(const vector<Item> &items, int k, int avlCapacity, vector<vector<int>> *vPtr) {
	if (k < 0) {
		return 0;
	}

	vector<vector<int>> &V = *vPtr;
	if (V[k][avlCapacity] == -1) {
		int withoutCurItem = knapsack(items, k - 1, avlCapacity, vPtr);
		int withCurItem = avlCapacity < items[k].weight ? 0 : items[k].value + knapsack(items, k - 1, avlCapacity - items[k].weight, vPtr);
		V[k][avlCapacity] = max(withoutCurItem, withCurItem);
	}
	return V[k][avlCapacity];
}

template <>
struct SerializationTraits<Item> : UserSerTraits<Item, int, int> {};

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"items", "capacity"};
  return GenericTestMain(args, "knapsack.cc", "knapsack.tsv",
                         &OptimumSubjectToCapacity, DefaultComparator{},
                         param_names);
}
