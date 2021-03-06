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
      .major = 1,
      .minor = 1,
      .patch = 0,
      .name = "Anastasia",
  };

}  // namespace nt

#endif