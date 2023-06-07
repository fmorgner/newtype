#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/impl/type_traits_extensions.hpp"
#include "newtype/newtype.hpp"

#include <catch2/catch_test_macros.hpp>

#include <type_traits>

SCENARIO("Addition", "[arithmetic]")
{
  struct addable_type
  {
    auto constexpr operator+(addable_type const &) const -> addable_type
    {
      return {};
    };
  };

  GIVEN("A new_type instance not deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<int, struct tag>;

    THEN("it is not addable")
    {
      REQUIRE(!nt::impl::is_addable_v<type_alias>);
    }
  }

  GIVEN("A new_type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;

    THEN("it is addable")
    {
      REQUIRE(nt::impl::is_addable_v<type_alias>);
    }
  }

  GIVEN("A new_type over a non-addable class type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<void *, struct tag, deriving(nt::Arithmetic)>;

    THEN("it is not addable")
    {
      REQUIRE(!nt::impl::is_addable_v<addable_type> == nt::impl::is_addable_v<type_alias>);
    }
  }

  GIVEN("A new_type over an addable class type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<addable_type, struct tag, deriving(nt::Arithmetic)>;

    THEN("it is addable")
    {
      REQUIRE(nt::impl::is_addable_v<addable_type> == nt::impl::is_addable_v<type_alias>);
    }
  }

  GIVEN("A new_type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;

    THEN("addition produces the same type")
    {
      REQUIRE(std::is_same_v<type_alias, decltype(std::declval<type_alias const &>() + std::declval<type_alias const &>())>);
    }
  }

  GIVEN("Two objects of a new_type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;
    auto lhs = type_alias{24};
    auto rhs = type_alias{18};

    THEN("addition produces the correct result with respect to the base type")
    {
      REQUIRE((lhs + rhs).decay() == 24 + 18);
    }
  }
}

SCENARIO("Subtraction", "[arithmetic]")
{
  struct subtractable_type
  {
    auto constexpr operator-(subtractable_type const &) const -> subtractable_type
    {
      return {};
    };
  };

  GIVEN("A new_type not deriving nt::arithmetic")
  {
    using type_alias = nt::new_type<int, struct tag>;

    THEN("it is not subtractable")
    {
      REQUIRE(!nt::impl::is_subtractable_v<type_alias>);
    }
  }

  GIVEN("A new_type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;

    THEN("it is subtractable")
    {
      REQUIRE(nt::impl::is_subtractable_v<type_alias>);
    }
  }

  GIVEN("A new_type over a non-subtractable class type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<void *, struct tag, deriving(nt::Arithmetic)>;

    THEN("it is not addable")
    {
      REQUIRE(!nt::impl::is_subtractable_v<type_alias>);
    }
  }

  GIVEN("A new_type over a subtractable class type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<subtractable_type, struct tag, deriving(nt::Arithmetic)>;

    THEN("it is subtractable")
    {
      REQUIRE(nt::impl::is_subtractable_v<type_alias>);
    }
  }

  GIVEN("A new_type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;

    THEN("subtraction produces the same type")
    {
      REQUIRE(std::is_same_v<type_alias, decltype(std::declval<type_alias const &>() - std::declval<type_alias const &>())>);
    }
  }

  GIVEN("Two objects of a new_type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;
    auto lhs = type_alias{24};
    auto rhs = type_alias{18};

    THEN("subtraction produces the correct result with respect to the base type")
    {
      REQUIRE((lhs - rhs).decay() == 24 - 18);
    }
  }
}

SCENARIO("Multiplication", "[arithmetic]")
{
  struct multipliable_type
  {
    auto constexpr operator*(multipliable_type const &) const -> multipliable_type
    {
      return {};
    };
  };

  GIVEN("A new_type not deriving nt::arithmetic")
  {
    using type_alias = nt::new_type<int, struct tag>;

    THEN("it is not multipliable")
    {
      REQUIRE(!nt::impl::is_multipliable_v<type_alias>);
    }
  }

  GIVEN("A new_type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;

    THEN("it is multipliable")
    {
      REQUIRE(nt::impl::is_multipliable_v<type_alias>);
    }
  }

  GIVEN("A new_type over a non-multipliable class type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<void *, struct tag, deriving(nt::Arithmetic)>;

    THEN("it is not multipliable")
    {
      REQUIRE(!nt::impl::is_multipliable_v<type_alias>);
    }
  }

  GIVEN("A new_type over a multipliable class type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<multipliable_type, struct tag, deriving(nt::Arithmetic)>;

    THEN("it is multipliable")
    {
      REQUIRE(nt::impl::is_multipliable_v<type_alias>);
    }
  }

  GIVEN("A new_type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;

    THEN("multiplication produces the same type")
    {
      REQUIRE(std::is_same_v<type_alias, decltype(std::declval<type_alias const &>() * std::declval<type_alias const &>())>);
    }
  }

  GIVEN("Two objects of a new_type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;
    auto lhs = type_alias{24};
    auto rhs = type_alias{18};

    THEN("multiplication produces the correct result with respect to the base type")
    {
      REQUIRE((lhs * rhs).decay() == 24 * 18);
    }
  }
}

SCENARIO("Division", "[arithmetic]")
{
  struct dividable_type
  {
    auto constexpr operator/(dividable_type const &) const -> dividable_type
    {
      return {};
    };
  };

  GIVEN("A new_type not deriving nt::arithmetic")
  {
    using type_alias = nt::new_type<int, struct tag>;

    THEN("it is not divisible")
    {
      REQUIRE(!nt::impl::is_dividable_v<type_alias>);
    }
  }

  GIVEN("A new_type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;

    THEN("it is divisible")
    {
      REQUIRE(nt::impl::is_dividable_v<type_alias>);
    }
  }

  GIVEN("A new_type over a non-divisible class type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<void *, struct tag, deriving(nt::Arithmetic)>;

    THEN("it is not divisible")
    {
      REQUIRE(!nt::impl::is_dividable_v<type_alias>);
    }
  }

  GIVEN("A new_type over a divisible class type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<dividable_type, struct tag, deriving(nt::Arithmetic)>;

    THEN("it is divisible")
    {
      REQUIRE(nt::impl::is_dividable_v<type_alias>);
    }
  }

  GIVEN("A new_type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;

    THEN("division produces the same type")
    {
      REQUIRE(std::is_same_v<type_alias, decltype(std::declval<type_alias const &>() / std::declval<type_alias const &>())>);
    }
  }

  GIVEN("Two objects of a new_type deriving nt::Arithmetic")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Arithmetic)>;
    auto lhs = type_alias{30};
    auto rhs = type_alias{15};

    THEN("division produces the correct result with respect to the base type")
    {
      REQUIRE((lhs / rhs).decay() == 30 / 15);
    }
  }
}