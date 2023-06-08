#ifndef NEWTYPE_IMPL_TYPE_TRAITS_EXTENSIONS_HPP
#define NEWTYPE_IMPL_TYPE_TRAITS_EXTENSIONS_HPP

#include "newtype/version.hpp"

#include <cstddef>
#include <functional>
#include <iosfwd>
#include <type_traits>

namespace nt::impl
{

  inline namespace equality_comparable
  {

    template<typename T, typename = void>
    struct is_equality_comparable : std::false_type
    {
    };

    template<typename T>
    struct is_equality_comparable<T, std::void_t<decltype(std::declval<T const &>() == std::declval<T const &>())>> : std::true_type
    {
    };

    template<typename T>
    auto constexpr is_equality_comparable_v = is_equality_comparable<T>::value;

    template<typename T, typename = void>
    struct is_nothrow_equality_comparable : std::false_type
    {
    };

    template<typename T>
    struct is_nothrow_equality_comparable<T, std::void_t<decltype(std::declval<T const &>() == std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() == std::declval<T const &>())>
    {
    };

    template<typename T>
    auto constexpr is_nothrow_equality_comparable_v = is_nothrow_equality_comparable<T>::value;

    template<typename T, typename = void>
    struct is_inequality_comparable : std::false_type
    {
    };

    template<typename T>
    struct is_inequality_comparable<T, std::void_t<decltype(std::declval<T const &>() != std::declval<T const &>())>> : std::true_type
    {
    };

    template<typename T>
    auto constexpr is_inequality_comparable_v = is_inequality_comparable<T>::value;

    template<typename T, typename = void>
    struct is_nothrow_inequality_comparable : std::false_type
    {
    };

    template<typename T>
    struct is_nothrow_inequality_comparable<T, std::void_t<decltype(std::declval<T const &>() != std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() != std::declval<T const &>())>
    {
    };

    template<typename T>
    auto constexpr is_nothrow_inequality_comparable_v = is_nothrow_inequality_comparable<T>::value;

  }  // namespace equality_comparable

  inline namespace relationally_comparable
  {

    template<typename T, typename = void>
    struct is_less_than_comparable : std::false_type
    {
    };

    template<typename T>
    struct is_less_than_comparable<T, std::void_t<decltype(std::declval<T const &>() < std::declval<T const &>())>> : std::true_type
    {
    };

    template<typename T>
    auto constexpr is_less_than_comparable_v = is_less_than_comparable<T>::value;

    template<typename T, typename = void>
    struct is_nothrow_less_than_comparable : std::false_type
    {
    };

    template<typename T>
    struct is_nothrow_less_than_comparable<T, std::void_t<decltype(std::declval<T const &>() < std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() < std::declval<T const &>())>
    {
    };

    template<typename T>
    auto constexpr is_nothrow_less_than_comparable_v = is_nothrow_less_than_comparable<T>::value;

    template<typename T, typename = void>
    struct is_greater_than_comparable : std::false_type
    {
    };

    template<typename T>
    struct is_greater_than_comparable<T, std::void_t<decltype(std::declval<T const &>() > std::declval<T const &>())>> : std::true_type
    {
    };

    template<typename T>
    auto constexpr is_greater_than_comparable_v = is_greater_than_comparable<T>::value;

    template<typename T, typename = void>
    struct is_nothrow_greater_than_comparable : std::false_type
    {
    };

    template<typename T>
    struct is_nothrow_greater_than_comparable<T, std::void_t<decltype(std::declval<T const &>() > std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() > std::declval<T const &>())>
    {
    };

    template<typename T>
    auto constexpr is_nothrow_greater_than_comparable_v = is_nothrow_greater_than_comparable<T>::value;

    template<typename T, typename = void>
    struct is_less_than_equal_to_comparable : std::false_type
    {
    };

    template<typename T>
    struct is_less_than_equal_to_comparable<T, std::void_t<decltype(std::declval<T const &>() <= std::declval<T const &>())>> : std::true_type
    {
    };

    template<typename T>
    auto constexpr is_less_than_equal_to_comparable_v = is_less_than_equal_to_comparable<T>::value;

    template<typename T, typename = void>
    struct is_nothrow_less_than_equal_to_comparable : std::false_type
    {
    };

    template<typename T>
    struct is_nothrow_less_than_equal_to_comparable<T, std::void_t<decltype(std::declval<T const &>() <= std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() <= std::declval<T const &>())>
    {
    };

    template<typename T>
    auto constexpr is_nothrow_less_than_equal_to_comparable_v = is_nothrow_less_than_equal_to_comparable<T>::value;

    template<typename T, typename = void>
    struct is_greater_than_equal_to_comparable : std::false_type
    {
    };

    template<typename T>
    struct is_greater_than_equal_to_comparable<T, std::void_t<decltype(std::declval<T const &>() >= std::declval<T const &>())>>
        : std::true_type
    {
    };

    template<typename T>
    auto constexpr is_greater_than_equal_to_comparable_v = is_greater_than_equal_to_comparable<T>::value;

    template<typename T, typename = void>
    struct is_nothrow_greater_than_equal_to_comparable : std::false_type
    {
    };

    template<typename T>
    struct is_nothrow_greater_than_equal_to_comparable<T, std::void_t<decltype(std::declval<T const &>() >= std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() >= std::declval<T const &>())>
    {
    };

    template<typename T>
    auto constexpr is_nothrow_greater_than_equal_to_comparable_v = is_nothrow_greater_than_equal_to_comparable<T>::value;
  }  // namespace relationally_comparable

  inline namespace iostreamable
  {

    template<typename StreamType, typename T, typename = void>
    struct is_output_streamable : std::false_type
    {
    };

    template<typename StreamType, typename T>
    struct is_output_streamable<StreamType, T, std::void_t<decltype(std::declval<StreamType &>() << std::declval<T const &>())>>
        : std::true_type
    {
    };

    template<typename StreamType, typename T>
    auto constexpr is_output_streamable_v = is_output_streamable<StreamType, T>::value;

    template<typename StreamType, typename T, typename = void>
    struct is_nothrow_output_streamable : std::false_type
    {
    };

    template<typename StreamType, typename T>
    struct is_nothrow_output_streamable<StreamType, T, std::void_t<decltype(std::declval<StreamType &>() << std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<StreamType &>() << std::declval<T const &>())>
    {
    };

    template<typename StreamType, typename T>
    auto constexpr is_nothrow_output_streamable_v = is_nothrow_output_streamable<StreamType, T>::value;

    template<typename StreamType, typename T, typename = void>
    struct is_input_streamable : std::false_type
    {
    };

    template<typename StreamType, typename T>
    struct is_input_streamable<StreamType, T, std::void_t<decltype(std::declval<StreamType &>() >> std::declval<T &>())>> : std::true_type
    {
    };

    template<typename StreamType, typename T>
    auto constexpr is_input_streamable_v = is_input_streamable<StreamType, T>::value;

    template<typename StreamType, typename T, typename = void>
    struct is_nothrow_input_streamable : std::false_type
    {
    };

    template<typename StreamType, typename T>
    struct is_nothrow_input_streamable<StreamType, T, std::void_t<decltype(std::declval<StreamType &>() >> std::declval<T &>())>>
        : std::bool_constant<noexcept(std::declval<StreamType &>() >> std::declval<T &>())>
    {
    };

    template<typename StreamType, typename T>
    auto constexpr is_nothrow_input_streamable_v = is_nothrow_input_streamable<StreamType, T>::value;

  }  // namespace iostreamable

  inline namespace arithmetic
  {

    template<typename T, typename = void>
    struct is_addable : std::false_type
    {
    };

    template<typename T>
    struct is_addable<T, std::void_t<decltype(std::declval<T const &>() + std::declval<T const &>())>> : std::true_type
    {
    };

    template<typename T>
    auto constexpr is_addable_v = is_addable<T>::value;

    template<typename T, typename = void>
    struct is_nothrow_addable : std::false_type
    {
    };

    template<typename T>
    struct is_nothrow_addable<T, std::void_t<decltype(std::declval<T const &>() + std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() + std::declval<T const &>())>
    {
    };

    template<typename T>
    auto constexpr is_nothrow_addable_v = is_nothrow_addable<T>::value;

    template<typename T, typename = void>
    struct is_subtractable : std::false_type
    {
    };

    template<typename T>
    struct is_subtractable<T, std::void_t<decltype(std::declval<T const &>() - std::declval<T const &>())>> : std::true_type
    {
    };

    template<typename T>
    auto constexpr is_subtractable_v = is_subtractable<T>::value;

    template<typename T, typename = void>
    struct is_nothrow_subtractable : std::false_type
    {
    };

    template<typename T>
    struct is_nothrow_subtractable<T, std::void_t<decltype(std::declval<T const &>() - std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() - std::declval<T const &>())>
    {
    };

    template<typename T>
    auto constexpr is_nothrow_subtractable_v = is_nothrow_subtractable<T>::value;

    template<typename T, typename = void>
    struct is_multipliable : std::false_type
    {
    };

    template<typename T>
    struct is_multipliable<T, std::void_t<decltype(std::declval<T const &>() * std::declval<T const &>())>> : std::true_type
    {
    };

    template<typename T>
    auto constexpr is_multipliable_v = is_multipliable<T>::value;

    template<typename T, typename = void>
    struct is_nothrow_multipliable : std::false_type
    {
    };

    template<typename T>
    struct is_nothrow_multipliable<T, std::void_t<decltype(std::declval<T const &>() * std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() * std::declval<T const &>())>
    {
    };

    template<typename T>
    auto constexpr is_nothrow_multipliable_v = is_nothrow_multipliable<T>::value;

    template<typename T, typename = void>
    struct is_dividable : std::false_type
    {
    };

    template<typename T>
    struct is_dividable<T, std::void_t<decltype(std::declval<T const &>() / std::declval<T const &>())>> : std::true_type
    {
    };

    template<typename T>
    auto constexpr is_dividable_v = is_dividable<T>::value;

    template<typename T, typename = void>
    struct is_nothrow_dividable : std::false_type
    {
    };

    template<typename T>
    struct is_nothrow_dividable<T, std::void_t<decltype(std::declval<T const &>() / std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() / std::declval<T const &>())>
    {
    };

    template<typename T>
    auto constexpr is_nothrow_dividable_v = is_nothrow_dividable<T>::value;

  }  // namespace arithmetic

  inline namespace compound_arithmetic
  {

    template<typename T, typename = void>
    struct is_add_assignable : std::false_type
    {
    };

    template<typename T>
    struct is_add_assignable<T, std::void_t<decltype(std::declval<T &>() += std::declval<T const &>())>> : std::true_type
    {
    };

    template<typename T>
    auto constexpr is_add_assignable_v = is_add_assignable<T>::value;

    template<typename T, typename = void>
    struct is_nothrow_add_assignable : std::false_type
    {
    };

    template<typename T>
    struct is_nothrow_add_assignable<T, std::void_t<decltype(std::declval<T &>() += std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T &>() += std::declval<T const &>())>
    {
    };

    template<typename T>
    auto constexpr is_nothrow_add_assignable_v = is_nothrow_add_assignable<T>::value;

    template<typename T, typename = void>
    struct is_subtract_assignable : std::false_type
    {
    };

    template<typename T>
    struct is_subtract_assignable<T, std::void_t<decltype(std::declval<T &>() -= std::declval<T const &>())>> : std::true_type
    {
    };

    template<typename T>
    auto constexpr is_subtract_assignable_v = is_subtract_assignable<T>::value;

    template<typename T, typename = void>
    struct is_nothrow_subtract_assignable : std::false_type
    {
    };

    template<typename T>
    struct is_nothrow_subtract_assignable<T, std::void_t<decltype(std::declval<T &>() -= std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T &>() -= std::declval<T const &>())>
    {
    };

    template<typename T>
    auto constexpr is_nothrow_subtract_assignable_v = is_nothrow_subtract_assignable<T>::value;

    template<typename T, typename = void>
    struct is_multiply_assignable : std::false_type
    {
    };

    template<typename T>
    struct is_multiply_assignable<T, std::void_t<decltype(std::declval<T &>() *= std::declval<T const &>())>> : std::true_type
    {
    };

    template<typename T>
    auto constexpr is_multiply_assignable_v = is_multiply_assignable<T>::value;

    template<typename T, typename = void>
    struct is_nothrow_multiply_assignable : std::false_type
    {
    };

    template<typename T>
    struct is_nothrow_multiply_assignable<T, std::void_t<decltype(std::declval<T &>() *= std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T &>() *= std::declval<T const &>())>
    {
    };

    template<typename T>
    auto constexpr is_nothrow_multiply_assignable_v = is_nothrow_multiply_assignable<T>::value;

    template<typename T, typename = void>
    struct is_divide_assignable : std::false_type
    {
    };

    template<typename T>
    struct is_divide_assignable<T, std::void_t<decltype(std::declval<T &>() /= std::declval<T const &>())>> : std::true_type
    {
    };

    template<typename T>
    auto constexpr is_divide_assignable_v = is_divide_assignable<T>::value;

    template<typename T, typename = void>
    struct is_nothrow_divide_assignable : std::false_type
    {
    };

    template<typename T>
    struct is_nothrow_divide_assignable<T, std::void_t<decltype(std::declval<T &>() /= std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T &>() /= std::declval<T const &>())>
    {
    };

    template<typename T>
    auto constexpr is_nothrow_divide_assignable_v = is_nothrow_divide_assignable<T>::value;

  }  // namespace compound_arithmetic

  inline namespace iterable_begin
  {
    template<typename T, typename = void>
    struct has_free_begin : std::false_type
    {
    };

    template<typename T>
    struct has_free_begin<T, std::void_t<decltype(begin(std::declval<T &>()))>>
        : std::is_same<typename T::iterator, std::remove_cvref_t<decltype(begin(std::declval<T &>()))>>
    {
    };

    template<typename T>
    struct has_free_begin<T const, std::void_t<decltype(begin(std::declval<T const &>()))>>
        : std::is_same<typename T::const_iterator, std::remove_cvref_t<decltype(begin(std::declval<T const &>()))>>
    {
    };

    template<typename T>
    auto constexpr has_free_begin_v = has_free_begin<T>::value;

    template<typename T, typename = void>
    struct has_member_begin : std::false_type
    {
    };

    template<typename T>
    struct has_member_begin<T, std::void_t<decltype(std::declval<T &>().begin())>>
        : std::is_same<typename T::iterator, std::remove_cvref_t<decltype(std::declval<T &>().begin())>>
    {
    };

    template<typename T>
    struct has_member_begin<T const, std::void_t<decltype(std::declval<T const &>().begin())>>
        : std::is_same<typename T::const_iterator, std::remove_cvref_t<decltype(std::declval<T const &>().begin())>>
    {
    };

    template<typename T>
    auto constexpr has_member_begin_v = has_member_begin<T>::value;

    template<typename T>
    struct has_begin : std::disjunction<has_free_begin<T>, has_member_begin<T>>
    {
    };

    template<typename T>
    auto constexpr has_begin_v = has_begin<T>::value;
  }  // namespace iterable_begin

  inline namespace iterable_cbegin
  {
    template<typename T, typename = void>
    struct has_free_cbegin : std::false_type
    {
    };

    template<typename T>
    struct has_free_cbegin<T, std::void_t<decltype(cbegin(std::declval<T const &>()))>>
        : std::is_same<typename T::const_iterator, std::remove_cvref_t<decltype(cbegin(std::declval<T const &>()))>>
    {
    };

    template<typename T>
    auto constexpr has_free_cbegin_v = has_free_cbegin<T>::value;

    template<typename T, typename = void>
    struct has_member_cbegin : std::false_type
    {
    };

    template<typename T>
    struct has_member_cbegin<T, std::void_t<decltype(std::declval<T const &>().cbegin())>>
        : std::is_same<typename T::const_iterator, decltype(std::declval<T const &>().cbegin())>
    {
    };

    template<typename T>
    auto constexpr has_member_cbegin_v = has_member_cbegin<T>::value;

    template<typename T>
    struct has_cbegin : std::disjunction<has_free_cbegin<T>, has_member_cbegin<T>>
    {
    };

    template<typename T>
    auto constexpr has_cbegin_v = has_cbegin<T>::value;
  }  // namespace iterable_cbegin

  inline namespace iterable_rbegin
  {
    template<typename T, typename = void>
    struct has_free_rbegin : std::false_type
    {
    };

    template<typename T>
    struct has_free_rbegin<T, std::void_t<decltype(rbegin(std::declval<T &>()))>>
        : std::is_same<typename T::reverse_iterator, std::remove_cvref_t<decltype(rbegin(std::declval<T &>()))>>
    {
    };

    template<typename T>
    struct has_free_rbegin<T const, std::void_t<decltype(rbegin(std::declval<T const &>()))>>
        : std::is_same<typename T::const_reverse_iterator, std::remove_cvref_t<decltype(rbegin(std::declval<T const &>()))>>
    {
    };

    template<typename T>
    auto constexpr has_free_rbegin_v = has_free_rbegin<T>::value;

    template<typename T, typename = void>
    struct has_member_rbegin : std::false_type
    {
    };

    template<typename T>
    struct has_member_rbegin<T, std::void_t<decltype(std::declval<T &>().rbegin())>>
        : std::is_same<typename T::reverse_iterator, std::remove_cvref_t<decltype(std::declval<T &>().rbegin())>>
    {
    };

    template<typename T>
    struct has_member_rbegin<T const, std::void_t<decltype(std::declval<T const &>().rbegin())>>
        : std::is_same<typename T::const_reverse_iterator, std::remove_cvref_t<decltype(std::declval<T const &>().rbegin())>>
    {
    };

    template<typename T>
    auto constexpr has_member_rbegin_v = has_member_rbegin<T>::value;

    template<typename T>
    struct has_rbegin : std::disjunction<has_free_rbegin<T>, has_member_rbegin<T>>
    {
    };

    template<typename T>
    auto constexpr has_rbegin_v = has_rbegin<T>::value;
  }  // namespace iterable_rbegin

  inline namespace iterable_crbegin
  {
    template<typename T, typename = void>
    struct has_free_crbegin : std::false_type
    {
    };

    template<typename T>
    struct has_free_crbegin<T, std::void_t<decltype(crbegin(std::declval<T const &>()))>>
        : std::is_same<typename T::const_reverse_iterator, std::remove_cvref_t<decltype(crbegin(std::declval<T const &>()))>>
    {
    };

    template<typename T>
    auto constexpr has_free_crbegin_v = has_free_crbegin<T>::value;

    template<typename T, typename = void>
    struct has_member_crbegin : std::false_type
    {
    };

    template<typename T>
    struct has_member_crbegin<T, std::void_t<decltype(std::declval<T const &>().crbegin())>>
        : std::is_same<typename T::const_reverse_iterator, std::remove_cvref_t<decltype(std::declval<T const &>().crbegin())>>
    {
    };

    template<typename T>
    auto constexpr has_member_crbegin_v = has_member_crbegin<T>::value;

    template<typename T>
    struct has_crbegin : std::disjunction<has_free_crbegin<T>, has_member_crbegin<T>>
    {
    };

    template<typename T>
    auto constexpr has_crbegin_v = has_crbegin<T>::value;
  }  // namespace iterable_crbegin

  inline namespace iterable_end
  {
    template<typename T, typename = void>
    struct has_free_end : std::false_type
    {
    };

    template<typename T>
    struct has_free_end<T, std::void_t<decltype(end(std::declval<T &>()))>>
        : std::is_same<typename T::iterator, std::remove_cvref_t<decltype(end(std::declval<T &>()))>>
    {
    };

    template<typename T>
    struct has_free_end<T const, std::void_t<decltype(end(std::declval<T const &>()))>>
        : std::is_same<typename T::const_iterator, std::remove_cvref_t<decltype(end(std::declval<T const &>()))>>
    {
    };

    template<typename T>
    auto constexpr has_free_end_v = has_free_end<T>::value;

    template<typename T, typename = void>
    struct has_member_end : std::false_type
    {
    };

    template<typename T>
    struct has_member_end<T, std::void_t<decltype(std::declval<T &>().end())>>
        : std::is_same<typename T::iterator, std::remove_cvref_t<decltype(std::declval<T &>().end())>>
    {
    };

    template<typename T>
    struct has_member_end<T const, std::void_t<decltype(std::declval<T const &>().end())>>
        : std::is_same<typename T::const_iterator, std::remove_cvref_t<decltype(std::declval<T const &>().end())>>
    {
    };

    template<typename T>
    auto constexpr has_member_end_v = has_member_end<T>::value;

    template<typename T>
    struct has_end : std::disjunction<has_free_end<T>, has_member_end<T>>
    {
    };

    template<typename T>
    auto constexpr has_end_v = has_end<T>::value;
  }  // namespace iterable_end

  inline namespace iterable_cend
  {
    template<typename T, typename = void>
    struct has_free_cend : std::false_type
    {
    };

    template<typename T>
    struct has_free_cend<T, std::void_t<decltype(cend(std::declval<T const &>()))>>
        : std::is_same<typename T::const_iterator, std::remove_cvref_t<decltype(cend(std::declval<T const &>()))>>
    {
    };

    template<typename T>
    auto constexpr has_free_cend_v = has_free_cend<T>::value;

    template<typename T, typename = void>
    struct has_member_cend : std::false_type
    {
    };

    template<typename T>
    struct has_member_cend<T, std::void_t<decltype(std::declval<T const &>().cend())>>
        : std::is_same<typename T::const_iterator, decltype(std::declval<T const &>().cend())>
    {
    };

    template<typename T>
    auto constexpr has_member_cend_v = has_member_cend<T>::value;

    template<typename T>
    struct has_cend : std::disjunction<has_free_cend<T>, has_member_cend<T>>
    {
    };

    template<typename T>
    auto constexpr has_cend_v = has_cend<T>::value;
  }  // namespace iterable_cend

  inline namespace iterable_rend
  {
    template<typename T, typename = void>
    struct has_free_rend : std::false_type
    {
    };

    template<typename T>
    struct has_free_rend<T, std::void_t<decltype(rend(std::declval<T &>()))>>
        : std::is_same<typename T::reverse_iterator, std::remove_cvref_t<decltype(rend(std::declval<T &>()))>>
    {
    };

    template<typename T>
    struct has_free_rend<T const, std::void_t<decltype(rend(std::declval<T const &>()))>>
        : std::is_same<typename T::const_reverse_iterator, std::remove_cvref_t<decltype(rend(std::declval<T const &>()))>>
    {
    };

    template<typename T>
    auto constexpr has_free_rend_v = has_free_rend<T>::value;

    template<typename T, typename = void>
    struct has_member_rend : std::false_type
    {
    };

    template<typename T>
    struct has_member_rend<T, std::void_t<decltype(std::declval<T &>().rend())>>
        : std::is_same<typename T::reverse_iterator, std::remove_cvref_t<decltype(std::declval<T &>().rend())>>
    {
    };

    template<typename T>
    struct has_member_rend<T const, std::void_t<decltype(std::declval<T const &>().rend())>>
        : std::is_same<typename T::const_reverse_iterator, std::remove_cvref_t<decltype(std::declval<T const &>().rend())>>
    {
    };

    template<typename T>
    auto constexpr has_member_rend_v = has_member_rend<T>::value;

    template<typename T>
    struct has_rend : std::disjunction<has_free_rend<T>, has_member_rend<T>>
    {
    };

    template<typename T>
    auto constexpr has_rend_v = has_rend<T>::value;
  }  // namespace iterable_rend

  inline namespace iterable_crend
  {
    template<typename T, typename = void>
    struct has_free_crend : std::false_type
    {
    };

    template<typename T>
    struct has_free_crend<T, std::void_t<decltype(crend(std::declval<T const &>()))>>
        : std::is_same<typename T::const_reverse_iterator, std::remove_cvref_t<decltype(crend(std::declval<T const &>()))>>
    {
    };

    template<typename T>
    auto constexpr has_free_crend_v = has_free_crend<T>::value;

    template<typename T, typename = void>
    struct has_member_crend : std::false_type
    {
    };

    template<typename T>
    struct has_member_crend<T, std::void_t<decltype(std::declval<T const &>().crend())>>
        : std::is_same<typename T::const_reverse_iterator, std::remove_cvref_t<decltype(std::declval<T const &>().crend())>>
    {
    };

    template<typename T>
    auto constexpr has_member_crend_v = has_member_crend<T>::value;

    template<typename T>
    struct has_crend : std::disjunction<has_free_crend<T>, has_member_crend<T>>
    {
    };

    template<typename T>
    auto constexpr has_crend_v = has_crend<T>::value;
  }  // namespace iterable_crend

}  // namespace nt::impl

#endif