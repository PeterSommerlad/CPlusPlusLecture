

#include <any>
#include <iostream>

namespace protocol {

struct LedData {
	unsigned const red;
	unsigned const green;
	unsigned const blue;
};

std::ostream & operator << (std::ostream & out, LedData const & led) {
	out << "R: " << led.red << " G: " << led.green << " B: " << led.blue << '\n';
	return out;
}

enum class command {
	connect, disconnect, turnOnLed, turnOffLed
};

struct Message {
	command const cmd;
	std::any const data;
};

void turn_on_led(LedData const & ledData) {
	std::cout << "Turning on LED: " << ledData;
}

struct dispatcher {
	void handle_message(Message const & msg) const {
		auto const & cmd = msg.cmd;
		auto const & data = msg.data;
		switch(cmd) {
		case command::turnOnLed:
		{
			LedData ledData = std::any_cast<LedData>(data);
			turn_on_led(ledData);
			break;
		}
		//...
		default:
			break;
		}
	}
};

}

int main() {
	using namespace protocol;
	dispatcher message_dispatcher{};

	Message turn_led_red{command::turnOnLed, LedData{255, 0, 0}};
	message_dispatcher.handle_message(turn_led_red);
}
