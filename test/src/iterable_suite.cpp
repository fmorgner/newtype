#include "iterable_suite.hpp"

#include "kawaii.hpp"
#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/impl/type_traits_extensions.hpp"
#include "newtype/newtype.hpp"

#include <cute/cute.h>

#include <algorithm>
#include <array>
#include <iterator>
#include <numeric>

namespace
{

  struct with_member
  {
    using iterator = char *;
    using const_iterator = char const *;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    auto begin() -> iterator;
    auto begin() const -> const_iterator;
    auto cbegin() const -> const_iterator;
    auto rbegin() -> reverse_iterator;
    auto rbegin() const -> const_reverse_iterator;
    auto crbegin() const -> const_reverse_iterator;

    auto end() -> iterator;
    auto end() const -> const_iterator;
    auto cend() const -> const_iterator;
    auto rend() -> reverse_iterator;
    auto rend() const -> const_reverse_iterator;
    auto crend() const -> const_reverse_iterator;
  };

  struct with_free
  {
    using iterator = char *;
    using const_iterator = char const *;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  };

  auto begin(with_free &) -> with_free::iterator
  {
    return {};
  }

  auto begin(with_free const &) -> with_free::const_iterator
  {
    return {};
  }

  auto cbegin(with_free const &) -> with_free::const_iterator
  {
    return {};
  }

  auto rbegin(with_free &) -> with_free::reverse_iterator
  {
    return {};
  }

  auto rbegin(with_free const &) -> with_free::const_reverse_iterator
  {
    return {};
  }

  auto crbegin(with_free const &) -> with_free::const_reverse_iterator
  {
    return {};
  }

  auto end(with_free &) -> with_free::iterator
  {
    return {};
  }

  auto end(with_free const &) -> with_free::const_iterator
  {
    return {};
  }

  auto cend(with_free const &) -> with_free::const_iterator
  {
    return {};
  }

  auto rend(with_free &) -> with_free::reverse_iterator
  {
    return {};
  }

  auto rend(with_free const &) -> with_free::const_reverse_iterator
  {
    return {};
  }

  auto crend(with_free const &) -> with_free::const_reverse_iterator
  {
    return {};
  }

}  // namespace

inline namespace combined_enablement_tests
{

  auto a_new__type_not_deriving_iterable_has_no_begin() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::has_begin_v<type_alias>));
  }

  auto a_new__type_not_deriving_iterable_has_no_constant_begin() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::has_begin_v<type_alias const>));
  }

  auto a_new__type_not_deriving_iterable_has_no_cbegin() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::has_cbegin_v<type_alias>));
  }

  auto a_new__type_not_deriving_iterable_has_no_rbegin() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::has_rbegin_v<type_alias>));
  }

  auto a_new__type_not_deriving_iterable_has_no_constant_rbegin() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::has_rbegin_v<type_alias const>));
  }

  auto a_new__type_not_deriving_iterable_has_no_crbegin() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::has_crbegin_v<type_alias>));
  }

  auto a_new__type_not_deriving_iterable_has_no_end() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::has_end_v<type_alias>));
  }

  auto a_new__type_not_deriving_iterable_has_no_constant_end() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::has_end_v<type_alias const>));
  }

  auto a_new__type_not_deriving_iterable_has_no_cend() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::has_cend_v<type_alias>));
  }

  auto a_new__type_not_deriving_iterable_has_no_rend() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::has_rend_v<type_alias>));
  }

  auto a_new__type_not_deriving_iterable_has_no_constant_rend() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::has_rend_v<type_alias const>));
  }

  auto a_new__type_not_deriving_iterable_has_no_crend() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::has_crend_v<type_alias>));
  }

  auto a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_begin() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_begin_v<type_alias>));
  }

  auto a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_constant_begin() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_begin_v<type_alias const>));
  }

  auto a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_cbegin() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_cbegin_v<type_alias>));
  }

  auto a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_rbegin() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_rbegin_v<type_alias>));
  }

  auto a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_constant_rbegin() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_rbegin_v<type_alias const>));
  }

  auto a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_crbegin() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_crbegin_v<type_alias>));
  }

  auto a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_end() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_end_v<type_alias>));
  }

  auto a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_constant_end() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_end_v<type_alias const>));
  }

  auto a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_cend() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_cend_v<type_alias>));
  }

  auto a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_rend() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_rend_v<type_alias>));
  }

  auto a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_constant_rend() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_rend_v<type_alias const>));
  }

  auto a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_crend() -> void
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_crend_v<type_alias>));
  }

}  // namespace combined_enablement_tests

inline namespace member_enablement_tests
{

  auto a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_begin() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_member_begin_v<type_alias>));
  }

  auto a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_constant_begin() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_member_begin_v<type_alias const>));
  }

  auto a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_cbegin() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_member_cbegin_v<type_alias>));
  }

  auto a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_rbegin() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_member_rbegin_v<type_alias>));
  }

  auto a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_constant_rbegin() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_member_rbegin_v<type_alias const>));
  }

  auto a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_crbegin() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_member_crbegin_v<type_alias>));
  }

  auto a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_end() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_member_end_v<type_alias>));
  }

  auto a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_constant_end() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_member_end_v<type_alias const>));
  }

  auto a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_cend() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_member_cend_v<type_alias>));
  }

  auto a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_rend() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_member_rend_v<type_alias>));
  }

  auto a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_constant_rend() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_member_rend_v<type_alias const>));
  }

  auto a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_crend() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_member_crend_v<type_alias>));
  }

  auto a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_begin() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_begin_v<type_alias>);
  }

  auto a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_constant_begin() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_begin_v<type_alias const>);
  }

  auto a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_cbegin() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_cbegin_v<type_alias>);
  }

  auto a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_rbegin() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_rbegin_v<type_alias>);
  }

  auto a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_constant_rbegin() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_rbegin_v<type_alias const>);
  }

  auto a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_crbegin() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_crbegin_v<type_alias>);
  }

  auto a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_end() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_end_v<type_alias>);
  }

  auto a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_constant_end() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_end_v<type_alias const>);
  }

  auto a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_cend() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_cend_v<type_alias>);
  }

  auto a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_rend() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_rend_v<type_alias>);
  }

  auto a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_constant_rend() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_rend_v<type_alias const>);
  }

  auto a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_crend() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_crend_v<type_alias>);
  }

}  // namespace member_enablement_tests

inline namespace free_enablement_tests
{
  auto a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_begin() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_free_begin_v<type_alias>));
  }

  auto a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_constant_begin() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_free_begin_v<type_alias const>));
  }

  auto a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_cbegin() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_free_cbegin_v<type_alias>));
  }

  auto a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_rbegin() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_free_rbegin_v<type_alias>));
  }

  auto a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_constant_rbegin() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_free_rbegin_v<type_alias const>));
  }

  auto a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_crbegin() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_free_crbegin_v<type_alias>));
  }

  auto a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_end() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_free_end_v<type_alias>));
  }

  auto a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_constant_end() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_free_end_v<type_alias const>));
  }

  auto a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_cend() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_free_cend_v<type_alias>));
  }

  auto a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_rend() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_free_rend_v<type_alias>));
  }

  auto a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_constant_rend() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_free_rend_v<type_alias const>));
  }

  auto a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_crend() -> void
  {
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_free_crend_v<type_alias>));
  }

  auto a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_begin() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_free_begin_v<type_alias>);
  }

  auto a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_constant_begin() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_free_begin_v<type_alias const>);
  }

  auto a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_cbegin() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_free_cbegin_v<type_alias>);
  }

  auto a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_rbegin() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_free_rbegin_v<type_alias>);
  }

  auto a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_constant_rbegin() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_free_rbegin_v<type_alias const>);
  }

  auto a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_crbegin() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_free_crbegin_v<type_alias>);
  }

  auto a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_end() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_free_end_v<type_alias>);
  }

  auto a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_constant_end() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_free_end_v<type_alias const>);
  }

  auto a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_cend() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_free_cend_v<type_alias>);
  }

  auto a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_rend() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_free_rend_v<type_alias>);
  }

  auto a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_constant_rend() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_free_rend_v<type_alias const>);
  }

  auto a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_crend() -> void
  {
    using type_alias = nt::new_type<with_free, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_free_crend_v<type_alias>);
  }

}  // namespace free_enablement_tests

inline namespace semantic_tests
{

  auto a_non_const_object_of_iterable_new__type_can_be_used_in_value_range_for() -> void
  {
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;
    auto object = type_alias{{1, 2, 3}};
    for (auto e : object)
    {
      (void)e;
    }
    ASSERT(true);
  }

  auto a_const_object_of_iterable_new__type_can_be_used_in_value_range_for() -> void
  {
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;
    auto const object = type_alias{{1, 2, 3}};
    for (auto e : object)
    {
      (void)e;
    }
    ASSERT(true);
  }

  auto a_non_const_object_of_iterable_new__type_can_be_used_in_reference_range_for() -> void
  {
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;
    auto object = type_alias{{1, 2, 3}};
    for (auto & e : object)
    {
      (void)e;
    }
    ASSERT(true);
  }

  auto a_const_object_of_iterable_new__type_can_be_used_in_const_reference_range_for() -> void
  {
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;
    auto const object = type_alias{{1, 2, 3}};
    for (auto const & e : object)
    {
      (void)e;
    }
    ASSERT(true);
  }

  auto applying_accumulate_to_an_interable_new__type_yields_the_same_result_as_when_applied_to_the_base_type() -> void
  {
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;
    auto const nt_object = type_alias{{1, 2, 3}};
    auto const bt_object = type_alias::base_type{1, 2, 3};

    auto nt_result = std::accumulate(std::cbegin(nt_object), std::cend(nt_object), 0);
    auto bt_result = std::accumulate(std::cbegin(bt_object), std::cend(bt_object), 0);

    ASSERT_EQUAL(bt_result, nt_result);
  }

  auto iterating_over_an_iterable_new__type_yields_the_elements_in_the_same_order_as_when_iterating_the_base_type() -> void
  {
    using std::cbegin, std::cend, std::equal;
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;
    auto const nt_object = type_alias{{1, 2, 3}};
    auto const bt_object = type_alias::base_type{1, 2, 3};

    ASSERT(equal(cbegin(nt_object), cend(nt_object), cbegin(bt_object), cend(bt_object)));
  }

}  // namespace semantic_tests

auto iterable_suite() -> std::pair<cute::suite, std::string>
{
  return {{
              /// Combined Enablement Tests
              KAWAII(a_new__type_not_deriving_iterable_has_no_begin),
              KAWAII(a_new__type_not_deriving_iterable_has_no_constant_begin),
              KAWAII(a_new__type_not_deriving_iterable_has_no_cbegin),
              KAWAII(a_new__type_not_deriving_iterable_has_no_rbegin),
              KAWAII(a_new__type_not_deriving_iterable_has_no_constant_rbegin),
              KAWAII(a_new__type_not_deriving_iterable_has_no_crbegin),
              KAWAII(a_new__type_not_deriving_iterable_has_no_end),
              KAWAII(a_new__type_not_deriving_iterable_has_no_constant_end),
              KAWAII(a_new__type_not_deriving_iterable_has_no_cend),
              KAWAII(a_new__type_not_deriving_iterable_has_no_rend),
              KAWAII(a_new__type_not_deriving_iterable_has_no_constant_rend),
              KAWAII(a_new__type_not_deriving_iterable_has_no_crend),
              KAWAII(a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_begin),
              KAWAII(a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_constant_begin),
              KAWAII(a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_cbegin),
              KAWAII(a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_rbegin),
              KAWAII(a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_constant_rbegin),
              KAWAII(a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_crbegin),
              KAWAII(a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_end),
              KAWAII(a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_constant_end),
              KAWAII(a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_cend),
              KAWAII(a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_rend),
              KAWAII(a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_constant_rend),
              KAWAII(a_new__type_on_a_non_iterable_type_deriving_iterable_has_no_crend),

              /// Member Enablement Tests
              KAWAII(a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_begin),
              KAWAII(a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_constant_begin),
              KAWAII(a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_cbegin),
              KAWAII(a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_rbegin),
              KAWAII(a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_constant_rbegin),
              KAWAII(a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_crbegin),
              KAWAII(a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_end),
              KAWAII(a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_constant_end),
              KAWAII(a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_cend),
              KAWAII(a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_rend),
              KAWAII(a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_constant_rend),
              KAWAII(a_new__type_on_a_non_member_iterable_type_deriving_iterable_has_no_member_crend),
              KAWAII(a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_begin),
              KAWAII(a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_constant_begin),
              KAWAII(a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_cbegin),
              KAWAII(a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_rbegin),
              KAWAII(a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_constant_rbegin),
              KAWAII(a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_crbegin),
              KAWAII(a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_end),
              KAWAII(a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_constant_end),
              KAWAII(a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_cend),
              KAWAII(a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_rend),
              KAWAII(a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_constant_rend),
              KAWAII(a_new__type_on_a_member_iterable_type_deriving_iterable_has_member_crend),

              /// Free Enablement Tests
              KAWAII(a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_begin),
              KAWAII(a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_constant_begin),
              KAWAII(a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_cbegin),
              KAWAII(a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_rbegin),
              KAWAII(a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_constant_rbegin),
              KAWAII(a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_crbegin),
              KAWAII(a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_end),
              KAWAII(a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_constant_end),
              KAWAII(a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_cend),
              KAWAII(a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_rend),
              KAWAII(a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_constant_rend),
              KAWAII(a_new__type_on_a_non_free_iterable_type_deriving_iterable_has_no_free_crend),
              KAWAII(a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_begin),
              KAWAII(a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_constant_begin),
              KAWAII(a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_cbegin),
              KAWAII(a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_rbegin),
              KAWAII(a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_constant_rbegin),
              KAWAII(a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_crbegin),
              KAWAII(a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_end),
              KAWAII(a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_constant_end),
              KAWAII(a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_cend),
              KAWAII(a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_rend),
              KAWAII(a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_constant_rend),
              KAWAII(a_new__type_on_a_free_iterable_type_deriving_iterable_has_free_crend),

              /// Semantic Tests
              KAWAII(a_non_const_object_of_iterable_new__type_can_be_used_in_value_range_for),
              KAWAII(a_const_object_of_iterable_new__type_can_be_used_in_value_range_for),
              KAWAII(a_non_const_object_of_iterable_new__type_can_be_used_in_reference_range_for),
              KAWAII(a_const_object_of_iterable_new__type_can_be_used_in_const_reference_range_for),
              KAWAII(applying_accumulate_to_an_interable_new__type_yields_the_same_result_as_when_applied_to_the_base_type),
              KAWAII(iterating_over_an_iterable_new__type_yields_the_elements_in_the_same_order_as_when_iterating_the_base_type),
          },

          "Iterable Tests"};
}