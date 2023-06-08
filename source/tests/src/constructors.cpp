#include "newtype/derivable.hpp"
#include "newtype/newtype.hpp"

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <type_traits>

using fundamental_types = std::tuple<bool,
                                     char,
                                     unsigned char,
                                     signed char,
                                     wchar_t,
                                     char16_t,
                                     char32_t,
                                     short,
                                     unsigned short,
                                     int,
                                     unsigned int,
                                     long,
                                     unsigned long,
                                     long long,
                                     unsigned long long,
                                     float,
                                     double,
                                     long double>;

TEMPLATE_LIST_TEST_CASE("Scenario: Construction from Fundamental Types", "[construction]", fundamental_types)
{
  GIVEN("A new_type over a fundamental type")
  {
    using type_alias = nt::new_type<TestType, struct tag>;

    THEN("objects of it can be constructed from the fundamental type")
    {
      STATIC_REQUIRE(std::is_constructible_v<type_alias, TestType>);
    }
  }
}

SCENARIO("Default Construction", "[construction]")
{
  struct not_default_constructible
  {
    not_default_constructible() = delete;
  };

  GIVEN("A new_type over a default-constructible type")
  {
    using type_alias = nt::new_type<int, struct tag>;
    static_assert(std::is_default_constructible_v<type_alias::base_type>);

    THEN("it is default-constructible")
    {
      STATIC_REQUIRE(std::is_default_constructible_v<type_alias>);
    }
  }

  GIVEN("A new_type over a type that is not default-constructible")
  {
    using type_alias = nt::new_type<not_default_constructible, struct tag>;
    static_assert(!std::is_default_constructible_v<type_alias::base_type>);

    THEN("it is not default-constructible")
    {
      STATIC_REQUIRE_FALSE(std::is_default_constructible_v<type_alias>);
    }
  }
}

SCENARIO("Copy Construction", "[construction]")
{
  struct not_copy_constructible
  {
    not_copy_constructible() = default;
    not_copy_constructible(not_copy_constructible const &) = delete;
    not_copy_constructible(not_copy_constructible &&) = default;
    auto operator=(not_copy_constructible const &) -> not_copy_constructible & = default;
    auto operator=(not_copy_constructible &&) -> not_copy_constructible & = default;
  };

  GIVEN("A new_type over a copy-constructible type")
  {
    using type_alias = nt::new_type<int, struct tag>;
    static_assert(std::is_copy_constructible_v<type_alias::base_type>);

    THEN("it is copy-constructible")
    {
      STATIC_REQUIRE(std::is_copy_constructible_v<type_alias>);
    }
  }

  GIVEN("A new_type over a type that is not copy-constructible")
  {
    using type_alias = nt::new_type<not_copy_constructible, struct tag>;
    static_assert(!std::is_copy_constructible_v<type_alias::base_type>);

    THEN("it is not copy-constructible")
    {
      STATIC_REQUIRE_FALSE(std::is_copy_constructible_v<type_alias>);
    }
  }
}
