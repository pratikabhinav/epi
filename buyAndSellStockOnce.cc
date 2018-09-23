#include <vector>
#include <limits>
#include <algorithm>
#include "test_framework/generic_test.h"
using std::vector;
using std::numeric_limits;
using std::max;
using std::min;

double BuyAndSellStockOnce(const vector<double>& prices) {
	double minSoFar = numeric_limits<double>::max(), maxProfit = 0;
	for (const double& price : prices) {
		double maxProfitToday = price - minSoFar;
		maxProfit = max(maxProfit, maxProfitToday);
		minSoFar = min(price, minSoFar);
	}
  
	return maxProfit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
