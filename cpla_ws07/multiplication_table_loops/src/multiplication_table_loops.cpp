#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	for (int i=1; i <=20; ++i){
		cout << '\n';
		for (int j=1; j <=20; ++j)
			cout << setw(4) << j*i ;
	}
	cout << '\n';
}
