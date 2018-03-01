#include <variant>
#include <any>
#include <iostream>


namespace Television {

enum class Channel {
	cSRF1, cSRF2, c3Plus, c4Plus
};

struct OffState {
};

struct OnState {
	unsigned volume;
	Channel channel;
};

struct MuteState {
	Channel channel;
};

//From CPPReference: http://en.cppreference.com/w/cpp/utility/variant/visit
template<class... Ts>
struct overloaded : Ts... {
	using Ts::operator()...;
	explicit overloaded(Ts const &...f) : Ts{f}...{}
};

//template<class... Ts>
//overloaded(Ts...) -> overloaded<Ts...>;

struct Device {
	std::variant<OffState, OnState, MuteState> state;

	void volume_up() {
		std::visit(
				overloaded{
						[](auto&){
							std::cout << "ignoring volume change\n";
						},
						[](OnState & state) {
							std::cout << "increasing volume\n";
							state.volume++;
						}
				}
				, state);
	}

//	void volume_down() {
//		std::visit(, state);
//	}
//
//	void channel_up() {
//		std::visit(, state);
//	}
//
//	void channel_down() {
//		std::visit(, state);
//	}
//
//	void toggle_mute() {
//		std::visit(, state);
//	}
//
	void turn_on() {
		std::visit(
			overloaded{
					[](auto&){
						std::cout << "ignoring turn on\n";
					},
					[=](OffState & state) {
						std::cout << "turning on\n";
						this->state = OnState{};
					}
			}
			, state);
	}
//
//	void turn_off() {
//		std::visit(, state);
//	}
};

}

struct Base {
	void foo() {}
	void bar() {}
};

struct Sub : Base {
	void foo(int){}
	void bar(int){}
	using Base::foo, Base::bar;
};

int main() {
	Television::Device dev{};
	dev.turn_on();
	dev.volume_up();

}

