#include "derivation_clause_suite.hpp"

#include "kawaii.hpp"
#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"

#include <cute/cute.h>

#include <string>

inline namespace subset_tests
{

  auto an_empty_derivation_clause_does_not_contain_any_derivable() -> void
  {
    auto derivation_clause = nt::deriving();
    ASSERT(!derivation_clause(nt::Show));
  }

  auto a_derivation_clause_containing_only_show_does_not_contain_eqbase() -> void
  {
    auto derivation_clause = deriving(nt::Show);
    ASSERT(!derivation_clause(nt::EqBase));
  }

  auto a_derivation_clause_containing_only_show_does_contain_show() -> void
  {
    auto derivation_clause = deriving(nt::Show);
    ASSERT(derivation_clause(nt::Show));
  }

  auto a_derivation_clause_containing_only_show_and_eqbase_does_contain_show() -> void
  {
    auto derivation_clause = deriving(nt::Show, nt::EqBase);
    ASSERT(derivation_clause(nt::Show));
  }

  auto a_derivation_clause_containing_only_show_and_eqbase_does_contain_both_show_and_eqbase() -> void
  {
    auto derivation_clause = deriving(nt::Show, nt::EqBase);
    ASSERT(derivation_clause(nt::Show, nt::EqBase));
  }

  auto a_derivation_clause_containing_only_show_and_eqbase_does_not_contain_arithmetic() -> void
  {
    auto derivation_clause = deriving(nt::Show, nt::EqBase);
    ASSERT(!derivation_clause(nt::Arithmetic));
  }

  auto a_derivation_clause_containing_only_show_and_eqbase_does_not_contain_both_show_and_arithmetic() -> void
  {
    auto derivation_clause = deriving(nt::Show, nt::EqBase);
    ASSERT(!derivation_clause(nt::Show, nt::Arithmetic));
  }

}  // namespace subset_tests

inline namespace less_than_tests
{

  auto a_derivation_clause_containing_only_show_compares_less_than_one_containing_show_and_eqbase() -> void
  {
    auto only_show = deriving(nt::Show);
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);

    ASSERT(only_show < show_and_eqbase);
  }

  auto a_derivation_clause_containing_only_show_and_eqbase_does_not_compare_less_than_one_containing_show_and_eqbase() -> void
  {
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);
    auto also_show_and_eqbase = deriving(nt::Show, nt::EqBase);

    ASSERT(!(show_and_eqbase < also_show_and_eqbase));
  }

  auto a_derivation_clause_containing_only_show_and_eqbase_does_not_compare_less_than_one_containing_eqbase_and_show() -> void
  {
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);
    auto eqbase_and_show = deriving(nt::EqBase, nt::Show);

    ASSERT(!(show_and_eqbase < eqbase_and_show));
  }

  auto a_derivation_clause_containing_only_show_does_not_compare_less_than_one_containing_only_eqbase() -> void
  {
    auto show = deriving(nt::Show);
    auto eqbase = deriving(nt::EqBase);

    ASSERT(!(show < eqbase));
  }

}  // namespace less_than_tests

inline namespace greater_than_tests
{

  auto a_derivation_clause_containing_only_show_and_eqbase_compares_greater_than_one_containing_only_show() -> void
  {
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);
    auto show = deriving(nt::Show);

    ASSERT(show_and_eqbase > show);
  }

  auto a_derivation_clause_containing_only_show_and_eqbase_does_not_compare_greater_than_one_containing_only_show_and_eqbase() -> void
  {
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);
    auto also_show_and_eqbase = deriving(nt::Show, nt::EqBase);

    ASSERT(!(show_and_eqbase > also_show_and_eqbase));
  }

  auto a_derivation_clause_containing_only_show_and_eqbase_does_not_compare_greater_than_one_containing_only_eqbase_and_show() -> void
  {
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);
    auto eqbase_and_show = deriving(nt::EqBase, nt::Show);

    ASSERT(!(show_and_eqbase > eqbase_and_show));
  }

  auto a_derivation_clause_containing_only_show_does_not_compare_greater_than_one_containing_only_eqbase() -> void
  {
    auto show = deriving(nt::Show);
    auto eqbase = deriving(nt::EqBase);

    ASSERT(!(show > eqbase));
  }

}  // namespace greater_than_tests

inline namespace eqbaseuals_tests
{

  auto a_derivation_clause_containing_only_show_and_eqbase_is_eqbaseual_to_one_containing_only_show_and_eqbase() -> void
  {
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);
    auto also_show_and_eqbase = deriving(nt::Show, nt::EqBase);

    ASSERT_EQUAL(show_and_eqbase, also_show_and_eqbase);
  }

  auto a_derivation_clause_containing_only_show_and_eqbase_is_eqbaseual_to_one_containing_only_eqbase_and_show() -> void
  {
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);
    auto eqbase_and_show = deriving(nt::EqBase, nt::Show);

    ASSERT_EQUAL(show_and_eqbase, eqbase_and_show);
  }

  auto a_derivation_clause_containing_only_show_and_eqbase_is_not_eqbaseual_to_one_containing_only_arithmetic() -> void
  {
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);
    auto arithmetic = deriving(nt::Arithmetic);

    ASSERT(!(show_and_eqbase == arithmetic));
  }

  auto a_derivation_clause_containing_only_show_is_not_eqbaseual_to_one_containing_only_arithmetic() -> void
  {
    auto show = deriving(nt::Show);
    auto arithmetic = deriving(nt::Arithmetic);

    ASSERT(!(show == arithmetic));
  }

}  // namespace eqbaseuals_tests

inline namespace not_eqbaseuals_tests
{

  auto a_derivation_clause_containing_only_show_and_eqbase_is_not_not_eqbaseual_to_one_containing_only_show_and_eqbase() -> void
  {
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);
    auto also_show_and_eqbase = deriving(nt::Show, nt::EqBase);

    ASSERT(!(show_and_eqbase != also_show_and_eqbase));
  }

  auto a_derivation_clause_containing_only_show_and_eqbase_is_not_not_eqbaseual_to_one_containing_only_eqbase_and_show() -> void
  {
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);
    auto eqbase_and_show = deriving(nt::EqBase, nt::Show);

    ASSERT(!(show_and_eqbase != eqbase_and_show));
  }

  auto a_derivation_clause_containing_only_eqbase_and_show_is_not_eqbaseual_to_one_containing_only_arithmetic() -> void
  {
    auto eqbase_and_show = deriving(nt::EqBase, nt::Show);
    auto arithmetic = deriving(nt::Arithmetic);

    ASSERT(eqbase_and_show != arithmetic);
  }

  auto a_derivation_clause_containing_only_eqbase_is_not_eqbaseual_to_one_containing_only_arithmetic() -> void
  {
    auto eqbase = deriving(nt::EqBase);
    auto arithmetic = deriving(nt::Arithmetic);

    ASSERT(eqbase != arithmetic);
  }

}  // namespace not_eqbaseuals_tests

inline namespace less_than_or_eqbaseual_tests
{

  auto a_derivation_clause_containing_only_show_is_less_than_or_eqbaseual_to_one_containing_only_show_and_eqbase() -> void
  {
    auto only_show = deriving(nt::Show);
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);

    ASSERT(only_show <= show_and_eqbase);
  }

  auto a_derivation_clause_containing_only_show_and_eqbase_is_less_than_or_eqbaseual_to_one_containing_only_show_and_eqbase() -> void
  {
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);
    auto also_show_and_eqbase = deriving(nt::Show, nt::EqBase);

    ASSERT(show_and_eqbase <= also_show_and_eqbase);
  }

  auto a_derivation_clause_containing_only_arithmetic_is_neither_less_than_nor_eqbaseual_to_on_containing_only_show_and_eqbase() -> void
  {
    auto arithmetic = deriving(nt::Arithmetic);
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);

    ASSERT(!(arithmetic <= show_and_eqbase));
  }

}  // namespace less_than_or_eqbaseual_tests

inline namespace greater_than_or_eqbaseual_tests
{

  auto a_derivation_clause_containing_only_show_and_eqbase_is_greater_than_or_eqbaseual_to_one_containing_only_show() -> void
  {
    auto only_show = deriving(nt::Show);
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);

    ASSERT(show_and_eqbase >= only_show);
  }

  auto a_derivation_clause_containing_only_show_and_eqbase_is_greater_than_or_eqbaseual_to_one_containing_only_show_and_eqbase() -> void
  {
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);
    auto also_show_and_eqbase = deriving(nt::Show, nt::EqBase);

    ASSERT(show_and_eqbase >= also_show_and_eqbase);
  }

  auto a_derivation_clause_containing_only_show_and_eqbase_is_neither_greater_than_nor_eqbaseual_to_on_containing_only_arithmetic() -> void
  {
    auto arithmetic = deriving(nt::Arithmetic);
    auto show_and_eqbase = deriving(nt::Show, nt::EqBase);

    ASSERT(!(show_and_eqbase >= arithmetic));
  }

}  // namespace greater_than_or_eqbaseual_tests

auto derivation_clause_suite() -> std::pair<cute::suite, std::string>
{
  return {
      {
          /// Subset tests
          KAWAII(an_empty_derivation_clause_does_not_contain_any_derivable),
          KAWAII(a_derivation_clause_containing_only_show_does_not_contain_eqbase),
          KAWAII(a_derivation_clause_containing_only_show_does_contain_show),
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_does_contain_show),
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_does_contain_both_show_and_eqbase),
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_does_not_contain_arithmetic),
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_does_not_contain_both_show_and_arithmetic),

          /// Less-than tests
          KAWAII(a_derivation_clause_containing_only_show_compares_less_than_one_containing_show_and_eqbase),
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_does_not_compare_less_than_one_containing_show_and_eqbase),
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_does_not_compare_less_than_one_containing_eqbase_and_show),
          KAWAII(a_derivation_clause_containing_only_show_does_not_compare_less_than_one_containing_only_eqbase),

          /// Greater-than tests
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_compares_greater_than_one_containing_only_show),
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_does_not_compare_greater_than_one_containing_only_show_and_eqbase),
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_does_not_compare_greater_than_one_containing_only_eqbase_and_show),
          KAWAII(a_derivation_clause_containing_only_show_does_not_compare_greater_than_one_containing_only_eqbase),

          /// Equals tests
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_is_eqbaseual_to_one_containing_only_show_and_eqbase),
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_is_eqbaseual_to_one_containing_only_eqbase_and_show),
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_is_not_eqbaseual_to_one_containing_only_arithmetic),
          KAWAII(a_derivation_clause_containing_only_show_is_not_eqbaseual_to_one_containing_only_arithmetic),

          /// Not-Equals tests
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_is_not_not_eqbaseual_to_one_containing_only_show_and_eqbase),
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_is_not_not_eqbaseual_to_one_containing_only_eqbase_and_show),
          KAWAII(a_derivation_clause_containing_only_eqbase_and_show_is_not_eqbaseual_to_one_containing_only_arithmetic),
          KAWAII(a_derivation_clause_containing_only_eqbase_is_not_eqbaseual_to_one_containing_only_arithmetic),

          /// Less-than or Equals tests
          KAWAII(a_derivation_clause_containing_only_show_is_less_than_or_eqbaseual_to_one_containing_only_show_and_eqbase),
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_is_less_than_or_eqbaseual_to_one_containing_only_show_and_eqbase),
          KAWAII(a_derivation_clause_containing_only_arithmetic_is_neither_less_than_nor_eqbaseual_to_on_containing_only_show_and_eqbase),

          /// Greater-than or Equals tests
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_is_greater_than_or_eqbaseual_to_one_containing_only_show),
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_is_greater_than_or_eqbaseual_to_one_containing_only_show_and_eqbase),
          KAWAII(a_derivation_clause_containing_only_show_and_eqbase_is_neither_greater_than_nor_eqbaseual_to_on_containing_only_arithmetic),
      },
      "Derivation Clause Tests"};
}