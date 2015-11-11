#include <iostream>
#include <string>
struct Tracer{
	explicit Tracer(std::ostream & out,std::string name="")
	:out{out},name{name}{
		out << "Tracer created: " << name << std::endl;
	}
	~Tracer(){
		out << "Tracer destroyed: " << name << std::endl;
	}
	Tracer(Tracer const& other)
	:out{other.out},name{other.name+" copy"}{
		out << "Tracer copied: " << name << std::endl;
	}
	void show() const {
		out << "Tracer: " << name << std::endl;
	}
	std::ostream &out;
	std::string name;
};
void foo(Tracer t){
	Tracer trace(t.out,"foo");
	t.show();
}
Tracer bar(Tracer const &t){
	Tracer trace(t.out,"bar");
	t.show();
	return trace;
}
int main(){
	Tracer m{std::cout,"main"};
	{
		Tracer inner{m.out,"inner"};
		foo(inner);
		auto trace=bar(inner);
		trace.show();
		inner.show();
	}
	foo(Tracer{m.out,"temp"});
	m.show();
}
