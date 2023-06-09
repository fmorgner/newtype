#ifndef NEWTYPE_NEWTYPE_HPP
#define NEWTYPE_NEWTYPE_HPP

#include <functional>
#include <istream>
#include <ostream>
#include <type_traits>
#include <utility>

namespace nt
{

  namespace impl
  {

    inline namespace storage
    {

      template<typename BaseType, typename TagType>
      struct new_type_storage
      {
        constexpr new_type_storage() noexcept(std::is_nothrow_default_constructible_v<BaseType>)
            : m_value{}
        {
        }

        constexpr new_type_storage(BaseType const & value)
            : m_value{value}
        {
        }

        constexpr new_type_storage(BaseType && value)
            : m_value{std::move(value)}
        {
        }

        BaseType m_value;
      };

      template<typename BaseType, typename TagType, bool = std::is_default_constructible_v<BaseType>>
      struct new_type_constructor : new_type_storage<BaseType, TagType>
      {
        using new_type_storage<BaseType, TagType>::new_type_storage;
      };

      template<typename BaseType, typename TagType>
      struct new_type_constructor<BaseType, TagType, false> : new_type_storage<BaseType, TagType>
      {
        using new_type_storage<BaseType, TagType>::new_type_storage;

        constexpr new_type_constructor() = delete;
      };

      template<typename BaseType, typename TagType, bool = std::is_copy_constructible_v<BaseType>>
      struct new_type_copy_constructor : new_type_constructor<BaseType, TagType>
      {
        using new_type_constructor<BaseType, TagType>::new_type_constructor;

        constexpr new_type_copy_constructor(new_type_copy_constructor const &) = default;
        constexpr new_type_copy_constructor(new_type_copy_constructor &&) = default;
        auto constexpr operator=(new_type_copy_constructor &) -> new_type_copy_constructor & = default;
        auto constexpr operator=(new_type_copy_constructor &&) -> new_type_copy_constructor & = default;
      };

      template<typename BaseType, typename TagType>
      struct new_type_copy_constructor<BaseType, TagType, false> : new_type_constructor<BaseType, TagType>
      {
        using new_type_constructor<BaseType, TagType>::new_type_constructor;

        constexpr new_type_copy_constructor(new_type_copy_constructor const &) = delete;
        constexpr new_type_copy_constructor(new_type_copy_constructor &&) = default;
        constexpr new_type_copy_constructor(BaseType const &) = delete;
        auto constexpr operator=(new_type_copy_constructor &) -> new_type_copy_constructor & = default;
        auto constexpr operator=(new_type_copy_constructor &&) -> new_type_copy_constructor & = default;
      };

      template<typename BaseType, typename TagType, bool = std::is_move_constructible_v<BaseType>>
      struct new_type_move_constructor : new_type_copy_constructor<BaseType, TagType>
      {
        using new_type_copy_constructor<BaseType, TagType>::new_type_copy_constructor;

        constexpr new_type_move_constructor(new_type_move_constructor const &) = default;
        constexpr new_type_move_constructor(new_type_move_constructor &&) = default;
        auto constexpr operator=(new_type_move_constructor &) -> new_type_move_constructor & = default;
        auto constexpr operator=(new_type_move_constructor &&) -> new_type_move_constructor & = default;
      };

      template<typename BaseType, typename TagType>
      struct new_type_move_constructor<BaseType, TagType, false> : new_type_copy_constructor<BaseType, TagType>
      {
        using new_type_copy_constructor<BaseType, TagType>::new_type_copy_constructor;

        constexpr new_type_move_constructor(new_type_move_constructor const &) = default;
        constexpr new_type_move_constructor(new_type_move_constructor &&) = delete;
        constexpr new_type_move_constructor(BaseType &&) = delete;
        auto constexpr operator=(new_type_move_constructor &) -> new_type_move_constructor & = default;
        auto constexpr operator=(new_type_move_constructor &&) -> new_type_move_constructor & = default;
      };

      template<typename BaseType, typename TagType, bool = std::is_copy_assignable_v<BaseType>>
      struct new_type_copy_assignment : new_type_move_constructor<BaseType, TagType>
      {
        using new_type_move_constructor<BaseType, TagType>::new_type_move_constructor;

        constexpr new_type_copy_assignment(new_type_copy_assignment const &) = default;
        constexpr new_type_copy_assignment(new_type_copy_assignment &&) = default;
        auto constexpr operator=(new_type_copy_assignment &) -> new_type_copy_assignment & = default;
        auto constexpr operator=(new_type_copy_assignment &&) -> new_type_copy_assignment & = default;
      };

      template<typename BaseType, typename TagType>
      struct new_type_copy_assignment<BaseType, TagType, false> : new_type_move_constructor<BaseType, TagType>
      {
        using new_type_move_constructor<BaseType, TagType>::new_type_move_constructor;

        constexpr new_type_copy_assignment(new_type_copy_assignment const &) = default;
        constexpr new_type_copy_assignment(new_type_copy_assignment &&) = default;
        auto constexpr operator=(new_type_copy_assignment &) -> new_type_copy_assignment & = default;
        auto constexpr operator=(new_type_copy_assignment &&) -> new_type_copy_assignment & = delete;
      };

      template<typename BaseType, typename TagType, bool = std::is_move_assignable_v<BaseType>>
      struct new_type_move_assignment : new_type_copy_assignment<BaseType, TagType>
      {
        using new_type_copy_assignment<BaseType, TagType>::new_type_copy_assignment;

        constexpr new_type_move_assignment(new_type_move_assignment const &) = default;
        constexpr new_type_move_assignment(new_type_move_assignment &&) = default;
        auto constexpr operator=(new_type_move_assignment &) -> new_type_move_assignment & = default;
        auto constexpr operator=(new_type_move_assignment &&) -> new_type_move_assignment & = default;
      };

      template<typename BaseType, typename TagType>
      struct new_type_move_assignment<BaseType, TagType, false> : new_type_copy_assignment<BaseType, TagType>
      {
        using new_type_copy_assignment<BaseType, TagType>::new_type_copy_assignment;

        constexpr new_type_move_assignment(new_type_move_assignment const &) = default;
        constexpr new_type_move_assignment(new_type_move_assignment &&) = default;
        auto constexpr operator=(new_type_move_assignment &) -> new_type_move_assignment & = default;
        auto constexpr operator=(new_type_move_assignment &&) -> new_type_move_assignment & = delete;
      };

    }  // namespace storage

    inline namespace member_types
    {

      template<typename T, bool = false, typename = std::void_t<>>
      struct new_type_iterator
      {
      };

      template<typename T>
      struct new_type_iterator<T, true, std::void_t<typename T::iterator>>
      {
        using iterator = typename T::iterator;
      };

      template<typename T, bool = false, typename = std::void_t<>>
      struct new_type_const_iterator
      {
      };

      template<typename T>
      struct new_type_const_iterator<T, true, std::void_t<typename T::const_iterator>>
      {
        using const_iterator = typename T::const_iterator;
      };

      template<typename T, bool = false, typename = std::void_t<>>
      struct new_type_reverse_iterator
      {
      };

      template<typename T>
      struct new_type_reverse_iterator<T, true, std::void_t<typename T::reverse_iterator>>
      {
        using reverse_iterator = typename T::reverse_iterator;
      };

      template<typename T, bool = false, typename = std::void_t<>>
      struct new_type_const_reverse_iterator
      {
      };

      template<typename T>
      struct new_type_const_reverse_iterator<T, true, std::void_t<typename T::const_reverse_iterator>>
      {
        using const_reverse_iterator = typename T::const_reverse_iterator;
      };

      template<typename T, bool Enabled>
      struct new_type_iterator_types
          : new_type_iterator<T, Enabled>
          , new_type_const_iterator<T, Enabled>
          , new_type_reverse_iterator<T, Enabled>
          , new_type_const_reverse_iterator<T, Enabled>
      {
      };

    }  // namespace member_types

  }    // namespace impl

  inline namespace lib
  {
    constexpr struct
    {
      int const major;
      int const minor;
      int const patch;

      char const * const name;
    } version{
        .major = 2,
        .minor = 0,
        .patch = 0,
        .name = "Brynn",
    };

  }  // namespace lib

  namespace concepts
  {

    inline namespace arithmetic
    {

      template<typename SubjectType>
      concept addable = requires(SubjectType lhs, SubjectType rhs) {
        {
          lhs + rhs
        } -> std::same_as<SubjectType>;
      };

      template<typename SubjectType>
      concept nothrow_addable = requires(SubjectType lhs, SubjectType rhs) {
        requires addable<SubjectType>;
        {
          lhs + rhs
        } noexcept;
      };

      template<typename SubjectType>
      concept divisible = requires(SubjectType lhs, SubjectType rhs) {
        {
          lhs / rhs
        } -> std::same_as<SubjectType>;
      };

      template<typename SubjectType>
      concept nothrow_divisible = requires(SubjectType lhs, SubjectType rhs) {
        requires divisible<SubjectType>;
        {
          lhs / rhs
        } noexcept;
      };

      template<typename SubjectType>
      concept multipliable = requires(SubjectType lhs, SubjectType rhs) {
        {
          lhs * rhs
        } -> std::same_as<SubjectType>;
      };

      template<typename SubjectType>
      concept nothrow_multipliable = requires(SubjectType lhs, SubjectType rhs) {
        requires multipliable<SubjectType>;
        {
          lhs / rhs
        } noexcept;
      };

      template<typename SubjectType>
      concept subtractable = requires(SubjectType lhs, SubjectType rhs) {
        {
          lhs - rhs
        } -> std::same_as<SubjectType>;
      };

      template<typename SubjectType>
      concept nothrow_subtractable = requires(SubjectType lhs, SubjectType rhs) {
        requires subtractable<SubjectType>;
        {
          lhs - rhs
        } noexcept;
      };

    }  // namespace arithmetic

    inline namespace comparability
    {

      template<typename SubjectType>
      concept equality_comparable = requires(SubjectType lhs, SubjectType rhs) {
        {
          lhs == rhs
        } -> std::convertible_to<bool>;
      };

      template<typename SubjectType>
      concept nothrow_equality_comparable = requires(SubjectType lhs, SubjectType rhs) {
        requires equality_comparable<SubjectType>;
        {
          lhs == rhs
        } noexcept;
      };

      template<typename SubjectType>
      concept inequality_comparable = requires(SubjectType lhs, SubjectType rhs) {
        {
          lhs != rhs
        } -> std::convertible_to<bool>;
      };

      template<typename SubjectType>
      concept nothrow_inequality_comparable = requires(SubjectType lhs, SubjectType rhs) {
        requires inequality_comparable<SubjectType>;
        {
          lhs != rhs
        } noexcept;
      };

      template<typename SubjectType>
      concept less_than_comparable = requires(SubjectType lhs, SubjectType rhs) {
        {
          lhs < rhs
        } -> std::convertible_to<bool>;
      };

      template<typename SubjectType>
      concept nothrow_less_than_comparable = requires(SubjectType lhs, SubjectType rhs) {
        requires less_than_comparable<SubjectType>;
        {
          lhs < rhs
        } noexcept;
      };

      template<typename SubjectType>
      concept less_than_equal_comparable = requires(SubjectType lhs, SubjectType rhs) {
        {
          lhs <= rhs
        } -> std::convertible_to<bool>;
      };

      template<typename SubjectType>
      concept nothrow_less_than_equal_comparable = requires(SubjectType lhs, SubjectType rhs) {
        requires less_than_equal_comparable<SubjectType>;
        {
          lhs <= rhs
        } noexcept;
      };

      template<typename SubjectType>
      concept greater_than_comparable = requires(SubjectType lhs, SubjectType rhs) {
        {
          lhs > rhs
        } -> std::convertible_to<bool>;
      };

      template<typename SubjectType>
      concept nothrow_greater_than_comparable = requires(SubjectType lhs, SubjectType rhs) {
        requires greater_than_comparable<SubjectType>;
        {
          lhs > rhs
        } noexcept;
      };

      template<typename SubjectType>
      concept greater_than_equal_comparable = requires(SubjectType lhs, SubjectType rhs) {
        {
          lhs >= rhs
        } -> std::convertible_to<bool>;
      };

      template<typename SubjectType>
      concept nothrow_greater_than_equal_comparable = requires(SubjectType lhs, SubjectType rhs) {
        requires greater_than_equal_comparable<SubjectType>;
        {
          lhs >= rhs
        } noexcept;
      };

    }  // namespace comparability

    inline namespace compound_arithmetic
    {
      template<typename SubjectType>
      concept compound_addable = requires(SubjectType & lhs, SubjectType const & rhs) {
        {
          lhs += rhs
        } -> std::convertible_to<SubjectType &>;
      };

      template<typename SubjectType>
      concept nothrow_compound_addable = requires(SubjectType & lhs, SubjectType const & rhs) {
        requires compound_addable<SubjectType>;
        {
          lhs += rhs
        } noexcept;
      };

      template<typename SubjectType>
      concept compound_divisible = requires(SubjectType & lhs, SubjectType const & rhs) {
        {
          lhs /= rhs
        } -> std::convertible_to<SubjectType &>;
      };

      template<typename SubjectType>
      concept nothrow_compound_divisible = requires(SubjectType & lhs, SubjectType const & rhs) {
        requires compound_divisible<SubjectType>;
        {
          lhs /= rhs
        } noexcept;
      };

      template<typename SubjectType>
      concept compound_multipliable = requires(SubjectType & lhs, SubjectType const & rhs) {
        {
          lhs *= rhs
        } -> std::convertible_to<SubjectType &>;
      };

      template<typename SubjectType>
      concept nothrow_compound_multipliable = requires(SubjectType & lhs, SubjectType const & rhs) {
        requires compound_multipliable<SubjectType>;
        {
          lhs *= rhs
        } noexcept;
      };

      template<typename SubjectType>
      concept compound_subtractable = requires(SubjectType & lhs, SubjectType const & rhs) {
        {
          lhs -= rhs
        } -> std::convertible_to<SubjectType &>;
      };

      template<typename SubjectType>
      concept nothrow_compound_subtractable = requires(SubjectType & lhs, SubjectType const & rhs) {
        requires compound_subtractable<SubjectType>;
        {
          lhs -= rhs
        } noexcept;
      };
    }  // namespace compound_arithmetic

    inline namespace iostreamable
    {

      template<typename SubjectType, typename CharType, typename StreamTraits>
      concept input_streamable = requires(SubjectType subject) {
        {
          std::declval<std::basic_istream<CharType, StreamTraits> &>() >> subject
        } -> std::same_as<std::basic_istream<CharType, StreamTraits> &>;
      };

      template<typename SubjectType, typename CharType, typename StreamTraits>
      concept nothrow_input_streamable = requires(SubjectType subject) {
        requires input_streamable<SubjectType, CharType, StreamTraits>;
        {
          std::declval<std::basic_istream<CharType, StreamTraits> &>() >> subject
        } noexcept;
      };

      template<typename SubjectType, typename CharType, typename StreamTraits>
      concept output_streamable = requires(SubjectType subject) {
        {
          std::declval<std::basic_ostream<CharType, StreamTraits> &>() << subject
        } -> std::same_as<std::basic_ostream<CharType, StreamTraits> &>;
      };

      template<typename SubjectType, typename CharType, typename StreamTraits>
      concept nothrow_output_streamable = requires(SubjectType subject) {
        requires output_streamable<SubjectType, CharType, StreamTraits>;
        {
          std::declval<std::basic_ostream<CharType, StreamTraits> &>() << subject
        } noexcept;
      };

    }  // namespace iostreamable

    inline namespace iterable
    {

      template<typename SubjectType>
      concept free_begin = requires(SubjectType & subject) {
        typename SubjectType::iterator;
        {
          begin(subject)
        } -> std::same_as<typename SubjectType::iterator>;
      };

      template<typename SubjectType>
      concept const_free_begin = requires(SubjectType const & subject) {
        typename SubjectType::const_iterator;
        {
          begin(subject)
        } -> std::same_as<typename SubjectType::const_iterator>;
      };

      template<typename SubjectType>
      concept member_begin = requires(SubjectType & subject) {
        typename SubjectType::iterator;
        {
          subject.begin()
        } -> std::same_as<typename SubjectType::iterator>;
      };

      template<typename SubjectType>
      concept const_member_begin = requires(SubjectType const & subject) {
        typename SubjectType::const_iterator;
        {
          subject.begin()
        } -> std::same_as<typename SubjectType::const_iterator>;
      };

      template<typename SubjectType>
      concept beginnable = free_begin<SubjectType> || member_begin<SubjectType>;

      template<typename SubjectType>
      concept const_beginnable = const_free_begin<SubjectType> || const_member_begin<SubjectType>;

      template<typename SubjectType>
      concept free_cbegin = requires(SubjectType const & subject) {
        typename SubjectType::const_iterator;
        {
          cbegin(subject)
        } -> std::same_as<typename SubjectType::const_iterator>;
      };

      template<typename SubjectType>
      concept member_cbegin = requires(SubjectType const & subject) {
        typename SubjectType::const_iterator;
        {
          subject.cbegin()
        } -> std::same_as<typename SubjectType::const_iterator>;
      };

      template<typename SubjectType>
      concept cbeginnable = free_cbegin<SubjectType> || member_cbegin<SubjectType>;

      template<typename SubjectType>
      concept free_rbegin = requires(SubjectType & subject) {
        typename SubjectType::reverse_iterator;
        {
          rbegin(subject)
        } -> std::same_as<typename SubjectType::reverse_iterator>;
      };

      template<typename SubjectType>
      concept const_free_rbegin = requires(SubjectType const & subject) {
        typename SubjectType::const_reverse_iterator;
        {
          rbegin(subject)
        } -> std::same_as<typename SubjectType::const_reverse_iterator>;
      };

      template<typename SubjectType>
      concept member_rbegin = requires(SubjectType & subject) {
        typename SubjectType::reverse_iterator;
        {
          subject.rbegin()
        } -> std::same_as<typename SubjectType::reverse_iterator>;
      };

      template<typename SubjectType>
      concept const_member_rbegin = requires(SubjectType const & subject) {
        typename SubjectType::const_reverse_iterator;
        {
          subject.rbegin()
        } -> std::same_as<typename SubjectType::const_reverse_iterator>;
      };

      template<typename SubjectType>
      concept rbeginnable = free_rbegin<SubjectType> || member_rbegin<SubjectType>;

      template<typename SubjectType>
      concept const_rbeginnable = const_free_rbegin<SubjectType> || const_member_rbegin<SubjectType>;

      template<typename SubjectType>
      concept free_crbegin = requires(SubjectType const & subject) {
        typename SubjectType::const_reverse_iterator;
        {
          crbegin(subject)
        } -> std::same_as<typename SubjectType::const_reverse_iterator>;
      };

      template<typename SubjectType>
      concept member_crbegin = requires(SubjectType const & subject) {
        typename SubjectType::const_reverse_iterator;
        {
          subject.crbegin()
        } -> std::same_as<typename SubjectType::const_reverse_iterator>;
      };

      template<typename SubjectType>
      concept crbeginnable = free_crbegin<SubjectType> || member_crbegin<SubjectType>;

      template<typename SubjectType>
      concept free_end = requires(SubjectType & subject) {
        typename SubjectType::iterator;
        {
          end(subject)
        } -> std::same_as<typename SubjectType::iterator>;
      };

      template<typename SubjectType>
      concept const_free_end = requires(SubjectType const & subject) {
        typename SubjectType::const_iterator;
        {
          end(subject)
        } -> std::same_as<typename SubjectType::const_iterator>;
      };

      template<typename SubjectType>
      concept member_end = requires(SubjectType & subject) {
        typename SubjectType::iterator;
        {
          subject.end()
        } -> std::same_as<typename SubjectType::iterator>;
      };

      template<typename SubjectType>
      concept const_member_end = requires(SubjectType const & subject) {
        typename SubjectType::const_iterator;
        {
          subject.end()
        } -> std::same_as<typename SubjectType::const_iterator>;
      };

      template<typename SubjectType>
      concept endable = free_end<SubjectType> || member_end<SubjectType>;

      template<typename SubjectType>
      concept const_endable = const_free_end<SubjectType> || const_member_end<SubjectType>;

      template<typename SubjectType>
      concept free_cend = requires(SubjectType const & subject) {
        typename SubjectType::const_iterator;
        {
          cend(subject)
        } -> std::same_as<typename SubjectType::const_iterator>;
      };

      template<typename SubjectType>
      concept member_cend = requires(SubjectType const & subject) {
        typename SubjectType::const_iterator;
        {
          subject.cend()
        } -> std::same_as<typename SubjectType::const_iterator>;
      };

      template<typename SubjectType>
      concept cendable = free_cend<SubjectType> || member_cend<SubjectType>;

      template<typename SubjectType>
      concept free_rend = requires(SubjectType & subject) {
        typename SubjectType::reverse_iterator;
        {
          rend(subject)
        } -> std::same_as<typename SubjectType::reverse_iterator>;
      };

      template<typename SubjectType>
      concept const_free_rend = requires(SubjectType const & subject) {
        typename SubjectType::const_reverse_iterator;
        {
          rend(subject)
        } -> std::same_as<typename SubjectType::const_reverse_iterator>;
      };

      template<typename SubjectType>
      concept member_rend = requires(SubjectType & subject) {
        typename SubjectType::reverse_iterator;
        {
          subject.rend()
        } -> std::same_as<typename SubjectType::reverse_iterator>;
      };

      template<typename SubjectType>
      concept const_member_rend = requires(SubjectType const & subject) {
        typename SubjectType::const_reverse_iterator;
        {
          subject.rend()
        } -> std::same_as<typename SubjectType::const_reverse_iterator>;
      };

      template<typename SubjectType>
      concept rendable = free_rend<SubjectType> || member_rend<SubjectType>;

      template<typename SubjectType>
      concept const_rendable = const_free_rend<SubjectType> || const_member_rend<SubjectType>;

      template<typename SubjectType>
      concept free_crend = requires(SubjectType const & subject) {
        typename SubjectType::const_reverse_iterator;
        {
          crend(subject)
        } -> std::same_as<typename SubjectType::const_reverse_iterator>;
      };

      template<typename SubjectType>
      concept member_crend = requires(SubjectType const & subject) {
        typename SubjectType::const_reverse_iterator;
        {
          subject.crend()
        } -> std::same_as<typename SubjectType::const_reverse_iterator>;
      };

      template<typename SubjectType>
      concept crendable = free_crend<SubjectType> || member_crend<SubjectType>;
    }  // namespace iterable

    inline namespace standard_extensions
    {

      template<typename SubjectType>
      concept hashable = requires(SubjectType subject) {
        {
          std::hash<SubjectType>{}(subject)
        } -> std::convertible_to<std::size_t>;
      };

    }

  }  // namespace concepts

  template<typename DerivableTag>
  struct derivable final
  {
    using tag_type = DerivableTag;
  };

  inline namespace derivables
  {

    auto constexpr Arithmetic = derivable<struct arithmetic_tag>{};
    auto constexpr EqBase = derivable<struct eq_base_tag>{};
    auto constexpr Hash = derivable<struct hash_tag>{};
    auto constexpr ImplicitConversion = derivable<struct implicit_conversion_tag>{};
    auto constexpr Indirection = derivable<struct indirection_tag>{};
    auto constexpr Iterable = derivable<struct iterable_tag>{};
    auto constexpr Read = derivable<struct read_tag>{};
    auto constexpr Relational = derivable<struct relational_tag>{};
    auto constexpr Show = derivable<struct show_tag>{};

  }  // namespace derivables

  template<typename... DerivableTags>
  struct derivation_clause
  {
    template<auto... Needles>
    using contains = std::disjunction<std::is_same<DerivableTags, typename decltype(Needles)::tag_type>...>;

    constexpr derivation_clause(derivable<DerivableTags>...) noexcept
    {
    }

    template<typename DerivableTag>
    auto constexpr operator()(derivable<DerivableTag>) const noexcept -> bool
    {
      return (std::is_same_v<DerivableTags, DerivableTag> || ...);
    }

    template<typename DerivableTag, typename... RemainingDerivableTags>
    auto constexpr operator()(derivable<DerivableTag>, derivable<RemainingDerivableTags>...) const noexcept -> bool
    {
      return (*this)(derivable<DerivableTag>{}) && (*this)(derivable<RemainingDerivableTags>{}...);
    }

    template<typename... OtherDerivableTags>
    auto constexpr operator<(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool
    {
      return (sizeof...(DerivableTags) < sizeof...(OtherDerivableTags)) && other(derivable<DerivableTags>{}...);
    }

    template<typename... OtherDerivableTags>
    auto constexpr operator>(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool
    {
      return other < *this;
    }

    template<typename... OtherDerivableTags>
    auto constexpr operator==(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool
    {
      return sizeof...(DerivableTags) == sizeof...(OtherDerivableTags) && other(derivable<DerivableTags>{}...);
    }

    template<typename... OtherDerivableTags>
    auto constexpr operator!=(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool
    {
      return !(*this == other);
    }

    template<typename... OtherDerivableTags>
    auto constexpr operator<=(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool
    {
      return *this < other || *this == other;
    }

    template<typename... OtherDerivableTags>
    auto constexpr operator>=(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool
    {
      return *this > other || *this == other;
    }
  };

  template<typename DerivationClause, auto... Features>
  concept contains = requires(DerivationClause clause) { requires DerivationClause::template contains<Features...>::value; };

  template<typename... DerivableTags>
  auto constexpr deriving(derivable<DerivableTags>... features) noexcept -> derivation_clause<DerivableTags...>
  {
    return {features...};
  }

  template<typename BaseType, typename TagType, auto DerivationClause = deriving()>
  class new_type
      : impl::new_type_move_assignment<BaseType, TagType>
      , public impl::new_type_iterator_types<BaseType, DerivationClause(nt::Iterable)>
  {
    static_assert(!std::is_reference_v<BaseType>, "The base type must not be a reference type");
    static_assert(!std::is_void_v<std::remove_cv_t<BaseType>>, "The base type must not be possibly cv-qualified void");

    template<typename CharType,
             typename StreamTraits,
             nt::concepts::input_streamable<CharType, StreamTraits> BaseTypeT,
             typename TagTypeT,
             nt::contains<nt::Read> auto DerivationClauseV>
    auto friend operator>>(std::basic_istream<CharType, StreamTraits> &, new_type<BaseTypeT, TagTypeT, DerivationClauseV> &) noexcept(
        nt::concepts::nothrow_input_streamable<BaseTypeT, CharType, StreamTraits>) -> std::basic_istream<CharType, StreamTraits> &;

    template<nt::concepts::compound_addable BaseTypeT, typename TagTypeT, nt::contains<nt::Arithmetic> auto DerivationClauseV>
    auto constexpr friend
    operator+=(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & lhs,
               new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & rhs) noexcept(nt::concepts::nothrow_compound_addable<BaseTypeT>)
        -> new_type<BaseTypeT, TagTypeT, DerivationClauseV> &;

    template<nt::concepts::compound_subtractable BaseTypeT, typename TagTypeT, nt::contains<nt::Arithmetic> auto DerivationClauseV>
    auto constexpr friend
    operator-=(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & lhs,
               new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & rhs) noexcept(nt::concepts::nothrow_compound_subtractable<BaseTypeT>)
        -> new_type<BaseTypeT, TagTypeT, DerivationClauseV> &;

    template<nt::concepts::compound_multipliable BaseTypeT, typename TagTypeT, nt::contains<nt::Arithmetic> auto DerivationClauseV>
    auto constexpr friend
    operator*=(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & lhs,
               new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & rhs) noexcept(nt::concepts::nothrow_compound_multipliable<BaseTypeT>)
        -> new_type<BaseTypeT, TagTypeT, DerivationClauseV> &;

    template<nt::concepts::compound_divisible BaseTypeT, typename TagTypeT, nt::contains<nt::Arithmetic> auto DerivationClauseV>
    auto constexpr friend
    operator/=(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & lhs,
               new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & rhs) noexcept(nt::concepts::nothrow_compound_divisible<BaseTypeT>)
        -> new_type<BaseTypeT, TagTypeT, DerivationClauseV> &;

    template<nt::concepts::free_begin BaseTypeT, typename TagTypeT, nt::contains<nt::Iterable> auto DerivationClauseV>
    auto constexpr friend begin(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & obj) ->
        typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::iterator;

    template<nt::concepts::const_free_begin BaseTypeT, typename TagTypeT, nt::contains<nt::Iterable> auto DerivationClauseV>
    auto constexpr friend begin(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj) ->
        typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_iterator;

    template<nt::concepts::free_cbegin BaseTypeT, typename TagTypeT, nt::contains<nt::Iterable> auto DerivationClauseV>
    auto constexpr friend cbegin(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj) ->
        typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_iterator;

    template<nt::concepts::free_rbegin BaseTypeT, typename TagTypeT, nt::contains<nt::Iterable> auto DerivationClauseV>
    auto constexpr friend rbegin(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & obj) ->
        typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::reverse_iterator;

    template<nt::concepts::const_free_rbegin BaseTypeT, typename TagTypeT, nt::contains<nt::Iterable> auto DerivationClauseV>
    auto constexpr friend rbegin(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj) ->
        typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_reverse_iterator;

    template<nt::concepts::free_crbegin BaseTypeT, typename TagTypeT, nt::contains<nt::Iterable> auto DerivationClauseV>
    auto constexpr friend crbegin(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj) ->
        typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_reverse_iterator;

    template<nt::concepts::free_end BaseTypeT, typename TagTypeT, nt::contains<nt::Iterable> auto DerivationClauseV>
    auto constexpr friend end(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & obj) ->
        typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::iterator;

    template<nt::concepts::const_free_end BaseTypeT, typename TagTypeT, nt::contains<nt::Iterable> auto DerivationClauseV>
    auto constexpr friend end(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj) ->
        typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_iterator;

    template<nt::concepts::free_cend BaseTypeT, typename TagTypeT, nt::contains<nt::Iterable> auto DerivationClauseV>
    auto constexpr friend cend(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj) ->
        typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_iterator;

    template<nt::concepts::free_rend BaseTypeT, typename TagTypeT, nt::contains<nt::Iterable> auto DerivationClauseV>
    auto constexpr friend rend(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & obj) ->
        typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::reverse_iterator;

    template<nt::concepts::const_free_rend BaseTypeT, typename TagTypeT, nt::contains<nt::Iterable> auto DerivationClauseV>
    auto constexpr friend rend(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj) ->
        typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_reverse_iterator;

    template<nt::concepts::free_crend BaseTypeT, typename TagTypeT, nt::contains<nt::Iterable> auto DerivationClauseV>
    auto constexpr friend crend(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj) ->
        typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_reverse_iterator;

    using super = impl::new_type_move_assignment<BaseType, TagType>;

  public:
    using base_type = BaseType;
    using tag_type = TagType;
    using derivation_clause_type = decltype(DerivationClause);

    auto constexpr static derivation_clause = DerivationClause;

    using super::super;

    constexpr new_type() noexcept(std::is_nothrow_default_constructible_v<BaseType>) = default;
    constexpr new_type(new_type const &) noexcept(std::is_nothrow_copy_constructible_v<BaseType>) = default;
    constexpr new_type(new_type &&) noexcept(std::is_nothrow_move_constructible_v<BaseType>) = default;

    auto constexpr operator=(new_type const &) noexcept(std::is_nothrow_copy_assignable_v<BaseType>) -> new_type & = default;
    auto constexpr operator=(new_type &&) noexcept(std::is_nothrow_move_assignable_v<BaseType>) -> new_type & = default;

    auto constexpr decay() const noexcept(std::is_nothrow_copy_constructible_v<BaseType>) -> BaseType
    {
      return this->m_value;
    }

    template<typename NewType = new_type, std::enable_if_t<NewType::derivation_clause(nt::ImplicitConversion)> * = nullptr>
    constexpr operator base_type() const noexcept(std::is_nothrow_copy_constructible_v<base_type>)
    {
      return decay();
    }

    template<typename NewType = new_type, std::enable_if_t<!NewType::derivation_clause(nt::ImplicitConversion)> * = nullptr>
    explicit constexpr operator base_type() const noexcept(std::is_nothrow_copy_constructible_v<base_type>)
    {
      return decay();
    }

    template<typename NewType = new_type>
    auto constexpr operator->() noexcept -> std::enable_if_t<NewType::derivation_clause(nt::Indirection), BaseType *>
    {
      return std::addressof(this->m_value);
    }

    template<typename NewType = new_type>
    auto constexpr operator->() const noexcept -> std::enable_if_t<NewType::derivation_clause(nt::Indirection), BaseType const *>
    {
      return std::addressof(this->m_value);
    }

    template<nt::concepts::member_begin BaseTypeT = BaseType, nt::contains<nt::Iterable> auto DerivationClauseV = DerivationClause>
    auto constexpr begin() -> typename new_type<BaseTypeT, TagType, DerivationClauseV>::iterator
    {
      return this->m_value.begin();
    }

    template<nt::concepts::const_member_begin BaseTypeT = BaseType, nt::contains<nt::Iterable> auto DerivationClauseV = DerivationClause>
    auto constexpr begin() const -> typename new_type<BaseTypeT, TagType, DerivationClauseV>::const_iterator
    {
      return this->m_value.begin();
    }

    template<nt::concepts::member_cbegin BaseTypeT = BaseType, nt::contains<nt::Iterable> auto DerivationClauseV = DerivationClause>
    auto constexpr cbegin() const -> typename new_type<BaseTypeT, TagType, DerivationClauseV>::const_iterator
    {
      return this->m_value.cbegin();
    }

    template<nt::concepts::member_cbegin BaseTypeT = BaseType, nt::contains<nt::Iterable> auto DerivationClauseV = DerivationClause>
    auto constexpr rbegin() -> typename new_type<BaseTypeT, TagType, DerivationClauseV>::reverse_iterator
    {
      return this->m_value.rbegin();
    }

    template<nt::concepts::member_cbegin BaseTypeT = BaseType, nt::contains<nt::Iterable> auto DerivationClauseV = DerivationClause>
    auto constexpr rbegin() const -> typename new_type<BaseTypeT, TagType, DerivationClauseV>::const_reverse_iterator
    {
      return this->m_value.rbegin();
    }

    template<nt::concepts::member_crbegin BaseTypeT = BaseType, nt::contains<nt::Iterable> auto DerivationClauseV = DerivationClause>
    auto constexpr crbegin() const -> typename new_type<BaseTypeT, TagType, DerivationClauseV>::const_reverse_iterator
    {
      return this->m_value.crbegin();
    }

    template<nt::concepts::member_end BaseTypeT = BaseType, nt::contains<nt::Iterable> auto DerivationClauseV = DerivationClause>
    auto constexpr end() -> typename new_type<BaseTypeT, TagType, DerivationClauseV>::iterator
    {
      return this->m_value.end();
    }

    template<nt::concepts::const_member_end BaseTypeT = BaseType, nt::contains<nt::Iterable> auto DerivationClauseV = DerivationClause>
    auto constexpr end() const -> typename new_type<BaseTypeT, TagType, DerivationClauseV>::const_iterator
    {
      return this->m_value.end();
    }

    template<nt::concepts::member_cend BaseTypeT = BaseType, nt::contains<nt::Iterable> auto DerivationClauseV = DerivationClause>
    auto constexpr cend() const -> typename new_type<BaseTypeT, TagType, DerivationClauseV>::const_iterator
    {
      return this->m_value.cend();
    }

    template<nt::concepts::member_rend BaseTypeT = BaseType, nt::contains<nt::Iterable> auto DerivationClauseV = DerivationClause>
    auto constexpr rend() -> typename new_type<BaseTypeT, TagType, DerivationClauseV>::reverse_iterator
    {
      return this->m_value.rend();
    }

    template<nt::concepts::const_member_rend BaseTypeT = BaseType, nt::contains<nt::Iterable> auto DerivationClauseV = DerivationClause>
    auto constexpr rend() const -> typename new_type<BaseTypeT, TagType, DerivationClauseV>::const_reverse_iterator
    {
      return this->m_value.rend();
    }

    template<nt::concepts::const_member_rend BaseTypeT = BaseType, nt::contains<nt::Iterable> auto DerivationClauseV = DerivationClause>
    auto constexpr crend() const -> typename new_type<BaseTypeT, TagType, DerivationClauseV>::const_reverse_iterator
    {
      return this->m_value.crend();
    }
  };

  template<nt::concepts::equality_comparable BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator==(new_type<BaseType, TagType, DerivationClause> const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(nt::concepts::nothrow_equality_comparable<BaseType>) -> bool
  {
    return lhs.decay() == rhs.decay();
  }

  template<nt::concepts::equality_comparable BaseType, typename TagType, nt::contains<nt::EqBase> auto DerivationClause>
  auto constexpr operator==(new_type<BaseType, TagType, DerivationClause> const & lhs,
                            BaseType const & rhs) noexcept(nt::concepts::nothrow_equality_comparable<BaseType>) -> bool
  {
    return lhs.decay() == rhs;
  }

  template<nt::concepts::equality_comparable BaseType, typename TagType, nt::contains<nt::EqBase> auto DerivationClause>
  auto constexpr
  operator==(BaseType const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(nt::concepts::nothrow_equality_comparable<BaseType>) -> bool
  {
    return lhs == rhs.decay();
  }

  template<nt::concepts::inequality_comparable BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator!=(new_type<BaseType, TagType, DerivationClause> const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(nt::concepts::nothrow_inequality_comparable<BaseType>) -> bool
  {
    return lhs.decay() != rhs.decay();
  }

  template<nt::concepts::inequality_comparable BaseType, typename TagType, nt::contains<nt::EqBase> auto DerivationClause>
  auto constexpr operator!=(new_type<BaseType, TagType, DerivationClause> const & lhs,
                            BaseType const & rhs) noexcept(nt::concepts::nothrow_inequality_comparable<BaseType>) -> bool
  {
    return lhs.decay() != rhs;
  }

  template<nt::concepts::inequality_comparable BaseType, typename TagType, nt::contains<nt::EqBase> auto DerivationClause>
  auto constexpr
  operator!=(BaseType const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(nt::concepts::nothrow_inequality_comparable<BaseType>) -> bool
  {
    return lhs != rhs.decay();
  }

  template<nt::concepts::less_than_comparable BaseType, typename TagType, nt::contains<nt::Relational> auto DerivationClause>
  auto constexpr
  operator<(new_type<BaseType, TagType, DerivationClause> const & lhs,
            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(nt::concepts::nothrow_less_than_comparable<BaseType>)
  {
    return lhs.decay() < rhs.decay();
  }

  template<nt::concepts::greater_than_comparable BaseType, typename TagType, nt::contains<nt::Relational> auto DerivationClause>
  auto constexpr
  operator>(new_type<BaseType, TagType, DerivationClause> const & lhs,
            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(nt::concepts::nothrow_greater_than_comparable<BaseType>)
  {
    return lhs.decay() > rhs.decay();
  }

  template<nt::concepts::less_than_equal_comparable BaseType, typename TagType, nt::contains<nt::Relational> auto DerivationClause>
  auto constexpr
  operator<=(new_type<BaseType, TagType, DerivationClause> const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(nt::concepts::nothrow_less_than_equal_comparable<BaseType>)
  {
    return lhs.decay() <= rhs.decay();
  }

  template<nt::concepts::greater_than_equal_comparable BaseType, typename TagType, nt::contains<nt::Relational> auto DerivationClause>
  auto constexpr
  operator>=(new_type<BaseType, TagType, DerivationClause> const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(nt::concepts::nothrow_greater_than_equal_comparable<BaseType>)
  {
    return lhs.decay() >= rhs.decay();
  }

  template<typename CharType,
           typename StreamTraits,
           nt::concepts::output_streamable<CharType, StreamTraits> BaseType,
           typename TagType,
           nt::contains<nt::Show> auto DerivationClause>
  auto operator<<(std::basic_ostream<CharType, StreamTraits> & output, new_type<BaseType, TagType, DerivationClause> const & source) noexcept(
      nt::concepts::nothrow_output_streamable<BaseType, CharType, StreamTraits>) -> std::basic_ostream<CharType, StreamTraits> &
  {
    return output << source.decay();
  }

  template<typename CharType,
           typename StreamTraits,
           nt::concepts::input_streamable<CharType, StreamTraits> BaseType,
           typename TagType,
           nt::contains<nt::Read> auto DerivationClause>
  auto operator>>(std::basic_istream<CharType, StreamTraits> & input, new_type<BaseType, TagType, DerivationClause> & target) noexcept(
      nt::concepts::nothrow_input_streamable<BaseType, CharType, StreamTraits>) -> std::basic_istream<CharType, StreamTraits> &
  {
    return input >> target.m_value;
  }

  template<nt::concepts::addable BaseType, typename TagType, nt::contains<nt::Arithmetic> auto DerivationClause>
  auto constexpr
  operator+(new_type<BaseType, TagType, DerivationClause> const & lhs, new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(
      nt::concepts::nothrow_addable<BaseType> && std::is_nothrow_copy_constructible_v<BaseType>)
      -> new_type<BaseType, TagType, DerivationClause>
  {
    return {lhs.decay() + rhs.decay()};
  }

  template<nt::concepts::compound_addable BaseType, typename TagType, nt::contains<nt::Arithmetic> auto DerivationClause>
  auto constexpr
  operator+=(new_type<BaseType, TagType, DerivationClause> & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(nt::concepts::nothrow_compound_addable<BaseType>)
      -> new_type<BaseType, TagType, DerivationClause> &
  {
    lhs.m_value += rhs.m_value;
    return lhs;
  }

  template<nt::concepts::subtractable BaseType, typename TagType, nt::contains<nt::Arithmetic> auto DerivationClause>
  auto constexpr
  operator-(new_type<BaseType, TagType, DerivationClause> const & lhs, new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(
      nt::concepts::nothrow_subtractable<BaseType> && std::is_nothrow_copy_constructible_v<BaseType>)
      -> new_type<BaseType, TagType, DerivationClause>
  {
    return {lhs.decay() - rhs.decay()};
  }

  template<nt::concepts::compound_subtractable BaseType, typename TagType, nt::contains<nt::Arithmetic> auto DerivationClause>
  auto constexpr
  operator-=(new_type<BaseType, TagType, DerivationClause> & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(nt::concepts::nothrow_compound_subtractable<BaseType>)
      -> new_type<BaseType, TagType, DerivationClause> &
  {
    lhs.m_value -= rhs.m_value;
    return lhs;
  }

  template<nt::concepts::multipliable BaseType, typename TagType, nt::contains<nt::Arithmetic> auto DerivationClause>
  auto constexpr
  operator*(new_type<BaseType, TagType, DerivationClause> const & lhs, new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(
      nt::concepts::nothrow_multipliable<BaseType> && std::is_nothrow_copy_constructible_v<BaseType>)
      -> new_type<BaseType, TagType, DerivationClause>
  {
    return {lhs.decay() * rhs.decay()};
  }

  template<nt::concepts::compound_multipliable BaseType, typename TagType, nt::contains<nt::Arithmetic> auto DerivationClause>
  auto constexpr
  operator*=(new_type<BaseType, TagType, DerivationClause> & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(nt::concepts::nothrow_compound_multipliable<BaseType>)
      -> new_type<BaseType, TagType, DerivationClause> &
  {
    lhs.m_value *= rhs.m_value;
    return lhs;
  }

  template<nt::concepts::divisible BaseType, typename TagType, nt::contains<nt::Arithmetic> auto DerivationClause>
  auto constexpr
  operator/(new_type<BaseType, TagType, DerivationClause> const & lhs, new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(
      nt::concepts::nothrow_divisible<BaseType> && std::is_nothrow_copy_constructible_v<BaseType>)
      -> new_type<BaseType, TagType, DerivationClause>
  {
    return {lhs.decay() / rhs.decay()};
  }

  template<nt::concepts::compound_divisible BaseType, typename TagType, nt::contains<nt::Arithmetic> auto DerivationClause>
  auto constexpr
  operator/=(new_type<BaseType, TagType, DerivationClause> & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(nt::concepts::nothrow_compound_divisible<BaseType>)
      -> new_type<BaseType, TagType, DerivationClause> &
  {
    lhs.m_value /= rhs.m_value;
    return lhs;
  }

  template<nt::concepts::free_begin BaseType, typename TagType, nt::contains<nt::Iterable> auto DerivationClause>
  auto constexpr begin(new_type<BaseType, TagType, DerivationClause> & obj) -> typename new_type<BaseType, TagType, DerivationClause>::iterator
  {
    return begin(obj.m_value);
  }

  template<nt::concepts::const_free_begin BaseType, typename TagType, nt::contains<nt::Iterable> auto DerivationClause>
  auto constexpr begin(new_type<BaseType, TagType, DerivationClause> const & obj) ->
      typename new_type<BaseType, TagType, DerivationClause>::const_iterator
  {
    return begin(obj.m_value);
  }

  template<nt::concepts::free_cbegin BaseType, typename TagType, nt::contains<nt::Iterable> auto DerivationClause>
  auto constexpr cbegin(new_type<BaseType, TagType, DerivationClause> const & obj) ->
      typename new_type<BaseType, TagType, DerivationClause>::const_iterator
  {
    return cbegin(obj.m_value);
  }

  template<nt::concepts::free_rbegin BaseType, typename TagType, nt::contains<nt::Iterable> auto DerivationClause>
  auto constexpr rbegin(new_type<BaseType, TagType, DerivationClause> & obj) ->
      typename new_type<BaseType, TagType, DerivationClause>::reverse_iterator
  {
    return rbegin(obj.m_value);
  }

  template<nt::concepts::const_free_rbegin BaseType, typename TagType, nt::contains<nt::Iterable> auto DerivationClause>
  auto constexpr rbegin(new_type<BaseType, TagType, DerivationClause> const & obj) ->
      typename new_type<BaseType, TagType, DerivationClause>::const_reverse_iterator
  {
    return rbegin(obj.m_value);
  }

  template<nt::concepts::free_crbegin BaseType, typename TagType, nt::contains<nt::Iterable> auto DerivationClause>
  auto constexpr crbegin(new_type<BaseType, TagType, DerivationClause> const & obj) ->
      typename new_type<BaseType, TagType, DerivationClause>::const_reverse_iterator
  {
    return crbegin(obj.m_value);
  }

  template<nt::concepts::free_end BaseType, typename TagType, nt::contains<nt::Iterable> auto DerivationClause>
  auto constexpr end(new_type<BaseType, TagType, DerivationClause> & obj) -> typename new_type<BaseType, TagType, DerivationClause>::iterator
  {
    return end(obj.m_value);
  }

  template<nt::concepts::const_free_end BaseType, typename TagType, nt::contains<nt::Iterable> auto DerivationClause>
  auto constexpr end(new_type<BaseType, TagType, DerivationClause> const & obj) ->
      typename new_type<BaseType, TagType, DerivationClause>::const_iterator
  {
    return end(obj.m_value);
  }

  template<nt::concepts::free_cend BaseType, typename TagType, nt::contains<nt::Iterable> auto DerivationClause>
  auto constexpr cend(new_type<BaseType, TagType, DerivationClause> const & obj) ->
      typename new_type<BaseType, TagType, DerivationClause>::const_iterator
  {
    return cend(obj.m_value);
  }

  template<nt::concepts::free_rend BaseType, typename TagType, nt::contains<nt::Iterable> auto DerivationClause>
  auto constexpr rend(new_type<BaseType, TagType, DerivationClause> & obj) ->
      typename new_type<BaseType, TagType, DerivationClause>::reverse_iterator
  {
    return rend(obj.m_value);
  }

  template<nt::concepts::const_free_rend BaseType, typename TagType, nt::contains<nt::Iterable> auto DerivationClause>
  auto constexpr rend(new_type<BaseType, TagType, DerivationClause> const & obj) ->
      typename new_type<BaseType, TagType, DerivationClause>::const_reverse_iterator
  {
    return rend(obj.m_value);
  }

  template<nt::concepts::free_crend BaseType, typename TagType, nt::contains<nt::Iterable> auto DerivationClause>
  auto constexpr crend(new_type<BaseType, TagType, DerivationClause> const & obj) ->
      typename new_type<BaseType, TagType, DerivationClause>::const_reverse_iterator
  {
    return crend(obj.m_value);
  }

}  // namespace nt

namespace std
{
  template<nt::concepts::hashable BaseType, typename TagType, nt::contains<nt::Hash> auto DerivationClause>
  struct hash<nt::new_type<BaseType, TagType, DerivationClause>>
  {
    auto constexpr operator()(nt::new_type<BaseType, TagType, DerivationClause> const & object) const
    {
      return std::hash<BaseType>{}(object.decay());
    }
  };
}  // namespace std

#endif
