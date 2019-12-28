#ifndef NEWTYPE_TEST_EQUALITY_COMPARISON_SUITE_HPP
#define NEWTYPE_TEST_EQUALITY_COMPARISON_SUITE_HPP

#include <cute/cute_suite.h>

#include <string>
#include <utility>

auto equality_comparison_suite() -> std::pair<cute::suite, std::string>;

#endif