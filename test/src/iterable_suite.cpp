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

}

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
    static_assert(nt::impl::has_member_begin_v<std::array<int, 3>>);
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_begin_v<type_alias>);
  }

  auto a_new__type_based_on_an_iterable_type_with_constant_member_begin_deriving_iterable_has_constant_member_begin() -> void
  {
    static_assert(nt::impl::has_member_begin_v<std::array<int const, 3>>);
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_begin_v<type_alias const>);
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
          },
          "Iterable Tests"};
}