#ifndef NEWTYPE_IMPL_TYPE_TRAITS_EXTENSIONS_HPP
#define NEWTYPE_IMPL_TYPE_TRAITS_EXTENSIONS_HPP

#include "newtype/version.hpp"

#include <cstddef>
#include <functional>
#include <iosfwd>
#include <type_traits>

namespace nt::impl
{

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

}  // namespace nt::impl

#endif