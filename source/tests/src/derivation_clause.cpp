#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"

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

    THEN("it copares less-than one containing nt::Show and nt::EqBase")
    {
      STATIC_REQUIRE(clause < deriving(nt::Show, nt::EqBase));
    }

    THEN("it does not compare less-than one conataining only nt::EqBase")
    {
      STATIC_REQUIRE_FALSE(clause < deriving(nt::EqBase));
    }

    THEN("it does not compare greater-than one conataining only nt::EqBase")
    {
      STATIC_REQUIRE_FALSE(clause > deriving(nt::EqBase));
    }

    THEN("it does not compare equal-to one containiing only nt::Arithmetic")
    {
      STATIC_REQUIRE_FALSE(clause == deriving(nt::Arithmetic));
    }

    THEN("it compares not-equal-to one containing only nt::Arithmetic")
    {
      STATIC_REQUIRE(clause != deriving(nt::Arithmetic));
    }

    THEN("it compares less-than-equal to one containing both nt::Show and nt::EqBase")
    {
      STATIC_REQUIRE(clause <= deriving(nt::Show, nt::EqBase));
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

    THEN("it does not compare less-than one containing nt::Show and nt::EqBase")
    {
      STATIC_REQUIRE_FALSE(clause < deriving(nt::Show, nt::EqBase));
    }

    THEN("it does not compare less-than one containing nt::EqBase and nt::Show")
    {
      STATIC_REQUIRE_FALSE(clause < deriving(nt::EqBase, nt::Show));
    }

    THEN("it compares greater-than one containing only nt::Show")
    {
      STATIC_REQUIRE(clause > deriving(nt::Show));
    }

    THEN("it does not compare greater-than one containing both nt::Show and nt::EqBase")
    {
      STATIC_REQUIRE_FALSE(clause > deriving(nt::Show, nt::EqBase));
    }

    THEN("it does not compare greater-than one containing both nt::EqBase and nt::Show")
    {
      STATIC_REQUIRE_FALSE(clause > deriving(nt::EqBase, nt::Show));
    }

    THEN("it compares equal-to one containing both nt::Show and nt::EqBase")
    {
      STATIC_REQUIRE(clause == deriving(nt::Show, nt::EqBase));
    }

    THEN("it compares equal-to one containing both nt::EqBase and nt::Show")
    {
      STATIC_REQUIRE(clause == deriving(nt::EqBase, nt::Show));
    }

    THEN("it does not compare equal-to one containiing only nt::Arithmetic")
    {
      STATIC_REQUIRE_FALSE(clause == deriving(nt::Arithmetic));
    }

    THEN("it does not compare equal-to one containiing all nt::Show, nt::EqBase, and nt::Arithmetic")
    {
      STATIC_REQUIRE_FALSE(clause == deriving(nt::Show, nt::EqBase, nt::Arithmetic));
    }

    THEN("it does not compare not-equal-to one containing both nt::Show and nt::EqBase")
    {
      STATIC_REQUIRE_FALSE(clause != deriving(nt::Show, nt::EqBase));
    }

    THEN("it does not compare not-equal-to one containing both nt::Show and nt::EqBase")
    {
      STATIC_REQUIRE_FALSE(clause != deriving(nt::EqBase, nt::Show));
    }

    THEN("it compares not-equal-to one containing only nt::Arithmetic")
    {
      STATIC_REQUIRE(clause != deriving(nt::Arithmetic));
    }

    THEN("it compares less-than-equal to one containing both nt::Show and nt::EqBase")
    {
      STATIC_REQUIRE(clause <= deriving(nt::Show, nt::EqBase));
    }

    THEN("a derivation clause containing only nt::Arithmetic does not compare less-than-equal to it")
    {
      STATIC_REQUIRE_FALSE(deriving(nt::Arithmetic) <= clause);
    }

    THEN("it compares greather-than-equal to one containing only nt::Show")
    {
      STATIC_REQUIRE(clause >= deriving(nt::Show));
    }

    THEN("it compares greather-than-equal to one containing both nt::Show and nt::EqBase")
    {
      STATIC_REQUIRE(clause >= deriving(nt::Show, nt::EqBase));
    }

    THEN("it does not compare greather-than-eqaul to one containing only nt::Arithmetic")
    {
      STATIC_REQUIRE_FALSE(clause >= deriving(nt::Arithmetic));
    }
  }
}
