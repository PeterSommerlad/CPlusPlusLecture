#include <memory>
#include <array>
#include <utility>

using BigObject = std::array<int, 1000000>;

struct ContainerForBigObject {
  ContainerForBigObject()
      : resource{std::make_unique<BigObject>()}
  {}

  ContainerForBigObject(ContainerForBigObject const & other)
      : resource{std::make_unique<BigObject>(*other.resource)} {}

  ContainerForBigObject(ContainerForBigObject && other)
      : resource{std::move(other.resource)}
  {}

  ContainerForBigObject & operator=(ContainerForBigObject const & other) {
    resource = std::make_unique<BigObject>(*other.resource);
    return *this;
  }

  ContainerForBigObject & operator=(ContainerForBigObject && other) {
    std::swap(resource, other.resource);
    //resource = std::move(other.resource) is possible too
    return *this;
  }

private:
  std::unique_ptr<BigObject> resource;
};


int main() {
	ContainerForBigObject cbo{};
	ContainerForBigObject cbo_copy{cbo};
	ContainerForBigObject cbo_moved{std::move(cbo)};
	cbo = cbo_moved;
	cbo_moved = std::move(cbo_copy);
}
