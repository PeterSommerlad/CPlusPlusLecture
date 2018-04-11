


#include "Galaxy.h"

#include <iostream>


struct MultiPurposeCrewVehicle {
  void travelThroughSpace(Galaxy destination) {
	  std::cout << "Traveling to " << destination.name << " it takes a long time\n";
  }
};

struct GalaxyClassShip {
  void travelThroughSpace(Galaxy destination) {
	  std::cout << "Traveling to " << destination.name << " it takes a long time\n";
  }
  void travelThroughHyperspace(Galaxy destination) {
	  std::cout << "Traveling to " << destination.name << " it is quite fast\n";
  }
};

struct HeartOfGold {
  void travelThroughSpace(Galaxy destination) {
	  std::cout << "Traveling to " << destination.name << " it takes a long time\n";
  }
  Galaxy travelImprobably() {
	  auto newLocation = Galaxy::random();
	  std::cout << "Traveled to " << newLocation << ", probably not where you wanted to go\n";
	  return newLocation;

  }
};



//Provides travelThroughSpace
struct SpaceDriveTag {};

//Provides travelThroughSpace and travelThroughHyperspace
struct HyperspaceDriveTag : SpaceDriveTag {};

//Provides travelThroughSpace and travelImprobably
struct InfniteProbabilityDriveTag : SpaceDriveTag {};


template<typename>
struct SpaceshipTraits {
  using Drive = SpaceDriveTag;
};

template<>
struct SpaceshipTraits<GalaxyClassShip> {
  using Drive = HyperspaceDriveTag;
};

template<>
struct SpaceshipTraits<HeartOfGold> {
	using Drive = InfniteProbabilityDriveTag;
};


template<typename Spaceship>
void travelToDispatched(Galaxy destination, Spaceship & ship, SpaceDriveTag) {
  ship.travelThroughSpace(destination);
}

template<typename Spaceship>
void travelToDispatched(Galaxy destination, Spaceship & ship, HyperspaceDriveTag) {
	  ship.travelThroughHyperspace(destination);
}

template<typename Spaceship>
void travelToDispatched(Galaxy destination, Spaceship & ship, InfniteProbabilityDriveTag) {
	ship.travelImprobably();
}

template<typename SpaceShip>
void travelTo(Galaxy destination, SpaceShip & ship) {
  typename SpaceshipTraits<SpaceShip>::Drive drive{};
  travelToDispatched(destination, ship, drive);
}


int main(int argc, char **argv) {
	MultiPurposeCrewVehicle mpcv{};
	GalaxyClassShip enterprise{};
	HeartOfGold heartOfGold{};

	travelTo(Galaxy::Milkyway, mpcv);
	travelTo(Galaxy::Andromeda, enterprise);
	travelTo(Galaxy::FoxnaxDwarf, heartOfGold);
}


