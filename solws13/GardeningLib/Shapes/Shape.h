#ifndef SHAPE_H_
#define SHAPE_H_

#include <iosfwd>
#include <string>

namespace Gardening {

struct Shape {
	static const double pi;
	static const double seedPerSquareMeter;

	virtual ~Shape() = default;

	void print(std::ostream & out) const;

	virtual unsigned pegs() const = 0;
	virtual double ropes() const = 0;
	virtual double seeds() const = 0;

protected:
	explicit Shape(std::string const & name);

private:
	std::string const name;
};

}

#endif /* SHAPE_H_ */
