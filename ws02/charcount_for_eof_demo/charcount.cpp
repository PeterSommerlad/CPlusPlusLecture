#include <iostream>
int main(){
    size_t count{0};
    char c{};
    while (std::cin >> c) ++count;
    std::cout << count << "\n";
}
