#include "iterable_suite.hpp"

#include "kawaii.hpp"
#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/impl/type_traits_extensions.hpp"
#include "newtype/new_type.hpp"

#include <cute/cute.h>

#include <array>
#include <iterator>

namespace
{

  struct with_member
  {
    using iterator = void *;
    using const_iterator = void const *;

    auto begin() -> iterator;
    auto begin() const -> const_iterator;
  };

}  // namespace

inline namespace begin_tests
{

  auto a_new__type_not_deriving_iterable_has_no_begin() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::has_begin_v<type_alias>));
  }

  auto a_new__type_based_on_a_non_iterable_type_deriving_iterable_has_no_begin() -> void
  {
    static_assert(!nt::impl::has_begin_v<int>);
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_begin_v<type_alias>));
  }

  auto a_new__type_based_on_an_iterable_type_with_member_begin_deriving_iterable_has_member_begin() -> void
  {
    static_assert(nt::impl::has_member_begin_v<with_member>);
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_begin_v<type_alias>);
  }

  auto a_new__type_based_on_an_iterable_type_with_constant_member_begin_deriving_iterable_has_constant_member_begin() -> void
  {
    static_assert(nt::impl::has_member_begin_v<with_member const>);
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_begin_v<type_alias const>);
  }

  auto a_new__type_based_on_an_iterable_type_without_free_begin_deriving_iterable_has_no_free_begin() -> void
  {
    static_assert(!nt::impl::has_free_begin_v<with_member>);
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!nt::impl::has_free_begin_v<type_alias>);
  }

  auto a_new__type_based_on_an_iterable_type_without_constant_free_begin_deriving_iterable_has_no_constant_free_begin() -> void
  {
    static_assert(!nt::impl::has_free_begin_v<with_member const>);
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!nt::impl::has_free_begin_v<type_alias const>);
  }

}  // namespace begin_tests

auto iterable_suite() -> std::pair<cute::suite, std::string>
{
  return {{
              /// 'begin' Tests
              KAWAII(a_new__type_not_deriving_iterable_has_no_begin),
              KAWAII(a_new__type_based_on_a_non_iterable_type_deriving_iterable_has_no_begin),
              KAWAII(a_new__type_based_on_an_iterable_type_with_member_begin_deriving_iterable_has_member_begin),
              KAWAII(a_new__type_based_on_an_iterable_type_with_constant_member_begin_deriving_iterable_has_constant_member_begin),
              KAWAII(a_new__type_based_on_an_iterable_type_without_free_begin_deriving_iterable_has_no_free_begin),
              KAWAII(a_new__type_based_on_an_iterable_type_without_constant_free_begin_deriving_iterable_has_no_constant_free_begin),
          },
          "Iterable Tests"};
}