#include "equality_comparison_suite.hpp"

#include "kawaii.hpp"
#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/new_type.hpp"

#include <cute/cute.h>

#include <string>
#include <type_traits>
#include <utility>

inline namespace basic_equality_comparsion_tests
{

  auto two_instances_of_the_same_new__type_with_the_same_value_compare_equal() -> void
  {
    using type_alias = nt::new_type<int, struct eq_test_tag_1>;

    auto constexpr lhs = type_alias{42};
    auto constexpr rhs = type_alias{42};

    ASSERT_EQUAL(lhs, rhs);
  }

  auto two_instances_of_the_same_new__type_with_the_same_value_do_not_compare_not_equal() -> void
  {
    using type_alias = nt::new_type<int, struct eq_test_tag_1>;

    auto constexpr lhs = type_alias{42};
    auto constexpr rhs = type_alias{42};

    ASSERT(!(lhs != rhs));
  }

  auto two_instances_of_the_same_new__type_with_differing_values_do_compare_not_equal() -> void
  {
    using type_alias = nt::new_type<int, struct eq_test_tag_1>;

    auto constexpr lhs = type_alias{42};
    auto constexpr rhs = type_alias{43};

    ASSERT_NOT_EQUAL_TO(lhs, rhs);
  }

  auto two_instances_of_the_same_new__type_with_differing_values_do_not_compare_equal() -> void
  {
    using type_alias = nt::new_type<int, struct eq_test_tag_1>;

    auto constexpr lhs = type_alias{42};
    auto constexpr rhs = type_alias{43};

    ASSERT(!(lhs == rhs));
  }

}  // namespace basic_equality_comparsion_tests

inline namespace equality_comparsion_noexcept_tests
{

  auto equality_comparison_on_a_new__type_is_noexcept_if_the_base_type_is_noexcept_comparable() -> void
  {
    using type_alias = nt::new_type<int, struct eq_test_tag_2>;
    static_assert(noexcept(std::declval<int &>() == std::declval<int &>()), "Sanity Check");
    ASSERT(noexcept(std::declval<type_alias &>() == std::declval<type_alias &>()));
  }

  auto equality_comparison_on_a_new__type_is_not_noexcept_if_the_base_type_is_not_noexcept_comparable() -> void
  {
    struct strange_type
    {
      auto constexpr operator==(strange_type const &) const noexcept(false) -> bool
      {
        return false;
      }
    };

    using type_alias = nt::new_type<strange_type, struct eq_test_tag_3>;
    static_assert(!noexcept(std::declval<strange_type &>() == std::declval<strange_type &>()), "Sanity Check");
    ASSERT(!noexcept(std::declval<type_alias &>() == std::declval<type_alias &>()));
  }

  auto inequality_comparison_on_a_new__type_is_noexcept_if_the_base_type_is_noexcept_comparable() -> void
  {
    using type_alias = nt::new_type<int, struct eq_test_tag_4>;
    static_assert(noexcept(std::declval<int &>() != std::declval<int &>()), "Sanity Check");
    ASSERT(noexcept(std::declval<type_alias &>() != std::declval<type_alias &>()));
  }

  auto inequality_comparison_on_a_new__type_is_not_noexcept_if_the_base_type_is_not_noexcept_comparable() -> void
  {
    struct strange_type
    {
      auto constexpr operator!=(strange_type const &) const noexcept(false) -> bool
      {
        return false;
      }
    };

    using type_alias = nt::new_type<strange_type, struct eq_test_tag_5>;
    static_assert(!noexcept(std::declval<strange_type &>() != std::declval<strange_type &>()), "Sanity Check");
    ASSERT(!noexcept(std::declval<type_alias &>() != std::declval<type_alias &>()));
  }

}  // namespace equality_comparsion_noexcept_tests

inline namespace equality_comparison_return_type_tests
{

  auto equality_comparsion_of_two_new__type_instances_returns_bool() -> void
  {
    using type_alias = nt::new_type<int, struct eq_test_tag_6>;
    ASSERT((std::is_same_v<bool, decltype(std::declval<type_alias &>() == std::declval<type_alias &>())>));
  }

  auto inequality_comparsion_of_two_new__type_instances_returns_bool() -> void
  {
    using type_alias = nt::new_type<int, struct eq_test_tag_7>;
    ASSERT((std::is_same_v<bool, decltype(std::declval<type_alias &>() != std::declval<type_alias &>())>));
  }

}  // namespace equality_comparison_return_type_tests

auto equality_comparison_suite() -> std::pair<cute::suite, std::string>
{
  return {{
              // Basic Equality Comparison Tests
              KAWAII(two_instances_of_the_same_new__type_with_the_same_value_compare_equal),
              KAWAII(two_instances_of_the_same_new__type_with_the_same_value_do_not_compare_not_equal),
              KAWAII(two_instances_of_the_same_new__type_with_differing_values_do_compare_not_equal),
              KAWAII(two_instances_of_the_same_new__type_with_differing_values_do_not_compare_equal),

              // Equality Comparison noexcept Tests
              KAWAII(equality_comparison_on_a_new__type_is_noexcept_if_the_base_type_is_noexcept_comparable),
              KAWAII(equality_comparison_on_a_new__type_is_not_noexcept_if_the_base_type_is_not_noexcept_comparable),
              KAWAII(inequality_comparison_on_a_new__type_is_noexcept_if_the_base_type_is_noexcept_comparable),
              KAWAII(inequality_comparison_on_a_new__type_is_not_noexcept_if_the_base_type_is_not_noexcept_comparable),

              // Equality Comparison Return Type Tests
              KAWAII(equality_comparsion_of_two_new__type_instances_returns_bool),
              KAWAII(inequality_comparsion_of_two_new__type_instances_returns_bool),
          },
          "Equality Comparison Tests"};
}