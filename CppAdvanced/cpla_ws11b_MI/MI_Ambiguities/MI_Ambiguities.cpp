class BaseX {
  void foo() {} //private
};

struct BaseY {
  void foo() {} //public
};

struct Derived : BaseX, BaseY {};


int main(int argc, char **argv) {
	Derived d{};
	d.foo(); //ambiguous
	d.BaseX::foo(); //not accessible
	d.BaseY::foo(); //works
}
