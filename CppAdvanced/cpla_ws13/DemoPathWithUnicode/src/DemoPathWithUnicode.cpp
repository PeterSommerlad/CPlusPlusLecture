#include <experimental/filesystem>
#include <iostream>
using namespace std;
namespace fs=std::experimental::filesystem;

int main(int argc, char **argv) {
	fs::path p{u8"./H\u00e4ll\u00f6"};
	cout << p << '\n';
	if (is_directory(p)){
			cout << " DIR exists" << '\n';
			fs::remove(p);
	}else{
		cout << "creating dir "<<p ;
		if (fs::create_directory(p))
			cout << " success";
		else
			cout << " failed";

		cout << '\n';
	}
}
