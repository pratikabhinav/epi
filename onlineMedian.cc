#include <vector>
#include <queue>
#include <functional>
#include "test_framework/generic_test.h"
using std::vector;
using std::priority_queue;
using std::greater;
using std::less;

vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin,
                            const vector<int>::const_iterator& sequence_end) {
	priority_queue<int, vector<int>, greater<>> min_heap;
	priority_queue<int, vector<int>, less<>> max_heap;
	vector<double> result;

	while (sequence_begin != sequence_end) {
		min_heap.emplace(*sequence_begin++);
		max_heap.emplace(min_heap.top());
		min_heap.pop();

		if (size(max_heap) > size(min_heap)) {
			min_heap.emplace(max_heap.top());
			max_heap.pop();
		}

		result.emplace_back(size(min_heap) == size(max_heap) ? 0.5 * (min_heap.top() + max_heap.top()) : min_heap.top());
	}
	return result;
}
vector<double> OnlineMedianWrapper(const vector<int>& sequence) {
  return OnlineMedian(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "online_median.cc", "online_median.tsv",
                         &OnlineMedianWrapper, DefaultComparator{},
                         param_names);
}
