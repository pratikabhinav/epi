#include <functional>
#include <queue>
#include <string>
#include <vector>
#include "test_framework/generic_test.h"

using std::greater;
using std::priority_queue;
using std::string;
using std::vector;

vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator sequence_end, int k) {
	
	priority_queue<int, vector<int>, greater<>> min_heap;

	for (int i = 0; i < k && sequence_begin != sequence_end; ++i) {
		min_heap.push(*sequence_begin++);
	}

	vector<int> result;
	while (sequence_begin != sequence_end) {
		min_heap.push(*sequence_begin++);
		result.push_back(min_heap.top());
		min_heap.pop();
	}

	while (!empty(min_heap)) {
		result.push_back(min_heap.top());
		min_heap.pop();
	}

	return result;
}
vector<int> SortApproximatelySortedDataWrapper(const vector<int>& sequence,
                                               int k) {
  return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(
      args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
      &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
