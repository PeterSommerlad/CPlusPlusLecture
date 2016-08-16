template <typename ADD>
concept bool Addable(){
        return requires(ADD a, ADD b){
                {a+b}->ADD;
        };
}

template <Addable A>
struct Twice {
auto operator()(A a) {
	return a+a;
}
};

auto twice(Addable a) {
return a+a;
}

int main(){
	struct X{};
//	Twice<X> tryit;
//	tryit(X{});
	Twice<int> works;
	works(42);
	twice(42);
}
