#include "newtype/concepts.hpp"
#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/newtype.hpp"

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <string>
#include <unordered_map>

TEMPLATE_TEST_CASE("Hash", "[hash]", std::string, int)
{
  GIVEN("A new_type not deriving nt::Hash")
  {
    using type_alias = nt::new_type<TestType, struct tag>;
    static_assert(nt::concepts::hashable<typename type_alias::base_type>);

    THEN("it is not hashable")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::hashable<type_alias>);
    }
  }

  GIVEN("A new_type over a hashable type deriving nt::Hash")
  {
    using type_alias = nt::new_type<TestType, struct tag, deriving(nt::Hash)>;
    static_assert(nt::concepts::hashable<typename type_alias::base_type>);

    THEN("it is hashable")
    {
      STATIC_REQUIRE(nt::concepts::hashable<type_alias>);
    }
  }

  GIVEN("A new_type over a non-hashable type deriving nt::Hash")
  {
    struct non_hashable
    {
    };
    using type_alias = nt::new_type<non_hashable, struct tag, deriving(nt::Hash)>;
    static_assert(!nt::concepts::hashable<typename type_alias::base_type>);

    THEN("it is not hashable")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::hashable<type_alias>);
    }
  }

  GIVEN("A hashable new_type")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Hash)>;
    static_assert(nt::concepts::hashable<typename type_alias::base_type>);

    THEN("it can be used a the key in an unordered_map")
    {
      auto map = std::unordered_map<type_alias, int>{};
      map[type_alias{42}] = 43;
      REQUIRE(map[type_alias{42}] == 43);
    }
  }
}
