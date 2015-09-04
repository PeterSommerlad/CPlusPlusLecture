#include <iostream>
#include <string>
void askForName(std::ostream &out){
  out << "What is your name? ";
}
std::string inputName(std::istream &in){
  std::string name{};
  in >> name;
  return name;
}
void sayGreeting(std::ostream &out,std::string name){
  out << "Hello " << name << ", how are you?\n";
}
int main() {
  askForName(std::cout);
  sayGreeting(std::cout, inputName(std::cin));
}
