#include <deque>
#include <vector>
#include <queue>
#include <initializer_list>
#include <utility>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::deque;
using std::vector;
using std::queue;
using std::initializer_list;
using std::pair;
using std::make_pair;

void FlipColor(int x, int y, vector<deque<bool>>* image_ptr) {
	vector<deque<bool>> &image = *image_ptr;
	const bool color = image[x][y];

	queue <pair<int, int>> q;
	image[x][y] = !color;
	q.emplace(x, y);
	while (!empty(q)) {
		const auto[x, y] = q.front();
		q.pop();
		for (const auto &[nextX, nextY] : initializer_list<pair<int, int>> {
			{x, y + 1}, { x, y - 1 }, { x + 1, y }, { x - 1, y }
		}) {
			if (nextX >= 0 && nextX < size(image) && nextY >= 0 && nextY < size(image[nextX]) && image[nextX][nextY] == color){
				image[nextX][nextY] = !color;
				q.emplace(nextX, nextY);
			}
		}
	}
}
vector<vector<int>> FlipColorWrapper(TimedExecutor& executor, int x, int y,
                                     vector<vector<int>> image) {
  vector<deque<bool>> b;
  b.reserve(image.size());
  for (const vector<int>& row : image) {
    deque<bool> tmp;
    tmp.resize(row.size());
    for (int i = 0; i < row.size(); ++i) {
      tmp[i] = static_cast<bool>(row[i]);
    }
    b.push_back(tmp);
  }

  executor.Run([&] { FlipColor(x, y, &b); });

  image.resize(b.size());

  for (int i = 0; i < image.size(); ++i) {
    image[i].resize(b.size());
    for (int j = 0; j < image[i].size(); ++j) {
      image[i][j] = b[i][j];
    }
  }
  return image;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "x", "y", "image"};
  return GenericTestMain(args, "matrix_connected_regions.cc", "painting.tsv",
                         &FlipColorWrapper, DefaultComparator{}, param_names);
}
