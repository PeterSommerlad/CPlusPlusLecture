#include<vector>
#include<string>

// (c) by Nicolai Josuttis, used with permission

std::vector<std::string> createAndInsert() {
	std::vector < std::string > coll;
	coll.reserve(3);
	std::string s("data");

	coll.push_back(s);

	coll.push_back(s + s);

	coll.push_back(s);

	return coll;
}

int main(int argc, char **argv) {
	std::vector<std::string> v;
	v = createAndInsert();
}

