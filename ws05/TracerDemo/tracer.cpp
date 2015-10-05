#include <iostream>
#include <string>
struct Tracer{
	explicit Tracer(std::string name="")
	:name{name}{
		std::cout << "Tracer created: " << name << std::endl;
	}
	~Tracer(){
		std::cout << "Tracer destroyed: " << name << std::endl;
	}
	Tracer(Tracer const& other)
	:name{other.name+" copy"}{
		std::cout << "Tracer copied: " << name << std::endl;
	}
	void show() const {
		std::cout << "Tracer: " << name << std::endl;
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
		foo(inner);
		auto trace=bar(inner);
		trace.show();
		inner.show();
	}
	foo(Tracer("temp"));
	m.show();
}
