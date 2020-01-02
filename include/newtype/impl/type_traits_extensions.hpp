#ifndef NEWTYPE_IMPL_TYPE_TRAITS_EXTENSIONS_HPP
#define NEWTYPE_IMPL_TYPE_TRAITS_EXTENSIONS_HPP

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
     * @brief A trait to test if a given type is input streamable
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
     * @brief A trait to test if a given type is input streamable
     *
     * @tparam T The type to test
     * @note This specialization forms the case for subtractable T
     */
    template<typename T>
    struct is_subtractable<T, std::void_t<decltype(std::declval<T const &>() + std::declval<T const &>())>> : std::true_type
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
    struct is_nothrow_subtractable<T, std::void_t<decltype(std::declval<T const &>() + std::declval<T const &>())>>
        : std::bool_constant<noexcept(std::declval<T const &>() + std::declval<T const &>())>
    {
    };

    /**
     * @brief A variable template to test if a given type is noexcept subtractable
     *
     * @tparam T The type to test
     */
    template<typename T>
    auto constexpr is_nothrow_subtractable_v = is_nothrow_subtractable<T>::value;

  }  // namespace arithmetic

}  // namespace nt::impl

#endif