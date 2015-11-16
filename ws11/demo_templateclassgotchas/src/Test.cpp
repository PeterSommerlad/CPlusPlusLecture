#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"

template <typename T>
struct parent {
	int foo() const { return 42; }
	static int const bar{43};
};

int foo() { return 1; }
double const bar{ 3.14};

template <typename T>
struct demogotchas : parent<T> {
	std::string demo()const {
		std::ostringstream result{};
		result << bar << " bar \n";
		result << this->bar << " this->bar \n";
		result << demogotchas::bar << " demogotchas::bar\n";
		result << foo() << " foo() \n";
		result << this->foo() << " this->foo() \n";
		return result.str();
	}
};


void demoInheritingClassTemplateNameResolutionProblem() {
	demogotchas<int> demo{};
	ASSERT_EQUAL(
"3.14 bar \n"
"43 this->bar \n"
"43 demogotchas::bar\n"
"1 foo() \n"
"42 this->foo() \n",demo.demo());

}

void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(demoInheritingClassTemplateNameResolutionProblem));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main(){
    runSuite();
    return 0;
}



