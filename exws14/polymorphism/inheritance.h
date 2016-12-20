#ifndef INHERITANCE_H_
#define INHERITANCE_H_

#include <iostream>

using std::cout;

struct monster {
	monster() {
		cout << "a monster is bread\n";
	}
	~monster() {
		cout << "monster killed\n";
	}
	void health() {
		cout << "immortal?\n";
	}
	virtual void attack() {
		cout << "roar\n";
	}
};

struct troll: monster {
	troll() {
		cout << "a troll grows\n";
	}
	~troll() {
		cout << "troll petrified\n";
	}
	void attack() {
		swing_club();
	}
	virtual void swing_club() {
		cout << "clubbing kills me\n";
		myhealth--;
	}
	void health() {
		cout << "troll-health:" << myhealth << '\n';
	}
protected:
	int myhealth { 10 };
};

struct forum_troll: troll {
	forum_troll() :
			troll { } {
		cout << "not quite a monster\n";
	}
	~forum_troll() {
		cout << "troll banned\n";
	}
	virtual void swing_club() {
		cout << "swinging is healthy\n";
		myhealth++;
	}
	void attack() {
		cout << "write stupid things\n";
	}
};

#endif /* INHERITANCE_H_ */
