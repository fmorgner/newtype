#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/newtype.hpp"

#include <catch2/catch_test_macros.hpp>

#include <istream>
#include <string>
#include <type_traits>
#include <utility>

inline namespace traits_extensions
{

  template<typename T, typename = void>
  struct has_less_than : std::false_type
  {
  };

  template<typename T>
  struct has_less_than<T, std::void_t<decltype(std::declval<T const &>() < std::declval<T const &>())>> : std::true_type
  {
  };

  template<typename T>
  auto constexpr has_less_than_v = has_less_than<T>::value;

  template<typename T>
  auto constexpr has_nothrow_less_than_v = has_less_than_v<T> && noexcept(std::declval<T const &>() < std::declval<T const &>());

  template<typename T, typename = void>
  struct has_greater_than : std::false_type
  {
  };

  template<typename T>
  struct has_greater_than<T, std::void_t<decltype(std::declval<T const &>() > std::declval<T const &>())>> : std::true_type
  {
  };

  template<typename T>
  auto constexpr has_greater_than_v = has_greater_than<T>::value;

  template<typename T>
  auto constexpr has_nothrow_greater_than_v = has_less_than_v<T> && noexcept(std::declval<T const &>() < std::declval<T const &>());

  template<typename T, typename = void>
  struct has_less_than_equal_to : std::false_type
  {
  };

  template<typename T>
  struct has_less_than_equal_to<T, std::void_t<decltype(std::declval<T const &>() <= std::declval<T const &>())>> : std::true_type
  {
  };

  template<typename T>
  auto constexpr has_less_than_equal_to_v = has_less_than_equal_to<T>::value;

  template<typename T>
  auto constexpr has_nothrow_less_than_equal_to_v = has_less_than_v<T> && noexcept(std::declval<T const &>() < std::declval<T const &>());

  template<typename T, typename = void>
  struct has_greater_than_equal_to : std::false_type
  {
  };

  template<typename T>
  struct has_greater_than_equal_to<T, std::void_t<decltype(std::declval<T const &>() >= std::declval<T const &>())>> : std::true_type
  {
  };

  template<typename T>
  auto constexpr has_greater_than_equal_to_v = has_greater_than_equal_to<T>::value;

  template<typename T>
  auto constexpr has_nothrow_greater_than_equal_to_v = has_less_than_v<T> && noexcept(std::declval<T const &>() < std::declval<T const &>());

}  // namespace traits_extensions

SCENARIO("Relational Operator Availability")
{
  GIVEN("A new_type over a relationally comparable type not deriving nt::Relational")
  {
    using type_alias = nt::new_type<int, struct tag>;
    static_assert(has_less_than_v<type_alias::base_type>);
    static_assert(has_less_than_equal_to_v<type_alias::base_type>);
    static_assert(has_greater_than_v<type_alias::base_type>);
    static_assert(has_greater_than_equal_to_v<type_alias::base_type>);

    THEN("it does not have <")
    {
      STATIC_REQUIRE_FALSE(has_less_than_v<type_alias>);
    }

    THEN("it does not have <=")
    {
      STATIC_REQUIRE_FALSE(has_less_than_equal_to_v<type_alias>);
    }

    THEN("it does not have >")
    {
      STATIC_REQUIRE_FALSE(has_greater_than_v<type_alias>);
    }

    THEN("it does not have >=")
    {
      STATIC_REQUIRE_FALSE(has_greater_than_equal_to_v<type_alias>);
    }
  }

  GIVEN("A new_type over a relationally comparable type deriving nt::Relational")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Relational)>;
    static_assert(has_less_than_v<type_alias::base_type>);
    static_assert(has_less_than_equal_to_v<type_alias::base_type>);
    static_assert(has_greater_than_v<type_alias::base_type>);
    static_assert(has_greater_than_equal_to_v<type_alias::base_type>);

    THEN("it does have <")
    {
      STATIC_REQUIRE(has_less_than_v<type_alias>);
    }

    THEN("it does have <=")
    {
      STATIC_REQUIRE(has_less_than_equal_to_v<type_alias>);
    }

    THEN("it does have >")
    {
      STATIC_REQUIRE(has_greater_than_v<type_alias>);
    }

    THEN("it does have >=")
    {
      STATIC_REQUIRE(has_greater_than_equal_to_v<type_alias>);
    }
  }

  GIVEN("A new_type over a type that is not relationally comparable not deriving nt::Relational")
  {
    using type_alias = nt::new_type<std::istream, struct tag>;
    static_assert(!has_less_than_v<type_alias::base_type>);
    static_assert(!has_less_than_equal_to_v<type_alias::base_type>);
    static_assert(!has_greater_than_v<type_alias::base_type>);
    static_assert(!has_greater_than_equal_to_v<type_alias::base_type>);

    THEN("it does not have <")
    {
      STATIC_REQUIRE_FALSE(has_less_than_v<type_alias>);
    }

    THEN("it does not have <=")
    {
      STATIC_REQUIRE_FALSE(has_less_than_equal_to_v<type_alias>);
    }

    THEN("it does not have >")
    {
      STATIC_REQUIRE_FALSE(has_greater_than_v<type_alias>);
    }

    THEN("it does not have >=")
    {
      STATIC_REQUIRE_FALSE(has_greater_than_equal_to_v<type_alias>);
    }
  }

  GIVEN("A new_type over a type that is not relationally comparable deriving nt::Relational")
  {
    using type_alias = nt::new_type<std::istream, struct tag, deriving(nt::Relational)>;
    static_assert(!has_less_than_v<type_alias::base_type>);
    static_assert(!has_less_than_equal_to_v<type_alias::base_type>);
    static_assert(!has_greater_than_v<type_alias::base_type>);
    static_assert(!has_greater_than_equal_to_v<type_alias::base_type>);

    THEN("it does not have <")
    {
      STATIC_REQUIRE_FALSE(has_less_than_v<type_alias>);
    }

    THEN("it does not have <=")
    {
      STATIC_REQUIRE_FALSE(has_less_than_equal_to_v<type_alias>);
    }

    THEN("it does not have >")
    {
      STATIC_REQUIRE_FALSE(has_greater_than_v<type_alias>);
    }

    THEN("it does not have >=")
    {
      STATIC_REQUIRE_FALSE(has_greater_than_equal_to_v<type_alias>);
    }
  }
}

SCENARIO("Relational Comparisons")
{
  GIVEN("A new_type over a relationally comparable type deriving nt::Relational")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Relational)>;
    static_assert(has_less_than_v<type_alias::base_type>);
    static_assert(has_less_than_equal_to_v<type_alias::base_type>);
    static_assert(has_greater_than_v<type_alias::base_type>);
    static_assert(has_greater_than_equal_to_v<type_alias::base_type>);

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
    static_assert(has_nothrow_less_than_v<type_alias::base_type>);
    static_assert(has_nothrow_less_than_equal_to_v<type_alias::base_type>);
    static_assert(has_nothrow_greater_than_v<type_alias::base_type>);
    static_assert(has_nothrow_greater_than_equal_to_v<type_alias::base_type>);

    THEN("it is nothrow-comparable using < ")
    {
      STATIC_REQUIRE(has_nothrow_less_than_v<type_alias>);
    }

    THEN("it is nothrow-comparable using <= ")
    {
      STATIC_REQUIRE(has_nothrow_less_than_equal_to_v<type_alias>);
    }

    THEN("it is nothrow-comparable using > ")
    {
      STATIC_REQUIRE(has_nothrow_greater_than_v<type_alias>);
    }

    THEN("it is nothrow-comparable using >= ")
    {
      STATIC_REQUIRE(has_nothrow_greater_than_equal_to_v<type_alias>);
    }
  }

  GIVEN("A new_type over a non-nothrow relationally comparable type deriving nt::Relational")
  {
    struct strange_type
    {
      auto constexpr operator<(strange_type const & other) const noexcept(false) -> bool;
      auto constexpr operator>(strange_type const & other) const noexcept(false) -> bool;
      auto constexpr operator<=(strange_type const & other) const noexcept(false) -> bool;
      auto constexpr operator>=(strange_type const & other) const noexcept(false) -> bool;
    };

    using type_alias = nt::new_type<strange_type, struct tag, deriving(nt::Relational)>;
    static_assert(has_less_than_v<type_alias::base_type> && !has_nothrow_less_than_v<type_alias::base_type>);
    static_assert(has_less_than_equal_to_v<type_alias::base_type> && !has_nothrow_less_than_equal_to_v<type_alias::base_type>);
    static_assert(has_greater_than_v<type_alias::base_type> && !has_nothrow_greater_than_v<type_alias::base_type>);
    static_assert(has_greater_than_equal_to_v<type_alias::base_type> && !has_nothrow_greater_than_equal_to_v<type_alias::base_type>);

    THEN("it is not nothrow-comparable using < ")
    {
      STATIC_REQUIRE(has_less_than_v<type_alias> && !has_nothrow_less_than_v<type_alias>);
    }

    THEN("it is not nothrow-comparable using <= ")
    {
      STATIC_REQUIRE(has_less_than_equal_to_v<type_alias> && !has_nothrow_less_than_equal_to_v<type_alias>);
    }

    THEN("it is not nothrow-comparable using > ")
    {
      STATIC_REQUIRE(has_greater_than_v<type_alias> && !has_nothrow_greater_than_v<type_alias>);
    }

    THEN("it is not nothrow-comparable using >= ")
    {
      STATIC_REQUIRE(has_greater_than_equal_to_v<type_alias> && !has_nothrow_greater_than_equal_to_v<type_alias>);
    }
  }
}
