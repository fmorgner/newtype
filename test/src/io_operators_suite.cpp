#include "io_operators_suite.hpp"

#include "kawaii.hpp"
#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/newtype.hpp"

#include <cute/cute.h>

#include <iosfwd>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

inline namespace traits_extensions
{

  template<typename T, typename = void>
  struct has_stream_input : std::false_type
  {
  };

  template<typename T>
  struct has_stream_input<T, std::void_t<decltype(std::declval<std::istream &>() >> std::declval<T &>())>> : std::true_type
  {
  };

  template<typename T>
  auto constexpr has_stream_input_v = has_stream_input<T>::value;

  template<typename T, typename = void>
  struct has_stream_output : std::false_type
  {
  };

  template<typename T>
  struct has_stream_output<T, std::void_t<decltype(std::declval<std::ostream &>() << std::declval<T &>())>> : std::true_type
  {
  };

  template<typename T>
  auto constexpr has_stream_output_v = has_stream_output<T>::value;

}  // namespace traits_extensions

inline namespace stream_input_operator_tests
{

  auto a_new__type_has_the_stream_input_operator_if_the_derivation_clause_contains_read() -> void
  {
    using type_alias = nt::new_type<int, struct input_op_test_tag_1, deriving(nt::Read)>;
    ASSERT(has_stream_input_v<type_alias>);
  }

  auto a_new__type_does_not_have_the_stream_input_operator_if_the_derivation_clause_does_not_contain_read() -> void
  {
    using type_alias = nt::new_type<int, struct input_op_test_tag_2>;
    ASSERT(!has_stream_input_v<type_alias>);
  }

  auto a_instance_of_a_new__type_can_be_read_from_an_istream_if_the_base_type_can_be_read_from_an_istream() -> void
  {
    static_assert(has_stream_input_v<int>, "Sanity Check");
    using type_alias = nt::new_type<int, struct input_op_test_tag_3, deriving(nt::Read)>;

    auto obj = type_alias{};
    auto input = std::istringstream{"42"};

    input >> obj;

    ASSERT_EQUAL(42, obj.decay());
  }

}  // namespace stream_input_operator_tests

inline namespace stream_output_operator_tests
{

  auto a_new__type_has_the_stream_output_operator_if_the_derivation_clause_contains_show() -> void
  {
    using type_alias = nt::new_type<int, struct output_op_test_tag_4, deriving(nt::Show)>;
    ASSERT(has_stream_output_v<type_alias>);
  }

  auto a_new__type_does_not_have_the_stream_output_operator_if_the_derivation_clause_does_not_contain_show() -> void
  {
    using type_alias = nt::new_type<int, struct output_op_test_tag_5>;
    ASSERT(!has_stream_output_v<type_alias>);
  }

  auto a_instance_of_a_new__type_can_be_written_to_an_ostream_if_the_base_type_can_be_written_to_an_ostream() -> void
  {
    static_assert(has_stream_output_v<int>, "Sanity Check");
    using type_alias = nt::new_type<int, struct output_op_test_tag_6, deriving(nt::Show)>;

    auto obj = type_alias{42};
    auto output = std::ostringstream{};

    output << obj;

    ASSERT_EQUAL("42", output.str());
  }

}  // namespace stream_output_operator_tests

auto io_operators_suite() -> std::pair<cute::suite, std::string>
{
  return {{
              // Stream Input Operator Tests
              KAWAII(a_new__type_has_the_stream_input_operator_if_the_derivation_clause_contains_read),
              KAWAII(a_new__type_does_not_have_the_stream_input_operator_if_the_derivation_clause_does_not_contain_read),
              KAWAII(a_instance_of_a_new__type_can_be_read_from_an_istream_if_the_base_type_can_be_read_from_an_istream),

              // Stream Ouput Operator Tests
              KAWAII(a_new__type_has_the_stream_output_operator_if_the_derivation_clause_contains_show),
              KAWAII(a_new__type_does_not_have_the_stream_output_operator_if_the_derivation_clause_does_not_contain_show),
              KAWAII(a_instance_of_a_new__type_can_be_written_to_an_ostream_if_the_base_type_can_be_written_to_an_ostream),
          },
          "I/O Operators Tests"};
}