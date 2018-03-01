#include <iostream>
#include <string>


//bool contains(std::string const & str, std::string const & substr) {
//  return str.find(substr) != std::string::npos;
//}

bool contains(std::string_view str, std::string_view substr) {
  return str.find(substr) != std::string::npos;
}


int main() {
  std::string s{"it is where you look last"};
  std::cout << std::boolalpha << contains(s, "last");
}
