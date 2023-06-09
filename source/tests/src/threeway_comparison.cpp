#include "newtype/newtype.hpp"

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <compare>
#include <string>
#include <vector>

TEMPLATE_TEST_CASE("Scenario: Three-way Comparison", "[comparison]", int, std::string, std::vector<double>)
{
  GIVEN("A new_type over a <=> comparable base type deriving nt::ThreewayCompare")
  {
    using type_alias = nt::new_type<TestType, struct tag, deriving(nt::ThreewayCompare)>;
    static_assert(std::three_way_comparable<TestType>);

    THEN("it is equality-comparable")
    {
      STATIC_REQUIRE(std::equality_comparable<type_alias>);
    }

    THEN("it is inequality-comparable")
    {
      STATIC_REQUIRE(nt::concepts::inequality_comparable<type_alias>);
    }

    THEN("it is three-way comparable")
    {
      STATIC_REQUIRE(std::three_way_comparable<type_alias>);
    }

    THEN("it is less-than comparable")
    {
      STATIC_REQUIRE(nt::concepts::less_than_comparable<type_alias>);
    }

    THEN("it is less-than-equal comparable")
    {
      STATIC_REQUIRE(nt::concepts::greater_than_equal_comparable<type_alias>);
    }

    THEN("it is greater-than comparable")
    {
      STATIC_REQUIRE(nt::concepts::less_than_comparable<type_alias>);
    }

    THEN("it is greater-than-equal comparable")
    {
      STATIC_REQUIRE(nt::concepts::greater_than_equal_comparable<type_alias>);
    }
  }
}