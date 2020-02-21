#ifndef NEWTYPE_TEST_ITERABLE_SUITE_HPP
#define NEWTYPE_TEST_ITERABLE_SUITE_HPP

#include <cute/cute_suite.h>

#include <string>
#include <utility>

auto iterable_suite() -> std::pair<cute::suite, std::string>;

#endif