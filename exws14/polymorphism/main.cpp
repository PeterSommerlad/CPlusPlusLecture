#include "Inheritance.h"

int main() {
	cout << "a ------\n";
	forum_troll ft { };
	troll t { ft };
	monster &m { ft };
	cout << "b ------\n";
	ft.attack();
	t.attack();
	m.attack();
	cout << "c ------\n";
	ft.swing_club();
	t.swing_club();
	cout << "d ------\n";
	ft.health();
	t.health();
	m.health();
	cout << "end ------\n";
}
