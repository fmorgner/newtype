#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/newtype.hpp"

#include <catch2/catch_test_macros.hpp>

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

SCENARIO("Stream Input")
{
  GIVEN("A new_type over a stream-inputtable type deriving nt::Read")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Read)>;
    static_assert(has_stream_input_v<type_alias::base_type>);

    THEN("it has the stream input operator")
    {
      STATIC_REQUIRE(has_stream_input_v<type_alias>);
    }

    THEN("an instance of it can be read from an std::istream")
    {
      auto obj = type_alias{};
      auto str = std::istringstream{"42"};

      str >> obj;

      REQUIRE(obj.decay() == 42);
    }
  }

  GIVEN("A new_type over a non-stream-inputtable type deriving nt::Read")
  {
    using type_alias = nt::new_type<std::istream, struct tag, deriving(nt::Read)>;
    static_assert(!has_stream_input_v<type_alias::base_type>);

    THEN("it does not have the input operator")
    {
      STATIC_REQUIRE(!has_stream_input_v<type_alias>);
    }
  }
}

SCENARIO("Stream Output")
{
  GIVEN("A new_type over a stream-outputtable type deriving nt::Show")
  {
    using type_alias = nt::new_type<int, struct tag, deriving(nt::Show)>;
    static_assert(has_stream_output_v<type_alias::base_type>);

    THEN("it has the stream output operator")
    {
      STATIC_REQUIRE(has_stream_output_v<type_alias>);
    }

    THEN("an instance of it can be written to an std::ostream")
    {
      auto obj = type_alias{42};
      auto str = std::ostringstream{};

      str << obj;

      REQUIRE(str.str() == "42");
    }
  }

  GIVEN("A new_type over a non-stream-outputtable type deriving nt::Show")
  {
    using type_alias = nt::new_type<std::istream, struct tag, deriving(nt::Show)>;
    static_assert(!has_stream_output_v<type_alias::base_type>);

    THEN("it does not have the output operator")
    {
      STATIC_REQUIRE(!has_stream_output_v<type_alias>);
    }
  }
}
