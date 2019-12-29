#ifndef NEWTYPE_DERIVABLE_HPP
#define NEWTYPE_DERIVABLE_HPP

#include "newtype/type.hpp"

namespace nt
{

  template<typename NameTag>
  using derivable = type<NameTag>;

  /**
   * @brief A set of standard derivation tags
   *
   * This convenience namespace contains all standard derivation tags.
   *
   * @since 1.0.0
   */
  inline namespace derivables
  {

    /**
     * @brief A tag to enable derivation of arithmetic operators
     *
     * @since 1.0.0
     */
    auto constexpr Arithmetic = derivable<struct arithmetic_tag>{};

    /**
     * @brief A tag to enable derivation of equality comparison operators
     *
     * @since 1.0.0
     */
    auto constexpr EqBase = derivable<struct eq_tag>{};

    /**
     * @brief A tag to enable derivation of the implicit "conversion to base type" operator
     *
     * @note If this tag is not present in the derivation clause of any given nt::new_type, the type instance only supports explicit
     * "conversion to base type"
     * @since 1.0.0
     */
    auto constexpr ImplicitConversion = derivable<struct implicit_conversion_tag>{};

    /**
     * @brief A tag to enable access to the members of the base type object through a pointer
     *
     * @since 1.0.0
     */
    auto constexpr Indirection = derivable<struct indirection_tag>{};

    /**
     * @brief A tag to enable derivation of the stream input operator
     *
     * @since 1.0.0
     */
    auto constexpr Read = derivable<struct read_tag>{};

    /**
     * @brief A tag to enable derivation of the relational operators
     *
     * @since 1.0.0
     */
    auto constexpr Relational = derivable<struct relational_tag>{};

    /**
     * @brief A tag to enable derivation of the stream output operator
     *
     * @since 1.0.0
     */
    auto constexpr Show = derivable<struct show_tag>{};

  }  // namespace derivables

}  // namespace nt

#endif