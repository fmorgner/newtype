#include "hash_suite.hpp"

#include "kawaii.hpp"
#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/impl/type_traits_extensions.hpp"
#include "newtype/newtype.hpp"

#include <cute/cute.h>

#include <unordered_map>

inline namespace hashable_tests
{

  auto a_new__type_that_does_not_include_hash_in_its_derivation_clause_is_not_hashable() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!nt::impl::is_hashable_v<type_alias>);
  }

  auto a_new__type_that_does_include_hash_in_its_derivation_clause_is_hashable() -> void
  {
    static_assert(nt::impl::is_hashable_v<int>, "Sanity Check");
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Hash)>;
    ASSERT(nt::impl::is_hashable_v<type_alias>);
  }

  auto a_new__type_that_does_include_hash_in_its_derivation_clause_but_whose_base_type_is_not_hashable_is_also_not_hashable() -> void
  {
    struct not_hashable
    {
    };

    static_assert(!nt::impl::is_hashable_v<not_hashable>, "Sanity Check");
    using type_alias = nt::new_type<not_hashable, struct tag, deriving(nt::Hash)>;
    ASSERT(!nt::impl::is_hashable_v<type_alias>);
  }

}  // namespace hashable_tests

inline namespace usage_tests
{

  auto a_new__type_that_is_hashable_can_be_used_in_an_unordered__map() -> void
  {
    static_assert(nt::impl::is_hashable_v<int>, "Sanity Check");
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Hash)>;

    auto map = std::unordered_map<type_alias, int>{};
    map[type_alias{42}] = 43;
    ASSERT_EQUAL(43, map[type_alias{42}]);
  }

}  // namespace usage_tests

auto hash_suite() -> std::pair<cute::suite, std::string>
{
  return {{
              // Hashable Tests
              KAWAII(a_new__type_that_does_not_include_hash_in_its_derivation_clause_is_not_hashable),
              KAWAII(a_new__type_that_does_include_hash_in_its_derivation_clause_is_hashable),
              KAWAII(a_new__type_that_does_include_hash_in_its_derivation_clause_but_whose_base_type_is_not_hashable_is_also_not_hashable),

              // Usage Tests
              KAWAII(a_new__type_that_is_hashable_can_be_used_in_an_unordered__map),
          },
          "std::hash Support Tests"};
}