#include "timer.h"
#include <iostream>
#include <forward_list>
#include <list>
#include <deque>
#include <vector>

size_t const SZ{100000};

template<typename CONT>
void remove_middle_elements(CONT &c){
    while(!c.empty()){
        size_t middle{c.size()/2};
        auto it=c.begin();
        std::advance(it,middle);
        c.erase(it);
    }
}

void fill_empty_fwlist(){
    size_t sz{SZ};
    std::forward_list<int> list{};
    while (sz--){
        list.push_front(sz);
    }
    sz=SZ;
    while (!list.empty()){
        auto it=list.before_begin();
        std::advance(it,sz/2);
        if(sz)sz--;
        list.erase_after(it);
    }
}
void fill_empty_deque(){
    size_t sz{SZ};
    std::deque<int> list{};
    while (sz--){
        list.push_front(sz);
    }
    remove_middle_elements(list);
}
void fill_empty_list(){
    size_t sz{SZ};
    std::list<int> list{};
    while (sz--){
        list.push_back(sz);
    }
    remove_middle_elements(list);
}
void fill_vector(){
    size_t size{SZ};
    std::vector<int> v{};
    while (size--) {
        v.push_back(size);
    }
    remove_middle_elements(v);
}




int main(){
    std::cout << time_func(fill_vector).count() << "us - vector back\n";
    std::cout << time_func(fill_empty_deque).count() << "us - deque front\n";
    std::cout << time_func(fill_empty_fwlist).count() << "us - forward_list front\n";
    std::cout << time_func(fill_empty_list).count() << "us - list back\n";
}



