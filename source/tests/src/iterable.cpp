#include "newtype/newtype.hpp"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <array>
#include <iterator>
#include <numeric>

namespace iterable_types
{

  struct with_member
  {
    using iterator = char *;
    using const_iterator = char const *;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    auto constexpr begin() -> iterator;
    auto constexpr begin() const -> const_iterator;
    auto constexpr cbegin() const -> const_iterator;
    auto constexpr rbegin() -> reverse_iterator;
    auto constexpr rbegin() const -> const_reverse_iterator;
    auto constexpr crbegin() const -> const_reverse_iterator;

    auto constexpr end() -> iterator;
    auto constexpr end() const -> const_iterator;
    auto constexpr cend() const -> const_iterator;
    auto constexpr rend() -> reverse_iterator;
    auto constexpr rend() const -> const_reverse_iterator;
    auto constexpr crend() const -> const_reverse_iterator;
  };

  struct with_free
  {
    using iterator = char *;
    using const_iterator = char const *;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  };

  auto constexpr begin(with_free &) -> with_free::iterator;
  auto constexpr begin(with_free const &) -> with_free::const_iterator;
  auto constexpr cbegin(with_free const &) -> with_free::const_iterator;
  auto constexpr rbegin(with_free &) -> with_free::reverse_iterator;
  auto constexpr rbegin(with_free const &) -> with_free::const_reverse_iterator;
  auto constexpr crbegin(with_free const &) -> with_free::const_reverse_iterator;
  auto constexpr end(with_free &) -> with_free::iterator;
  auto constexpr end(with_free const &) -> with_free::const_iterator;
  auto constexpr cend(with_free const &) -> with_free::const_iterator;
  auto constexpr rend(with_free &) -> with_free::reverse_iterator;
  auto constexpr rend(with_free const &) -> with_free::const_reverse_iterator;
  auto constexpr crend(with_free const &) -> with_free::const_reverse_iterator;

}  // namespace iterable_types

SCENARIO("Iterators", "[iterators]")
{
  GIVEN("A new_type over a non-iterable base type not deriving nt::Iterable")
  {
    using type_alias = nt::new_type<int, struct tag>;
    static_assert(!nt::concepts::beginnable<type_alias::base_type>);
    static_assert(!nt::concepts::beginnable<type_alias::base_type const>);
    static_assert(!nt::concepts::cbeginnable<type_alias::base_type>);
    static_assert(!nt::concepts::rbeginnable<type_alias::base_type>);
    static_assert(!nt::concepts::rbeginnable<type_alias::base_type const>);
    static_assert(!nt::concepts::crbeginnable<type_alias::base_type>);
    static_assert(!nt::concepts::endable<type_alias::base_type>);
    static_assert(!nt::concepts::endable<type_alias::base_type const>);
    static_assert(!nt::concepts::cendable<type_alias::base_type>);
    static_assert(!nt::concepts::rendable<type_alias::base_type>);
    static_assert(!nt::concepts::rendable<type_alias::base_type const>);
    static_assert(!nt::concepts::crendable<type_alias::base_type>);

    THEN("it has no begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::beginnable<type_alias>);
    }

    THEN("it has no constant begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::beginnable<type_alias const>);
    }

    THEN("it has no cbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::cbeginnable<type_alias>);
    }

    THEN("it has no rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::rbeginnable<type_alias>);
    }

    THEN("it has no constant rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::rbeginnable<type_alias const>);
    }

    THEN("it has no crbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::crbeginnable<type_alias>);
    }

    THEN("it has no end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::endable<type_alias>);
    }

    THEN("it has no constant end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::endable<type_alias const>);
    }

    THEN("it has no cend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::cendable<type_alias>);
    }

    THEN("it has no rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::rendable<type_alias>);
    }

    THEN("it has no constant rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::rendable<type_alias const>);
    }

    THEN("it has no crend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::crendable<type_alias>);
    }
  }

  GIVEN("A new_type over a non-iterable base type deriving nt::Iterable")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    static_assert(!nt::concepts::beginnable<type_alias::base_type>);
    static_assert(!nt::concepts::beginnable<type_alias::base_type const>);
    static_assert(!nt::concepts::cbeginnable<type_alias::base_type>);
    static_assert(!nt::concepts::rbeginnable<type_alias::base_type>);
    static_assert(!nt::concepts::rbeginnable<type_alias::base_type const>);
    static_assert(!nt::concepts::crbeginnable<type_alias::base_type>);
    static_assert(!nt::concepts::endable<type_alias::base_type>);
    static_assert(!nt::concepts::endable<type_alias::base_type const>);
    static_assert(!nt::concepts::cendable<type_alias::base_type>);
    static_assert(!nt::concepts::rendable<type_alias::base_type>);
    static_assert(!nt::concepts::rendable<type_alias::base_type const>);
    static_assert(!nt::concepts::crendable<type_alias::base_type>);

    THEN("it has no begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::beginnable<type_alias>);
    }

    THEN("it has no constant begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::beginnable<type_alias const>);
    }

    THEN("it has no cbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::cbeginnable<type_alias>);
    }

    THEN("it has no rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::rbeginnable<type_alias>);
    }

    THEN("it has no constant rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::rbeginnable<type_alias const>);
    }

    THEN("it has no crbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::crbeginnable<type_alias>);
    }

    THEN("it has no end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::endable<type_alias>);
    }

    THEN("it has no constant end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::endable<type_alias const>);
    }

    THEN("it has no cend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::cendable<type_alias>);
    }

    THEN("it has no rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::rendable<type_alias>);
    }

    THEN("it has no constant rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::rendable<type_alias const>);
    }

    THEN("it has no crend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::crendable<type_alias>);
    }
  }

  GIVEN("A new_type over an iterable base type not deriving nt::Iterable")
  {
    using type_alias = nt::new_type<std::array<int, 1>, struct tag>;
    static_assert(nt::concepts::beginnable<type_alias::base_type>);
    static_assert(nt::concepts::const_beginnable<type_alias::base_type>);
    static_assert(nt::concepts::cbeginnable<type_alias::base_type>);
    static_assert(nt::concepts::rbeginnable<type_alias::base_type>);
    static_assert(nt::concepts::const_rbeginnable<type_alias::base_type>);
    static_assert(nt::concepts::crbeginnable<type_alias::base_type>);
    static_assert(nt::concepts::endable<type_alias::base_type>);
    static_assert(nt::concepts::const_endable<type_alias::base_type>);
    static_assert(nt::concepts::cendable<type_alias::base_type>);
    static_assert(nt::concepts::rendable<type_alias::base_type>);
    static_assert(nt::concepts::const_rendable<type_alias::base_type>);
    static_assert(nt::concepts::crendable<type_alias::base_type>);

    THEN("it has no begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::beginnable<type_alias>);
    }

    THEN("it has no constant begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::beginnable<type_alias const>);
    }

    THEN("it has no cbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::cbeginnable<type_alias>);
    }

    THEN("it has no rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::rbeginnable<type_alias>);
    }

    THEN("it has no constant rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::rbeginnable<type_alias const>);
    }

    THEN("it has no crbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::crbeginnable<type_alias>);
    }

    THEN("it has no end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::endable<type_alias>);
    }

    THEN("it has no constant end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::endable<type_alias const>);
    }

    THEN("it has no cend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::cendable<type_alias>);
    }

    THEN("it has no rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::rendable<type_alias>);
    }

    THEN("it has no constant rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::rendable<type_alias const>);
    }

    THEN("it has no crend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::crendable<type_alias>);
    }
  }

  GIVEN("A new_type over an iterable base type deriving nt::Iterable")
  {
    using type_alias = nt::new_type<std::array<int, 1>, struct tag, deriving(nt::Iterable)>;
    static_assert(nt::concepts::beginnable<type_alias::base_type>);
    static_assert(nt::concepts::const_beginnable<type_alias::base_type>);
    static_assert(nt::concepts::cbeginnable<type_alias::base_type>);
    static_assert(nt::concepts::rbeginnable<type_alias::base_type>);
    static_assert(nt::concepts::const_rbeginnable<type_alias::base_type>);
    static_assert(nt::concepts::crbeginnable<type_alias::base_type>);
    static_assert(nt::concepts::endable<type_alias::base_type>);
    static_assert(nt::concepts::const_endable<type_alias::base_type>);
    static_assert(nt::concepts::cendable<type_alias::base_type>);
    static_assert(nt::concepts::rendable<type_alias::base_type>);
    static_assert(nt::concepts::const_rendable<type_alias::base_type>);
    static_assert(nt::concepts::crendable<type_alias::base_type>);

    THEN("it has begin")
    {
      STATIC_REQUIRE(nt::concepts::beginnable<type_alias>);
    }

    THEN("it has constant begin")
    {
      STATIC_REQUIRE(nt::concepts::const_beginnable<type_alias>);
    }

    THEN("it has cbegin")
    {
      STATIC_REQUIRE(nt::concepts::cbeginnable<type_alias>);
    }

    THEN("it has rbegin")
    {
      STATIC_REQUIRE(nt::concepts::rbeginnable<type_alias>);
    }

    THEN("it has constant rbegin")
    {
      STATIC_REQUIRE(nt::concepts::const_rbeginnable<type_alias>);
    }

    THEN("it has crbegin")
    {
      STATIC_REQUIRE(nt::concepts::crbeginnable<type_alias>);
    }

    THEN("it has end")
    {
      STATIC_REQUIRE(nt::concepts::endable<type_alias>);
    }

    THEN("it has constant end")
    {
      STATIC_REQUIRE(nt::concepts::const_endable<type_alias>);
    }

    THEN("it has cend")
    {
      STATIC_REQUIRE(nt::concepts::cendable<type_alias>);
    }

    THEN("it has rend")
    {
      STATIC_REQUIRE(nt::concepts::rendable<type_alias>);
    }

    THEN("it has constant rend")
    {
      STATIC_REQUIRE(nt::concepts::const_rendable<type_alias>);
    }

    THEN("it has crend")
    {
      STATIC_REQUIRE(nt::concepts::crendable<type_alias>);
    }
  }
}

SCENARIO("Iterators (member)", "[iterators]")
{
  GIVEN("A new_type over a non-iterable base type not deriving nt::Iterable")
  {
    using type_alias = nt::new_type<int, struct tag>;
    static_assert(!nt::concepts::member_begin<type_alias::base_type>);
    static_assert(!nt::concepts::const_member_begin<type_alias::base_type>);
    static_assert(!nt::concepts::member_cbegin<type_alias::base_type>);
    static_assert(!nt::concepts::member_rbegin<type_alias::base_type>);
    static_assert(!nt::concepts::const_member_rbegin<type_alias::base_type>);
    static_assert(!nt::concepts::member_crbegin<type_alias::base_type>);
    static_assert(!nt::concepts::member_end<type_alias::base_type>);
    static_assert(!nt::concepts::const_member_end<type_alias::base_type>);
    static_assert(!nt::concepts::member_cend<type_alias::base_type>);
    static_assert(!nt::concepts::member_rend<type_alias::base_type>);
    static_assert(!nt::concepts::const_member_rend<type_alias::base_type>);
    static_assert(!nt::concepts::member_crend<type_alias::base_type>);

    THEN("it has no member begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_begin<type_alias>);
    }

    THEN("it has no member constant begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_begin<type_alias const>);
    }

    THEN("it has no member cbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_cbegin<type_alias>);
    }

    THEN("it has no member rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_rbegin<type_alias>);
    }

    THEN("it has no member constant rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_rbegin<type_alias const>);
    }

    THEN("it has no member crbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_crbegin<type_alias>);
    }

    THEN("it has no member end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_end<type_alias>);
    }

    THEN("it has no member constant end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_end<type_alias const>);
    }

    THEN("it has no member cend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_cend<type_alias>);
    }

    THEN("it has no member rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_rend<type_alias>);
    }

    THEN("it has no member constant rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_rend<type_alias const>);
    }

    THEN("it has no member crend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_crend<type_alias>);
    }
  }

  GIVEN("A new_type over a non-iterable base type deriving nt::Iterable")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    static_assert(!nt::concepts::member_begin<type_alias::base_type>);
    static_assert(!nt::concepts::const_member_begin<type_alias::base_type>);
    static_assert(!nt::concepts::member_cbegin<type_alias::base_type>);
    static_assert(!nt::concepts::member_rbegin<type_alias::base_type>);
    static_assert(!nt::concepts::const_member_rbegin<type_alias::base_type>);
    static_assert(!nt::concepts::member_crbegin<type_alias::base_type>);
    static_assert(!nt::concepts::member_end<type_alias::base_type>);
    static_assert(!nt::concepts::const_member_end<type_alias::base_type>);
    static_assert(!nt::concepts::member_cend<type_alias::base_type>);
    static_assert(!nt::concepts::member_rend<type_alias::base_type>);
    static_assert(!nt::concepts::const_member_rend<type_alias::base_type>);
    static_assert(!nt::concepts::member_crend<type_alias::base_type>);

    THEN("it has no member begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_begin<type_alias>);
    }

    THEN("it has no member constant begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_begin<type_alias const>);
    }

    THEN("it has no member cbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_cbegin<type_alias>);
    }

    THEN("it has no member rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_rbegin<type_alias>);
    }

    THEN("it has no member constant rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_rbegin<type_alias const>);
    }

    THEN("it has no member crbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_crbegin<type_alias>);
    }

    THEN("it has no member end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_end<type_alias>);
    }

    THEN("it has no member constant end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_end<type_alias const>);
    }

    THEN("it has no member cend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_cend<type_alias>);
    }

    THEN("it has no member rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_rend<type_alias>);
    }

    THEN("it has no member constant rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_rend<type_alias const>);
    }

    THEN("it has no member crend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_crend<type_alias>);
    }
  }

  GIVEN("A new_type over an iterable base type not deriving nt::Iterable")
  {
    using type_alias = nt::new_type<std::array<int, 1>, struct tag>;
    static_assert(nt::concepts::member_begin<type_alias::base_type>);
    static_assert(nt::concepts::const_member_begin<type_alias::base_type>);
    static_assert(nt::concepts::member_cbegin<type_alias::base_type>);
    static_assert(nt::concepts::member_rbegin<type_alias::base_type>);
    static_assert(nt::concepts::const_member_rbegin<type_alias::base_type>);
    static_assert(nt::concepts::member_crbegin<type_alias::base_type>);
    static_assert(nt::concepts::member_end<type_alias::base_type>);
    static_assert(nt::concepts::const_member_end<type_alias::base_type>);
    static_assert(nt::concepts::member_cend<type_alias::base_type>);
    static_assert(nt::concepts::member_rend<type_alias::base_type>);
    static_assert(nt::concepts::const_member_rend<type_alias::base_type>);
    static_assert(nt::concepts::member_crend<type_alias::base_type>);

    THEN("it has no member begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_begin<type_alias>);
    }

    THEN("it has no member constant begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_begin<type_alias const>);
    }

    THEN("it has no member cbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_cbegin<type_alias>);
    }

    THEN("it has no member rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_rbegin<type_alias>);
    }

    THEN("it has no member constant rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_rbegin<type_alias const>);
    }

    THEN("it has no member crbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_crbegin<type_alias>);
    }

    THEN("it has no member end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_end<type_alias>);
    }

    THEN("it has no member constant end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_end<type_alias const>);
    }

    THEN("it has no member cend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_cend<type_alias>);
    }

    THEN("it has no member rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_rend<type_alias>);
    }

    THEN("it has no member constant rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_rend<type_alias const>);
    }

    THEN("it has no member crend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::member_crend<type_alias>);
    }
  }

  GIVEN("A new_type over an iterable base type deriving nt::Iterable")
  {
    using type_alias = nt::new_type<std::array<int, 1>, struct tag, deriving(nt::Iterable)>;
    static_assert(nt::concepts::member_begin<type_alias::base_type>);
    static_assert(nt::concepts::const_member_begin<type_alias::base_type>);
    static_assert(nt::concepts::member_cbegin<type_alias::base_type>);
    static_assert(nt::concepts::member_rbegin<type_alias::base_type>);
    static_assert(nt::concepts::const_member_rbegin<type_alias::base_type>);
    static_assert(nt::concepts::member_crbegin<type_alias::base_type>);
    static_assert(nt::concepts::member_end<type_alias::base_type>);
    static_assert(nt::concepts::const_member_end<type_alias::base_type>);
    static_assert(nt::concepts::member_cend<type_alias::base_type>);
    static_assert(nt::concepts::member_rend<type_alias::base_type>);
    static_assert(nt::concepts::const_member_rend<type_alias::base_type>);
    static_assert(nt::concepts::member_crend<type_alias::base_type>);

    THEN("it has member begin")
    {
      STATIC_REQUIRE(nt::concepts::member_begin<type_alias>);
    }

    THEN("it has member constant begin")
    {
      STATIC_REQUIRE(nt::concepts::const_member_begin<type_alias>);
    }

    THEN("it has member cbegin")
    {
      STATIC_REQUIRE(nt::concepts::member_cbegin<type_alias>);
    }

    THEN("it has member rbegin")
    {
      STATIC_REQUIRE(nt::concepts::member_rbegin<type_alias>);
    }

    THEN("it has member constant rbegin")
    {
      STATIC_REQUIRE(nt::concepts::const_member_rbegin<type_alias>);
    }

    THEN("it has member crbegin")
    {
      STATIC_REQUIRE(nt::concepts::member_crbegin<type_alias>);
    }

    THEN("it has member end")
    {
      STATIC_REQUIRE(nt::concepts::member_end<type_alias>);
    }

    THEN("it has member constant end")
    {
      STATIC_REQUIRE(nt::concepts::const_member_end<type_alias>);
    }

    THEN("it has member cend")
    {
      STATIC_REQUIRE(nt::concepts::member_cend<type_alias>);
    }

    THEN("it has member rend")
    {
      STATIC_REQUIRE(nt::concepts::member_rend<type_alias>);
    }

    THEN("it has member constant rend")
    {
      STATIC_REQUIRE(nt::concepts::const_member_rend<type_alias>);
    }

    THEN("it has member crend")
    {
      STATIC_REQUIRE(nt::concepts::member_crend<type_alias>);
    }
  }
}

SCENARIO("Iterators (free)", "[iterators]")
{
  GIVEN("A new_type over a non-iterable base type not deriving nt::Iterable")
  {
    using type_alias = nt::new_type<int, struct tag>;
    static_assert(!nt::concepts::free_begin<type_alias::base_type>);
    static_assert(!nt::concepts::const_free_begin<type_alias::base_type>);
    static_assert(!nt::concepts::free_cbegin<type_alias::base_type>);
    static_assert(!nt::concepts::free_rbegin<type_alias::base_type>);
    static_assert(!nt::concepts::const_free_rbegin<type_alias::base_type>);
    static_assert(!nt::concepts::free_crbegin<type_alias::base_type>);
    static_assert(!nt::concepts::free_end<type_alias::base_type>);
    static_assert(!nt::concepts::const_free_end<type_alias::base_type>);
    static_assert(!nt::concepts::free_cend<type_alias::base_type>);
    static_assert(!nt::concepts::free_rend<type_alias::base_type>);
    static_assert(!nt::concepts::const_free_rend<type_alias::base_type>);
    static_assert(!nt::concepts::free_crend<type_alias::base_type>);

    THEN("it has no free begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_begin<type_alias>);
    }

    THEN("it has no free constant begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::const_free_begin<type_alias>);
    }

    THEN("it has no free cbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_cbegin<type_alias>);
    }

    THEN("it has no free rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_rbegin<type_alias>);
    }

    THEN("it has no free constant rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::const_free_rbegin<type_alias>);
    }

    THEN("it has no free crbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_crbegin<type_alias>);
    }

    THEN("it has no free end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_end<type_alias>);
    }

    THEN("it has no free constant end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::const_free_end<type_alias>);
    }

    THEN("it has no free cend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_cend<type_alias>);
    }

    THEN("it has no free rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_rend<type_alias>);
    }

    THEN("it has no free constant rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::const_free_rend<type_alias>);
    }

    THEN("it has no free crend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_crend<type_alias>);
    }
  }

  GIVEN("A new_type over a non-iterable base type deriving nt::Iterable")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    static_assert(!nt::concepts::free_begin<type_alias::base_type>);
    static_assert(!nt::concepts::const_free_begin<type_alias::base_type>);
    static_assert(!nt::concepts::free_cbegin<type_alias::base_type>);
    static_assert(!nt::concepts::free_rbegin<type_alias::base_type>);
    static_assert(!nt::concepts::const_free_rbegin<type_alias::base_type>);
    static_assert(!nt::concepts::free_crbegin<type_alias::base_type>);
    static_assert(!nt::concepts::free_end<type_alias::base_type>);
    static_assert(!nt::concepts::const_free_end<type_alias::base_type>);
    static_assert(!nt::concepts::free_cend<type_alias::base_type>);
    static_assert(!nt::concepts::free_rend<type_alias::base_type>);
    static_assert(!nt::concepts::const_free_rend<type_alias::base_type>);
    static_assert(!nt::concepts::free_crend<type_alias::base_type>);

    THEN("it has no free begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_begin<type_alias>);
    }

    THEN("it has no free constant begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::const_free_begin<type_alias>);
    }

    THEN("it has no free cbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_cbegin<type_alias>);
    }

    THEN("it has no free rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_rbegin<type_alias>);
    }

    THEN("it has no free constant rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::const_free_rbegin<type_alias>);
    }

    THEN("it has no free crbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_crbegin<type_alias>);
    }

    THEN("it has no free end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_end<type_alias>);
    }

    THEN("it has no free constant end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::const_free_end<type_alias>);
    }

    THEN("it has no free cend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_cend<type_alias>);
    }

    THEN("it has no free rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_rend<type_alias>);
    }

    THEN("it has no free constant rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::const_free_rend<type_alias>);
    }

    THEN("it has no free crend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_crend<type_alias>);
    }
  }

  GIVEN("A new_type over an iterable base type not deriving nt::Iterable")
  {
    using type_alias = nt::new_type<std::array<int, 1>, struct tag>;
    static_assert(nt::concepts::free_begin<type_alias::base_type>);
    static_assert(nt::concepts::const_free_begin<type_alias::base_type>);
    static_assert(nt::concepts::free_cbegin<type_alias::base_type>);
    static_assert(nt::concepts::free_rbegin<type_alias::base_type>);
    static_assert(nt::concepts::const_free_rbegin<type_alias::base_type>);
    static_assert(nt::concepts::free_crbegin<type_alias::base_type>);
    static_assert(nt::concepts::free_end<type_alias::base_type>);
    static_assert(nt::concepts::const_free_end<type_alias::base_type>);
    static_assert(nt::concepts::free_cend<type_alias::base_type>);
    static_assert(nt::concepts::free_rend<type_alias::base_type>);
    static_assert(nt::concepts::const_free_rend<type_alias::base_type>);
    static_assert(nt::concepts::free_crend<type_alias::base_type>);

    THEN("it has no free begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_begin<type_alias>);
    }

    THEN("it has no free constant begin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_begin<type_alias const>);
    }

    THEN("it has no free cbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_cbegin<type_alias>);
    }

    THEN("it has no free rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_rbegin<type_alias>);
    }

    THEN("it has no free constant rbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_rbegin<type_alias const>);
    }

    THEN("it has no free crbegin")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_crbegin<type_alias>);
    }

    THEN("it has no free end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_end<type_alias>);
    }

    THEN("it has no free constant end")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_end<type_alias const>);
    }

    THEN("it has no free cend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_cend<type_alias>);
    }

    THEN("it has no free rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_rend<type_alias>);
    }

    THEN("it has no free constant rend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_rend<type_alias const>);
    }

    THEN("it has no free crend")
    {
      STATIC_REQUIRE_FALSE(nt::concepts::free_crend<type_alias>);
    }
  }

  GIVEN("A new_type over an iterable base type deriving nt::Iterable")
  {
    using type_alias = nt::new_type<std::array<int, 1>, struct tag, deriving(nt::Iterable)>;
    static_assert(nt::concepts::free_begin<type_alias::base_type>);
    static_assert(nt::concepts::const_free_begin<type_alias::base_type>);
    static_assert(nt::concepts::free_cbegin<type_alias::base_type>);
    static_assert(nt::concepts::free_rbegin<type_alias::base_type>);
    static_assert(nt::concepts::const_free_rbegin<type_alias::base_type>);
    static_assert(nt::concepts::free_crbegin<type_alias::base_type>);
    static_assert(nt::concepts::free_end<type_alias::base_type>);
    static_assert(nt::concepts::const_free_end<type_alias::base_type>);
    static_assert(nt::concepts::free_cend<type_alias::base_type>);
    static_assert(nt::concepts::free_rend<type_alias::base_type>);
    static_assert(nt::concepts::const_free_rend<type_alias::base_type>);
    static_assert(nt::concepts::free_crend<type_alias::base_type>);

    THEN("it has free begin")
    {
      STATIC_REQUIRE(nt::concepts::free_begin<type_alias>);
    }

    THEN("it has free constant begin")
    {
      STATIC_REQUIRE(nt::concepts::const_free_begin<type_alias>);
    }

    THEN("it has free cbegin")
    {
      STATIC_REQUIRE(nt::concepts::free_cbegin<type_alias>);
    }

    THEN("it has free rbegin")
    {
      STATIC_REQUIRE(nt::concepts::free_rbegin<type_alias>);
    }

    THEN("it has free constant rbegin")
    {
      STATIC_REQUIRE(nt::concepts::const_free_rbegin<type_alias>);
    }

    THEN("it has free crbegin")
    {
      STATIC_REQUIRE(nt::concepts::free_crbegin<type_alias>);
    }

    THEN("it has free end")
    {
      STATIC_REQUIRE(nt::concepts::free_end<type_alias>);
    }

    THEN("it has free constant end")
    {
      STATIC_REQUIRE(nt::concepts::const_free_end<type_alias>);
    }

    THEN("it has free cend")
    {
      STATIC_REQUIRE(nt::concepts::free_cend<type_alias>);
    }

    THEN("it has free rend")
    {
      STATIC_REQUIRE(nt::concepts::free_rend<type_alias>);
    }

    THEN("it has free constant rend")
    {
      STATIC_REQUIRE(nt::concepts::const_free_rend<type_alias>);
    }

    THEN("it has free crend")
    {
      STATIC_REQUIRE(nt::concepts::free_crend<type_alias>);
    }
  }
}

SCENARIO("Iterator Semantics", "[iterators]")
{
  GIVEN("An iterable new_type")
  {
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;

    THEN("a non-const object can be used in value range-based for")
    {
      auto obj = type_alias{{1, 2, 3}};
      auto res = 0;
      for (auto e : obj)
      {
        res += e;
      }
      REQUIRE(res == 6);
    }

    THEN("a const object can be used in value range-based for")
    {
      auto const obj = type_alias{{1, 2, 3}};
      auto res = 0;
      for (auto e : obj)
      {
        res += e;
      }
      REQUIRE(res == 6);
    }

    THEN("a non-const object can be used in reference range-based for")
    {
      auto obj = type_alias{{1, 2, 3}};
      auto res = 0;
      for (auto & e : obj)
      {
        res += e;
      }
      REQUIRE(res == 6);
    }

    THEN("a const object can be used in const-reference range-based for")
    {
      auto const obj = type_alias{{1, 2, 3}};
      auto res = 0;
      for (auto const & e : obj)
      {
        res += e;
      }
      REQUIRE(res == 6);
    }

    THEN("using an instance of it in an STL algorithm yields the same results as using an instance of the base type")
    {
      auto const base_obj = type_alias::base_type{{1, 2, 3}};
      auto const nt_obj = type_alias{base_obj};

      auto base_res = std::accumulate(begin(base_obj), end(base_obj), 0);
      auto nt_res = std::accumulate(begin(nt_obj), end(nt_obj), 0);

      REQUIRE(nt_res == base_res);
    }

    THEN("iterating over an instance yields the same elements in the same order as iterating over an instance of the base type")
    {
      auto const base_obj = type_alias::base_type{{1, 2, 3}};
      auto const nt_obj = type_alias{base_obj};

      REQUIRE(std::equal(cbegin(nt_obj), cend(nt_obj), cbegin(base_obj), cend(base_obj)));
    }
  }
}
