#ifndef SWITCH_H_
#define SWITCH_H_
#include <iosfwd>
class Switch {
public:
	Switch();
	void PushButton() ;
	void print(std::ostream &) const;
private:
	enum class togglestate:unsigned char;
	togglestate state;
};

inline
std::ostream & operator<<(std::ostream& out,Switch const &s){
	s.print(out);
	return out;
}


#endif /* SWITCH_H_ */
