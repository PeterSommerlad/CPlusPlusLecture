#include "random.h"

#include <exception>
#include <iostream>

PercentageRandomProvider<> const percentageNumberGenerator{};

struct ExplodesException {};

template <unsigned ChanceToExplode>
struct Liquid {
	Liquid(unsigned amount) : amount{amount}{}

	Liquid(Liquid && other) noexcept(noexcept(other.shake())) {
		other.shake();
		amount = other.amount;
	}

	~Liquid() {
		//shake()
	}

	void shake() noexcept(ChanceToExplode == 0)  {
		if constexpr(ChanceToExplode>0){
			auto randomNumber = percentageNumberGenerator();
			if (randomNumber < ChanceToExplode) {
				amount = 0;
				throw ExplodesException{};
			}
		}
	}
private:
	unsigned amount{};
};

using Nitroglycerin = Liquid<75>;
using JetFuel = Liquid<10>;
using Water = Liquid<0>;

template <typename Liquid>
struct Barrel {
	Barrel(Liquid && content) : content{std::move(content)}{}
	void poke() noexcept(noexcept(std::declval<Liquid>().shake())) {
		content.shake();
	}
private:
	Liquid content;
};

int main() {
	Barrel<Water> water{Water{50}};
	std::cout << "is water.poke() noexcept? " << noexcept(water.poke()) << '\n';

	Barrel<JetFuel> jetFuel{JetFuel{50}};
	std::cout << "is jetFuel.poke() noexcept? " << noexcept(jetFuel.poke()) << '\n';

	Barrel<Nitroglycerin> nitroglycerin{Nitroglycerin{50}};
	std::cout << "is nitroglycerin.poke() noexcept? " << noexcept(nitroglycerin.poke()) << '\n';
}

