#include "new_type_constructor_suite.hpp"

#include "kawaii.hpp"
#include "newtype/derivable.hpp"
#include "newtype/new_type.hpp"

#include <cute/cute.h>

#include <type_traits>

inline namespace constructor_tests
{

  struct not_default_constructible
  {
    not_default_constructible() = delete;
  };

  auto a_new__type_based_on_a_type_that_is_default_constructible_is_default_constructible_too() -> void
  {
    using nt_float = nt::new_type<float, struct nt_float_tag>;

    ASSERT(std::is_default_constructible_v<nt_float>);
  }

  auto a_new__type_based_on_a_type_that_is_not_default_constructible_is_not_default_constructible_too() -> void
  {
    using nt_not_default_constructible = nt::new_type<not_default_constructible, struct nt_not_default_constructible_tag>;

    ASSERT(!std::is_default_constructible_v<nt_not_default_constructible>);
  }

  template<typename OldType>
  auto a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type() -> void
  {
    using nt_old = nt::new_type<OldType, struct nt_old_tag>;

    ASSERT((std::is_constructible_v<nt_old, OldType>));
  }

}  // namespace constructor_tests

auto new_type_constructor_suite() -> std::pair<cute::suite, std::string>
{
  return {{
              KAWAII(a_new__type_based_on_a_type_that_is_default_constructible_is_default_constructible_too),
              KAWAII(a_new__type_based_on_a_type_that_is_not_default_constructible_is_not_default_constructible_too),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<bool>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<char>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<unsigned char>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<signed char>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<wchar_t>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<char16_t>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<char32_t>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<short>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<unsigned short>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<int>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<unsigned int>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<long>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<unsigned long>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<long long>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<unsigned long long>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<float>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<double>),
              KAWAII(a_new__type_based_on_a_fundamental_type_can_be_constructed_with_a_value_of_fundamental_type<long double>),
          },
          "new_type Constructor Tests"};
}