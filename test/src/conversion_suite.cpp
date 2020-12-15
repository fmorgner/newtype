#include "conversion_suite.hpp"

#include "kawaii.hpp"
#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/newtype.hpp"

#include <cute/cute.h>

#include <algorithm>
#include <iterator>
#include <limits>
#include <random>
#include <string>
#include <type_traits>
#include <vector>

inline namespace traits_extensions
{

  template<typename To, typename From, typename = void>
  struct is_implicitly_convertible : std::false_type
  {
  };

  template<typename To, typename From>
  struct is_implicitly_convertible<To, From, std::void_t<decltype(std::declval<To &>() = std::declval<From &>())>> : std::true_type
  {
  };

  template<typename To, typename From>
  auto constexpr is_implicitly_convertible_v = is_implicitly_convertible<To, From>::value;

}  // namespace traits_extensions

inline namespace ddt_support
{

  template<typename T>
  struct datum
  {
    T value;
    cute::test_failure failure;
  };

  template<typename ValueType>
  auto generate_test_set(std::size_t size) -> std::vector<datum<ValueType>>
  {
    auto device = std::random_device{};
    auto generator = std::mt19937{device()};
    auto distribution = [&] {
      auto min = std::numeric_limits<ValueType>::min();
      auto max = std::numeric_limits<ValueType>::max();
      if constexpr (std::is_floating_point_v<ValueType>)
      {
        return std::uniform_real_distribution<ValueType>(min, max);
      }
      else
      {
        return std::uniform_int_distribution<ValueType>(min, max);
      }
    }();

    auto data = std::vector<datum<ValueType>>{};
    generate_n(std::back_inserter(data), size, [&] {
      auto point = distribution(generator);
      return datum<ValueType>{point, DDT()};
    });
    return data;
  }

}  // namespace ddt_support

inline namespace implicit_conversion_tests
{

  template<typename T>
  auto a_new__type_without_deriving_implicit_conversion_is_not_implicitly_convertible_to_the_base_type() -> void
  {
    using type_alias = nt::new_type<T, struct conversion_test_1_tag>;
    ASSERT(!(is_implicitly_convertible_v<T, type_alias>));
  }

  template<typename T>
  auto a_new__type_with_deriving_implicit_conversion_is_implicitly_convertible_to_the_base_type() -> void
  {
    using type_alias = nt::new_type<T, struct conversion_test_2_tag, deriving(nt::ImplicitConversion)>;
    ASSERT((is_implicitly_convertible_v<T, type_alias>));
  }

}  // namespace implicit_conversion_tests

inline namespace decay_tests
{

  template<typename T>
  auto decay_on_a_new__type_has_a_return_type_equal_to_the_base_type() -> void
  {
    using type_alias = nt::new_type<T, struct conversion_test_3_tag>;
    ASSERT((std::is_same_v<T, decltype(std::declval<type_alias &>().decay())>));
  }

  template<typename T>
  auto decay_on_a_new__type_returns_the_underlying_value() -> void
  {
    using type_alias = nt::new_type<T, struct conversion_test_4_tag>;
    auto data = generate_test_set<T>(2 << 16);
    for_each(begin(data), end(data), [](auto & test) { ASSERT_EQUAL_DDT(test.value, type_alias{test.value}.decay(), test.failure); });
  }

}  // namespace decay_tests

inline namespace decay_noexcept_tests
{

  auto decay_on_a_new__type_is_noexcept_if_the_base_type_can_be_copied_without_throwing() -> void
  {
    static_assert(std::is_nothrow_copy_constructible_v<int>, "Sanity check");
    using type_alias = nt::new_type<int, struct conversion_test_5_tag>;
    ASSERT(noexcept(type_alias{}.decay()));
  }

  auto decay_on_a_new__type_is_not_noexcept_if_the_base_type_can_be_not_copied_without_throwing() -> void
  {
    struct strange_type
    {
      strange_type() = default;
      strange_type(strange_type const &) noexcept(false)
      {
      }
    };

    static_assert(!std::is_nothrow_copy_constructible_v<strange_type>, "Sanity check");
    using type_alias = nt::new_type<strange_type, struct conversion_test_6_tag>;
    ASSERT(!noexcept(type_alias{}.decay()));
  }

}  // namespace decay_noexcept_tests

inline namespace conversion_operator_noexcept_tests
{

  auto new__type_conversion_operator_is_noexcept_if_the_base_type_can_be_copied_without_throwing() -> void
  {
    static_assert(std::is_nothrow_copy_constructible_v<int>, "Sanity check");
    using type_alias = nt::new_type<int, struct conversion_test_5_tag>;
    ASSERT(noexcept(static_cast<int>(type_alias{})));
  }

  auto new__type_conversion_operator_is_not_noexcept_if_the_base_type_can_not_be_copied_without_throwing() -> void
  {
    struct strange_type
    {
      strange_type() = default;
      strange_type(strange_type const &) noexcept(false)
      {
      }
    };

    static_assert(!std::is_nothrow_copy_constructible_v<strange_type>, "Sanity check");
    using type_alias = nt::new_type<strange_type, struct conversion_test_5_tag>;
    ASSERT(!noexcept(static_cast<strange_type>(type_alias{})));
  }

}  // namespace conversion_operator_noexcept_tests

auto conversion_suite() -> std::pair<cute::suite, std::string>
{
  return {{
              /// Implicit Conversion Tests
              KAWAII(a_new__type_without_deriving_implicit_conversion_is_not_implicitly_convertible_to_the_base_type<bool>),
              KAWAII(a_new__type_without_deriving_implicit_conversion_is_not_implicitly_convertible_to_the_base_type<char>),
              KAWAII(a_new__type_without_deriving_implicit_conversion_is_not_implicitly_convertible_to_the_base_type<int>),
              KAWAII(a_new__type_without_deriving_implicit_conversion_is_not_implicitly_convertible_to_the_base_type<double>),
              KAWAII(a_new__type_without_deriving_implicit_conversion_is_not_implicitly_convertible_to_the_base_type<std::string>),
              KAWAII(a_new__type_with_deriving_implicit_conversion_is_implicitly_convertible_to_the_base_type<bool>),
              KAWAII(a_new__type_with_deriving_implicit_conversion_is_implicitly_convertible_to_the_base_type<char>),
              KAWAII(a_new__type_with_deriving_implicit_conversion_is_implicitly_convertible_to_the_base_type<int>),
              KAWAII(a_new__type_with_deriving_implicit_conversion_is_implicitly_convertible_to_the_base_type<double>),
              KAWAII(a_new__type_with_deriving_implicit_conversion_is_implicitly_convertible_to_the_base_type<std::string>),

              /// Decay Tests
              KAWAII(decay_on_a_new__type_has_a_return_type_equal_to_the_base_type<bool>),
              KAWAII(decay_on_a_new__type_has_a_return_type_equal_to_the_base_type<char>),
              KAWAII(decay_on_a_new__type_has_a_return_type_equal_to_the_base_type<int>),
              KAWAII(decay_on_a_new__type_has_a_return_type_equal_to_the_base_type<double>),
              KAWAII(decay_on_a_new__type_has_a_return_type_equal_to_the_base_type<std::string>),
              KAWAII(decay_on_a_new__type_returns_the_underlying_value<char>),
              KAWAII(decay_on_a_new__type_returns_the_underlying_value<int>),
              KAWAII(decay_on_a_new__type_returns_the_underlying_value<double>),

              /// Decay noexcept Tests
              KAWAII(decay_on_a_new__type_is_noexcept_if_the_base_type_can_be_copied_without_throwing),
              KAWAII(decay_on_a_new__type_is_not_noexcept_if_the_base_type_can_be_not_copied_without_throwing),

              /// Conversion Operator noexcept Tests
              KAWAII(new__type_conversion_operator_is_noexcept_if_the_base_type_can_be_copied_without_throwing),
              KAWAII(new__type_conversion_operator_is_not_noexcept_if_the_base_type_can_not_be_copied_without_throwing),
          },
          "Conversion Tests"};
}