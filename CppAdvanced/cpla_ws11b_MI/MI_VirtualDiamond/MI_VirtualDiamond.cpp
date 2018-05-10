#include <string>
#include <iostream>

#include <ostream>

struct Building {
	Building(std::string const & location) : location{location}{
		std::cout << "new location " << location << '\n';
	}
	std::string location;
};

struct Skyscraper : public virtual Building {
	Skyscraper(std::string const & location, unsigned height) : Building{location}, height{height} {}
	unsigned height;
};

struct Hotel : public virtual Building {
	Hotel(std::string const & location, unsigned rooms) : Building{location}, rooms{rooms} {}
	unsigned rooms;
};

struct SkyscraperHotel : public Skyscraper, public Hotel {
	SkyscraperHotel() : Building{"here"}, Skyscraper{"somewhere", 100}, Hotel{"elsewhere", 200} {}
};



int main(int argc, char **argv) {
	SkyscraperHotel sh{};
	std::cout << "Skyscraper location: " << sh.Skyscraper::location << '\n';
	std::cout << "Hotel location: " << sh.Hotel::location << '\n';
}


