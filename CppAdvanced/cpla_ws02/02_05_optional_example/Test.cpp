#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <optional>
#include <fstream>
#include <string>
#include <utility>
#include <experimental/filesystem>

std::optional<std::ifstream> openFile(std::string const name) {
  std::ifstream file{name};
  if (file.is_open()) return std::move(file);
  return{};
}

void testNonExistingFile() {
  auto nofile = openFile("gugus.txt");
  ASSERTM("file shouldn't be opened", !nofile);
}

void testExistingFile(){
  std::string const name{"hello.txt"};
  std::string const writtencontent{"hello, world"};
  std::ofstream of{name};
  of << writtencontent <<'\n';
  of.close();
  {
    auto somefile = openFile(name);
    ASSERTM("file should be opened", !!somefile);
    std::string content{};
    std::getline(*somefile, content);
    ASSERT_EQUAL(writtencontent, content);
  }
  std::experimental::filesystem::remove(name);
}


void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(testNonExistingFile));
	s.push_back(CUTE(testExistingFile));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}


