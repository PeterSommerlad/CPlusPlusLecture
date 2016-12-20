#ifndef BEDFACTORY_H_
#define BEDFACTORY_H_
#include <memory>
#include <iosfwd>
#include <vector>
using ShapePtr=std::shared_ptr<class Shape>;
ShapePtr makeBed(std::istream &in);

std::vector<ShapePtr> createAllBeds(std::istream &in);
#endif /* BEDFACTORY_H_ */
