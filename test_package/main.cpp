#include <newtype/newtype.hpp>

#include <iostream>

using Integer = nt::new_type<int, struct IntegerTag, deriving(nt::Show)>;

auto main() -> int
{
  auto n = Integer{42};
  std::cout << "n == " << n.decay() << '\n';
}