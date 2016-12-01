#include "values.h"

#include <iostream>

void test() {
	Values<int> vi;
	for (int i = 0; i != 10; ++i) {
		vi.add(i);
	}

	if (!vi.remove(1)) {
		std::cout << "Can't remove 1\n";
	}

	if (vi.remove(1)) {
		std::cout << "Can remove 1 twice\n";
	}

	if (!vi.remove(9)) {
		std::cout << "Can't remove 9\n";
	}
	std::cout << "size: " << vi.values().size() << std::endl;
}

void failing_test() {
	Values<int> vi { };
	for (int i = 0; i != 10; ++i) {
		vi.add(i);
	}
	vi.remove(9);
}

int main() {
	test();
	failing_test();
}
