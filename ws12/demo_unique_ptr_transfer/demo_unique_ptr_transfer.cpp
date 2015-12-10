#include <memory>
#include <iostream>
std::unique_ptr<int> afactory(int i){
    return std::make_unique<int>(i);
}
int main(){
    auto pi=afactory(42);

    std::cout << "*pi =" << *pi << '\n';
    std::cout << "pi.valid? "<< std::boolalpha
              << static_cast<bool>(pi) << '\n';
    auto pj=std::move(pi);
    std::cout << "*pj =" << *pj << '\n';
    std::cout << "pi.valid still? "
              << static_cast<bool>(pi) << '\n';
    std::cout << "pj.valid still? "
              << static_cast<bool>(pj) << '\n';
}


