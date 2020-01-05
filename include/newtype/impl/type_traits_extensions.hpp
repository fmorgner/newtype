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

    /**
     * @brief A trait to test if a given type is comparable using operator==
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-equals-comparable T
     */
    template<typename T, typename = void>
    struct is_equality_comparable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is comparable using operator==
     *
     * @tparam T The type to test
     * @note This specialization forms the case for equals-comparable T
     */
    template<typename T>
    struct is_equality_comparable<T, std::void_t<decltype(std::declval<T const &>() == std::declval<T const &>())>> : std::true_type
    {
    };

    /**
     * @brief A variable template to test if a given type is comparable using operator==
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_equality_comparable_v = is_equality_comparable<T>::value;

    /**
     * @brief A trait to test if a given type is noexcept comparable using operator==
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-noexcept equals-comparable or non-equals-comparable T
     */
    template<typename T, typename = void>
    struct is_nothrow_equality_comparable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is noexcept comparable using operator==
     *
     * @tparam T The type to test
     * @note This specialization forms the case for equals-comparable T detemining if T is noexcept comparable using operator==
     */
    template<typename T>
    struct is_nothrow_equality_comparable<T, std::void_t<decltype(std::declval<T const &>() == std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() == std::declval<T const &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept comparable using operator==
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_nothrow_equality_comparable_v = is_nothrow_equality_comparable<T>::value;

    /**
     * @brief A trait to test if a given type is comparable using operator!=
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-not-equals-comparable T
     */
    template<typename T, typename = void>
    struct is_inequality_comparable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is comparable using operator!=
     *
     * @tparam T The type to test
     * @note This specialization forms the case for not-equals-comparable T
     */
    template<typename T>
    struct is_inequality_comparable<T, std::void_t<decltype(std::declval<T const &>() != std::declval<T const &>())>> : std::true_type
    {
    };

    /**
     * @brief A variable template to test if a given type is comparable using operator!=
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_inequality_comparable_v = is_inequality_comparable<T>::value;

    /**
     * @brief A trait to test if a given type is noexcept comparable using operator!=
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-noexcept not-equals-comparable or non-not-equals-comparable T
     */
    template<typename T, typename = void>
    struct is_nothrow_inequality_comparable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is noexcept comparable using operator==
     *
     * @tparam T The type to test
     * @note This specialization forms the case for equals-comparable T detemining if T is noexcept comparable using operator!=
     */
    template<typename T>
    struct is_nothrow_inequality_comparable<T, std::void_t<decltype(std::declval<T const &>() != std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() != std::declval<T const &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept comparable using operator!=
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_nothrow_inequality_comparable_v = is_nothrow_inequality_comparable<T>::value;

  }  // namespace equality_comparable

  inline namespace relationally_comparable
  {

    /**
     * @brief A trait to test if a given type is comparable using operator<
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-less-than-comparable T
     */
    template<typename T, typename = void>
    struct is_less_than_comparable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is comparable using operator<
     *
     * @tparam T The type to test
     * @note This specialization forms the case for less-than-comparable T
     */
    template<typename T>
    struct is_less_than_comparable<T, std::void_t<decltype(std::declval<T const &>() < std::declval<T const &>())>> : std::true_type
    {
    };

    /**
     * @brief A variable template to test if a given type is comparable using operator<
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_less_than_comparable_v = is_less_than_comparable<T>::value;

    /**
     * @brief A trait to test if a given type is noexcept comparable using operator<
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-noexcept less-than-comparable or non-less-than-comparable T
     */
    template<typename T, typename = void>
    struct is_nothrow_less_than_comparable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is noexcept comparable using operator<
     *
     * @tparam T The type to test
     * @note This specialization forms the case for less-than-comparable T detemining if T is noexcept comparable using operator<
     */
    template<typename T>
    struct is_nothrow_less_than_comparable<T, std::void_t<decltype(std::declval<T const &>() < std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() < std::declval<T const &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept comparable using operator<
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_nothrow_less_than_comparable_v = is_nothrow_less_than_comparable<T>::value;

    /**
     * @brief A trait to test if a given type is comparable using operator>
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-greater-than-comparable T
     */
    template<typename T, typename = void>
    struct is_greater_than_comparable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is comparable using operator>
     *
     * @tparam T The type to test
     * @note This specialization forms the case for greater-than-comparable T
     */
    template<typename T>
    struct is_greater_than_comparable<T, std::void_t<decltype(std::declval<T const &>() > std::declval<T const &>())>> : std::true_type
    {
    };

    /**
     * @brief A variable template to test if a given type is comparable using operator>
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_greater_than_comparable_v = is_greater_than_comparable<T>::value;

    /**
     * @brief A trait to test if a given type is noexcept comparable using operator>
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-noexcept greater-than-comparable or non-greater-than-comparable T
     */
    template<typename T, typename = void>
    struct is_nothrow_greater_than_comparable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is noexcept comparable using operator>
     *
     * @tparam T The type to test
     * @note This specialization forms the case for greater-than-comparable T detemining if T is noexcept comparable using operator>
     */
    template<typename T>
    struct is_nothrow_greater_than_comparable<T, std::void_t<decltype(std::declval<T const &>() > std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() > std::declval<T const &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept comparable using operator>
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_nothrow_greater_than_comparable_v = is_nothrow_greater_than_comparable<T>::value;

    /**
     * @brief A trait to test if a given type is comparable using operator<=
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-less-than-or-equal-to-comparable T
     */
    template<typename T, typename = void>
    struct is_less_than_equal_to_comparable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is comparable using operator<=
     *
     * @tparam T The type to test
     * @note This specialization forms the case for less-than-or-equal-to-comparable T
     */
    template<typename T>
    struct is_less_than_equal_to_comparable<T, std::void_t<decltype(std::declval<T const &>() <= std::declval<T const &>())>> : std::true_type
    {
    };

    /**
     * @brief A variable template to test if a given type is comparable using operator<=
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_less_than_equal_to_comparable_v = is_less_than_equal_to_comparable<T>::value;

    /**
     * @brief A trait to test if a given type is noexcept comparable using operator<=
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-noexcept less-than-or-equal-to-comparable or non-less-than-or-equal-to-comparable T
     */
    template<typename T, typename = void>
    struct is_nothrow_less_than_equal_to_comparable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is noexcept comparable using operator<=
     *
     * @tparam T The type to test
     * @note This specialization forms the case for less-than-or-equal-to-comparable T detemining if T is noexcept comparable using operator<=
     */
    template<typename T>
    struct is_nothrow_less_than_equal_to_comparable<T, std::void_t<decltype(std::declval<T const &>() <= std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() <= std::declval<T const &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept comparable using operator<=
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_nothrow_less_than_equal_to_comparable_v = is_nothrow_less_than_equal_to_comparable<T>::value;

    /**
     * @brief A trait to test if a given type is comparable using operator>=
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-greater-than-or-equal-to-comparable T
     */
    template<typename T, typename = void>
    struct is_greater_than_equal_to_comparable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is comparable using operator>=
     *
     * @tparam T The type to test
     * @note This specialization forms the case for greater-than-or-equal-to-comparable T
     */
    template<typename T>
    struct is_greater_than_equal_to_comparable<T, std::void_t<decltype(std::declval<T const &>() >= std::declval<T const &>())>>
        : std::true_type
    {
    };

    /**
     * @brief A variable template to test if a given type is comparable using operator>=
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_greater_than_equal_to_comparable_v = is_greater_than_equal_to_comparable<T>::value;

    /**
     * @brief A trait to test if a given type is noexcept comparable using operator>=
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-noexcept greater-than-or-equal-to-comparable or
     * non-greater-than-or-equal-to-comparable T
     */
    template<typename T, typename = void>
    struct is_nothrow_greater_than_equal_to_comparable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is noexcept comparable using operator>=
     *
     * @tparam T The type to test
     * @note This specialization forms the case for greater-than-or-equal-to-comparable T detemining if T is noexcept comparable using
     * operator>=
     */
    template<typename T>
    struct is_nothrow_greater_than_equal_to_comparable<T, std::void_t<decltype(std::declval<T const &>() >= std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() >= std::declval<T const &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept comparable using operator>=
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_nothrow_greater_than_equal_to_comparable_v = is_nothrow_greater_than_equal_to_comparable<T>::value;
  }  // namespace relationally_comparable

  inline namespace iostreamable
  {

    /**
     * @brief A trait to test if a given type is output streamable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-output-streamable T
     */
    template<typename StreamType, typename T, typename = void>
    struct is_output_streamable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is output streamable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for output-streamable T
     */
    template<typename StreamType, typename T>
    struct is_output_streamable<StreamType, T, std::void_t<decltype(std::declval<StreamType &>() << std::declval<T const &>())>>
        : std::true_type
    {
    };

    /**
     * @brief A variable template to test if a given type is output streamable
     *
     * @tparam T The type to test
     */
    template<typename StreamType, typename T>
    auto constexpr is_output_streamable_v = is_output_streamable<StreamType, T>::value;

    /**
     * @brief A trait to test if a given type is noexcept output streamable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-noexcept output-streamable or non-output-streamable T
     */
    template<typename StreamType, typename T, typename = void>
    struct is_nothrow_output_streamable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is noexcept output streamable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for output-streamable T detemining if T is noexcept output-streamable
     */
    template<typename StreamType, typename T>
    struct is_nothrow_output_streamable<StreamType, T, std::void_t<decltype(std::declval<StreamType &>() << std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<StreamType &>() << std::declval<T const &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept output streamable
     *
     * @tparam T The type to test
     */
    template<typename StreamType, typename T>
    auto constexpr is_nothrow_output_streamable_v = is_nothrow_output_streamable<StreamType, T>::value;

    /**
     * @brief A trait to test if a given type is input streamable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-input-streamable T
     */
    template<typename StreamType, typename T, typename = void>
    struct is_input_streamable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is input streamable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for input-streamable T
     */
    template<typename StreamType, typename T>
    struct is_input_streamable<StreamType, T, std::void_t<decltype(std::declval<StreamType &>() >> std::declval<T &>())>> : std::true_type
    {
    };

    /**
     * @brief A variable template to test if a given type is input streamable
     *
     * @tparam T The type to test
     */
    template<typename StreamType, typename T>
    auto constexpr is_input_streamable_v = is_input_streamable<StreamType, T>::value;

    /**
     * @brief A trait to test if a given type is noexcept input streamable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-noexcept input-streamable or non-input-streamable T
     */
    template<typename StreamType, typename T, typename = void>
    struct is_nothrow_input_streamable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is noexcept input streamable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for input-streamable T detemining if T is noexcept input-streamable
     */
    template<typename StreamType, typename T>
    struct is_nothrow_input_streamable<StreamType, T, std::void_t<decltype(std::declval<StreamType &>() >> std::declval<T &>())>>
        : std::bool_constant<noexcept(std::declval<StreamType &>() >> std::declval<T &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept input streamable
     *
     * @tparam T The type to test
     */
    template<typename StreamType, typename T>
    auto constexpr is_nothrow_input_streamable_v = is_nothrow_input_streamable<StreamType, T>::value;

  }  // namespace iostreamable

  inline namespace arithmetic
  {

    /**
     * @brief A trait to test if a given type is addable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-addable T
     */
    template<typename T, typename = void>
    struct is_addable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is addable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for addable T
     */
    template<typename T>
    struct is_addable<T, std::void_t<decltype(std::declval<T const &>() + std::declval<T const &>())>> : std::true_type
    {
    };

    /**
     * @brief A variable template to test if a given type is addable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_addable_v = is_addable<T>::value;

    /**
     * @brief A trait to test if a given type is noexcept addable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-noexcept addable or non-addable T
     */
    template<typename T, typename = void>
    struct is_nothrow_addable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is noexcept addable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for addable T detemining if T is noexcept addable
     */
    template<typename T>
    struct is_nothrow_addable<T, std::void_t<decltype(std::declval<T const &>() + std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() + std::declval<T const &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept addable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_nothrow_addable_v = is_nothrow_addable<T>::value;

    /**
     * @brief A trait to test if a given type is subtractable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-subtractable T
     */
    template<typename T, typename = void>
    struct is_subtractable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is subtractable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for subtractable T
     */
    template<typename T>
    struct is_subtractable<T, std::void_t<decltype(std::declval<T const &>() - std::declval<T const &>())>> : std::true_type
    {
    };

    /**
     * @brief A variable template to test if a given type is subtractable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_subtractable_v = is_subtractable<T>::value;

    /**
     * @brief A trait to test if a given type is noexcept subtractable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-noexcept subtractable or non-subtractable T
     */
    template<typename T, typename = void>
    struct is_nothrow_subtractable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is noexcept subtractable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for subtractable T detemining if T is noexcept subtractable
     */
    template<typename T>
    struct is_nothrow_subtractable<T, std::void_t<decltype(std::declval<T const &>() - std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() - std::declval<T const &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept subtractable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_nothrow_subtractable_v = is_nothrow_subtractable<T>::value;

    /**
     * @brief A trait to test if a given type is multipliable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-multipliable T
     */
    template<typename T, typename = void>
    struct is_multipliable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is multipliable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for multipliable T
     */
    template<typename T>
    struct is_multipliable<T, std::void_t<decltype(std::declval<T const &>() * std::declval<T const &>())>> : std::true_type
    {
    };

    /**
     * @brief A variable template to test if a given type is multipliable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_multipliable_v = is_multipliable<T>::value;

    /**
     * @brief A trait to test if a given type is noexcept multipliable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-noexcept multipliable or non-multipliable T
     */
    template<typename T, typename = void>
    struct is_nothrow_multipliable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is noexcept multipliable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for multipliable T detemining if T is noexcept multipliable
     */
    template<typename T>
    struct is_nothrow_multipliable<T, std::void_t<decltype(std::declval<T const &>() * std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() * std::declval<T const &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept multipliable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_nothrow_multipliable_v = is_nothrow_multipliable<T>::value;

    /**
     * @brief A trait to test if a given type is dividable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-dividable T
     */
    template<typename T, typename = void>
    struct is_dividable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is dividable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for dividable T
     */
    template<typename T>
    struct is_dividable<T, std::void_t<decltype(std::declval<T const &>() / std::declval<T const &>())>> : std::true_type
    {
    };

    /**
     * @brief A variable template to test if a given type is dividable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_dividable_v = is_dividable<T>::value;

    /**
     * @brief A trait to test if a given type is noexcept dividable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-noexcept dividable or non-dividable T
     */
    template<typename T, typename = void>
    struct is_nothrow_dividable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is noexcept dividable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for dividable T detemining if T is noexcept dividable
     */
    template<typename T>
    struct is_nothrow_dividable<T, std::void_t<decltype(std::declval<T const &>() / std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() / std::declval<T const &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept dividable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_nothrow_dividable_v = is_nothrow_dividable<T>::value;

  }  // namespace arithmetic

  inline namespace compound_arithmetic
  {

    /**
     * @brief A trait to test if a given type is add-assignable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-add-assignable T
     */
    template<typename T, typename = void>
    struct is_add_assignable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is add-assignable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for add-assignable T
     */
    template<typename T>
    struct is_add_assignable<T, std::void_t<decltype(std::declval<T &>() += std::declval<T const &>())>> : std::true_type
    {
    };

    /**
     * @brief A variable template to test if a given type is add-assignable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_add_assignable_v = is_add_assignable<T>::value;

    /**
     * @brief A trait to test if a given type is noexcept add-assignable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-noexcept add-assignable or non-add-assignable T
     */
    template<typename T, typename = void>
    struct is_nothrow_add_assignable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is noexcept add-assignable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for add-assignable T detemining if T is noexcept add-assignable
     */
    template<typename T>
    struct is_nothrow_add_assignable<T, std::void_t<decltype(std::declval<T &>() += std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T &>() += std::declval<T const &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept add-assignable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_nothrow_add_assignable_v = is_nothrow_add_assignable<T>::value;

    /**
     * @brief A trait to test if a given type is subtract-assignable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-subtract-assignable T
     */
    template<typename T, typename = void>
    struct is_subtract_assignable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is subtract-assignable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for subtract-assignable T
     */
    template<typename T>
    struct is_subtract_assignable<T, std::void_t<decltype(std::declval<T &>() -= std::declval<T const &>())>> : std::true_type
    {
    };

    /**
     * @brief A variable template to test if a given type is subtract-assignable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_subtract_assignable_v = is_subtract_assignable<T>::value;

    /**
     * @brief A trait to test if a given type is noexcept subtract-assignable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-noexcept subtract-assignable or non-subtract-assignable T
     */
    template<typename T, typename = void>
    struct is_nothrow_subtract_assignable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is noexcept subtract-assignable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for subtract-assignable T detemining if T is noexcept subtract-assignable
     */
    template<typename T>
    struct is_nothrow_subtract_assignable<T, std::void_t<decltype(std::declval<T &>() -= std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T &>() -= std::declval<T const &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept subtract-assignable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_nothrow_subtract_assignable_v = is_nothrow_subtract_assignable<T>::value;

    /**
     * @brief A trait to test if a given type is multiply-assignable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-multiply-assignable T
     */
    template<typename T, typename = void>
    struct is_multiply_assignable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is multiply-assignable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for multiply-assignable T
     */
    template<typename T>
    struct is_multiply_assignable<T, std::void_t<decltype(std::declval<T &>() *= std::declval<T const &>())>> : std::true_type
    {
    };

    /**
     * @brief A variable template to test if a given type is multiply-assignable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_multiply_assignable_v = is_multiply_assignable<T>::value;

    /**
     * @brief A trait to test if a given type is noexcept multiply-assignable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-noexcept multiply-assignable or non-multiply-assignable T
     */
    template<typename T, typename = void>
    struct is_nothrow_multiply_assignable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is noexcept multiply-assignable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for multiply-assignable T detemining if T is noexcept multiply-assignable
     */
    template<typename T>
    struct is_nothrow_multiply_assignable<T, std::void_t<decltype(std::declval<T &>() *= std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T &>() *= std::declval<T const &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept multiply-assignable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_nothrow_multiply_assignable_v = is_nothrow_multiply_assignable<T>::value;

    /**
     * @brief A trait to test if a given type is divide-assignable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-divide-assignable T
     */
    template<typename T, typename = void>
    struct is_divide_assignable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is divide-assignable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for divide-assignable T
     */
    template<typename T>
    struct is_divide_assignable<T, std::void_t<decltype(std::declval<T &>() /= std::declval<T const &>())>> : std::true_type
    {
    };

    /**
     * @brief A variable template to test if a given type is divide-assignable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_divide_assignable_v = is_divide_assignable<T>::value;

    /**
     * @brief A trait to test if a given type is noexcept divide-assignable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-noexcept divide-assignable or non-divide-assignable T
     */
    template<typename T, typename = void>
    struct is_nothrow_divide_assignable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is noexcept divide-assignable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for divide-assignable T detemining if T is noexcept divide-assignable
     */
    template<typename T>
    struct is_nothrow_divide_assignable<T, std::void_t<decltype(std::declval<T &>() /= std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T &>() /= std::declval<T const &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept divide-assignable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_nothrow_divide_assignable_v = is_nothrow_divide_assignable<T>::value;

  }  // namespace compound_arithmetic

  inline namespace std_support
  {

    /**
     * @brief A trait to test if a given type is hashable
     *
     * @tparam T The type to test
     * @note This specialization forms the base case for non-hashable T
     */
    template<typename T, typename = void>
    struct is_hashable : std::false_type
    {
    };

    /**
     * @brief A trait to test if a given type is hashable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for hashable T
     */
    template<typename T>
    struct is_hashable<T, std::void_t<decltype(std::declval<std::hash<T> const &>()(std::declval<T const &>()))>>
        : std::is_same<std::size_t, decltype(std::declval<std::hash<T> const &>()(std::declval<T const &>()))>
    {
    };

    /**
     * @brief A variable template to test if a given type is hashable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_hashable_v = is_hashable<T>::value;

  }  // namespace std_support

}  // namespace nt::impl

#endif