#include <iostream>

struct Thing {
  Thing() {
    std::cout << "Create Thing\n";
  }

  Thing(Thing const &) {
    std::cout << "Copy Thing\n";
  }

  Thing(Thing &&) {
    std::cout << "Move Thing\n";
  }
};

Thing create() {
  Thing t{};
  return t;
}

int main() {
  Thing created = create();
}
