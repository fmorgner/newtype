#ifndef NEWTYPE_TEST_KAWAII_HPP
#define NEWTYPE_TEST_KAWAII_HPP

#include <cute/cute_test.h>

#include <algorithm>
#include <array>
#include <cctype>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>

namespace nt::test
{

  namespace impl
  {
    auto constexpr prepositions = std::array{"a", "an", "and", "as", "at", "by", "for", "in", "of", "on", "or", "the", "to"};
    auto constexpr keywords = std::array{"noexcept"};
    auto constexpr type_names = std::array{"new_type", "derivation_clause", "unordered_map"};

    auto inline replace_template_argument_syntax(std::string const & name) -> std::string
    {
      using namespace std::string_literals;

      auto template_argument_start = find(cbegin(name), cend(name), '<');

      if (template_argument_start == cend(name))
      {
        return name;
      }

      auto replaced{""s};

      copy(cbegin(name), template_argument_start, back_inserter(replaced));

      replaced += " [ T = ";

      auto template_argument_end = find(template_argument_start, cend(name), '>');

      copy(template_argument_start + 1, template_argument_end, back_inserter(replaced));

      return replaced + " ]";
    }

    auto inline is_prefix(std::string const & suspect, std::string const & of) -> bool
    {
      if (suspect.size() > of.size())
      {
        return false;
      }
      return equal(cbegin(suspect), cend(suspect), cbegin(of));
    }

    auto inline is_type_name_prefix(std::string const & suspect) -> bool
    {
      return std::any_of(cbegin(type_names), cend(type_names), [&](auto type_name) { return is_prefix(suspect, type_name); });
    }

    auto inline wordify(std::string const & name)
    {
      using namespace std::string_literals;
      using namespace impl;

      auto stream = std::stringstream{name};
      auto output{""s};

      while (stream)
      {
        auto current_char = static_cast<char>(stream.get());

        if (current_char == '_')
        {
          if (stream.peek() != '_')
          {
            output += ' ';
          }
          else
          {
            output += current_char;
            stream.ignore();
          }
        }
        else if (current_char != EOF)
        {
          output += current_char;
        }
      }

      return output;
    }

    auto inline titelize(std::string const & name) -> std::string
    {
      using namespace std::string_literals;

      auto stream = std::istringstream{name};
      auto buffer{""s};
      auto word{""s};
      auto first{false};

      while (stream >> word && word != "[")
      {
        auto is_preposition = std::find(cbegin(prepositions), cend(prepositions), word) != cend(prepositions);
        auto is_keyword = std::find(cbegin(keywords), cend(keywords), word) != cend(keywords);
        auto is_type_name = std::find(cbegin(type_names), cend(type_names), word) != cend(type_names);
        if ((!(is_preposition || is_keyword) || buffer.empty()) && !is_type_name)
        {
          word.front() = std::toupper(word.front());
        }
        buffer += (first ? "" : " ") + word;
        first = false;
      }

      auto rest{""s};

      if (stream)
      {
        buffer += " " + word;
        std::getline(stream, rest);
      }

      return buffer + rest;
    }

  }  // namespace impl

  auto inline go_full_kawaii(std::string kowai) -> std::string
  {
    using namespace impl;

    auto template_free = replace_template_argument_syntax(kowai);
    auto wordified = wordify(template_free);

    return titelize(wordified);
  }

}  // namespace nt::test

#define KAWAII(name) cute::test((&name), nt::test::go_full_kawaii(#name))

#endif