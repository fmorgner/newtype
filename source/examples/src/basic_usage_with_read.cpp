#include <newtype/derivable.hpp>
#include <newtype/deriving.hpp>
#include <newtype/newtype.hpp>

#include <iostream>

using Width = nt::new_type<unsigned int, struct width_tag, deriving(nt::Read)>;
using Height = nt::new_type<unsigned int, struct height_tag, deriving(nt::Read)>;
using Area = nt::new_type<unsigned int, struct area_tag, deriving(nt::Show)>;

struct Rectangle
{
  constexpr Rectangle(Width w, Height h)
      : width{w}
      , height{h}
  {
  }

  auto constexpr area() const noexcept -> Area
  {
    return {width.decay() * height.decay()};
  }

private:
  Width width;
  Height height;
};

int main()
{
  auto width = Width{};
  auto height = Height{};

  std::cin >> width >> height;

  auto rect = Rectangle{width, height};

  std::cout << rect.area() << '\n';
}