#include "Sack.h"

struct Present {};

class SantaClaus {
	Sack<Present> theSackFullOfPresents;
} santa;

struct Potatoes{};
struct PotatoChips{};
Sack<Sack<PotatoChips>> ZweifelFactory(std::vector<Sack<Potatoes>>);
