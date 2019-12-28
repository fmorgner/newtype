#ifndef NEWTYPE_NEW_TYPE_HPP
#define NEWTYPE_NEW_TYPE_HPP

#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/type.hpp"

#include <istream>
#include <ostream>
#include <type_traits>

namespace nt
{

  namespace impl
  {

    template<typename BaseType, typename TagType>
    struct new_type_storage
    {
      constexpr new_type_storage() noexcept(std::is_nothrow_default_constructible_v<BaseType>)
          : m_value{}
      {
      }

      template<typename ArgumentType>
      constexpr explicit new_type_storage(ArgumentType && value) noexcept(std::is_nothrow_constructible_v<BaseType, ArgumentType>)
          : m_value{std::forward<ArgumentType>(value)}
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

      new_type_constructor() = delete;
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

  }  // namespace impl

  /**
   * The class template nt::new_type is designed to allow the creation of new types based on existing types. Similarly to the Haskell newtype,
   * this class template creates a new type that is layout equivalent to the underlying type.
   *
   * @tparam BaseType An existing type that shall aliased
   * @tparam TagType A unique type to identify this nt::new_type
   * @tparam DervivationClause An nt::derivation_clause describing which features shall be automatically derived for the new type alias
   */
  template<typename BaseType, typename TagType, auto DerivationClause = deriving()>
  class new_type : impl::new_type_move_assignment<BaseType, TagType>
  {
    using super = impl::new_type_move_assignment<BaseType, TagType>;

    template<typename BaseTypeT,
             typename TagTypeT,
             auto DerivationClauseV,
             typename CharType,
             typename StreamTraits,
             typename Enablement,
             typename StreamType>
    auto friend operator>>(std::basic_istream<CharType, StreamTraits> & input,
                           new_type<BaseTypeT, TagTypeT, DerivationClauseV> & target) noexcept(noexcept(std::declval<StreamType &>() >>
                                                                                                        std::declval<BaseTypeT &>()))
        -> std::basic_istream<CharType, StreamTraits> &;

  public:
    /**
     * The base type of this nt::new_type
     */
    using base_type = BaseType;

    /**
     * The tag type of this nt::new_type
     */
    using tag_type = TagType;

    /**
     * The type of the derivation clause of this nt::newtype
     */
    using derivation_clause_type = decltype(DerivationClause);

    /**
     * The derivation clause fo this nt::new_type
     */
    auto constexpr static derivation_clause = DerivationClause;

    constexpr new_type() noexcept(std::is_nothrow_default_constructible_v<BaseType>) = default;

    constexpr new_type(new_type const &) noexcept(std::is_nothrow_copy_constructible_v<BaseType>) = default;

    constexpr new_type(new_type &&) noexcept(std::is_nothrow_move_constructible_v<BaseType>) = default;

    constexpr explicit new_type(BaseType const & value) noexcept(std::is_nothrow_copy_constructible_v<BaseType>)
        : super{value}
    {
    }

    constexpr explicit new_type(BaseType const && value) noexcept(std::is_nothrow_move_constructible_v<BaseType>)
        : super{std::move(value)}
    {
    }

    auto constexpr operator=(new_type const &) noexcept(std::is_nothrow_copy_assignable_v<BaseType>) -> new_type & = default;

    auto constexpr operator=(new_type &&) noexcept(std::is_nothrow_move_assignable_v<BaseType>) -> new_type & = default;

    auto constexpr decay() const noexcept(std::is_nothrow_copy_constructible_v<BaseType>) -> BaseType
    {
      return this->m_value;
    }

    /**
     * Convert this instance into the equivalent base type value
     *
     * @note This overload participates only in overload resolution if the derivation clause of this @p new_type contains
     * nt::ImplicitConversion
     */
    template<typename NewType = new_type, std::enable_if_t<NewType::derivation_clause(nt::ImplicitConversion)> * = nullptr>
    constexpr operator base_type() const noexcept(std::is_nothrow_copy_constructible_v<base_type>)
    {
      return decay();
    }

    /**
     * Convert this instance into the equivalent base type value
     *
     * @note This overload participates only in overload resolution if the derivation clause of this @p new_type does not contain
     * nt::ImplicitConversion
     */
    template<typename NewType = new_type, std::enable_if_t<!NewType::derivation_clause(nt::ImplicitConversion)> * = nullptr>
    explicit constexpr operator base_type() const noexcept(std::is_nothrow_copy_constructible_v<base_type>)
    {
      return decay();
    }
  };

  /**
   * Compare two objects for equality
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator==(new_type<BaseType, TagType, DerivationClause> const & lhs,
                            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(noexcept(std::declval<BaseType const &>() ==
                                                                                                         std::declval<BaseType const &>()))
      -> bool
  {
    return lhs.decay() == rhs.decay();
  }

  /**
   * Compare two objects for non-equality
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator!=(new_type<BaseType, TagType, DerivationClause> const & lhs,
                            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(noexcept(std::declval<BaseType const &>() !=
                                                                                                         std::declval<BaseType const &>()))
      -> bool
  {
    return lhs.decay() != rhs.decay();
  }

  /**
   * Check if one nt::new_type object is less-than an other
   *
   * @note This overload participates only in overload resolution if the derivation clause of this @p new_type does contain
   * nt::Relational
   * @return true iff. the object contained by lhs is less-than the one contained by rhs
   */
  template<typename BaseType, typename TagType, auto DerivationClause, typename = std::enable_if_t<DerivationClause(nt::Relational)>>
  auto constexpr operator<(new_type<BaseType, TagType, DerivationClause> const & lhs,
                           new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(noexcept(std::declval<BaseType const &>() <
                                                                                                        std::declval<BaseType const &>()))
      -> bool
  {
    return lhs.decay() < rhs.decay();
  }

  /**
   * Check if one nt::new_type object is greater-than an other
   *
   * @note This overload participates only in overload resolution if the derivation clause of this @p new_type does contain
   * nt::Relational
   * @return true iff. the object contained by lhs is greater-than the one contained by rhs
   */
  template<typename BaseType, typename TagType, auto DerivationClause, typename = std::enable_if_t<DerivationClause(nt::Relational)>>
  auto constexpr operator>(new_type<BaseType, TagType, DerivationClause> const & lhs,
                           new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(noexcept(std::declval<BaseType const &>() >
                                                                                                        std::declval<BaseType const &>()))
      -> bool
  {
    return lhs.decay() > rhs.decay();
  }

  /**
   * Check if one nt::new_type object is less-than or equal-to an other
   *
   * @note This overload participates only in overload resolution if the derivation clause of this @p new_type does contain
   * nt::Relational
   * @return true iff. the object contained by lhs is less-than or equal-to the one contained by rhs
   */
  template<typename BaseType, typename TagType, auto DerivationClause, typename = std::enable_if_t<DerivationClause(nt::Relational)>>
  auto constexpr operator<=(new_type<BaseType, TagType, DerivationClause> const & lhs,
                            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(noexcept(std::declval<BaseType const &>() <=
                                                                                                         std::declval<BaseType const &>()))
      -> bool
  {
    return lhs.decay() <= rhs.decay();
  }

  /**
   * Check if one nt::new_type object is greater-than or equal-to an other
   *
   * @note This overload participates only in overload resolution if the derivation clause of this @p new_type does contain
   * nt::Relational
   * @return true iff. the object contained by lhs is greater-than or equal-to the one contained by rhs
   */
  template<typename BaseType, typename TagType, auto DerivationClause, typename = std::enable_if_t<DerivationClause(nt::Relational)>>
  auto constexpr operator>=(new_type<BaseType, TagType, DerivationClause> const & lhs,
                            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(noexcept(std::declval<BaseType const &>() >=
                                                                                                         std::declval<BaseType const &>()))
      -> bool
  {
    return lhs.decay() >= rhs.decay();
  }

  template<typename BaseType,
           typename TagType,
           auto DerivationClause,
           typename CharType,
           typename StreamTraits,
           typename = std::enable_if_t<DerivationClause(nt::Show)>,
           typename StreamType = std::basic_ostream<CharType, StreamTraits>>
  auto operator<<(std::basic_ostream<CharType, StreamTraits> & output,
                  new_type<BaseType, TagType, DerivationClause> const & source) noexcept(noexcept(std::declval<StreamType &>()
                                                                                                  << std::declval<BaseType const &>()))
      -> std::basic_ostream<CharType, StreamTraits> &
  {
    return output << source.decay();
  }

  template<typename BaseType,
           typename TagType,
           auto DerivationClause,
           typename CharType,
           typename StreamTraits,
           typename = std::enable_if_t<DerivationClause(nt::Read)>,
           typename StreamType = std::basic_istream<CharType, StreamTraits>>
  auto operator>>(std::basic_istream<CharType, StreamTraits> & input, new_type<BaseType, TagType, DerivationClause> & target) noexcept(
      noexcept(std::declval<StreamType &>() >> std::declval<BaseType &>())) -> std::basic_istream<CharType, StreamTraits> &
  {
    return input >> target.m_value;
  }
}  // namespace nt

#endif
