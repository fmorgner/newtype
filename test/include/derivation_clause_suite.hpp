#ifndef NEWTYPE_TEST_DERIVATION_CLAUSE_SUITE_HPP
#define NEWTYPE_TEST_DERIVATION_CLAUSE_SUITE_HPP

#include <cute/cute_suite.h>

#include <string>
#include <utility>

auto derivation_clause_suite() -> std::pair<cute::suite, std::string>;

#endif