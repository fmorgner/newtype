#ifndef NEWTYPE_CONCEPTS_HPP
#define NEWTYPE_CONCEPTS_HPP

#include <concepts>
#include <cstddef>
#include <functional>

namespace nt::concepts
{

  template<typename SubjectType>
  concept equality_comparable = requires(SubjectType lhs, SubjectType rhs) {
    {
      lhs == rhs
    } -> std::convertible_to<bool>;
  };

  template<typename SubjectType>
  concept nothrow_equality_comparable = requires(SubjectType lhs, SubjectType rhs) {
    requires equality_comparable<SubjectType>;
    {
      lhs == rhs
    } noexcept;
  };

  template<typename SubjectType>
  concept inequality_comparable = requires(SubjectType lhs, SubjectType rhs) {
    {
      lhs != rhs
    } -> std::convertible_to<bool>;
  };

  template<typename SubjectType>
  concept nothrow_inequality_comparable = requires(SubjectType lhs, SubjectType rhs) {
    requires inequality_comparable<SubjectType>;
    {
      lhs != rhs
    } noexcept;
  };

  template<typename SubjectType>
  concept hashable = requires(SubjectType subject) {
    {
      std::hash<SubjectType>{}(subject)
    } -> std::convertible_to<std::size_t>;
  };

}  // namespace nt::concepts

#endif