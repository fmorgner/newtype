#ifndef NEWTYPE_TEST_NEW_TYPE_SUITE_HPP
#define NEWTYPE_TEST_NEW_TYPE_SUITE_HPP

#include <cute/cute_suite.h>

#include <string>
#include <utility>

auto new_type_constructor_suite() -> std::pair<cute::suite, std::string>;

#endif