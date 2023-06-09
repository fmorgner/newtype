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

  inline namespace compound_arithmetic
  {
    template<typename SubjectType>
    concept compound_addable = requires(SubjectType & lhs, SubjectType const & rhs) {
      {
        lhs += rhs
      } -> std::convertible_to<SubjectType &>;
    };

    template<typename SubjectType>
    concept nothrow_compound_addable = requires(SubjectType & lhs, SubjectType const & rhs) {
      requires compound_addable<SubjectType>;
      {
        lhs += rhs
      } noexcept;
    };

    template<typename SubjectType>
    concept compound_divisible = requires(SubjectType & lhs, SubjectType const & rhs) {
      {
        lhs /= rhs
      } -> std::convertible_to<SubjectType &>;
    };

    template<typename SubjectType>
    concept nothrow_compound_divisible = requires(SubjectType & lhs, SubjectType const & rhs) {
      requires compound_divisible<SubjectType>;
      {
        lhs /= rhs
      } noexcept;
    };

    template<typename SubjectType>
    concept compound_multipliable = requires(SubjectType & lhs, SubjectType const & rhs) {
      {
        lhs *= rhs
      } -> std::convertible_to<SubjectType &>;
    };

    template<typename SubjectType>
    concept nothrow_compound_multipliable = requires(SubjectType & lhs, SubjectType const & rhs) {
      requires compound_multipliable<SubjectType>;
      {
        lhs *= rhs
      } noexcept;
    };

    template<typename SubjectType>
    concept compound_subtractable = requires(SubjectType & lhs, SubjectType const & rhs) {
      {
        lhs -= rhs
      } -> std::convertible_to<SubjectType &>;
    };

    template<typename SubjectType>
    concept nothrow_compound_subtractable = requires(SubjectType & lhs, SubjectType const & rhs) {
      requires compound_subtractable<SubjectType>;
      {
        lhs -= rhs
      } noexcept;
    };
  }  // namespace compound_arithmetic

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

  inline namespace iterable
  {

    template<typename SubjectType>
    concept free_begin = requires(SubjectType & subject) {
      typename SubjectType::iterator;
      {
        begin(subject)
      } -> std::same_as<typename SubjectType::iterator>;
    };

    template<typename SubjectType>
    concept const_free_begin = requires(SubjectType const & subject) {
      typename SubjectType::const_iterator;
      {
        begin(subject)
      } -> std::same_as<typename SubjectType::const_iterator>;
    };

    template<typename SubjectType>
    concept member_begin = requires(SubjectType & subject) {
      typename SubjectType::iterator;
      {
        subject.begin()
      } -> std::same_as<typename SubjectType::iterator>;
    };

    template<typename SubjectType>
    concept const_member_begin = requires(SubjectType const & subject) {
      typename SubjectType::const_iterator;
      {
        subject.begin()
      } -> std::same_as<typename SubjectType::const_iterator>;
    };

    template<typename SubjectType>
    concept beginnable = free_begin<SubjectType> || member_begin<SubjectType>;

    template<typename SubjectType>
    concept const_beginnable = const_free_begin<SubjectType> || const_member_begin<SubjectType>;

    template<typename SubjectType>
    concept free_cbegin = requires(SubjectType const & subject) {
      typename SubjectType::const_iterator;
      {
        cbegin(subject)
      } -> std::same_as<typename SubjectType::const_iterator>;
    };

    template<typename SubjectType>
    concept member_cbegin = requires(SubjectType const & subject) {
      typename SubjectType::const_iterator;
      {
        subject.cbegin()
      } -> std::same_as<typename SubjectType::const_iterator>;
    };

    template<typename SubjectType>
    concept cbeginnable = free_cbegin<SubjectType> || member_cbegin<SubjectType>;

    template<typename SubjectType>
    concept free_rbegin = requires(SubjectType & subject) {
      typename SubjectType::reverse_iterator;
      {
        rbegin(subject)
      } -> std::same_as<typename SubjectType::reverse_iterator>;
    };

    template<typename SubjectType>
    concept const_free_rbegin = requires(SubjectType const & subject) {
      typename SubjectType::const_reverse_iterator;
      {
        rbegin(subject)
      } -> std::same_as<typename SubjectType::const_reverse_iterator>;
    };

    template<typename SubjectType>
    concept member_rbegin = requires(SubjectType & subject) {
      typename SubjectType::reverse_iterator;
      {
        subject.rbegin()
      } -> std::same_as<typename SubjectType::reverse_iterator>;
    };

    template<typename SubjectType>
    concept const_member_rbegin = requires(SubjectType const & subject) {
      typename SubjectType::const_reverse_iterator;
      {
        subject.rbegin()
      } -> std::same_as<typename SubjectType::const_reverse_iterator>;
    };

    template<typename SubjectType>
    concept rbeginnable = free_rbegin<SubjectType> || member_rbegin<SubjectType>;

    template<typename SubjectType>
    concept const_rbeginnable = const_free_rbegin<SubjectType> || const_member_rbegin<SubjectType>;

    template<typename SubjectType>
    concept free_crbegin = requires(SubjectType const & subject) {
      typename SubjectType::const_reverse_iterator;
      {
        crbegin(subject)
      } -> std::same_as<typename SubjectType::const_reverse_iterator>;
    };

    template<typename SubjectType>
    concept member_crbegin = requires(SubjectType const & subject) {
      typename SubjectType::const_reverse_iterator;
      {
        subject.crbegin()
      } -> std::same_as<typename SubjectType::const_reverse_iterator>;
    };

    template<typename SubjectType>
    concept crbeginnable = free_crbegin<SubjectType> || member_crbegin<SubjectType>;

    template<typename SubjectType>
    concept free_end = requires(SubjectType & subject) {
      typename SubjectType::iterator;
      {
        end(subject)
      } -> std::same_as<typename SubjectType::iterator>;
    };

    template<typename SubjectType>
    concept const_free_end = requires(SubjectType const & subject) {
      typename SubjectType::const_iterator;
      {
        end(subject)
      } -> std::same_as<typename SubjectType::const_iterator>;
    };

    template<typename SubjectType>
    concept member_end = requires(SubjectType & subject) {
      typename SubjectType::iterator;
      {
        subject.end()
      } -> std::same_as<typename SubjectType::iterator>;
    };

    template<typename SubjectType>
    concept const_member_end = requires(SubjectType const & subject) {
      typename SubjectType::const_iterator;
      {
        subject.end()
      } -> std::same_as<typename SubjectType::const_iterator>;
    };

    template<typename SubjectType>
    concept endable = free_end<SubjectType> || member_end<SubjectType>;

    template<typename SubjectType>
    concept const_endable = const_free_end<SubjectType> || const_member_end<SubjectType>;

    template<typename SubjectType>
    concept free_cend = requires(SubjectType const & subject) {
      typename SubjectType::const_iterator;
      {
        cend(subject)
      } -> std::same_as<typename SubjectType::const_iterator>;
    };

    template<typename SubjectType>
    concept member_cend = requires(SubjectType const & subject) {
      typename SubjectType::const_iterator;
      {
        subject.cend()
      } -> std::same_as<typename SubjectType::const_iterator>;
    };

    template<typename SubjectType>
    concept cendable = free_cend<SubjectType> || member_cend<SubjectType>;

    template<typename SubjectType>
    concept free_rend = requires(SubjectType & subject) {
      typename SubjectType::reverse_iterator;
      {
        rend(subject)
      } -> std::same_as<typename SubjectType::reverse_iterator>;
    };

    template<typename SubjectType>
    concept const_free_rend = requires(SubjectType const & subject) {
      typename SubjectType::const_reverse_iterator;
      {
        rend(subject)
      } -> std::same_as<typename SubjectType::const_reverse_iterator>;
    };

    template<typename SubjectType>
    concept member_rend = requires(SubjectType & subject) {
      typename SubjectType::reverse_iterator;
      {
        subject.rend()
      } -> std::same_as<typename SubjectType::reverse_iterator>;
    };

    template<typename SubjectType>
    concept const_member_rend = requires(SubjectType const & subject) {
      typename SubjectType::const_reverse_iterator;
      {
        subject.rend()
      } -> std::same_as<typename SubjectType::const_reverse_iterator>;
    };

    template<typename SubjectType>
    concept rendable = free_rend<SubjectType> || member_rend<SubjectType>;

    template<typename SubjectType>
    concept const_rendable = const_free_rend<SubjectType> || const_member_rend<SubjectType>;

    template<typename SubjectType>
    concept free_crend = requires(SubjectType const & subject) {
      typename SubjectType::const_reverse_iterator;
      {
        crend(subject)
      } -> std::same_as<typename SubjectType::const_reverse_iterator>;
    };

    template<typename SubjectType>
    concept member_crend = requires(SubjectType const & subject) {
      typename SubjectType::const_reverse_iterator;
      {
        subject.crend()
      } -> std::same_as<typename SubjectType::const_reverse_iterator>;
    };

    template<typename SubjectType>
    concept crendable = free_crend<SubjectType> || member_crend<SubjectType>;
  }  // namespace iterable

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