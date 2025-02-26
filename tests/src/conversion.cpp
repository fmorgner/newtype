#include "newtype/newtype.hpp"

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>

#include <string>
#include <type_traits>
#include <vector>

using test_types = std::tuple<bool, char, int, double, std::string>;

TEMPLATE_LIST_TEST_CASE("Scenario: Implicit Conversions", "[conversion]", test_types)
{
  GIVEN("A new_type not deriving nt::ImplicitConversion")
  {
    using type_alias = nt::new_type<TestType, struct conversion_test>;

    THEN("it is not implicitly convertible to the base type")
    {
      STATIC_REQUIRE(!std::is_convertible_v<type_alias, TestType>);
    }
  }

  GIVEN("A new_type deriving nt::ImplicitConversion")
  {
    using type_alias = nt::new_type<TestType, struct conversion_test, deriving(nt::ImplicitConversion)>;

    THEN("it is implicitly convertible to the base type")
    {
      STATIC_REQUIRE(std::is_convertible_v<type_alias, TestType>);
    }
  }
}

TEMPLATE_LIST_TEST_CASE("Scenario: Decay", "[conversion]", test_types)
{
  GIVEN("Any new_type")
  {
    using type_alias = nt::new_type<TestType, struct conversion_test>;

    THEN("it's decay() member function returns a value of the base type")
    {
      STATIC_REQUIRE(std::is_same_v<TestType, decltype(std::declval<type_alias>().decay())>);
    }
  }

  GIVEN("Any new_type")
  {
    using type_alias = nt::new_type<TestType, struct conversion_test>;

    WHEN("an object of that type is constructed")
    {
      auto integral_value = GENERATE(take(64, random(0, 127)));
      auto value = [integral_value] {
        if constexpr (std::is_same_v<std::string, TestType>)
        {
          return std::to_string(integral_value);
        }
        else
        {
          return static_cast<TestType>(integral_value);
        }
      }();
      auto obj = type_alias{value};

      THEN("it's decay() member function return the underlying value")
      {
        REQUIRE(obj.decay() == value);
      }
    }
  }
}

SCENARIO("Nothrow Decay")
{
  struct strange_type
  {
    strange_type(strange_type const &) noexcept(false)
    {
    }
  };

  GIVEN("A new_type over a nothrow-copyable type")
  {
    using type_alias = nt::new_type<int, struct conversion_test>;

    THEN("the decay member function is nothrow-invokable")
    {
      STATIC_REQUIRE(noexcept(std::declval<type_alias>().decay()));
    }
  }

  GIVEN("A new_type over a non-nothrow-copyable type")
  {
    using type_alias = nt::new_type<strange_type, struct conversion_test>;

    THEN("the decay member function is not nothrow-invokable")
    {
      STATIC_REQUIRE(!noexcept(std::declval<type_alias>().decay()));
    }
  }
}

SCENARIO("Nothrow Conversion")
{
  struct strange_type
  {
    strange_type(strange_type const &) noexcept(false)
    {
    }
  };

  GIVEN("A new_type over a nothrow-copy-constructible type")
  {
    using type_alias = nt::new_type<int, struct conversion_test>;

    THEN("the decay member function is nothrow-invokable")
    {
      STATIC_REQUIRE(noexcept(std::declval<type_alias>().operator int()));
    }
  }

  GIVEN("A new_type over a non-nothrow-copy-constructible type")
  {
    using type_alias = nt::new_type<strange_type, struct conversion_test>;

    THEN("the decay member function is not nothrow-invokable")
    {
      STATIC_REQUIRE(!noexcept(std::declval<type_alias>().operator strange_type()));
    }
  }
}
