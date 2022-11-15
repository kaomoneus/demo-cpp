#include "my_function.h"
#include "utils.h"

template<typename T>
struct framework {
  static constexpr bool valid = false;
  framework(T) {};
  int run() { return -1; }
};

template <typename R, typename A1, typename A2>
struct framework<R(A1,A2)> {
    using RetT = R;
    using Arg1T = A1;
    using Arg2T = A2;
    static constexpr bool valid = true;

    function<R(A1,A2)> f;

    framework(function<R(A1,A2)> f) : f(f) {}

    int run() {
      static_assert(
          is_arg_supported<Arg1T>(),
          "First argument of 'foo' is not supported."
      );
      static_assert(
          is_arg_supported<Arg2T>(),
          "Second argument of 'foo' is not supported."
      );

      Arg1T a = input<Arg1T>("First arg");
      Arg2T b = input<Arg2T>("Second arg");

      cout << "Result: " << fun(a, b) << "\n";
      return 0;
    }
};

int main() {
  static_assert(
      framework<decltype(fun)>::valid,
      "Wrong 'fun' format. Should be: <ret type> fun(arg1, arg2)"
  );
  return framework<decltype(fun)>(fun).run();
}