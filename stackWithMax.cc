#include <stdexcept>
#include <stack>
#include <algorithm>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

using std::length_error;
using std::stack;
using std::max;
using std::pair;


class Stack {
private:
	stack<pair<int, int>> element_with_cached_max;

 public:
  bool Empty() const {
	  return element_with_cached_max.empty();
  }
  int Pop() {
	  if (Empty()) {
		  throw length_error("Pop(): empty stack");
	}
	  int pop_element = element_with_cached_max.top().first;
	  element_with_cached_max.pop();
	  return pop_element;
  }
  int Max() const {
	  if (Empty()) {
		  throw length_error("Max(): empty stack");
	  }
	  return element_with_cached_max.top().second;
  }
  void Push(int x) {
	  element_with_cached_max.emplace(x, max(x, Empty() ? x : Max()));
  }
};

struct StackOp {
  std::string op;
  int argument;
};

template <>
struct SerializationTraits<StackOp> : UserSerTraits<StackOp, std::string, int> {
};

void StackTester(const std::vector<StackOp>& ops) {
  try {
    Stack s;
    for (auto& x : ops) {
      if (x.op == "Stack") {
        continue;
      } else if (x.op == "push") {
        s.Push(x.argument);
      } else if (x.op == "pop") {
        int result = s.Pop();
        if (result != x.argument) {
          throw TestFailure("Pop: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else if (x.op == "max") {
        int result = s.Max();
        if (result != x.argument) {
          throw TestFailure("Max: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else if (x.op == "empty") {
        int result = s.Empty();
        if (result != x.argument) {
          throw TestFailure("Empty: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else {
        throw std::runtime_error("Unsupported stack operation: " + x.op);
      }
    }
  } catch (length_error&) {
    throw TestFailure("Unexpected length_error exception");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "stack_with_max.cc", "stack_with_max.tsv",
                         &StackTester, DefaultComparator{}, param_names);
}
