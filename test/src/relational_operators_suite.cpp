#include "relational_operators_suite.hpp"

#include "kawaii.hpp"
#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/new_type.hpp"

#include <cute/cute.h>

#include <string>
#include <type_traits>
#include <utility>

inline namespace traits_extensions
{

  template<typename T, typename = void>
  struct has_less_than : std::false_type
  {
  };

  template<typename T>
  struct has_less_than<T, std::void_t<decltype(std::declval<T const &>() < std::declval<T const &>())>> : std::true_type
  {
  };

  template<typename T>
  auto constexpr has_less_than_v = has_less_than<T>::value;

  template<typename T, typename = void>
  struct has_greater_than : std::false_type
  {
  };

  template<typename T>
  struct has_greater_than<T, std::void_t<decltype(std::declval<T const &>() > std::declval<T const &>())>> : std::true_type
  {
  };

  template<typename T>
  auto constexpr has_greater_than_v = has_greater_than<T>::value;

  template<typename T, typename = void>
  struct has_less_than_equal_to : std::false_type
  {
  };

  template<typename T>
  struct has_less_than_equal_to<T, std::void_t<decltype(std::declval<T const &>() <= std::declval<T const &>())>> : std::true_type
  {
  };

  template<typename T>
  auto constexpr has_less_than_equal_to_v = has_less_than_equal_to<T>::value;

  template<typename T, typename = void>
  struct has_greater_than_equal_to : std::false_type
  {
  };

  template<typename T>
  struct has_greater_than_equal_to<T, std::void_t<decltype(std::declval<T const &>() >= std::declval<T const &>())>> : std::true_type
  {
  };

  template<typename T>
  auto constexpr has_greater_than_equal_to_v = has_greater_than_equal_to<T>::value;

}  // namespace traits_extensions

inline namespace relational_operator_presence_tests
{

  auto an_instance_of_new__type_has_less_than_if_its_derivation_clause_contains_relational() -> void
  {
    using type_alias = nt::new_type<int, struct relop_presensence_test_tag_1, deriving(nt::Relational)>;
    ASSERT(has_less_than_v<type_alias>);
  }

  auto an_instance_of_new__type_does_not_have_less_than_if_its_derivation_clause_does_not_contain_relational() -> void
  {
    using type_alias = nt::new_type<int, struct relop_presensence_test_tag_2>;
    ASSERT(!has_less_than_v<type_alias>);
  }

  auto an_instance_of_new__type_has_greater_than_if_its_derivation_clause_contains_relational() -> void
  {
    using type_alias = nt::new_type<int, struct relop_presensence_test_tag_3, deriving(nt::Relational)>;
    ASSERT(has_greater_than_v<type_alias>);
  }

  auto an_instance_of_new__type_does_not_have_greater_than_if_its_derivation_clause_does_not_contain_relational() -> void
  {
    using type_alias = nt::new_type<int, struct relop_presensence_test_tag_4>;
    ASSERT(!has_greater_than_v<type_alias>);
  }

  auto an_instance_of_new__type_has_less_than_or_equal_to_if_its_derivation_clause_contains_relational() -> void
  {
    using type_alias = nt::new_type<int, struct relop_presensence_test_tag_5, deriving(nt::Relational)>;
    ASSERT(has_less_than_equal_to_v<type_alias>);
  }

  auto an_instance_of_new__type_does_not_have_less_than_or_equal_to_if_its_derivation_clause_does_not_contain_relational() -> void
  {
    using type_alias = nt::new_type<int, struct relop_presensence_test_tag_6>;
    ASSERT(!has_less_than_equal_to_v<type_alias>);
  }

  auto an_instance_of_new__type_has_greater_than_or_equal_to_if_its_derivation_clause_contains_relational() -> void
  {
    using type_alias = nt::new_type<int, struct relop_presensence_test_tag_7, deriving(nt::Relational)>;
    ASSERT(has_greater_than_equal_to_v<type_alias>);
  }

  auto an_instance_of_new__type_does_not_have_greater_than_or_equal_to_if_its_derivation_clause_does_not_contain_relational() -> void
  {
    using type_alias = nt::new_type<int, struct relop_presensence_test_tag_8>;
    ASSERT(!has_greater_than_equal_to_v<type_alias>);
  }

}  // namespace relational_operator_presence_tests

inline namespace less_than_tests
{

  auto two_instances_of_the_same_new__type_compare_less_than_if_both_contained_values_would_compare_less_than() -> void
  {
    using type_alias = nt::new_type<int, struct less_than_test_tag_9, deriving(nt::Relational)>;
    auto constexpr lhs{21};
    auto constexpr rhs{42};
    static_assert(lhs < rhs, "Sanity Check");
    ASSERT_LESS(type_alias{lhs}, type_alias{rhs});
  }

  auto two_instances_of_the_same_new__type_do_not_compare_less_than_if_both_contained_values_would_not_compare_less_than() -> void
  {
    using type_alias = nt::new_type<int, struct less_than_test_tag_10, deriving(nt::Relational)>;
    auto constexpr lhs{44};
    auto constexpr rhs{42};
    static_assert(!(lhs < rhs), "Sanity Check");
    ASSERT(!(type_alias{lhs} < type_alias{rhs}));
  }

  auto two_instances_of_the_same_new__type_compare_less_than_or_equal_if_both_contained_values_would_compare_less_than_or_equal() -> void
  {
    using type_alias = nt::new_type<int, struct less_than_test_tag_11, deriving(nt::Relational)>;
    auto constexpr lhs{33};
    auto constexpr rhs{42};
    static_assert(lhs <= rhs, "Sanity Check");
    ASSERT_LESS_EQUAL(type_alias{lhs}, type_alias{rhs});
  }

  auto two_instances_of_the_same_new__type_do_not_compare_less_than_or_equal_if_both_contained_values_would_not_compare_less_than_or_equal()
      -> void
  {
    using type_alias = nt::new_type<int, struct less_than_test_tag_12, deriving(nt::Relational)>;
    auto constexpr lhs{87};
    auto constexpr rhs{42};
    static_assert(!(lhs < rhs), "Sanity Check");
    ASSERT(!(type_alias{lhs} < type_alias{rhs}));
  }

}  // namespace less_than_tests

inline namespace greater_than_tests
{

  auto two_instances_of_the_same_new__type_compare_greater_than_if_both_contained_values_would_compare_greater_than() -> void
  {
    using type_alias = nt::new_type<int, struct greater_than_test_tag_13, deriving(nt::Relational)>;
    auto constexpr lhs{42};
    auto constexpr rhs{21};
    static_assert(lhs > rhs, "Sanity Check");
    ASSERT_GREATER(type_alias{lhs}, type_alias{rhs});
  }

  auto two_instances_of_the_same_new__type_do_not_compare_greater_than_if_both_contained_values_would_not_compare_greater_than() -> void
  {
    using type_alias = nt::new_type<int, struct greater_than_test_tag_14, deriving(nt::Relational)>;
    auto constexpr lhs{42};
    auto constexpr rhs{44};
    static_assert(!(lhs > rhs), "Sanity Check");
    ASSERT(!(type_alias{lhs} > type_alias{rhs}));
  }

  auto two_instances_of_the_same_new__type_compare_greater_than_or_equal_if_both_contained_values_would_compare_greater_than_or_equal() -> void
  {
    using type_alias = nt::new_type<int, struct greater_than_test_tag_15, deriving(nt::Relational)>;
    auto constexpr lhs{42};
    auto constexpr rhs{33};
    static_assert(lhs >= rhs, "Sanity Check");
    ASSERT_GREATER_EQUAL(type_alias{lhs}, type_alias{rhs});
  }

  auto
  two_instances_of_the_same_new__type_do_not_compare_greater_than_or_equal_if_both_contained_values_would_not_compare_greater_than_or_equal()
      -> void
  {
    using type_alias = nt::new_type<int, struct greater_than_test_tag_16, deriving(nt::Relational)>;
    auto constexpr lhs{42};
    auto constexpr rhs{87};
    static_assert(!(lhs > rhs), "Sanity Check");
    ASSERT(!(type_alias{lhs} > type_alias{rhs}));
  }

}  // namespace greater_than_tests

inline namespace relational_operator_noexcept_tests
{

  struct strange_type
  {
    auto constexpr operator<(strange_type const & other) const noexcept(false) -> bool;
    auto constexpr operator>(strange_type const & other) const noexcept(false) -> bool;
    auto constexpr operator<=(strange_type const & other) const noexcept(false) -> bool;
    auto constexpr operator>=(strange_type const & other) const noexcept(false) -> bool;
  };

  auto less_than_comparison_of_two_intances_of_the_same_new__type_is_noexcept_if_comparison_of_the_base_type_is_noexcept() -> void
  {
    using type_alias = nt::new_type<int, struct greater_than_test_tag_17, deriving(nt::Relational)>;
    static_assert(noexcept(std::declval<int const &>() < std::declval<int const &>()), "Sanity Check");
    ASSERT(noexcept(std::declval<type_alias const &>() < std::declval<type_alias const &>()));
  }

  auto less_than_comparison_of_two_intances_of_the_same_new__type_is_not_noexcept_if_comparison_of_the_base_type_is_not_noexcept() -> void
  {
    using type_alias = nt::new_type<strange_type, struct greater_than_test_tag_18, deriving(nt::Relational)>;
    static_assert(!noexcept(std::declval<strange_type const &>() < std::declval<strange_type const &>()), "Sanity Check");
    ASSERT(!noexcept(std::declval<type_alias const &>() < std::declval<type_alias const &>()));
  }

  auto less_than_equal_to_comparison_of_two_intances_of_the_same_new__type_is_noexcept_if_comparison_of_the_base_type_is_noexcept() -> void
  {
    using type_alias = nt::new_type<int, struct greater_than_test_tag_19, deriving(nt::Relational)>;
    static_assert(noexcept(std::declval<int const &>() <= std::declval<int const &>()), "Sanity Check");
    ASSERT(noexcept(std::declval<type_alias const &>() <= std::declval<type_alias const &>()));
  }

  auto less_than_equal_to_comparison_of_two_intances_of_the_same_new__type_is_not_noexcept_if_comparison_of_the_base_type_is_not_noexcept()
      -> void
  {
    using type_alias = nt::new_type<strange_type, struct greater_than_test_tag_20, deriving(nt::Relational)>;
    static_assert(!noexcept(std::declval<strange_type const &>() <= std::declval<strange_type const &>()), "Sanity Check");
    ASSERT(!noexcept(std::declval<type_alias const &>() <= std::declval<type_alias const &>()));
  }

  auto greater_than_comparison_of_two_intances_of_the_same_new__type_is_noexcept_if_comparison_of_the_base_type_is_noexcept() -> void
  {
    using type_alias = nt::new_type<int, struct greater_than_test_tag_21, deriving(nt::Relational)>;
    static_assert(noexcept(std::declval<int const &>() > std::declval<int const &>()), "Sanity Check");
    ASSERT(noexcept(std::declval<type_alias const &>() > std::declval<type_alias const &>()));
  }

  auto greater_than_comparison_of_two_intances_of_the_same_new__type_is_not_noexcept_if_comparison_of_the_base_type_is_not_noexcept() -> void
  {
    using type_alias = nt::new_type<strange_type, struct greater_than_test_tag_22, deriving(nt::Relational)>;
    static_assert(!noexcept(std::declval<strange_type const &>() > std::declval<strange_type const &>()), "Sanity Check");
    ASSERT(!noexcept(std::declval<type_alias const &>() > std::declval<type_alias const &>()));
  }

  auto greater_than_equal_to_comparison_of_two_intances_of_the_same_new__type_is_noexcept_if_comparison_of_the_base_type_is_noexcept() -> void
  {
    using type_alias = nt::new_type<int, struct greater_than_test_tag_23, deriving(nt::Relational)>;
    static_assert(noexcept(std::declval<int const &>() >= std::declval<int const &>()), "Sanity Check");
    ASSERT(noexcept(std::declval<type_alias const &>() >= std::declval<type_alias const &>()));
  }

  auto greater_than_equal_to_comparison_of_two_intances_of_the_same_new__type_is_not_noexcept_if_comparison_of_the_base_type_is_not_noexcept()
      -> void
  {
    using type_alias = nt::new_type<strange_type, struct greater_than_test_tag_24, deriving(nt::Relational)>;
    static_assert(!noexcept(std::declval<strange_type const &>() >= std::declval<strange_type const &>()), "Sanity Check");
    ASSERT(!noexcept(std::declval<type_alias const &>() >= std::declval<type_alias const &>()));
  }

}  // namespace relational_operator_noexcept_tests

auto relational_operators_suite() -> std::pair<cute::suite, std::string>
{
  return {
      {
          // clang-format off

              // Relational Operator Presensence Tests
              KAWAII(an_instance_of_new__type_has_less_than_if_its_derivation_clause_contains_relational),
              KAWAII(an_instance_of_new__type_does_not_have_less_than_if_its_derivation_clause_does_not_contain_relational),
              KAWAII(an_instance_of_new__type_has_greater_than_if_its_derivation_clause_contains_relational),
              KAWAII(an_instance_of_new__type_does_not_have_greater_than_if_its_derivation_clause_does_not_contain_relational),
              KAWAII(an_instance_of_new__type_has_less_than_or_equal_to_if_its_derivation_clause_contains_relational),
              KAWAII(an_instance_of_new__type_does_not_have_less_than_or_equal_to_if_its_derivation_clause_does_not_contain_relational),
              KAWAII(an_instance_of_new__type_has_greater_than_or_equal_to_if_its_derivation_clause_contains_relational),
              KAWAII(an_instance_of_new__type_does_not_have_greater_than_or_equal_to_if_its_derivation_clause_does_not_contain_relational),

              // Less-than Comparison Tests
              KAWAII(two_instances_of_the_same_new__type_compare_less_than_if_both_contained_values_would_compare_less_than),
              KAWAII(two_instances_of_the_same_new__type_do_not_compare_less_than_if_both_contained_values_would_not_compare_less_than),
              KAWAII(two_instances_of_the_same_new__type_compare_less_than_or_equal_if_both_contained_values_would_compare_less_than_or_equal),
              KAWAII(two_instances_of_the_same_new__type_do_not_compare_less_than_or_equal_if_both_contained_values_would_not_compare_less_than_or_equal),

              // Greater-than Comparison Tests
              KAWAII(two_instances_of_the_same_new__type_compare_greater_than_if_both_contained_values_would_compare_greater_than),
              KAWAII(two_instances_of_the_same_new__type_do_not_compare_greater_than_if_both_contained_values_would_not_compare_greater_than),
              KAWAII(two_instances_of_the_same_new__type_compare_greater_than_or_equal_if_both_contained_values_would_compare_greater_than_or_equal),
              KAWAII(two_instances_of_the_same_new__type_do_not_compare_greater_than_or_equal_if_both_contained_values_would_not_compare_greater_than_or_equal),

              // Relational Operators noexcept Tests
              KAWAII(less_than_comparison_of_two_intances_of_the_same_new__type_is_noexcept_if_comparison_of_the_base_type_is_noexcept),
              KAWAII(less_than_comparison_of_two_intances_of_the_same_new__type_is_not_noexcept_if_comparison_of_the_base_type_is_not_noexcept),
              KAWAII(less_than_equal_to_comparison_of_two_intances_of_the_same_new__type_is_noexcept_if_comparison_of_the_base_type_is_noexcept),
              KAWAII(less_than_equal_to_comparison_of_two_intances_of_the_same_new__type_is_not_noexcept_if_comparison_of_the_base_type_is_not_noexcept),
              KAWAII(greater_than_comparison_of_two_intances_of_the_same_new__type_is_noexcept_if_comparison_of_the_base_type_is_noexcept),
              KAWAII(greater_than_comparison_of_two_intances_of_the_same_new__type_is_not_noexcept_if_comparison_of_the_base_type_is_not_noexcept),
              KAWAII(greater_than_equal_to_comparison_of_two_intances_of_the_same_new__type_is_noexcept_if_comparison_of_the_base_type_is_noexcept),
              KAWAII(greater_than_equal_to_comparison_of_two_intances_of_the_same_new__type_is_not_noexcept_if_comparison_of_the_base_type_is_not_noexcept),

          // clang-format on
      },
      "Relational Operators Tests"};
}