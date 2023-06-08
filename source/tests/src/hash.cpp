#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/impl/type_traits_extensions.hpp"
#include "newtype/newtype.hpp"

#include <catch2/catch_test_macros.hpp>

#include <unordered_map>

SCENARIO("Hash", "[hash]")
{
  GIVEN("A new_type not deriving nt::Hash")
  {
    using type_alias = nt::new_type<int, struct tag>;

    THEN("it is not hashable")
    {
      REQUIRE_FALSE(nt::impl::is_hashable_v<type_alias>);
    }
  }

  GIVEN("A new_type over a hashable type deriving nt::Hash")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Hash)>;

    THEN("it is hashable")
    {
      REQUIRE(nt::impl::is_hashable_v<type_alias>);
    }
  }

  GIVEN("A new_type over a non-hashable type deriving nt::Hash")
  {
    struct non_hashable
    {
    };
    using type_alias = nt::new_type<non_hashable, struct tag, deriving(nt::Hash)>;

    THEN("it is not hashable")
    {
      REQUIRE_FALSE(nt::impl::is_hashable_v<type_alias>);
    }
  }

  GIVEN("A hashable new_type")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Hash)>;

    THEN("it can be used a the key in an unordered_map")
    {
      auto map = std::unordered_map<type_alias, int>{};
      map[type_alias{42}] = 43;
      REQUIRE(map[type_alias{42}] == 43);
    }
  }
}
