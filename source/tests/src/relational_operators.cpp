#include "newtype/newtype.hpp"

#include <catch2/catch_test_macros.hpp>

#include <istream>
#include <string>
#include <type_traits>
#include <utility>

SCENARIO("Relational Operator Availability")
{
  GIVEN("A new_type over a relationally comparable type not deriving nt::Relational")
  {
    using type_alias = nt::new_type<int, struct tag>;
    static_assert(nt::concepts::less_than_comparable<type_alias::base_type>);
    static_assert(nt::concepts::less_than_equal_comparable<type_alias::base_type>);
    static_assert(nt::concepts::greater_than_comparable<type_alias::base_type>);
    static_assert(nt::concepts::greater_than_equal_comparable<type_alias::base_type>);

    THEN("it does not have <")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::less_than_comparable<type_alias>);
    }

    THEN("it does not have <=")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::less_than_equal_comparable<type_alias>);
    }

    THEN("it does not have >")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::greater_than_comparable<type_alias>);
    }

    THEN("it does not have >=")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::greater_than_equal_comparable<type_alias>);
    }
  }

  GIVEN("A new_type over a relationally comparable type deriving nt::Relational")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Relational)>;
    static_assert(nt::concepts::less_than_comparable<type_alias::base_type>);
    static_assert(nt::concepts::less_than_equal_comparable<type_alias::base_type>);
    static_assert(nt::concepts::greater_than_comparable<type_alias::base_type>);
    static_assert(nt::concepts::greater_than_equal_comparable<type_alias::base_type>);

    THEN("it does have <")
    {
      STATIC_REQUIRE(nt::concepts::less_than_comparable<type_alias>);
    }

    THEN("it does have <=")
    {
      STATIC_REQUIRE(nt::concepts::less_than_equal_comparable<type_alias>);
    }

    THEN("it does have >")
    {
      STATIC_REQUIRE(nt::concepts::greater_than_comparable<type_alias>);
    }

    THEN("it does have >=")
    {
      STATIC_REQUIRE(nt::concepts::greater_than_equal_comparable<type_alias>);
    }
  }

  GIVEN("A new_type over a type that is not relationally comparable not deriving nt::Relational")
  {
    using type_alias = nt::new_type<std::istream, struct tag>;
    static_assert(!nt::concepts::less_than_comparable<type_alias::base_type>);
    static_assert(!nt::concepts::less_than_equal_comparable<type_alias::base_type>);
    static_assert(!nt::concepts::greater_than_comparable<type_alias::base_type>);
    static_assert(!nt::concepts::greater_than_equal_comparable<type_alias::base_type>);

    THEN("it does not have <")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::less_than_comparable<type_alias>);
    }

    THEN("it does not have <=")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::less_than_equal_comparable<type_alias>);
    }

    THEN("it does not have >")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::greater_than_comparable<type_alias>);
    }

    THEN("it does not have >=")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::greater_than_equal_comparable<type_alias>);
    }
  }

  GIVEN("A new_type over a type that is not relationally comparable deriving nt::Relational")
  {
    using type_alias = nt::new_type<std::istream, struct tag, deriving(nt::Relational)>;
    static_assert(!nt::concepts::less_than_comparable<type_alias::base_type>);
    static_assert(!nt::concepts::less_than_equal_comparable<type_alias::base_type>);
    static_assert(!nt::concepts::greater_than_comparable<type_alias::base_type>);
    static_assert(!nt::concepts::greater_than_equal_comparable<type_alias::base_type>);

    THEN("it does not have <")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::less_than_comparable<type_alias>);
    }

    THEN("it does not have <=")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::less_than_equal_comparable<type_alias>);
    }

    THEN("it does not have >")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::greater_than_comparable<type_alias>);
    }

    THEN("it does not have >=")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::greater_than_equal_comparable<type_alias>);
    }
  }
}

SCENARIO("Relational Comparisons")
{
  GIVEN("A new_type over a relationally comparable type deriving nt::Relational")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Relational)>;
    static_assert(nt::concepts::less_than_comparable<type_alias::base_type>);
    static_assert(nt::concepts::less_than_equal_comparable<type_alias::base_type>);
    static_assert(nt::concepts::greater_than_comparable<type_alias::base_type>);
    static_assert(nt::concepts::greater_than_equal_comparable<type_alias::base_type>);

    THEN("comparing two instances using < yields the same result as it does for the base type")
    {
      REQUIRE((type_alias{1} < type_alias{2}) == (1 < 2));
      REQUIRE((type_alias{2} < type_alias{1}) == (2 < 1));
    }

    THEN("comparing two instances using <= yields the same result as it does for the base type")
    {
      REQUIRE((type_alias{1} <= type_alias{2}) == (1 <= 2));
      REQUIRE((type_alias{2} <= type_alias{1}) == (2 <= 1));
    }

    THEN("comparing two instances using > yields the same result as it does for the base type")
    {
      REQUIRE((type_alias{1} > type_alias{2}) == (1 > 2));
      REQUIRE((type_alias{2} > type_alias{1}) == (2 > 1));
    }

    THEN("comparing two instances using >= yields the same result as it does for the base type")
    {
      REQUIRE((type_alias{1} >= type_alias{2}) == (1 >= 2));
      REQUIRE((type_alias{2} >= type_alias{1}) == (2 >= 1));
    }
  }
}

SCENARIO("Nothrow Relational Comparison")
{
  GIVEN("A new_type over a nothrow relationally comparable type deriving nt::Relational")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Relational)>;
    static_assert(nt::concepts::nothrow_less_than_comparable<type_alias::base_type>);
    static_assert(nt::concepts::nothrow_less_than_equal_comparable<type_alias::base_type>);
    static_assert(nt::concepts::nothrow_greater_than_comparable<type_alias::base_type>);
    static_assert(nt::concepts::nothrow_greater_than_equal_comparable<type_alias::base_type>);

    THEN("it is nothrow-comparable using < ")
    {
      STATIC_REQUIRE(nt::concepts::nothrow_less_than_comparable<type_alias>);
    }

    THEN("it is nothrow-comparable using <= ")
    {
      STATIC_REQUIRE(nt::concepts::nothrow_less_than_equal_comparable<type_alias>);
    }

    THEN("it is nothrow-comparable using > ")
    {
      STATIC_REQUIRE(nt::concepts::nothrow_greater_than_comparable<type_alias>);
    }

    THEN("it is nothrow-comparable using >= ")
    {
      STATIC_REQUIRE(nt::concepts::nothrow_greater_than_equal_comparable<type_alias>);
    }
  }

  GIVEN("A new_type over a non-nothrow relationally comparable type deriving nt::Relational")
  {
    struct strange_type
    {
      auto constexpr operator<(strange_type const &) const noexcept(false) -> bool
      {
        return false;
      }
      auto constexpr operator>(strange_type const &) const noexcept(false) -> bool
      {
        return false;
      }
      auto constexpr operator<=(strange_type const &) const noexcept(false) -> bool
      {
        return false;
      }
      auto constexpr operator>=(strange_type const &) const noexcept(false) -> bool
      {
        return false;
      }
    };

    using type_alias = nt::new_type<strange_type, struct tag, deriving(nt::Relational)>;
    static_assert(nt::concepts::less_than_comparable<type_alias::base_type> &&
                  !nt::concepts::nothrow_less_than_comparable<type_alias::base_type>);
    static_assert(nt::concepts::less_than_equal_comparable<type_alias::base_type> &&
                  !nt::concepts::nothrow_less_than_equal_comparable<type_alias::base_type>);
    static_assert(nt::concepts::greater_than_comparable<type_alias::base_type> &&
                  !nt::concepts::nothrow_greater_than_comparable<type_alias::base_type>);
    static_assert(nt::concepts::greater_than_equal_comparable<type_alias::base_type> &&
                  !nt::concepts::nothrow_greater_than_equal_comparable<type_alias::base_type>);

    THEN("it is not nothrow-comparable using < ")
    {
      STATIC_REQUIRE(nt::concepts::less_than_comparable<type_alias> && !nt::concepts::nothrow_less_than_comparable<type_alias>);
    }

    THEN("it is not nothrow-comparable using <= ")
    {
      STATIC_REQUIRE(nt::concepts::less_than_equal_comparable<type_alias> && !nt::concepts::nothrow_less_than_equal_comparable<type_alias>);
    }

    THEN("it is not nothrow-comparable using > ")
    {
      STATIC_REQUIRE(nt::concepts::greater_than_comparable<type_alias> && !nt::concepts::nothrow_greater_than_comparable<type_alias>);
    }

    THEN("it is not nothrow-comparable using >= ")
    {
      STATIC_REQUIRE(nt::concepts::greater_than_equal_comparable<type_alias> &&
                     !nt::concepts::nothrow_greater_than_equal_comparable<type_alias>);
    }
  }
}
