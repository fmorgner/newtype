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
    using reverse_iterator = void *;
    using const_reverse_iterator = void const *;

    auto begin() -> iterator;
    auto begin() const -> const_iterator;
    auto cbegin() const -> const_iterator;
    auto rbegin() -> reverse_iterator;
    auto rbegin() const -> const_reverse_iterator;
    auto crbegin() const -> const_reverse_iterator;
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

  auto accessing_the_first_element_of_an_iterator_on_a_new__type_yields_the_same_value_as_accessing_it_through_an_unwrapped_type() -> void
  {
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;
    auto weak = std::array{42, 21, 10};
    auto strong = type_alias{{42, 21, 10}};
    ASSERT_EQUAL(*weak.begin(), *strong.begin());
  }

  auto an_iterator_obtained_via_member_begin_compares_equal_to_an_iterator_obtained_via_free_begin() -> void
  {
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;
    auto instance = type_alias{{42, 21, 10}};
    ASSERT_EQUAL(begin(instance), instance.begin());
  }

}  // namespace begin_tests

inline namespace cbegin_tests
{

  auto a_new__type_not_deriving_iterable_has_no_cbegin() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::has_cbegin_v<type_alias>));
  }

  auto a_new__type_based_on_a_non_iterable_type_deriving_iterable_has_no_cbegin() -> void
  {
    static_assert(!nt::impl::has_cbegin_v<int>);
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_cbegin_v<type_alias>));
  }

  auto a_new__type_based_on_an_iterable_type_with_member_cbegin_deriving_iterable_has_member_cbegin() -> void
  {
    static_assert(nt::impl::has_member_cbegin_v<with_member>);
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_cbegin_v<type_alias>);
  }

  auto a_new__type_based_on_an_iterable_type_without_free_cbegin_deriving_iterable_has_no_free_cbegin() -> void
  {
    static_assert(!nt::impl::has_free_cbegin_v<with_member>);
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!nt::impl::has_free_cbegin_v<type_alias>);
  }

  auto accessing_the_first_element_of_a_constant_iterator_on_a_new__type_yields_the_same_value_as_accessing_it_through_an_unwrapped_type()
      -> void
  {
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;
    auto weak = std::array{42, 21, 10};
    auto strong = type_alias{{42, 21, 10}};
    ASSERT_EQUAL(*weak.cbegin(), *strong.cbegin());
  }

  auto an_iterator_obtained_via_member_cbegin_compares_equal_to_an_iterator_obtained_via_free_cbegin() -> void
  {
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;
    auto instance = type_alias{{42, 21, 10}};
    ASSERT_EQUAL(cbegin(instance), instance.cbegin());
  }

}  // namespace cbegin_tests

inline namespace rbegin_tests
{

  auto a_new__type_not_deriving_iterable_has_no_rbegin() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::has_rbegin_v<type_alias>));
  }

  auto a_new__type_based_on_a_non_iterable_type_deriving_iterable_has_no_rbegin() -> void
  {
    static_assert(!nt::impl::has_rbegin_v<int>);
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_rbegin_v<type_alias>));
  }

  auto a_new__type_based_on_an_iterable_type_with_member_rbegin_deriving_iterable_has_member_rbegin() -> void
  {
    static_assert(nt::impl::has_member_rbegin_v<with_member>);
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_rbegin_v<type_alias>);
  }

  auto a_new__type_based_on_an_iterable_type_with_constant_member_rbegin_deriving_iterable_has_constant_member_rbegin() -> void
  {
    static_assert(nt::impl::has_member_rbegin_v<with_member const>);
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_rbegin_v<type_alias const>);
  }

  auto a_new__type_based_on_an_iterable_type_without_free_rbegin_deriving_iterable_has_no_free_rbegin() -> void
  {
    static_assert(!nt::impl::has_free_rbegin_v<with_member>);
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!nt::impl::has_free_rbegin_v<type_alias>);
  }

  auto a_new__type_based_on_an_iterable_type_without_constant_free_rbegin_deriving_iterable_has_no_constant_free_rbegin() -> void
  {
    static_assert(!nt::impl::has_free_rbegin_v<with_member const>);
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!nt::impl::has_free_rbegin_v<type_alias const>);
  }

  auto accessing_the_first_element_of_a_reverse_iterator_on_a_new__type_yields_the_same_value_as_accessing_it_through_an_unwrapped_type()
      -> void
  {
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;
    auto weak = std::array{42, 21, 10};
    auto strong = type_alias{{42, 21, 10}};
    ASSERT_EQUAL(*weak.rbegin(), *strong.rbegin());
  }

  auto an_iterator_obtained_via_member_rbegin_compares_equal_to_an_iterator_obtained_via_free_rbegin() -> void
  {
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;
    auto instance = type_alias{{42, 21, 10}};
    ASSERT_EQUAL(rbegin(instance), instance.rbegin());
  }

}  // namespace rbegin_tests

inline namespace crbegin_tests
{

  auto a_new__type_not_deriving_iterable_has_no_crbegin() -> void
  {
    using type_alias = nt::new_type<int, struct tag>;
    ASSERT(!(nt::impl::has_crbegin_v<type_alias>));
  }

  auto a_new__type_based_on_a_non_iterable_type_deriving_iterable_has_no_crbegin() -> void
  {
    static_assert(!nt::impl::has_crbegin_v<int>);
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Iterable)>;
    ASSERT(!(nt::impl::has_crbegin_v<type_alias>));
  }

  auto a_new__type_based_on_an_iterable_type_with_member_crbegin_deriving_iterable_has_member_crbegin() -> void
  {
    static_assert(nt::impl::has_member_crbegin_v<with_member>);
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(nt::impl::has_member_crbegin_v<type_alias>);
  }

  auto a_new__type_based_on_an_iterable_type_without_free_crbegin_deriving_iterable_has_no_free_crbegin() -> void
  {
    static_assert(!nt::impl::has_free_crbegin_v<with_member>);
    using type_alias = nt::new_type<with_member, struct tag, deriving(nt::Iterable)>;
    ASSERT(!nt::impl::has_free_crbegin_v<type_alias>);
  }

  auto
  accessing_the_first_element_of_a_constant_reverse_iterator_on_a_new__type_yields_the_same_value_as_accessing_it_through_an_unwrapped_type()
      -> void
  {
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;
    auto weak = std::array{42, 21, 10};
    auto strong = type_alias{{42, 21, 10}};
    ASSERT_EQUAL(*weak.crbegin(), *strong.crbegin());
  }

  auto an_iterator_obtained_via_member_crbegin_compares_equal_to_an_iterator_obtained_via_free_crbegin() -> void
  {
    using type_alias = nt::new_type<std::array<int, 3>, struct tag, deriving(nt::Iterable)>;
    auto instance = type_alias{{42, 21, 10}};
    ASSERT_EQUAL(crbegin(instance), instance.crbegin());
  }

}  // namespace crbegin_tests

auto iterable_suite() -> std::pair<cute::suite, std::string>
{
  return {
      {
          // clang-format off
          /// 'begin' Tests
          KAWAII(a_new__type_not_deriving_iterable_has_no_begin),
          KAWAII(a_new__type_based_on_a_non_iterable_type_deriving_iterable_has_no_begin),
          KAWAII(a_new__type_based_on_an_iterable_type_with_member_begin_deriving_iterable_has_member_begin),
          KAWAII(a_new__type_based_on_an_iterable_type_with_constant_member_begin_deriving_iterable_has_constant_member_begin),
          KAWAII(a_new__type_based_on_an_iterable_type_without_free_begin_deriving_iterable_has_no_free_begin),
          KAWAII(a_new__type_based_on_an_iterable_type_without_constant_free_begin_deriving_iterable_has_no_constant_free_begin),
          KAWAII(accessing_the_first_element_of_an_iterator_on_a_new__type_yields_the_same_value_as_accessing_it_through_an_unwrapped_type),
          KAWAII(an_iterator_obtained_via_member_begin_compares_equal_to_an_iterator_obtained_via_free_begin),

          /// 'cbegin' Tests
          KAWAII(a_new__type_not_deriving_iterable_has_no_cbegin),
          KAWAII(a_new__type_based_on_a_non_iterable_type_deriving_iterable_has_no_cbegin),
          KAWAII(a_new__type_based_on_an_iterable_type_with_member_cbegin_deriving_iterable_has_member_cbegin),
          KAWAII(a_new__type_based_on_an_iterable_type_without_free_cbegin_deriving_iterable_has_no_free_cbegin),
          KAWAII(accessing_the_first_element_of_a_constant_iterator_on_a_new__type_yields_the_same_value_as_accessing_it_through_an_unwrapped_type),
          KAWAII(an_iterator_obtained_via_member_cbegin_compares_equal_to_an_iterator_obtained_via_free_cbegin),

          /// 'rbegin' Tests
          KAWAII(a_new__type_not_deriving_iterable_has_no_rbegin),
          KAWAII(a_new__type_based_on_a_non_iterable_type_deriving_iterable_has_no_rbegin),
          KAWAII(a_new__type_based_on_an_iterable_type_with_member_rbegin_deriving_iterable_has_member_rbegin),
          KAWAII(a_new__type_based_on_an_iterable_type_with_constant_member_rbegin_deriving_iterable_has_constant_member_rbegin),
          KAWAII(a_new__type_based_on_an_iterable_type_without_free_rbegin_deriving_iterable_has_no_free_rbegin),
          KAWAII(a_new__type_based_on_an_iterable_type_without_constant_free_rbegin_deriving_iterable_has_no_constant_free_rbegin),
          KAWAII(accessing_the_first_element_of_a_reverse_iterator_on_a_new__type_yields_the_same_value_as_accessing_it_through_an_unwrapped_type),
          KAWAII(an_iterator_obtained_via_member_rbegin_compares_equal_to_an_iterator_obtained_via_free_rbegin),

          /// 'cbegin' Tests
          KAWAII(a_new__type_not_deriving_iterable_has_no_crbegin),
          KAWAII(a_new__type_based_on_a_non_iterable_type_deriving_iterable_has_no_crbegin),
          KAWAII(a_new__type_based_on_an_iterable_type_with_member_crbegin_deriving_iterable_has_member_crbegin),
          KAWAII(a_new__type_based_on_an_iterable_type_without_free_crbegin_deriving_iterable_has_no_free_crbegin),
          KAWAII(accessing_the_first_element_of_a_constant_reverse_iterator_on_a_new__type_yields_the_same_value_as_accessing_it_through_an_unwrapped_type),
          KAWAII(an_iterator_obtained_via_member_crbegin_compares_equal_to_an_iterator_obtained_via_free_crbegin),
          // clang-format on
      },
      "Iterable Tests"};
}