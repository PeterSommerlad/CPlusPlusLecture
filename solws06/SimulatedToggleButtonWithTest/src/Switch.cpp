#include "Switch.h"
#include <ostream>
enum class Switch::togglestate:unsigned char{
	off, on, blink
};

Switch::Switch() :state{togglestate::off}{
}

void Switch::PushButton() {
	state = togglestate((int(state)+1)%3);
}

void Switch::print(std::ostream& out) const{
	switch(state){
	case togglestate::off: out << "off"; break;
	case togglestate::on:  out << "on"; break;
	case togglestate::blink:out << "blink"; break;
	}
}
