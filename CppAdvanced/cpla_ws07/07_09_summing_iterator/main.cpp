#include <iterator>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstddef>

struct SummingIter {

  using iterator_category = std::output_iterator_tag;
  using value_type = int;
  using difference_type = std::ptrdiff_t;
  using pointer = int *;
  using reference = int &;

  void operator++() { ++counter; }
  SummingIter& operator*() {
    return *this;
  }
  void operator=(value_type val) {
    sum += val;
  }
  double average() const {
    return sum / counter;
  }
  double sum{};
private:
  std::size_t counter{};
};


int main(int argc, char **argv) {
	std::vector<int> v {3, 1, 4, 1, 5, 9, 2};
	auto res = copy(v.begin(), v.end(), SummingIter{});
	std::cout << res.sum << " average: "<< res.average();
}
