#ifndef NEWTYPE_NEWTYPE_HPP
#define NEWTYPE_NEWTYPE_HPP

#include <algorithm>
#include <compare>
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
      template<typename T>
      struct new_type_storage
      {
        T m_value;
      };
    }  // namespace storage

    inline namespace member_types
    {

      template<typename T, bool = false, typename = std::void_t<>>
      struct new_type_iterator : new_type_storage<T>
      {
      };

      template<typename T>
      struct new_type_iterator<T, true, std::void_t<typename T::iterator>> : new_type_storage<T>
      {
        using iterator = typename T::iterator;
      };

      template<typename T, bool Enabled = false, typename = std::void_t<>>
      struct new_type_const_iterator : new_type_iterator<T, Enabled>
      {
      };

      template<typename T>
      struct new_type_const_iterator<T, true, std::void_t<typename T::const_iterator>> : new_type_iterator<T, true>
      {
        using const_iterator = typename T::const_iterator;
      };

      template<typename T, bool Enabled = false, typename = std::void_t<>>
      struct new_type_reverse_iterator : new_type_const_iterator<T, Enabled>
      {
      };

      template<typename T>
      struct new_type_reverse_iterator<T, true, std::void_t<typename T::reverse_iterator>> : new_type_const_iterator<T, true>
      {
        using reverse_iterator = typename T::reverse_iterator;
      };

      template<typename T, bool Enabled = false, typename = std::void_t<>>
      struct new_type_const_reverse_iterator : new_type_reverse_iterator<T, Enabled>
      {
      };

      template<typename T>
      struct new_type_const_reverse_iterator<T, true, std::void_t<typename T::const_reverse_iterator>> : new_type_reverse_iterator<T, true>
      {
        using const_reverse_iterator = typename T::const_reverse_iterator;
      };

      template<typename T, bool Enabled>
      struct new_type_iterator_types : new_type_const_reverse_iterator<T, Enabled>
      {
      };

    }  // namespace member_types

  }  // namespace impl

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
      concept nothrow_three_way_comparable = requires(SubjectType lhs, SubjectType rhs) {
        requires std::three_way_comparable<SubjectType>;
        {
          lhs <=> rhs
        } noexcept;
      };

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
    auto constexpr ThreewayCompare = derivable<struct threeway_compare_tag>{};

  }  // namespace derivables

  template<typename... DerivableTags>
  struct derivation_clause
  {
    template<auto Needle>
    using derives_one = std::disjunction<std::is_same<typename decltype(Needle)::tag_type, DerivableTags>...>;

    template<auto... Needles>
    using derives = std::conjunction<derives_one<Needles>...>;

    constexpr derivation_clause(derivable<DerivableTags>...) noexcept
    {
    }
  };

  template<typename DerivationClause, auto... Features>
  concept derives = requires(DerivationClause clause) { requires DerivationClause::template derives<Features...>::value; };

  template<typename DerivationClause, auto... Features>
  concept doesnt_derive = !derives<DerivationClause, Features...>;

  template<typename... DerivableTags>
  auto constexpr deriving(derivable<DerivableTags>... features) noexcept -> derivation_clause<DerivableTags...>
  {
    return {features...};
  }

  template<typename BaseType, typename TagType, auto DerivationClause = deriving()>
  class new_type : public impl::new_type_iterator_types<BaseType, nt::derives<decltype(DerivationClause), nt::Iterable>>
  {
    static_assert(!std::is_reference_v<BaseType>, "The base type must not be a reference type");
    static_assert(!std::is_void_v<std::remove_cv_t<BaseType>>, "The base type must not be possibly cv-qualified void");
    static_assert(!derives<decltype(DerivationClause), nt::Relational, nt::ThreewayCompare>,
                  "Cannot derive both nt::Relational and nt::ThreewayCompare at the same time.");

    using super = impl::new_type_iterator_types<BaseType, nt::derives<decltype(DerivationClause), nt::Iterable>>;

  public:
    using base_type = BaseType;
    using tag_type = TagType;
    using derivation_clause_type = decltype(DerivationClause);

    auto constexpr static derivation_clause = DerivationClause;

    constexpr new_type() noexcept(std::is_nothrow_default_constructible_v<BaseType>)
      requires std::constructible_from<BaseType>
    = default;

    constexpr new_type(new_type const &) noexcept(std::is_nothrow_copy_constructible_v<BaseType>)
      requires std::copy_constructible<BaseType>
    = default;

    constexpr new_type(new_type &&) noexcept(std::is_nothrow_move_constructible_v<BaseType>)
      requires std::move_constructible<BaseType>
    = default;

    constexpr new_type(BaseType const & base) noexcept(std::is_nothrow_copy_constructible_v<BaseType>)
      requires std::copy_constructible<BaseType>
        : super{base}
    {
    }

    constexpr new_type(BaseType && base) noexcept(std::is_nothrow_move_constructible_v<BaseType>)
      requires std::move_constructible<BaseType>
        : super{std::move(base)}
    {
    }

    auto constexpr operator=(new_type const &) noexcept(std::is_nothrow_copy_assignable_v<BaseType>) -> new_type & = default;
    auto constexpr operator=(new_type &&) noexcept(std::is_nothrow_move_assignable_v<BaseType>) -> new_type & = default;

    auto constexpr decay() const noexcept(std::is_nothrow_copy_constructible_v<BaseType>) -> BaseType
    {
      return this->m_value;
    }

    template<typename DerivationClauseT = decltype(DerivationClause)>
    constexpr operator base_type() const noexcept(std::is_nothrow_copy_constructible_v<base_type>)
      requires(nt::derives<DerivationClauseT, nt::ImplicitConversion>)
    {
      return decay();
    }

    template<typename DerivationClauseT = decltype(DerivationClause)>
    explicit constexpr operator base_type() const noexcept(std::is_nothrow_copy_constructible_v<base_type>)
      requires(nt::doesnt_derive<DerivationClauseT, nt::ImplicitConversion>)
    {
      return decay();
    }

    template<typename CharType, typename StreamTraits, nt::concepts::input_streamable<CharType, StreamTraits> BaseTypeT = BaseType>
    auto friend operator>>(std::basic_istream<CharType, StreamTraits> & in,
                           new_type & obj) noexcept(nt::concepts::nothrow_input_streamable<BaseTypeT, CharType, StreamTraits>)
        -> std::basic_istream<CharType, StreamTraits> &
      requires nt::derives<decltype(DerivationClause), nt::Read>
    {
      return in >> obj.m_value;
    }

    template<typename CharType, typename StreamTraits, nt::concepts::output_streamable<CharType, StreamTraits> BaseTypeT = BaseType>
    auto friend operator<<(std::basic_ostream<CharType, StreamTraits> & out,
                           new_type const & obj) noexcept(nt::concepts::nothrow_output_streamable<BaseType, CharType, StreamTraits>)
        -> std::basic_ostream<CharType, StreamTraits> &
      requires nt::derives<decltype(DerivationClause), nt::Show>
    {
      return out << obj.m_value;
    }

    /**
     * @brief Check two instances of nt::new_type<BaseType, TagType, DerivationClause> for equality.
     *
     * @param lhs The left-hand side of the comparison.
     * @param rhs The right-hand side of the comparison.
     *
     * @note This overload is available iff. the underlying type is equality-comparable and this nt::new_type does not derive
     * nt::ThreewayCompare.
     *
     * @return The value returned by the comparison of the underlying objects.
     *
     * @throws Any exception thrown by the comparison operator of the underlying objects of @ref lhs and @ref rhs. `noexcept` iff.
     * new_type::base_type is nothrow equality-comparable.
     */

    // THREE-WAY ORDER AND EQUAL

    auto constexpr operator<=>(new_type const & rhs) const noexcept(nt::concepts::nothrow_three_way_comparable<BaseType>)
      requires(std::three_way_comparable<BaseType> && nt::derives<derivation_clause_type, nt::ThreewayCompare>)
    {
      return decay() <=> rhs.decay();
    }

    auto constexpr operator==(new_type const & rhs) const -> bool
      requires(nt::concepts::equality_comparable<BaseType> && nt::derives<derivation_clause_type, nt::ThreewayCompare>)
    {
      return decay() == rhs.decay();
    }

    // NOT THREE-WAY EQUAL

    auto constexpr operator==(new_type const & rhs) const noexcept(nt::concepts::nothrow_equality_comparable<BaseType>) -> bool
      requires(nt::concepts::equality_comparable<BaseType> && nt::doesnt_derive<derivation_clause_type, nt::ThreewayCompare>)
    {
      return decay() == rhs.decay();
    }

    // BASE EQUAL

    auto constexpr operator==(BaseType const & rhs) const noexcept(nt::concepts::nothrow_equality_comparable<BaseType>) -> bool
      requires(nt::concepts::equality_comparable<BaseType> && nt::derives<derivation_clause_type, nt::EqBase>)
    {
      return decay() == rhs;
    }

    // NOT THREE-WAY EQUAL

    auto constexpr operator!=(new_type const & rhs) const noexcept(nt::concepts::nothrow_inequality_comparable<BaseType>) -> bool
      requires(nt::concepts::inequality_comparable<BaseType> && nt::doesnt_derive<derivation_clause_type, nt::ThreewayCompare>)
    {
      return decay() != rhs.decay();
    }

    // NOT THREE-WAY ORDER

    auto constexpr operator<(new_type const & rhs) const noexcept(nt::concepts::nothrow_less_than_comparable<BaseType>) -> bool
      requires(nt::concepts::less_than_comparable<BaseType> &&                    //
               nt::doesnt_derive<derivation_clause_type, nt::ThreewayCompare> &&  //
               nt::derives<derivation_clause_type, nt::Relational>)
    {
      return decay() < rhs.decay();
    }

    auto constexpr operator<=(new_type const & rhs) const noexcept(nt::concepts::nothrow_less_than_equal_comparable<BaseType>) -> bool
      requires(nt::concepts::less_than_equal_comparable<BaseType> &&              //
               nt::doesnt_derive<derivation_clause_type, nt::ThreewayCompare> &&  //
               nt::derives<derivation_clause_type, nt::Relational>)
    {
      return decay() <= rhs.decay();
    }

    auto constexpr operator>(new_type const & rhs) const noexcept(nt::concepts::nothrow_greater_than_comparable<BaseType>) -> bool
      requires(nt::concepts::greater_than_comparable<BaseType> &&                 //
               nt::doesnt_derive<derivation_clause_type, nt::ThreewayCompare> &&  //
               nt::derives<derivation_clause_type, nt::Relational>)
    {
      return decay() > rhs.decay();
    }

    auto constexpr operator>=(new_type const & rhs) const noexcept(nt::concepts::nothrow_greater_than_equal_comparable<BaseType>) -> bool
      requires(nt::concepts::greater_than_equal_comparable<BaseType> &&           //
               nt::doesnt_derive<derivation_clause_type, nt::ThreewayCompare> &&  //
               nt::derives<derivation_clause_type, nt::Relational>)
    {
      return decay() >= rhs.decay();
    }

    // ARITHMETIC

    auto constexpr operator+(new_type const & rhs) const noexcept(nt::concepts::nothrow_addable<BaseType>) -> new_type
      requires(nt::concepts::addable<BaseType> && nt::derives<derivation_clause_type, nt::Arithmetic>)
    {
      return {decay() + rhs.decay()};
    }

    auto constexpr operator+=(new_type const & rhs) const noexcept(nt::concepts::nothrow_compound_addable<BaseType>)
        -> new_type & requires(nt::concepts::compound_addable<BaseType> && nt::derives<derivation_clause_type, nt::Arithmetic>) {
          return this->m_value += rhs.decay();
        }

    auto constexpr
    operator-(new_type const & rhs) const noexcept(nt::concepts::nothrow_subtractable<BaseType>) -> new_type
      requires(nt::concepts::subtractable<BaseType> && nt::derives<derivation_clause_type, nt::Arithmetic>)
    {
      return {decay() - rhs.decay()};
    }

    auto constexpr operator-=(new_type const & rhs) const noexcept(nt::concepts::nothrow_compound_subtractable<BaseType>)
        -> new_type & requires(nt::concepts::compound_subtractable<BaseType> && nt::derives<derivation_clause_type, nt::Arithmetic>) {
          return this->m_value -= rhs.decay();
        }

    auto constexpr
    operator*(new_type const & rhs) const noexcept(nt::concepts::nothrow_multipliable<BaseType>) -> new_type
      requires(nt::concepts::multipliable<BaseType> && nt::derives<derivation_clause_type, nt::Arithmetic>)
    {
      return {decay() * rhs.decay()};
    }

    auto constexpr operator*=(new_type const & rhs) const noexcept(nt::concepts::nothrow_compound_multipliable<BaseType>)
        -> new_type & requires(nt::concepts::compound_multipliable<BaseType> && nt::derives<derivation_clause_type, nt::Arithmetic>) {
          return this->m_value *= rhs.decay();
        }

    auto constexpr
    operator/(new_type const & rhs) const noexcept(nt::concepts::nothrow_divisible<BaseType>) -> new_type
      requires(nt::concepts::divisible<BaseType> && nt::derives<derivation_clause_type, nt::Arithmetic>)
    {
      return {decay() / rhs.decay()};
    }

    auto constexpr operator/=(new_type const & rhs) const noexcept(nt::concepts::nothrow_compound_divisible<BaseType>)
        -> new_type & requires(nt::concepts::compound_divisible<BaseType> && nt::derives<derivation_clause_type, nt::Arithmetic>) {
          return this->m_value /= rhs.decay();
        }

    // INDIRECTION

    // template<typename DerivationClauseT = decltype(DerivationClause)>
    //   requires(nt::derives<DerivationClauseT, nt::Indirection>)
    // auto constexpr operator->() noexcept -> BaseType *
    // {
    //   return std::addressof(this->m_value);
    // }

    // template<typename DerivationClauseT = decltype(DerivationClause)>
    //   requires(nt::derives<DerivationClauseT, nt::Indirection>)
    // auto constexpr operator->() const noexcept -> BaseType const *
    // {
    //   return std::addressof(this->m_value);
    // }

    // FREE ITERATORS

    template<nt::concepts::free_begin BaseTypeT = BaseType>
    auto constexpr friend begin(new_type & obj) -> new_type<BaseTypeT, TagType, DerivationClause>::iterator
      requires nt::derives<decltype(DerivationClause), nt::Iterable>
    {
      using std::begin;
      return begin(obj.m_value);
    }

    template<nt::concepts::const_free_begin BaseTypeT = BaseType>
    auto constexpr friend begin(new_type const & obj) -> new_type<BaseTypeT, TagType, DerivationClause>::const_iterator
      requires nt::derives<decltype(DerivationClause), nt::Iterable>
    {
      using std::begin;
      return begin(obj.m_value);
    }

    template<nt::concepts::free_cbegin BaseTypeT = BaseType>
    auto constexpr friend cbegin(new_type const & obj) -> new_type<BaseTypeT, TagType, DerivationClause>::const_iterator
      requires nt::derives<decltype(DerivationClause), nt::Iterable>
    {
      using std::cbegin;
      return cbegin(obj.m_value);
    }

    template<nt::concepts::free_rbegin BaseTypeT = BaseType>
    auto constexpr friend rbegin(new_type & obj) -> new_type<BaseTypeT, TagType, DerivationClause>::reverse_iterator
      requires nt::derives<decltype(DerivationClause), nt::Iterable>
    {
      using std::rbegin;
      return rbegin(obj.m_value);
    }

    template<nt::concepts::const_free_rbegin BaseTypeT = BaseType>
    auto constexpr friend rbegin(new_type const & obj) -> new_type<BaseTypeT, TagType, DerivationClause>::const_reverse_iterator
      requires nt::derives<decltype(DerivationClause), nt::Iterable>
    {
      using std::rbegin;
      return rbegin(obj.m_value);
    }

    template<nt::concepts::free_crbegin BaseTypeT = BaseType>
    auto constexpr friend crbegin(new_type const & obj) -> new_type<BaseTypeT, TagType, DerivationClause>::const_reverse_iterator
      requires nt::derives<decltype(DerivationClause), nt::Iterable>
    {
      using std::crbegin;
      return crbegin(obj.m_value);
    }

    template<nt::concepts::free_end BaseTypeT = BaseType>
    auto constexpr friend end(new_type & obj) -> new_type<BaseTypeT, TagType, DerivationClause>::iterator
      requires nt::derives<decltype(DerivationClause), nt::Iterable>
    {
      using std::end;
      return end(obj.m_value);
    }

    template<nt::concepts::const_free_end BaseTypeT = BaseType>
    auto constexpr friend end(new_type const & obj) -> new_type<BaseTypeT, TagType, DerivationClause>::const_iterator
      requires nt::derives<decltype(DerivationClause), nt::Iterable>
    {
      using std::end;
      return end(obj.m_value);
    }

    template<nt::concepts::free_cend BaseTypeT = BaseType>
    auto constexpr friend cend(new_type const & obj) -> new_type<BaseTypeT, TagType, DerivationClause>::const_iterator
      requires nt::derives<decltype(DerivationClause), nt::Iterable>
    {
      using std::cend;
      return cend(obj.m_value);
    }

    template<nt::concepts::free_rend BaseTypeT = BaseType>
    auto constexpr friend rend(new_type & obj) -> new_type<BaseTypeT, TagType, DerivationClause>::reverse_iterator
      requires nt::derives<decltype(DerivationClause), nt::Iterable>
    {
      using std::rend;
      return rend(obj.m_value);
    }

    template<nt::concepts::const_free_rend BaseTypeT = BaseType>
    auto constexpr friend rend(new_type const & obj) -> new_type<BaseTypeT, TagType, DerivationClause>::const_reverse_iterator
      requires nt::derives<decltype(DerivationClause), nt::Iterable>
    {
      using std::rend;
      return rend(obj.m_value);
    }

    template<nt::concepts::free_crend BaseTypeT = BaseType>
    auto constexpr friend crend(new_type const & obj) -> new_type<BaseTypeT, TagType, DerivationClause>::const_reverse_iterator
      requires nt::derives<decltype(DerivationClause), nt::Iterable>
    {
      using std::crend;
      return crend(obj.m_value);
    }

    // MEMBER ITERATORS

    template<nt::concepts::member_begin BaseTypeT = BaseType>
    auto constexpr begin() -> new_type<BaseTypeT, TagType, DerivationClause>::iterator
      requires nt::derives<derivation_clause_type, nt::Iterable>
    {
      return this->m_value.begin();
    }

    template<nt::concepts::const_member_begin BaseTypeT = BaseType>
    auto constexpr begin() const -> new_type<BaseTypeT, TagType, DerivationClause>::const_iterator
      requires nt::derives<derivation_clause_type, nt::Iterable>
    {
      return this->m_value.begin();
    }

    template<nt::concepts::member_cbegin BaseTypeT = BaseType>
    auto constexpr cbegin() const -> new_type<BaseTypeT, TagType, DerivationClause>::const_iterator
      requires nt::derives<derivation_clause_type, nt::Iterable>
    {
      return this->m_value.cbegin();
    }

    template<nt::concepts::member_rbegin BaseTypeT = BaseType>
    auto constexpr rbegin() -> new_type<BaseTypeT, TagType, DerivationClause>::reverse_iterator
      requires nt::derives<derivation_clause_type, nt::Iterable>
    {
      return this->m_value.rbegin();
    }

    template<nt::concepts::const_member_rbegin BaseTypeT = BaseType>
    auto constexpr rbegin() const -> new_type<BaseTypeT, TagType, DerivationClause>::const_reverse_iterator
      requires nt::derives<derivation_clause_type, nt::Iterable>
    {
      return this->m_value.rbegin();
    }

    template<nt::concepts::member_crbegin BaseTypeT = BaseType>
    auto constexpr crbegin() const -> new_type<BaseTypeT, TagType, DerivationClause>::const_reverse_iterator
      requires nt::derives<derivation_clause_type, nt::Iterable>
    {
      return this->m_value.crbegin();
    }

    template<nt::concepts::member_end BaseTypeT = BaseType>
    auto constexpr end() -> new_type<BaseTypeT, TagType, DerivationClause>::iterator
      requires nt::derives<derivation_clause_type, nt::Iterable>
    {
      return this->m_value.end();
    }

    template<nt::concepts::const_member_end BaseTypeT = BaseType>
    auto constexpr end() const -> new_type<BaseTypeT, TagType, DerivationClause>::const_iterator
      requires nt::derives<derivation_clause_type, nt::Iterable>
    {
      return this->m_value.end();
    }

    template<nt::concepts::member_cend BaseTypeT = BaseType>
    auto constexpr cend() const -> new_type<BaseTypeT, TagType, DerivationClause>::const_iterator
      requires nt::derives<derivation_clause_type, nt::Iterable>
    {
      return this->m_value.cend();
    }

    template<nt::concepts::member_rend BaseTypeT = BaseType>
    auto constexpr rend() -> new_type<BaseTypeT, TagType, DerivationClause>::reverse_iterator
      requires nt::derives<derivation_clause_type, nt::Iterable>
    {
      return this->m_value.rend();
    }

    template<nt::concepts::const_member_rend BaseTypeT = BaseType>
    auto constexpr rend() const -> new_type<BaseTypeT, TagType, DerivationClause>::const_reverse_iterator
      requires nt::derives<derivation_clause_type, nt::Iterable>
    {
      return this->m_value.rend();
    }

    template<nt::concepts::member_crend BaseTypeT = BaseType>
    auto constexpr crend() const -> new_type<BaseTypeT, TagType, DerivationClause>::const_reverse_iterator
      requires nt::derives<derivation_clause_type, nt::Iterable>
    {
      return this->m_value.crend();
    }
  };

}  // namespace nt

namespace std
{
  template<nt::concepts::hashable BaseType, typename TagType, nt::derives<nt::Hash> auto DerivationClause>
  struct hash<nt::new_type<BaseType, TagType, DerivationClause>>
  {
    auto constexpr operator()(nt::new_type<BaseType, TagType, DerivationClause> const & object) const
    {
      return std::hash<BaseType>{}(object.decay());
    }
  };
}  // namespace std

#endif
