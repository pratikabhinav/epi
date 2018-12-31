#include <string>
#include <vector>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;
using std::unordered_map;
using std::numeric_limits;
using std::min;

int FindNearestRepetition(const vector<string>& paragraph) {
	unordered_map<string, int> latestIndexOfWord;
	int nearestDist = numeric_limits<int>::max();
	for (int i = 0; i < size(paragraph); ++i) {
		if (auto latestEqualWord = latestIndexOfWord.find(paragraph[i]);
		latestEqualWord != end(latestIndexOfWord)) {
			nearestDist = min(nearestDist, i - latestEqualWord->second);
		}
		latestIndexOfWord[paragraph[i]] = i;
	}
	return nearestDist != numeric_limits<int>::max() ? nearestDist : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
