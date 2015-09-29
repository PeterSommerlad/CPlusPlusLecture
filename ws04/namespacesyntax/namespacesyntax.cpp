namespace demo{
void foo(); //1
namespace subdemo{
void foo(){/*2*/}
} // subdemo
} // demo
namespace demo{
void bar(){
	foo(); //1
	subdemo::foo();//2
}
}
void demo::foo(){/*1*/} // definition
int main(){
	using ::demo::subdemo::foo;
	foo();//2
	demo::foo();//1
	demo::bar();
}
