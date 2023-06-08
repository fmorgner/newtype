#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/newtype.hpp"

#include <catch2/catch_test_macros.hpp>

#include <string>
#include <type_traits>
#include <utility>

SCENARIO("Equality Comparison", "[compare]")
{
  GIVEN("A new_type over an equality comparable type")
  {
    using type_alias = nt::new_type<int, struct tag>;

    THEN("two objects of it with the same value compare equal")
    {
      REQUIRE(type_alias{42} == type_alias{42});
    }

    THEN("two objects of it with the same value do not compare not-equal")
    {
      REQUIRE_FALSE(type_alias{42} != type_alias{42});
    }

    THEN("two object of it with different values do not compare equal")
    {
      REQUIRE_FALSE(type_alias{42} == type_alias{43});
    }

    THEN("two object of it with different values compare not-equal")
    {
      REQUIRE(type_alias{42} != type_alias{43});
    }

    THEN("equality comparison returns bool")
    {
      STATIC_REQUIRE(std::is_same_v<bool, decltype(std::declval<type_alias>() == std::declval<type_alias>())>);
    }

    THEN("inequality comparison returns bool")
    {
      STATIC_REQUIRE(std::is_same_v<bool, decltype(std::declval<type_alias>() != std::declval<type_alias>())>);
    }
  }

  GIVEN("A new_type deriving nt::EqBase")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::EqBase)>;

    THEN("an instance of it compares equal to the equivalent base type value")
    {
      REQUIRE(type_alias{42} == 42);
    }

    THEN("an instance of it comapres not-equal to a different base type value")
    {
      REQUIRE(type_alias{42} != 43);
    }
  }

  GIVEN("A new_type over a nothrow-comparable type")
  {
    using type_alias = nt::new_type<int, struct tag>;

    static_assert(noexcept(std::declval<type_alias::base_type>() == std::declval<type_alias::base_type>()));
    static_assert(noexcept(std::declval<type_alias::base_type>() != std::declval<type_alias::base_type>()));

    THEN("it is nothrow-equality-comparable")
    {
      STATIC_REQUIRE(noexcept(std::declval<type_alias>() == std::declval<type_alias>()));
    }

    THEN("it is nothrow-inequality-comparable")
    {
      STATIC_REQUIRE(noexcept(std::declval<type_alias>() != std::declval<type_alias>()));
    }
  }

  GIVEN("A new_type over a non-nothrow-comparable type")
  {
    struct not_nothrow_comparable
    {
      auto operator==(not_nothrow_comparable) const noexcept(false) -> bool;
      auto operator!=(not_nothrow_comparable) const noexcept(false) -> bool;
    };

    using type_alias = nt::new_type<not_nothrow_comparable, struct tag>;

    static_assert(!noexcept(std::declval<type_alias::base_type>() == std::declval<type_alias::base_type>()));
    static_assert(!noexcept(std::declval<type_alias::base_type>() != std::declval<type_alias::base_type>()));

    THEN("it is not nothrow-equality-comparable")
    {
      STATIC_REQUIRE_FALSE(noexcept(std::declval<type_alias>() == std::declval<type_alias>()));
    }

    THEN("it is not nothrow-inequality-comparable")
    {
      STATIC_REQUIRE_FALSE(noexcept(std::declval<type_alias>() != std::declval<type_alias>()));
    }
  }
}
