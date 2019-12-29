#ifndef NEWTYPE_NEW_TYPE_HPP
#define NEWTYPE_NEW_TYPE_HPP

#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/impl/new_type_storage.hpp"
#include "newtype/type.hpp"

#include <istream>
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
  class new_type : impl::new_type_move_assignment<BaseType, TagType>
  {
    static_assert(!std::is_reference_v<BaseType>, "The base type must not be a reference type");
    static_assert(!std::is_void_v<std::remove_cv_t<BaseType>>, "The base type must not be possibly cv-qualified void");

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV, typename CharType, typename StreamTraits>
    auto friend
    operator>>(std::basic_istream<CharType, StreamTraits> & input, new_type<BaseTypeT, TagTypeT, DerivationClauseV> & target) noexcept(
        noexcept(std::declval<std::basic_istream<CharType, StreamTraits> &>() >> std::declval<BaseTypeT &>()))
        -> std::enable_if_t<DerivationClauseV(nt::Read), std::basic_istream<CharType, StreamTraits>> &;

    using super = impl::new_type_move_assignment<BaseType, TagType>;

  public:
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

    /**
     * @brief The derivation clause fo this nt::new_type
     *
     * This static data-member provides conevient access to the derivation clause of this nt::new_type instance
     */
    auto constexpr static derivation_clause = DerivationClause;

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
  };

  /**
   * @brief Compare two objects for equality
   *
   * @throw This comparison operator throws any exception thrown by the base type comparison operator. It it noexcept iff. the base type
   * comparison operator is noexcept.
   * @return true iff. the base type comparison operator returns true, false otherwise.
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
   * @brief Compare two objects for non-equality
   *
   * @throw This comparison operator throws any exception thrown by the base type comparison operator. It it noexcept iff. the base type
   * comparison operator is noexcept.
   * @return true iff. the base type comparison operator returns true, false otherwise.
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
   * @brief Check if one nt::new_type object is less-than an other
   *
   * @note This operator is only avalaible if the the derivation clause of this nt::new_type does contains nt::Relational. Otherwise is is
   * defined as deleted.
   * @throw This comparison operator throws any exception thrown by the base type comparison operator. It it noexcept iff. the base type
   * comparison operator is noexcept.
   * @return true iff. the base type comparison operator returns true, false otherwise.
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator<(new_type<BaseType, TagType, DerivationClause> const & lhs,
                           new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(noexcept(std::declval<BaseType const &>() <
                                                                                                        std::declval<BaseType const &>()))
      -> std::enable_if_t<DerivationClause(nt::Relational), bool>
  {
    return lhs.decay() < rhs.decay();
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator<(new_type<BaseType, TagType, DerivationClause> const & lhs,
                           new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(noexcept(std::declval<BaseType const &>() <
                                                                                                        std::declval<BaseType const &>()))
      -> std::enable_if_t<!DerivationClause(nt::Relational), bool> = delete;

  /**
   * Check if one nt::new_type object is greater-than an other
   *
   * @note This operator is only avalaible if the the derivation clause of this nt::new_type does contains nt::Relational. Otherwise is is
   * defined as deleted.
   * @throw This comparison operator throws any exception thrown by the base type comparison operator. It it noexcept iff. the base type
   * comparison operator is noexcept.
   * @return true iff. the base type comparison operator returns true, false otherwise.
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator>(new_type<BaseType, TagType, DerivationClause> const & lhs,
                           new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(noexcept(std::declval<BaseType const &>() >
                                                                                                        std::declval<BaseType const &>()))
      -> std::enable_if_t<DerivationClause(nt::Relational), bool>
  {
    return lhs.decay() > rhs.decay();
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator>(new_type<BaseType, TagType, DerivationClause> const & lhs,
                           new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(noexcept(std::declval<BaseType const &>() >
                                                                                                        std::declval<BaseType const &>()))
      -> std::enable_if_t<!DerivationClause(nt::Relational), bool> = delete;

  /**
   * Check if one nt::new_type object is less-than or equal-to an other
   *
   * @note This operator is only avalaible if the the derivation clause of this nt::new_type does contains nt::Relational
   * @throw This comparison operator throws any exception thrown by the base type comparison operator. It it noexcept iff. the base type
   * comparison operator is noexcept.
   * @return true iff. the base type comparison operator returns true, false otherwise.
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator<=(new_type<BaseType, TagType, DerivationClause> const & lhs,
                            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(noexcept(std::declval<BaseType const &>() <=
                                                                                                         std::declval<BaseType const &>()))
      -> std::enable_if_t<DerivationClause(nt::Relational), bool>
  {
    return lhs.decay() <= rhs.decay();
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator<=(new_type<BaseType, TagType, DerivationClause> const & lhs,
                            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(noexcept(std::declval<BaseType const &>() <=
                                                                                                         std::declval<BaseType const &>()))
      -> std::enable_if_t<!DerivationClause(nt::Relational), bool> = delete;

  /**
   * Check if one nt::new_type object is greater-than or equal-to an other
   *
   * @note This operator is only avalaible if the the derivation clause of this nt::new_type does contains nt::Relational
   * @throw This comparison operator throws any exception thrown by the base type comparison operator. It it noexcept iff. the base type
   * comparison operator is noexcept.
   * @return true iff. the base type comparison operator returns true, false otherwise.
   */
  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator>=(new_type<BaseType, TagType, DerivationClause> const & lhs,
                            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(noexcept(std::declval<BaseType const &>() >=
                                                                                                         std::declval<BaseType const &>()))
      -> std::enable_if_t<DerivationClause(nt::Relational), bool>
  {
    return lhs.decay() >= rhs.decay();
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator>=(new_type<BaseType, TagType, DerivationClause> const & lhs,
                            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(noexcept(std::declval<BaseType const &>() >=
                                                                                                         std::declval<BaseType const &>()))
      -> std::enable_if_t<!DerivationClause(nt::Relational), bool> = delete;

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
      noexcept(std::declval<std::basic_ostream<CharType, StreamTraits> &>() << std::declval<BaseType const &>()))
      -> std::enable_if_t<DerivationClause(nt::Show), std::basic_ostream<CharType, StreamTraits>> &
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
      noexcept(std::declval<std::basic_istream<CharType, StreamTraits> &>() >> std::declval<BaseType &>()))
      -> std::enable_if_t<DerivationClause(nt::Read), std::basic_istream<CharType, StreamTraits>> &
  {
    return input >> target.m_value;
  }
}  // namespace nt

#endif
