#include <iostream>

struct Ghost {
	void haunt() const {
		std::cout << "booooo!\n";
	}
	//~Ghost() = delete;
};

Ghost evocate() {
	return Ghost{};
}


int main() {
	Ghost && sam = evocate();

	Ghost{}.haunt();
}
