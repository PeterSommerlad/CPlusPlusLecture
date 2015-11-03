#include <stack>
#include <queue>
#include <iostream>
int main(){
	std::stack<std::string> lifo;
	std::queue<std::string> fifo;
	for(std::string s
			:{"Fall","leaves","after","leaves","fall"}){
		lifo.push(s);
		fifo.push(s);
	}
	while (!lifo.empty()){
		std::cout << lifo.top() << " ";
		lifo.pop();
	} // fall leaves after leaves Fall
	std::cout << "\n";
	while (!fifo.empty()){
		std::cout << fifo.front() << " ";
		fifo.pop();
	} // Fall leaves after leaves fall
}
