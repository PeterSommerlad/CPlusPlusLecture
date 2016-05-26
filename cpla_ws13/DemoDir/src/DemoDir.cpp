#include <experimental/filesystem>
#include <iostream>
using namespace std;
namespace fs=std::experimental::filesystem;

int main(int argc, char **argv) {
	fs::path dir{"./"};
	if (argc >1)
		dir=argv[1];
	for (auto p:fs::directory_iterator(dir)){
		cout << p << '\t';
		if (is_directory(p)){
			cout << "DIR";
		}else
		try{
			auto sz=fs::file_size(p); // no file sizes for directory
			if (sz > 1024)
				cout << sz/1024 << " kB";
			else
				cout << sz << " Bytes";
		} catch(...){
			cout << "no file size available";
		}
		cout << '\n';
	}
}
