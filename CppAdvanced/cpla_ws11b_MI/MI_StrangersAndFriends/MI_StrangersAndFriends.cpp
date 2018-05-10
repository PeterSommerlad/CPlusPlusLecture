#include <string>
#include <iostream>


class Appenzeller {
	std::string geheimrezept;
	friend void ChristophHollenstein(Appenzeller const & app);
};

void ChristophHollenstein(Appenzeller const & app) {
	std::cout << app.geheimrezept << std::endl;
}

void UweOchsenknecht(Appenzeller const & app) {
	std::cout << app.geheimrezept << std::endl;
}

int main(int argc, char **argv) {

}
