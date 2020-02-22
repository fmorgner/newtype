#ifndef NEWTYPE_NEW_TYPE_HPP
#define NEWTYPE_NEW_TYPE_HPP

#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/impl/new_type_iterator_types.hpp"
#include "newtype/impl/new_type_storage.hpp"
#include "newtype/impl/type_traits_extensions.hpp"
#include "newtype/version.hpp"

#include <functional>
#include <istream>
#include <ostream>
#include <type_traits>

namespace nt
{

  /**
   * Create a new type based on an existing one
   */
  template<typename BaseType, typename TagType, auto DerivationClause = deriving()>
  class new_type
      : impl::new_type_move_assignment<BaseType, TagType>
      , public impl::new_type_iterator_types<BaseType, DerivationClause(nt::Iterable)>
  {
    static_assert(!std::is_reference_v<BaseType>, "The base type must not be a reference type");
    static_assert(!std::is_void_v<std::remove_cv_t<BaseType>>, "The base type must not be possibly cv-qualified void");

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV, typename CharType, typename StreamTraits>
    auto friend operator>>(std::basic_istream<CharType, StreamTraits> &, new_type<BaseTypeT, TagTypeT, DerivationClauseV> &) noexcept(
        impl::is_nothrow_input_streamable_v<std::basic_istream<CharType, StreamTraits>, BaseTypeT>)
        -> std::enable_if_t<DerivationClauseV(nt::Read) && impl::is_input_streamable_v<std::basic_istream<CharType, StreamTraits>, BaseTypeT>,
                            std::basic_istream<CharType, StreamTraits>> &;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend
    operator+=(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & lhs,
               new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & rhs) noexcept(impl::is_nothrow_add_assignable_v<BaseTypeT>)
        -> std::enable_if_t<DerivationClauseV(nt::Arithmetic) && impl::is_add_assignable_v<BaseTypeT>,
                            new_type<BaseTypeT, TagTypeT, DerivationClauseV> &>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend
    operator-=(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & lhs,
               new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & rhs) noexcept(impl::is_nothrow_subtract_assignable_v<BaseTypeT>)
        -> std::enable_if_t<DerivationClauseV(nt::Arithmetic) && impl::is_subtract_assignable_v<BaseTypeT>,
                            new_type<BaseTypeT, TagTypeT, DerivationClauseV> &>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend
    operator*=(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & lhs,
               new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & rhs) noexcept(impl::is_nothrow_multiply_assignable_v<BaseTypeT>)
        -> std::enable_if_t<DerivationClauseV(nt::Arithmetic) && impl::is_multiply_assignable_v<BaseTypeT>,
                            new_type<BaseTypeT, TagTypeT, DerivationClauseV> &>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend
    operator/=(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & lhs,
               new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & rhs) noexcept(impl::is_nothrow_divide_assignable_v<BaseTypeT>)
        -> std::enable_if_t<DerivationClauseV(nt::Arithmetic) && impl::is_divide_assignable_v<BaseTypeT>,
                            new_type<BaseTypeT, TagTypeT, DerivationClauseV> &>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend begin(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & obj)
        -> std::enable_if_t<DerivationClauseV(nt::Iterable) && impl::has_free_begin_v<BaseTypeT>,
                            typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::iterator>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend begin(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj)
        -> std::enable_if_t<DerivationClauseV(nt::Iterable) && impl::has_free_begin_v<BaseTypeT>,
                            typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_iterator>;

    using super = impl::new_type_move_assignment<BaseType, TagType>;

  public:
    /// Member Type Aliases

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

    /// Static Data Members

    /**
     * The derivation clause fo this nt::new_type
     */
    auto constexpr static derivation_clause = DerivationClause;

    /// Constructors

    using super::super;

    /**
     * Construct an instance of this nt::new_type by default initializing the contained object
     */
    constexpr new_type() noexcept(std::is_nothrow_default_constructible_v<BaseType>) = default;

    /**
     * Copy-construct an instance of this nt::new_type from an existing one
     */
    constexpr new_type(new_type const &) noexcept(std::is_nothrow_copy_constructible_v<BaseType>) = default;

    /**
     * Move-construct an instance of this nt::new_type from an existing one
     */
    constexpr new_type(new_type &&) noexcept(std::is_nothrow_move_constructible_v<BaseType>) = default;

    /// Assignment Operators

    /**
     * Copy-assign the value of an existing instance of this nt::new_type to this instance
     */
    auto constexpr operator=(new_type const &) noexcept(std::is_nothrow_copy_assignable_v<BaseType>) -> new_type & = default;

    /**
     * Move-assign the value of an existing instance of this nt::new_type to this instance
     */
    auto constexpr operator=(new_type &&) noexcept(std::is_nothrow_move_assignable_v<BaseType>) -> new_type & = default;

    /// Accessors

    /**
     * Retrieve a copy of the object contained by this new_type object
     */
    auto constexpr decay() const noexcept(std::is_nothrow_copy_constructible_v<BaseType>) -> BaseType
    {
      return this->m_value;
    }

    /**
     * Retrieve a copy of the object contained by this new_type object
     */
    template<typename NewType = new_type, std::enable_if_t<NewType::derivation_clause(nt::ImplicitConversion)> * = nullptr>
    constexpr operator base_type() const noexcept(std::is_nothrow_copy_constructible_v<base_type>)
    {
      return decay();
    }

    /**
     * Convert this instance into the equivalent base type value
     */
    template<typename NewType = new_type, std::enable_if_t<!NewType::derivation_clause(nt::ImplicitConversion)> * = nullptr>
    explicit constexpr operator base_type() const noexcept(std::is_nothrow_copy_constructible_v<base_type>)
    {
      return decay();
    }

    /// Member Access Through Pointer

    /**
     * Perform "member access through pointer" via a pointer to object contained by this new_type
     */
    template<typename NewType = new_type>
    auto constexpr operator-> () noexcept -> std::enable_if_t<NewType::derivation_clause(nt::Indirection), BaseType *>
    {
      return std::addressof(this->m_value);
    }

    /**
     * Perform "member access through pointer" via a pointer to object contained by this new_type
     */
    template<typename NewType = new_type>
    auto constexpr operator-> () const noexcept -> std::enable_if_t<NewType::derivation_clause(nt::Indirection), BaseType const *>
    {
      return std::addressof(this->m_value);
    }

    /// Iterators

    /**
     * Get an iterator to the beginning of the object contained by this new_type
     */
    template<typename NewType = new_type, std::enable_if_t<NewType::derivation_clause(nt::Iterable)> * = nullptr>
    auto constexpr begin()
        -> std::enable_if_t<NewType::derivation_clause(nt::Iterable) && impl::has_member_begin_v<BaseType>, typename NewType::iterator>
    {
      return this->m_value.begin();
    }

    /**
     * Get an iterator to the beginning of the object contained by this new_type
     */
    template<typename NewType = new_type>
    auto constexpr begin() const -> std::enable_if_t<NewType::derivation_clause(nt::Iterable) && impl::has_member_begin_v<BaseType const>,
                                                     typename NewType::const_iterator>
    {
      return this->m_value.begin();
    }
  };

  /// Equality Comparison Operators

  /**
   * Check two instances of new_type<BaseType, TagType, DerivationClause> for equality
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator==(new_type<BaseType, TagType, DerivationClause> const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_equality_comparable_v<BaseType>)
      -> std::enable_if_t<impl::is_equality_comparable_v<BaseType>, bool>
  {
    return lhs.decay() == rhs.decay();
  }

  /**
   * Check an instance of new_type<BaseType, TagType, DerivationClause> for equality with an instance of BaseType
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator==(new_type<BaseType, TagType, DerivationClause> const & lhs,
                            BaseType const & rhs) noexcept(impl::is_nothrow_equality_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::EqBase) && impl::is_equality_comparable_v<BaseType>, bool>
  {
    return lhs.decay() == rhs;
  }

  /**
   * Check an instance of BaseType for equality with an instance of new_type<BaseType, TagType, DerivationClause>
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator==(BaseType const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_equality_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::EqBase) && impl::is_equality_comparable_v<BaseType>, bool>
  {
    return lhs == rhs.decay();
  }

  /**
   * Check two instances of new_type<BaseType, TagType, DerivationClause> for in-equality
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator!=(new_type<BaseType, TagType, DerivationClause> const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_inequality_comparable_v<BaseType>)
      -> std::enable_if_t<impl::is_inequality_comparable_v<BaseType>, bool>
  {
    return lhs.decay() != rhs.decay();
  }

  /**
   * Check an instance of new_type<BaseType, TagType, DerivationClause> for in-equality with an instance of BaseType
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator!=(new_type<BaseType, TagType, DerivationClause> const & lhs,
                            BaseType const & rhs) noexcept(impl::is_nothrow_inequality_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::EqBase) && impl::is_inequality_comparable_v<BaseType>, bool>
  {
    return lhs.decay() != rhs;
  }

  /**
   * Check an instance of BaseType for in-equality with an instance of new_type<BaseType, TagType, DerivationClause>
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator!=(BaseType const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_inequality_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::EqBase) && impl::is_inequality_comparable_v<BaseType>, bool>
  {
    return lhs != rhs.decay();
  }

  /// Relational Comparison Operators

  /**
   * Compare two instances of the same new_type using '<' (less-than)
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator<(new_type<BaseType, TagType, DerivationClause> const & lhs,
            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_less_than_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Relational) && impl::is_less_than_comparable_v<BaseType>, bool>
  {
    return lhs.decay() < rhs.decay();
  }

  /**
   * Compare two instances of the same new_type using '>' (greater-than)
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator>(new_type<BaseType, TagType, DerivationClause> const & lhs,
            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_greater_than_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Relational) && impl::is_greater_than_comparable_v<BaseType>, bool>
  {
    return lhs.decay() > rhs.decay();
  }

  /**
   * Compare two instances of the same new_type using '<=' (less-than-equal)
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator<=(new_type<BaseType, TagType, DerivationClause> const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_less_than_equal_to_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Relational) && impl::is_less_than_equal_to_comparable_v<BaseType>, bool>
  {
    return lhs.decay() <= rhs.decay();
  }

  /**
   * Compare two instances of the same new_type using '>=' (greater-than-equal)
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator>=(new_type<BaseType, TagType, DerivationClause> const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_greater_than_equal_to_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Relational) && impl::is_greater_than_equal_to_comparable_v<BaseType>, bool>
  {
    return lhs.decay() >= rhs.decay();
  }

  /// Stream I/O Operators

  /**
   * Write an instance of new_type<BaseType, TagType, DerivationClause> to a standard ostream
   */
  template<typename BaseType, typename TagType, auto DerivationClause, typename CharType, typename StreamTraits>
  auto operator<<(std::basic_ostream<CharType, StreamTraits> & output, new_type<BaseType, TagType, DerivationClause> const & source) noexcept(
      impl::is_nothrow_output_streamable_v<std::basic_ostream<CharType, StreamTraits>, BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Show) && impl::is_output_streamable_v<std::basic_ostream<CharType, StreamTraits>, BaseType>,
                          std::basic_ostream<CharType, StreamTraits>> &
  {
    return output << source.decay();
  }

  /**
   * Read an instance of new_type<BaseType, TagType, DerivationClause> from the a standard istream
   */
  template<typename BaseType, typename TagType, auto DerivationClause, typename CharType, typename StreamTraits>
  auto operator>>(std::basic_istream<CharType, StreamTraits> & input, new_type<BaseType, TagType, DerivationClause> & target) noexcept(
      impl::is_nothrow_input_streamable_v<std::basic_istream<CharType, StreamTraits>, BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Read) && impl::is_input_streamable_v<std::basic_istream<CharType, StreamTraits>, BaseType>,
                          std::basic_istream<CharType, StreamTraits>> &
  {
    return input >> target.m_value;
  }

  /// Arithmetic Operators

  /**
   * Add two instances of the same new_type
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator+(new_type<BaseType, TagType, DerivationClause> const & lhs, new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(
      impl::is_nothrow_addable_v<BaseType> && std::is_nothrow_copy_constructible_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Arithmetic) && impl::is_addable_v<BaseType>, new_type<BaseType, TagType, DerivationClause>>
  {
    return {lhs.decay() + rhs.decay()};
  }

  /**
   * Add two instances of the same new_type by overwriting the first one
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator+=(new_type<BaseType, TagType, DerivationClause> & lhs,
                            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_add_assignable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Arithmetic) && impl::is_add_assignable_v<BaseType>,
                          new_type<BaseType, TagType, DerivationClause> &>
  {
    lhs.m_value += rhs.m_value;
    return lhs;
  }

  /**
   * Subtract two instances of the same new_type
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator-(new_type<BaseType, TagType, DerivationClause> const & lhs, new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(
      impl::is_nothrow_subtractable_v<BaseType> && std::is_nothrow_copy_constructible_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Arithmetic) && impl::is_subtractable_v<BaseType>, new_type<BaseType, TagType, DerivationClause>>
  {
    return {lhs.decay() - rhs.decay()};
  }

  /**
   * Subtract two instances of the same new_type by overwriting the first one
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator-=(new_type<BaseType, TagType, DerivationClause> & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_subtract_assignable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Arithmetic) && impl::is_subtract_assignable_v<BaseType>,
                          new_type<BaseType, TagType, DerivationClause> &>
  {
    lhs.m_value -= rhs.m_value;
    return lhs;
  }

  /**
   * Multiply two instances of the same new_type
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator*(new_type<BaseType, TagType, DerivationClause> const & lhs, new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(
      impl::is_nothrow_multipliable_v<BaseType> && std::is_nothrow_copy_constructible_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Arithmetic) && impl::is_multipliable_v<BaseType>, new_type<BaseType, TagType, DerivationClause>>
  {
    return {lhs.decay() * rhs.decay()};
  }

  /**
   * Multiply two instances of the same new_type by overwriting the first one
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator*=(new_type<BaseType, TagType, DerivationClause> & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_multiply_assignable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Arithmetic) && impl::is_multiply_assignable_v<BaseType>,
                          new_type<BaseType, TagType, DerivationClause> &>
  {
    lhs.m_value *= rhs.m_value;
    return lhs;
  }

  /**
   * Divide two instances of the same nt::new_type
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator/(new_type<BaseType, TagType, DerivationClause> const & lhs, new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(
      impl::is_nothrow_dividable_v<BaseType> && std::is_nothrow_copy_constructible_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Arithmetic) && impl::is_dividable_v<BaseType>, new_type<BaseType, TagType, DerivationClause>>
  {
    return {lhs.decay() / rhs.decay()};
  }

  /**
   * Divide two instances of the same new_type by overwriting the first one
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator/=(new_type<BaseType, TagType, DerivationClause> & lhs,
                            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_divide_assignable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Arithmetic) && impl::is_divide_assignable_v<BaseType>,
                          new_type<BaseType, TagType, DerivationClause> &>
  {
    lhs.m_value /= rhs.m_value;
    return lhs;
  }

  /// Iterators

  /**
   * Get an iterator to the beginning of the object contained by an instance of new_type
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr begin(new_type<BaseType, TagType, DerivationClause> & obj)
      -> std::enable_if_t<DerivationClause(nt::Iterable) && impl::has_free_begin_v<BaseType>,
                          typename new_type<BaseType, TagType, DerivationClause>::iterator>
  {
    return begin(obj.m_value);
  }

  /**
   * Get a constant iterator to the beginning of the object contained by an instance of new_type
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr begin(new_type<BaseType, TagType, DerivationClause> const & obj)
      -> std::enable_if_t<DerivationClause(nt::Iterable) && impl::has_free_begin_v<BaseType const>,
                          typename new_type<BaseType, TagType, DerivationClause>::const_iterator>
  {
    return begin(obj.m_value);
  }

}  // namespace nt

namespace std
{
  /**
   * Hash an instance of new_type using the hash implementation of the base type
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  struct hash<nt::new_type<BaseType, TagType, DerivationClause>>
  {
    template<typename BaseTypeT = BaseType, auto DerivationClauseV = DerivationClause>
    auto constexpr operator()(nt::new_type<BaseType, TagType, DerivationClause> const & object,
                              std::enable_if_t<DerivationClauseV(nt::Hash) && nt::impl::is_hashable_v<BaseTypeT>> * = nullptr) const
        -> std::size_t
    {
      return std::hash<BaseType>{}(object.decay());
    }
  };
}  // namespace std

#endif
