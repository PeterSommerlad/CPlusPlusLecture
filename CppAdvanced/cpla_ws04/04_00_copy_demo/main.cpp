#include<iostream>

struct CopyableThing {
  CopyableThing() {
    std::cout << "Create Thing\n";
  }
  CopyableThing(CopyableThing const &) {
    std::cout << "Copy Thing\n";
  }
};

CopyableThing create() {
  CopyableThing t{};
  return t;
}

int main() {
  CopyableThing created = create();
}
