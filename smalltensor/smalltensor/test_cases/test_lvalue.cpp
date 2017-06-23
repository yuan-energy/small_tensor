#include <iostream>
#include <type_traits>
using namespace std;
struct test {
  test() {
      std::cout << "constructing" << std::endl;
  }
  ~test() {
      std::cout << "destroy" << std::endl;
  }
};
 
// template <typename T>
// constexpr T &lvalue(T &&r) noexcept { return r; }

template <typename T>
inline constexpr std::remove_reference_t<T> &lvalue(T &&r) noexcept {
    return static_cast<std::remove_reference_t<T> &>(r);
}

int main()
{
  int ten = 10;
  test& ref = lvalue(test());
  std::cout << "now use" << std::endl;
  test apple;
  apple = ref;
  // using ref is UB
}