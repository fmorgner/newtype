#ifndef NEWTYPE_CONCEPTS_HPP
#define NEWTYPE_CONCEPTS_HPP

#include <concepts>
#include <cstddef>
#include <functional>

namespace nt::concepts
{
  template<typename SubjectType>
  concept hashable = requires(SubjectType subject) {
    {
      std::hash<SubjectType>{}(subject)
    } -> std::convertible_to<std::size_t>;
  };

}  // namespace nt::concepts

#endif