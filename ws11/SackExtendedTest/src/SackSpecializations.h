#ifndef SACKSPECIALIZATIONS_H_
#define SACKSPECIALIZATIONS_H_


template <typename T> class Sack; // forward declaration

template <typename T>
struct Sack<T*>
{
	~Sack()=delete;
};
//-----
#include <vector>
#include <string>
#include <stdexcept>
template <>
class Sack<char const *> {
	typedef std::vector<std::string> SackType;
	typedef SackType::size_type size_type;
	SackType theSack;
public:
	// no explicit ctor/dtor required
	bool empty() { return theSack.empty() ; }
	size_type size() { return theSack.size();}
	void putInto(char const *item) { theSack.push_back(item);}
	std::string getOut() {
		if (! size()) throw std::logic_error{"empty Sack"};
		std::string result=theSack.back();
		theSack.pop_back();
		return result;
	}
};
#endif /*SACKSPECIALIZATIONS_H_*/
