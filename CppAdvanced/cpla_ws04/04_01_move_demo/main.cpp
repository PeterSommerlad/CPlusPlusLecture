#include <iostream>

struct MoveableThing {
  MoveableThing() {
    std::cout << "Create Thing\n";
  }

  MoveableThing(MoveableThing &&) {
    std::cout << "Move Thing\n";
  }
};

MoveableThing create() {
  MoveableThing t{};
  return t;
}

int main() {
  MoveableThing created = create();
}
