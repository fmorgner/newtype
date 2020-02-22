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
#include <iterator>
#include <ostream>
#include <type_traits>

namespace nt
{

  /**
   * @brief Create a new type based on an existing one
   *
   * The class template nt::new_type is designed to allow the creation of new types based on existing types. Similarly to the Haskell newtype,
   * this class template creates a new type that is layout equivalent to the underlying type.
   *
   * @tparam BaseType An existing type that shall aliased
   * @tparam TagType A unique type to identify this nt::new_type
   * @tparam DervivationClause An nt::derivation_clause describing which features shall be automatically derived for the new type alias
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

    using super = impl::new_type_move_assignment<BaseType, TagType>;

  public:
    /// @section Type aliases

    /**
     * @brief The base type of this nt::new_type
     *
     * This type alias provides convenient access to the contained objects type
     */
    using base_type = BaseType;

    /**
     * @brief The tag type of this nt::new_type
     *
     * This type alias provides convenient access to the tag type of this nt::new_type instance
     */
    using tag_type = TagType;

    /**
     * @brief The type of the derivation clause of this nt::newtype
     *
     * This type alias provides convenient access to the type of the derivation clause of this nt::new_type instance
     */
    using derivation_clause_type = decltype(DerivationClause);

    /// @section Derivation clause access

    /**
     * @brief The derivation clause fo this nt::new_type
     *
     * This static data-member provides conevient access to the derivation clause of this nt::new_type instance
     */
    auto constexpr static derivation_clause = DerivationClause;

    /// @section Constructors

    using super::super;

    /**
     * @brief Construct an instance of this nt::new_type by default initializing the contained object
     *
     * @note This constructor is available iff. the base type is default-constructible. Otherwise is is defined as deleted.
     * @throw This constructor throws any exception thrown the base type constructor. It is noexcept iff. the base type constructor is noexcept
     */
    constexpr new_type() noexcept(std::is_nothrow_default_constructible_v<BaseType>) = default;

    /**
     * @brief Copy-construct an instance of this nt::new_type from an existing one
     *
     * @note This constructor is available iff. the base type is copy-constructible. Otherwise is is defined as deleted.
     * @throw This constructor throws any exception thrown the base type copy-constructor. It is noexcept iff. the base type copy-constructor
     * is noexcept
     */
    constexpr new_type(new_type const &) noexcept(std::is_nothrow_copy_constructible_v<BaseType>) = default;

    /**
     * @brief Move-construct an instance of this nt::new_type from an existing one
     *
     * @note This constructor is available iff. the base type is move-constructible. Otherwise is is defined as deleted.
     * @throw This constructor throws any exception thrown the base type move-constructor. It is noexcept iff. the base types move-constructor
     * is noexcept
     */
    constexpr new_type(new_type &&) noexcept(std::is_nothrow_move_constructible_v<BaseType>) = default;

    /// @section Assignment operators

    /**
     * @brief Copy-assign the value of an existing instance of this nt::new_type to this instance
     *
     * @note This assignment operator is available iff. the base type is copy-assignable. Otherwise it is defined as deleted.
     * @throw This assignment operator throws any exception thrown by the base type copy-assignment operator. It is noexcept iff. the base type
     * copy-assignment operator is noexcept.
     * @return A reference to this instance
     */
    auto constexpr operator=(new_type const &) noexcept(std::is_nothrow_copy_assignable_v<BaseType>) -> new_type & = default;

    /**
     * @brief Move-assign the value of an existing instance of this nt::new_type to this instance
     *
     * @note This assignment operator is available iff. the base type is move-assignable. Otherwise it is defined as deleted.
     * @throw This assignment operator throws any exception thrown by the base type move-assignment operator. It is noexcept iff. the base type
     * move-assignment operator is noexcept.
     * @return A reference to this instance
     */
    auto constexpr operator=(new_type &&) noexcept(std::is_nothrow_move_assignable_v<BaseType>) -> new_type & = default;

    /// @section Accessors

    /**
     * @brief Obtain a copy of the contained base type object
     *
     * @return BaseType
     */
    auto constexpr decay() const noexcept(std::is_nothrow_copy_constructible_v<BaseType>) -> BaseType
    {
      return this->m_value;
    }

    /**
     * @brief Convert this instance into the equivalent base type value
     *
     * @note This is only available if the derivation clause of this nt::new_type contains nt::ImplicitConversion
     */
    template<typename NewType = new_type, std::enable_if_t<NewType::derivation_clause(nt::ImplicitConversion)> * = nullptr>
    constexpr operator base_type() const noexcept(std::is_nothrow_copy_constructible_v<base_type>)
    {
      return decay();
    }

    /**
     * @brief Convert this instance into the equivalent base type value
     *
     * @note This overload is only avalaible if the derivation clause of this nt::new_type does not contain nt::ImplicitConversion
     */
    template<typename NewType = new_type, std::enable_if_t<!NewType::derivation_clause(nt::ImplicitConversion)> * = nullptr>
    explicit constexpr operator base_type() const noexcept(std::is_nothrow_copy_constructible_v<base_type>)
    {
      return decay();
    }

    /// @section Indirection operators

    /**
     * @brief Perform an access to a member of the base type
     *
     * @return A pointer to the contained base type object
     */
    template<typename NewType = new_type>
    auto constexpr operator-> () noexcept -> std::enable_if_t<NewType::derivation_clause(nt::Indirection), BaseType *>
    {
      return std::addressof(this->m_value);
    }

    /**
     * @brief Perform an access to a member of the base type
     *
     * @return A pointer to the contained base type object
     */
    template<typename NewType = new_type>
    auto constexpr operator-> () const noexcept -> std::enable_if_t<NewType::derivation_clause(nt::Indirection), BaseType const *>
    {
      return std::addressof(this->m_value);
    }

    /// @section Iterators

    /**
     * @brief Get the begin iterator of the base type
     *
     * @return An iterator to the beginning of the base type sequence
     * @throw Any exception thrown by the overload of 'begin' selected
     */
    template<typename NewType = new_type, std::enable_if_t<NewType::derivation_clause(nt::Iterable)> * = nullptr>
    auto constexpr begin()
        -> std::enable_if_t<NewType::derivation_clause(nt::Iterable) && impl::has_member_begin_v<BaseType>, typename NewType::iterator>
    {
      return this->m_value.begin();
    }

    /**
     * @brief Get the begin iterator of the base type
     *
     * @note Overload for constant instances
     * @return An iterator to the beginning of the base type sequence
     * @throw Any exception thrown by the overload of 'begin' selected
     */
    template<typename NewType = new_type>
    auto constexpr begin() const -> std::enable_if_t<NewType::derivation_clause(nt::Iterable) && impl::has_member_begin_v<BaseType const>,
                                                     typename NewType::const_iterator>
    {
      return this->m_value.begin();
    }
  };

  /// @section Equality comparison operators

  /**
   * @brief Compare two objects for equality
   *
   * @throw This comparison operator throws any exception thrown by the base type comparison operator. It it noexcept iff. the base type
   * comparison operator is noexcept.
   * @return true iff. the base type comparison operator returns true, false otherwise.
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
   * @brief Compare an instance of a given nt::new_type with an object of its base type
   *
   * @throw This comparison operator throws any exception thrown by the base type comparison operator. It it noexcept iff. the base type
   * comparison operator is noexcept.
   * @return true iff. the base type comparison operator returns true, false otherwise.
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator==(new_type<BaseType, TagType, DerivationClause> const & lhs,
                            BaseType const & rhs) noexcept(impl::is_nothrow_equality_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::EqBase) && impl::is_equality_comparable_v<BaseType>, bool>
  {
    return lhs.decay() == rhs;
  }

  /**
   * @brief Compare an instance of the base type with an instance of a given nt::new_type
   *
   * @throw This comparison operator throws any exception thrown by the base type comparison operator. It it noexcept iff. the base type
   * comparison operator is noexcept.
   * @return true iff. the base type comparison operator returns true, false otherwise.
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
   * @brief Compare two objects for non-equality
   *
   * @throw This comparison operator throws any exception thrown by the base type comparison operator. It it noexcept iff. the base type
   * comparison operator is noexcept.
   * @return true iff. the base type comparison operator returns true, false otherwise.
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
   * @brief Compare an instance of a given nt::new_type with an object of its base type
   *
   * @throw This comparison operator throws any exception thrown by the base type comparison operator. It it noexcept iff. the base type
   * comparison operator is noexcept.
   * @return true iff. the base type comparison operator returns true, false otherwise.
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator!=(new_type<BaseType, TagType, DerivationClause> const & lhs,
                            BaseType const & rhs) noexcept(impl::is_nothrow_inequality_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::EqBase) && impl::is_inequality_comparable_v<BaseType>, bool>
  {
    return lhs.decay() != rhs;
  }

  /**
   * @brief Compare an instance of the base type with an instance of a given nt::new_type
   *
   * @throw This comparison operator throws any exception thrown by the base type comparison operator. It it noexcept iff. the base type
   * comparison operator is noexcept.
   * @return true iff. the base type comparison operator returns true, false otherwise.
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator!=(BaseType const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_inequality_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::EqBase) && impl::is_inequality_comparable_v<BaseType>, bool>
  {
    return lhs != rhs.decay();
  }

  /// @section Relational operators

  /**
   * @brief Check if one nt::new_type object is less-than an other
   *
   * @note This operator is only available if the the derivation clause of this nt::new_type does contains nt::Relational and the base type is
   * less-than comparable.
   * @throw This comparison operator throws any exception thrown by the base type comparison operator. It it noexcept iff. the base type
   * comparison operator is noexcept.
   * @return true iff. the base type comparison operator returns true, false otherwise.
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
   * Check if one nt::new_type object is greater-than an other
   *
   * @note This operator is only available if the the derivation clause of this nt::new_type does contains nt::Relational and the base type is
   * greater-than comparable.
   * @throw This comparison operator throws any exception thrown by the base type comparison operator. It it noexcept iff. the base type
   * comparison operator is noexcept.
   * @return true iff. the base type comparison operator returns true, false otherwise.
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
   * Check if one nt::new_type object is less-than or equal-to an other
   *
   * @note This operator is only available if the the derivation clause of this nt::new_type does contains nt::Relational and the base type is
   * less-than-or-equal-to comparable.
   * @throw This comparison operator throws any exception thrown by the base type comparison operator. It it noexcept iff. the base type
   * comparison operator is noexcept.
   * @return true iff. the base type comparison operator returns true, false otherwise.
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
   * Check if one nt::new_type object is greater-than or equal-to an other
   *
   * @note This operator is only available if the the derivation clause of this nt::new_type does contains nt::Relational and the base type is
   * greater-than-or-equal comparable
   * @throw This comparison operator throws any exception thrown by the base type comparison operator. It it noexcept iff. the base type
   * comparison operator is noexcept.
   * @return true iff. the base type comparison operator returns true, false otherwise.
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator>=(new_type<BaseType, TagType, DerivationClause> const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_greater_than_equal_to_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Relational) && impl::is_greater_than_equal_to_comparable_v<BaseType>, bool>
  {
    return lhs.decay() >= rhs.decay();
  }

  /// @section Stream input/output operators

  /**
   * @brief Write the contained base type object to a standard output stream
   *
   * @note This operator is only available if the derivation clause of the passed in nt::new_type object contains nt::Show.
   * @param output The output stream to write to
   * @param source An instance of an nt::new_type that shall be written to the stream
   * @return The a reference to the output stream
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
   * @brief Read an object of the base type from a standard input stream
   *
   * @note This operator is only available if the derivation clause of the passed in nt::new_type object contains nt::Read.
   * @param output The input stream to read from
   * @param source An instance of an nt::new_type that shall be read from the stream
   * @return The a reference to the input stream
   */
  template<typename BaseType, typename TagType, auto DerivationClause, typename CharType, typename StreamTraits>
  auto operator>>(std::basic_istream<CharType, StreamTraits> & input, new_type<BaseType, TagType, DerivationClause> & target) noexcept(
      impl::is_nothrow_input_streamable_v<std::basic_istream<CharType, StreamTraits>, BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Read) && impl::is_input_streamable_v<std::basic_istream<CharType, StreamTraits>, BaseType>,
                          std::basic_istream<CharType, StreamTraits>> &
  {
    return input >> target.m_value;
  }

  /// @section Arithmetic operators

  /**
   * @brief Add two instances of the same nt::new_type
   *
   * @note This operator is only available if the derivation clause of the passed in nt::new_type objects contains nt::Arithmetic and the base
   * type is addable.
   * @param lhs The left-hand side of the addition
   * @param rhs The right-hand side of the addition
   * @return a new instance of the same nt::new_type
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
   * @brief Add two instances of the same nt::new_type, modifying the left-hand side
   *
   * @note This operator is only available if the derivation clause of the passed in nt::new_type objects contains nt::Arithmetic and the base
   * type is addable.
   * @param lhs The left-hand side of the addition
   * @param rhs The right-hand side of the addition
   * @return a reference to the the modified value
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
   * @brief Subtract two instances of the same nt::new_type
   *
   * @note This operator is only available if the derivation clause of the passed in nt::new_type objects contains nt::Arithmetic and the base
   * type is subtractable.
   * @param lhs The left-hand side of the subtraction
   * @param rhs The right-hand side of the subtraction
   * @return a new instance of the same nt::new_type
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
   * @brief Subtract two instances of the same nt::new_type, modifying the left-hand side
   *
   * @note This operator is only available if the derivation clause of the passed in nt::new_type objects contains nt::Arithmetic and the base
   * type is subtractable.
   * @param lhs The left-hand side of the subtractition
   * @param rhs The right-hand side of the subtractition
   * @return a reference to the the modified value
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
   * @brief Multiply two instances of the same nt::new_type
   *
   * @note This operator is only available if the derivation clause of the passed in nt::new_type objects contains nt::Arithmetic and the base
   * type is multipliable.
   * @param lhs The left-hand side of the multiplication
   * @param rhs The right-hand side of the multiplication
   * @return a new instance of the same nt::new_type
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
   * @brief Multiply two instances of the same nt::new_type, modifying the left-hand side
   *
   * @note This operator is only available if the derivation clause of the passed in nt::new_type objects contains nt::Arithmetic and the base
   * type is multiplyable.
   * @param lhs The left-hand side of the multiplication
   * @param rhs The right-hand side of the multiplication
   * @return a reference to the the modified value
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
   * @brief Divide two instances of the same nt::new_type
   *
   * @note This operator is only available if the derivation clause of the passed in nt::new_type objects contains nt::Arithmetic and the base
   * type is dividable.
   * @param lhs The left-hand side of the division
   * @param rhs The right-hand side of the division
   * @return a new instance of the same nt::new_type
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
   * @brief Divide two instances of the same nt::new_type, modifying the left-hand side
   *
   * @note This operator is only available if the derivation clause of the passed in nt::new_type objects contains nt::Arithmetic and the base
   * type is dividable.
   * @param lhs The left-hand side of the division
   * @param rhs The right-hand side of the division
   * @return a reference to the the modified value
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

  /// @section Free Iterator Accessors

  /**
   * @brief Get the begin iterator of the base type
   *
   * @return An iterator to the beginning of the base type sequence
   * @throw Any exception thrown by the overload of 'begin' selected
   */
  template<typename BaseType, typename TagType, auto DerivationClause, typename NewType = new_type<BaseType, TagType, DerivationClause>>
  auto constexpr begin(new_type<BaseType, TagType, DerivationClause> & obj)
      -> std::enable_if_t<DerivationClause(nt::Iterable) && impl::has_free_begin_v<BaseType>, typename NewType::iterator>
  {
    return begin(obj);
  }

  /**
   * @brief Get the begin iterator of the base type
   *
   * @note Overload for constant instances
   * @return An iterator to the beginning of the base type sequence
   * @throw Any exception thrown by the overload of 'begin' selected
   */
  template<typename BaseType, typename TagType, auto DerivationClause, typename NewType = new_type<BaseType, TagType, DerivationClause>>
  auto constexpr begin(new_type<BaseType, TagType, DerivationClause> const & obj)
      -> std::enable_if_t<DerivationClause(nt::Iterable) && impl::has_free_begin_v<BaseType const>, typename NewType::const_iterator>
  {
    return begin(obj);
  }

}  // namespace nt

namespace std
{
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
