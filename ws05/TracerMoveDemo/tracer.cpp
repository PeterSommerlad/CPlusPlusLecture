#include <iostream>
#include <string>
struct Tracer{
	explicit Tracer(std::string name="")
	:name{name}{
		std::cout << "Tracer created: "
				  << name << std::endl;
	}
	~Tracer(){
		std::cout << "Tracer destroyed: "
				  << name << std::endl;
	}
	Tracer(Tracer && other)
	:name{other.name}{ // normally std::move(other.name)
		other.name+=" moved from"; // simulate "emptying" moved from value
		std::cout << "Tracer moved: "
				  << name << std::endl;
	}
	void show() const {
		std::cout << "Tracer: "
				  << name << std::endl;
	}
	std::string name;
};
void foo(Tracer t){
	Tracer trace("foo");
	t.show();
}
Tracer bar(Tracer const &t){
	Tracer trace("bar");
	t.show();
	return trace;
}
int main(){
	Tracer m("main");
	{
		Tracer inner("inner");
		foo(std::move(inner));
		auto trace=bar(inner);
		trace.show();
		inner.show();
	}
	foo(Tracer("temp"));
	m.show();
}
