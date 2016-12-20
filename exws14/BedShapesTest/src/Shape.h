#ifndef SHAPE_H_
#define SHAPE_H_
#include <string>
#include <iosfwd>
class Shape {
public:
	Shape()=default;
	virtual ~Shape()=default;
	virtual unsigned int pegs() const=0;
	virtual double rope() const=0;
	virtual double seeds() const=0;
	virtual std::string name() const =0;
	void print(std::ostream &os)const;
};
inline std::ostream &operator<<(std::ostream &os,Shape const &s){
	s.print(os);
	return os;
}

#endif /* SHAPE_H_ */
