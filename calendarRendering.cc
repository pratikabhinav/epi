#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;
using std::max;

struct Event {
  int start, finish;
};

struct Endpoint {
	int time;
	bool isStart;
};


int FindMaxSimultaneousEvents(const vector<Event>& A) {
	vector<Endpoint> E;
	for (const Event &event : A) {
		E.emplace_back(Endpoint{ event.start, true });
		E.emplace_back(Endpoint{ event.finish, false });
	}
	sort(begin(E), end(E), [](const Endpoint &a, const Endpoint &b) {
		return a.time != b.time ? a.time < b.time :(a.isStart && !b.isStart);
	});

	int globalMax = 0, localMax = 0;
	for (const Endpoint &endpoint : E) {
		if (endpoint.isStart) {
			++localMax;
			globalMax = max(globalMax, localMax);
		}
		else {
			--localMax;
		}
	}

	return globalMax;
}
template <>
struct SerializationTraits<Event> : UserSerTraits<Event, int, int> {};

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "calendar_rendering.cc",
                         "calendar_rendering.tsv", &FindMaxSimultaneousEvents,
                         DefaultComparator{}, param_names);
}
