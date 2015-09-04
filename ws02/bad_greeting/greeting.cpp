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
void sayGreeting(std::ostream &out,
                 std::string name1,
                 std::string name2){
  out << "Hello " << name1 << ", do you love "
      << name2 << "?\n";
}
int main() {
  askForName(std::cout);
  sayGreeting(std::cout, inputName(std::cin),
              inputName(std::cin)); // order is unspecified
}
