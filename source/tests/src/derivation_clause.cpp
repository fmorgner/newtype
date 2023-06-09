#include "newtype/newtype.hpp"

#include <catch2/catch_test_macros.hpp>

#include <string>

SCENARIO("Derivation Clause", "[infrastructure]")
{
  GIVEN("An empty derivation clause")
  {
    auto clause = nt::deriving();

    THEN("it doesn't contain any derivable")
    {
      STATIC_REQUIRE_FALSE(clause(nt::Show));
    }
  }

  GIVEN("A derivation clause containing only nt::Show")
  {
    auto clause = deriving(nt::Show);

    THEN("it doesn't contain nt::EqBase")
    {
      STATIC_REQUIRE_FALSE(clause(nt::EqBase));
    }

    THEN("it contains nt::Show")
    {
      STATIC_REQUIRE(clause(nt::Show));
    }
  }

  GIVEN("A derivation clause containing only nt::Show and nt::EqBase")
  {
    auto clause = deriving(nt::Show, nt::EqBase);

    THEN("it contains nt::EqBase")
    {
      STATIC_REQUIRE(clause(nt::EqBase));
    }

    THEN("it contains nt::Show")
    {
      STATIC_REQUIRE(clause(nt::Show));
    }

    THEN("it contains both nt::Show and nt::EqBase")
    {
      STATIC_REQUIRE(clause(nt::Show, nt::EqBase));
    }

    THEN("it does not contain nt::Arithmetic")
    {
      STATIC_REQUIRE_FALSE(clause(nt::Arithmetic));
    }

    THEN("it does not contain both nt::Arithmetic and nt::Show")
    {
      STATIC_REQUIRE_FALSE(clause(nt::Arithmetic, nt::Show));
    }
  }
}
