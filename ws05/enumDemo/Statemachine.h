#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

struct Statemachine {
	Statemachine();
	void processInput(char c);
	bool isDone() const;
private:
	enum class State : unsigned short;
	State theState;
};

#endif /* STATEMACHINE_H_ */
