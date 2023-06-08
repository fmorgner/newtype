#ifndef NEWTYPE_CONCEPTS_HPP
#define NEWTYPE_CONCEPTS_HPP

#include <concepts>
#include <cstddef>
#include <functional>
#include <iosfwd>

namespace nt::concepts
{

  inline namespace arithmetic
  {

    template<typename SubjectType>
    concept addable = requires(SubjectType lhs, SubjectType rhs) {
      {
        lhs + rhs
      } -> std::same_as<SubjectType>;
    };

    template<typename SubjectType>
    concept nothrow_addable = requires(SubjectType lhs, SubjectType rhs) {
      requires addable<SubjectType>;
      {
        lhs + rhs
      } noexcept;
    };

    template<typename SubjectType>
    concept divisible = requires(SubjectType lhs, SubjectType rhs) {
      {
        lhs / rhs
      } -> std::same_as<SubjectType>;
    };

    template<typename SubjectType>
    concept nothrow_divisible = requires(SubjectType lhs, SubjectType rhs) {
      requires divisible<SubjectType>;
      {
        lhs / rhs
      } noexcept;
    };

    template<typename SubjectType>
    concept multipliable = requires(SubjectType lhs, SubjectType rhs) {
      {
        lhs * rhs
      } -> std::same_as<SubjectType>;
    };

    template<typename SubjectType>
    concept nothrow_multipliable = requires(SubjectType lhs, SubjectType rhs) {
      requires multipliable<SubjectType>;
      {
        lhs / rhs
      } noexcept;
    };

    template<typename SubjectType>
    concept subtractable = requires(SubjectType lhs, SubjectType rhs) {
      {
        lhs - rhs
      } -> std::same_as<SubjectType>;
    };

    template<typename SubjectType>
    concept nothrow_subtractable = requires(SubjectType lhs, SubjectType rhs) {
      requires subtractable<SubjectType>;
      {
        lhs - rhs
      } noexcept;
    };

  }  // namespace arithmetic

  inline namespace comparability
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
    concept less_than_comparable = requires(SubjectType lhs, SubjectType rhs) {
      {
        lhs < rhs
      } -> std::convertible_to<bool>;
    };

    template<typename SubjectType>
    concept nothrow_less_than_comparable = requires(SubjectType lhs, SubjectType rhs) {
      requires less_than_comparable<SubjectType>;
      {
        lhs < rhs
      } noexcept;
    };

    template<typename SubjectType>
    concept less_than_equal_comparable = requires(SubjectType lhs, SubjectType rhs) {
      {
        lhs <= rhs
      } -> std::convertible_to<bool>;
    };

    template<typename SubjectType>
    concept nothrow_less_than_equal_comparable = requires(SubjectType lhs, SubjectType rhs) {
      requires less_than_equal_comparable<SubjectType>;
      {
        lhs <= rhs
      } noexcept;
    };

    template<typename SubjectType>
    concept greater_than_comparable = requires(SubjectType lhs, SubjectType rhs) {
      {
        lhs > rhs
      } -> std::convertible_to<bool>;
    };

    template<typename SubjectType>
    concept nothrow_greater_than_comparable = requires(SubjectType lhs, SubjectType rhs) {
      requires greater_than_comparable<SubjectType>;
      {
        lhs > rhs
      } noexcept;
    };

    template<typename SubjectType>
    concept greater_than_equal_comparable = requires(SubjectType lhs, SubjectType rhs) {
      {
        lhs >= rhs
      } -> std::convertible_to<bool>;
    };

    template<typename SubjectType>
    concept nothrow_greater_than_equal_comparable = requires(SubjectType lhs, SubjectType rhs) {
      requires greater_than_equal_comparable<SubjectType>;
      {
        lhs >= rhs
      } noexcept;
    };

  }  // namespace comparability

  inline namespace iostreamable
  {

    template<typename SubjectType, typename CharType, typename StreamTraits>
    concept input_streamable = requires(SubjectType subject) {
      {
        std::declval<std::basic_istream<CharType, StreamTraits> &>() >> subject
      } -> std::same_as<std::basic_istream<CharType, StreamTraits> &>;
    };

    template<typename SubjectType, typename CharType, typename StreamTraits>
    concept nothrow_input_streamable = requires(SubjectType subject) {
      requires input_streamable<SubjectType, CharType, StreamTraits>;
      {
        std::declval<std::basic_istream<CharType, StreamTraits> &>() >> subject
      } noexcept;
    };

    template<typename SubjectType, typename CharType, typename StreamTraits>
    concept output_streamable = requires(SubjectType subject) {
      {
        std::declval<std::basic_ostream<CharType, StreamTraits> &>() << subject
      } -> std::same_as<std::basic_ostream<CharType, StreamTraits> &>;
    };

    template<typename SubjectType, typename CharType, typename StreamTraits>
    concept nothrow_output_streamable = requires(SubjectType subject) {
      requires output_streamable<SubjectType, CharType, StreamTraits>;
      {
        std::declval<std::basic_ostream<CharType, StreamTraits> &>() << subject
      } noexcept;
    };

  }  // namespace iostreamable

  inline namespace standard_extensions
  {

    template<typename SubjectType>
    concept hashable = requires(SubjectType subject) {
      {
        std::hash<SubjectType>{}(subject)
      } -> std::convertible_to<std::size_t>;
    };

  }

}  // namespace nt::concepts

#endif