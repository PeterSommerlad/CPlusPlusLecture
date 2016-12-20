#ifndef SHOPPINGLIST_H_
#define SHOPPINGLIST_H_

#include <iosfwd>
#include <vector>
#include <memory>
using ShapePtr=std::shared_ptr<class Shape>;
void printShoppingList(std::vector<ShapePtr>, std::ostream&);

#endif /* SHOPPINGLIST_H_ */
