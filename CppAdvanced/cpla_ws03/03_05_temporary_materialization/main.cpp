#include <iostream>

struct Ghost {
	void haunt() const {
		std::cout << "booooo!\n";
	}
	//~Ghost() = delete;
};

Ghost evoke() {
	return Ghost{};
}


int main() {
	Ghost && sam = evoke();

	Ghost{}.haunt();
}
