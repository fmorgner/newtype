#include "conversion_suite.hpp"
#include "kawaii.hpp"
#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/impl/type_traits_extensions.hpp"
#include "newtype/new_type.hpp"

#include <cute/cute.h>

#include <type_traits>

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

auto arithmetic_suite() -> std::pair<cute::suite, std::string>
{
  return {{
              /// Addition Tests
              KAWAII(a_new__type_not_deriving_arithmetic_is_not_addable_with_instances_of_itself),
              KAWAII(a_new__type_deriving_arithmetic_is_addable_with_instances_of_itself),
              KAWAII(addition_of_two_instances_of_a_new__type_deriving_arithmetic_produces_an_instance_of_the_same_new__type),
              KAWAII(addition_of_two_instances_of_a_new__type_deriving_arithmetic_produces_the_correct_value_with_respect_to_the_base_type),
          },
          "Arithmetic Operators Tests"};
}