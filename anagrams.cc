#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
#include <tuple>
#include "test_framework/generic_test.h"

using std::string;
using std::unordered_map;
using std::vector;
using std::tuple;

vector<vector<string>> FindAnagrams(const vector<string>& dictionary) {
	unordered_map<string, vector<string>> sortedStringToAnagrams;
	for (const string &s : dictionary) {
		string sortedString(s);
		sort(begin(sortedString), end(sortedString));
		sortedStringToAnagrams[sortedString].emplace_back(s);
	}

	vector<vector<string>> anagramGroups;
	for (const auto &[key, group] : sortedStringToAnagrams) {
		if (size(group) >= 2) {
			anagramGroups.emplace_back(group);
		}
	}
	return anagramGroups;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"dictionary"};
  return GenericTestMain(
      args, "anagrams.cc", "anagrams.tsv", &FindAnagrams,
      &UnorderedComparator<std::vector<std::vector<std::string>>>, param_names);
}
