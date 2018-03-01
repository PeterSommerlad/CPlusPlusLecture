#include <iostream>
#include <tuple>

struct S {
  int member_i;
  double member_d;
};

S create() {
	return S{};
}

int main() {
  auto [f, s] = std::make_tuple(1, 1.5);
  std::cout << "f = " << f << '\n';
  std::cout << "s = " << s;

  auto const & [i, d] = create();
}
