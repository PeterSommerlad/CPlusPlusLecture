#include <iostream>

struct Ball {
};

void pitcher() noexcept {
	throw Ball{};
}

int main() {
	try {
		pitcher();
	} catch(Ball const & b) {
		std::cout << "caught the ball!";
	}
}
