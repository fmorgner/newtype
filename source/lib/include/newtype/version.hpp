#ifndef NEWTYPE_VERSION_HPP
#define NEWTYPE_VERSION_HPP

namespace nt
{

  constexpr struct
  {
    int const major;
    int const minor;
    int const patch;

    char const * const name;
  } version{
      .major = 2,
      .minor = 0,
      .patch = 0,
      .name = "Brynn",
  };

}  // namespace nt

#endif