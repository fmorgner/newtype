#include "conversion_suite.hpp"
#include "kawaii.hpp"
#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/impl/type_traits_extensions.hpp"
#include "newtype/new_type.hpp"

#include <cute/cute.h>

#include <type_traits>

namespace
{

  struct addable_type
  {
    auto constexpr operator+(addable_type const &) const -> addable_type
    {
      return {};
    };
  };

  struct subtractable_type
  {
    auto constexpr operator-(subtractable_type const &) const -> subtractable_type
    {
      return {};
    };
  };

  struct multipliable_type
  {
    auto constexpr operator*(multipliable_type const &)const -> multipliable_type
    {
      return {};
    };
  };

  struct dividable_type
  {
    auto constexpr operator/(dividable_type const &) const -> dividable_type
    {
      return {};
    };
  };

}  // namespace

inline namespace addition_tests
{

  auto a_new__type_not_deriving_arithmetic_is_not_addable_with_instances_of_itself() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::is_addable_v<type_alias>));
  }

  auto a_new__type_deriving_arithmetic_is_addable_with_instances_of_itself() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;
    ASSERT(nt::impl::is_addable_v<type_alias>);
  }

  template<typename T>
  auto a_new__type_deriving_arithmetic_is_addable_with_instances_of_itself_if_the_base_type_is_addable() -> void
  {
    static_assert(nt::impl::is_addable_v<T>, "Sanity Check");
    using type_alias = nt::new_type<T, struct tag, deriving(nt::Arithmetic)>;
    ASSERT_EQUAL(nt::impl::is_addable_v<T>, nt::impl::is_addable_v<type_alias>);
  }

  auto addition_of_two_instances_of_a_new__type_deriving_arithmetic_produces_an_instance_of_the_same_new__type() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;
    ASSERT((std::is_same_v<type_alias, decltype(std::declval<type_alias const &>() + std::declval<type_alias const &>())>));
  }

  auto addition_of_two_instances_of_a_new__type_deriving_arithmetic_produces_the_correct_value_with_respect_to_the_base_type() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;
    auto lhs = type_alias{24};
    auto rhs = type_alias{18};
    ASSERT_EQUAL(24 + 18, (lhs + rhs).decay());
  }

}  // namespace addition_tests

inline namespace subtraction_tests
{

  auto a_new__type_not_deriving_arithmetic_is_not_subtractable_with_instances_of_itself() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::is_subtractable_v<type_alias>));
  }

  auto a_new__type_deriving_arithmetic_is_subtractable_with_instances_of_itself() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;
    ASSERT(nt::impl::is_subtractable_v<type_alias>);
  }

  template<typename T>
  auto a_new__type_deriving_arithmetic_is_subtractable_with_instances_of_itself_if_the_base_type_is_subtractable() -> void
  {
    static_assert(nt::impl::is_subtractable_v<T>, "Sanity Check");
    using type_alias = nt::new_type<T, struct tag, deriving(nt::Arithmetic)>;
    ASSERT_EQUAL(nt::impl::is_subtractable_v<T>, nt::impl::is_subtractable_v<type_alias>);
  }

  auto subtraction_of_two_instances_of_a_new__type_deriving_arithmetic_produces_an_instance_of_the_same_new__type() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;
    ASSERT((std::is_same_v<type_alias, decltype(std::declval<type_alias const &>() - std::declval<type_alias const &>())>));
  }

  auto subtraction_of_two_instances_of_a_new__type_deriving_arithmetic_produces_the_correct_value_with_respect_to_the_base_type() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;
    auto lhs = type_alias{24};
    auto rhs = type_alias{18};
    ASSERT_EQUAL(24 - 18, (lhs - rhs).decay());
  }

}  // namespace subtraction_tests

inline namespace multiplication_tests
{

  auto a_new__type_not_deriving_arithmetic_is_not_multipliable_with_instances_of_itself() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::is_multipliable_v<type_alias>));
  }

  auto a_new__type_deriving_arithmetic_is_multipliable_with_instances_of_itself() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;
    ASSERT(nt::impl::is_multipliable_v<type_alias>);
  }

  template<typename T>
  auto a_new__type_deriving_arithmetic_is_multipliable_with_instances_of_itself_if_the_base_type_is_multipliable() -> void
  {
    static_assert(nt::impl::is_multipliable_v<T>, "Sanity Check");
    using type_alias = nt::new_type<T, struct tag, deriving(nt::Arithmetic)>;
    ASSERT_EQUAL(nt::impl::is_multipliable_v<T>, nt::impl::is_multipliable_v<type_alias>);
  }

  auto multiplication_of_two_instances_of_a_new__type_deriving_arithmetic_produces_an_instance_of_the_same_new__type() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;
    ASSERT((std::is_same_v<type_alias, decltype(std::declval<type_alias const &>() * std::declval<type_alias const &>())>));
  }

  auto multiplication_of_two_instances_of_a_new__type_deriving_arithmetic_produces_the_correct_value_with_respect_to_the_base_type() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;
    auto lhs = type_alias{24};
    auto rhs = type_alias{18};
    ASSERT_EQUAL(24 * 18, (lhs * rhs).decay());
  }

}  // namespace multiplication_tests

inline namespace division_tests
{

  auto a_new__type_not_deriving_arithmetic_is_not_dividable_with_instances_of_itself() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::is_dividable_v<type_alias>));
  }

  auto a_new__type_deriving_arithmetic_is_dividable_with_instances_of_itself() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;
    ASSERT(nt::impl::is_dividable_v<type_alias>);
  }

  template<typename T>
  auto a_new__type_deriving_arithmetic_is_dividable_with_instances_of_itself_if_the_base_type_is_dividable() -> void
  {
    static_assert(nt::impl::is_dividable_v<T>, "Sanity Check");
    using type_alias = nt::new_type<T, struct tag, deriving(nt::Arithmetic)>;
    ASSERT_EQUAL(nt::impl::is_dividable_v<T>, nt::impl::is_dividable_v<type_alias>);
  }

  auto division_of_two_instances_of_a_new__type_deriving_arithmetic_produces_an_instance_of_the_same_new__type() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;
    ASSERT((std::is_same_v<type_alias, decltype(std::declval<type_alias const &>() / std::declval<type_alias const &>())>));
  }

  auto division_of_two_instances_of_a_new__type_deriving_arithmetic_produces_the_correct_value_with_respect_to_the_base_type() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;
    auto lhs = type_alias{24};
    auto rhs = type_alias{2};
    ASSERT_EQUAL(24 / 2, (lhs / rhs).decay());
  }

}  // namespace division_tests

auto arithmetic_suite() -> std::pair<cute::suite, std::string>
{
  return {
      {
          /// Addition Tests
          KAWAII(a_new__type_not_deriving_arithmetic_is_not_addable_with_instances_of_itself),
          KAWAII(a_new__type_deriving_arithmetic_is_addable_with_instances_of_itself),
          KAWAII(a_new__type_deriving_arithmetic_is_addable_with_instances_of_itself_if_the_base_type_is_addable<int>),
          KAWAII(a_new__type_deriving_arithmetic_is_addable_with_instances_of_itself_if_the_base_type_is_addable<addable_type>),
          KAWAII(addition_of_two_instances_of_a_new__type_deriving_arithmetic_produces_an_instance_of_the_same_new__type),
          KAWAII(addition_of_two_instances_of_a_new__type_deriving_arithmetic_produces_the_correct_value_with_respect_to_the_base_type),

          /// Subtraction Tests
          KAWAII(a_new__type_not_deriving_arithmetic_is_not_subtractable_with_instances_of_itself),
          KAWAII(a_new__type_deriving_arithmetic_is_subtractable_with_instances_of_itself),
          KAWAII(a_new__type_deriving_arithmetic_is_subtractable_with_instances_of_itself_if_the_base_type_is_subtractable<int>),
          KAWAII(a_new__type_deriving_arithmetic_is_subtractable_with_instances_of_itself_if_the_base_type_is_subtractable<subtractable_type>),
          KAWAII(subtraction_of_two_instances_of_a_new__type_deriving_arithmetic_produces_an_instance_of_the_same_new__type),
          KAWAII(subtraction_of_two_instances_of_a_new__type_deriving_arithmetic_produces_the_correct_value_with_respect_to_the_base_type),

          /// Multiplication Tests
          KAWAII(a_new__type_not_deriving_arithmetic_is_not_multipliable_with_instances_of_itself),
          KAWAII(a_new__type_deriving_arithmetic_is_multipliable_with_instances_of_itself),
          KAWAII(a_new__type_deriving_arithmetic_is_multipliable_with_instances_of_itself_if_the_base_type_is_multipliable<int>),
          KAWAII(a_new__type_deriving_arithmetic_is_multipliable_with_instances_of_itself_if_the_base_type_is_multipliable<multipliable_type>),
          KAWAII(multiplication_of_two_instances_of_a_new__type_deriving_arithmetic_produces_an_instance_of_the_same_new__type),
          KAWAII(multiplication_of_two_instances_of_a_new__type_deriving_arithmetic_produces_the_correct_value_with_respect_to_the_base_type),

          /// Division Tests
          KAWAII(a_new__type_not_deriving_arithmetic_is_not_dividable_with_instances_of_itself),
          KAWAII(a_new__type_deriving_arithmetic_is_dividable_with_instances_of_itself),
          KAWAII(a_new__type_deriving_arithmetic_is_dividable_with_instances_of_itself_if_the_base_type_is_dividable<int>),
          KAWAII(a_new__type_deriving_arithmetic_is_dividable_with_instances_of_itself_if_the_base_type_is_dividable<dividable_type>),
          KAWAII(division_of_two_instances_of_a_new__type_deriving_arithmetic_produces_an_instance_of_the_same_new__type),
          KAWAII(division_of_two_instances_of_a_new__type_deriving_arithmetic_produces_the_correct_value_with_respect_to_the_base_type),
      },
      "Arithmetic Operators Tests"};
}