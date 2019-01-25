#include "list_node.h"
#include "reverse_linked_list_iterative.h"
#include "test_framework/generic_test.h"

bool IsLinkedListAPalindrome(shared_ptr<ListNode<int>> L) {
	shared_ptr<ListNode<int>> slow = L, fast = L;
	while (fast && fast->next) {
		fast = fast->next->next, slow = slow->next;
	}

	auto firstHalfIter = L, secondHalfIter = ReverseLinkedList(slow);
	while (secondHalfIter && firstHalfIter) {
		if (secondHalfIter->data != firstHalfIter->data) {
			return false;
		}
		secondHalfIter = secondHalfIter->next;
		firstHalfIter = firstHalfIter->next;
	}
	return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "is_list_palindromic.cc",
                         "is_list_palindromic.tsv", &IsLinkedListAPalindrome,
                         DefaultComparator{}, param_names);
}
