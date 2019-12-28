#ifndef NEWTYPE_NEW_TYPE_HPP
#define NEWTYPE_NEW_TYPE_HPP

#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/type.hpp"

#include <type_traits>

namespace nt
{

  namespace impl
  {

    /**
     * This class forms the a base type of nt::new_type and provides its storage
     *
     * This specialization enables the default constructor for cases in which @p BaseType is default constructible
     *
     * @tparam BaseType An existing type that shall aliased
     * @tparam TagType A unique type to identify this nt::new_type
     */
    template<typename BaseType, typename TagType, bool = std::is_default_constructible_v<BaseType>>
    struct new_type_storage
    {
      constexpr new_type_storage() noexcept(std::is_nothrow_default_constructible_v<BaseType>) = default;

      constexpr explicit new_type_storage(BaseType const & value) noexcept(std::is_nothrow_copy_constructible_v<BaseType>)
          : m_value{value}
      {
      }

      constexpr explicit new_type_storage(BaseType && value) noexcept(std::is_nothrow_move_constructible_v<BaseType>)
          : m_value{std::move(value)}
      {
      }

      /**
       * Retrieve the base type value contained in this @p new_type
       */
      auto constexpr decay() const noexcept(std::is_nothrow_copy_constructible_v<BaseType>) -> BaseType
      {
        return m_value;
      }

    private:
      BaseType m_value{};
    };

    /**
     * This class forms the a base type of nt::new_type and provides its storage
     *
     * This specialization explicitly deletes the default constructor for cases in which @p BaseType is not default
     * constructible
     *
     * @tparam BaseType An existing type that shall aliased
     * @tparam TagType A unique type to identify this nt::new_type
     */
    template<typename BaseType, typename TagType>
    struct new_type_storage<BaseType, TagType, false>
    {
      constexpr new_type_storage() = delete;

      constexpr explicit new_type_storage(BaseType const & value) noexcept(std::is_nothrow_copy_constructible_v<BaseType>)
          : m_value{value}
      {
      }

      constexpr explicit new_type_storage(BaseType && value) noexcept(std::is_nothrow_move_constructible_v<BaseType>)
          : m_value{std::move(value)}
      {
      }

      /**
       * Retrieve the base type value contained in this @p new_type
       */
      auto constexpr decay() const noexcept(std::is_nothrow_copy_constructible_v<BaseType>) -> BaseType
      {
        return m_value;
      }

    private:
      BaseType m_value;
    };

  }  // namespace impl

  /**
   * @tparam BaseType An existing type that shall aliased
   * @tparam TagType A unique type to identify this nt::new_type
   * @tparam DervivationClause An nt::derivation_clause describing which features shall be automatically derived for the new type alias
   */
  template<typename BaseType, typename TagType, auto DerivationClause = deriving()>
  class new_type : public impl::new_type_storage<BaseType, TagType>
  {
    using impl::new_type_storage<BaseType, TagType>::new_type_storage;

    using base_type = BaseType;
    using tag_type = TagType;

    auto constexpr static derivations = DerivationClause;

  public:
    using impl::new_type_storage<BaseType, TagType>::decay;

    /**
     * Convert this instance into the equivalent base type value
     *
     * @note This overload participates only in overload resolution if the derivation clause of this @p new_type contains
     * nt::ImplicitConversion
     */
    template<typename NewType = new_type, std::enable_if_t<NewType::derivations(nt::ImplicitConversion)> * = nullptr>
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
    template<typename NewType = new_type, std::enable_if_t<!NewType::derivations(nt::ImplicitConversion)> * = nullptr>
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

}  // namespace nt

#endif
