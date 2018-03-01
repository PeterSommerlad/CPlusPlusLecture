#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

int main() {
  using std::cout;
  fs::path const p{"./Hallo"};
  cout << p << '\n';
  if (is_directory(p)) {
    cout << " DIR exists" << '\n';
    fs::remove(p);
  } else {
    cout << "creating dir " << p ;
    if (fs::create_directory(p))
      cout << " success";
    else
      cout << " failed";
    cout << '\n';
  }
}
