








struct donothingfunctor{
	void operator()()const{}
};

















int main(){
	donothingfunctor const f{};
	f();
	donothingfunctor{}();
}
