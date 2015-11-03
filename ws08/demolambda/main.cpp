int main(){
    int j{};
    int k{};
    auto l=[&j,k](int i){ j = i; return i*i;};
    l(3);

    auto odd=[](int i){ return i%2;};
    auto divides=[](int i,int j){ return i%j==0;};
}


