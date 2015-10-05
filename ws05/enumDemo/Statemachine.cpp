#include "Statemachine.h"
#include <cctype>
enum class Statemachine::State: unsigned short {
	begin, middle, end
};

Statemachine::Statemachine()
:theState{State::begin} {}

void Statemachine::processInput(char c){
	switch(theState){
	case State::begin :
		if (! isspace(c))
			theState=State::middle;
		break;
	case State::middle :
		if (isspace(c))
			theState=State::end;
		break;
	case State::end : break;// ignore input
	}
}
bool Statemachine::isDone()const{
	return theState==State::end;
}
