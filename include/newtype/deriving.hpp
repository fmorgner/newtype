#ifndef NEWTYPE_DERIVING_HPP
#define NEWTYPE_DERIVING_HPP

#include "newtype/derivable.hpp"

#include <type_traits>

namespace nt
{

  /**
   * A @p deriving clause type
   *
   * @tparam DerivableTags A list of tag types defining a set of derivable features
   */
  template<typename... DerivableTags>
  struct derivation_clause
  {
    constexpr derivation_clause(derivable<DerivableTags>...) noexcept
    {
    }

    /**
     * Check whether the derivation clause contains a given derivable
     */
    template<typename DerivableTag>
    auto constexpr operator()(derivable<DerivableTag>) const noexcept -> bool
    {
      return (std::is_same_v<DerivableTags, DerivableTag> || ...);
    }

    /**
     * Check whether the derivation clause contains all derivables in a given lists
     */
    template<typename DerivableTag, typename... RemainingDerivableTags>
    auto constexpr operator()(derivable<DerivableTag>, derivable<RemainingDerivableTags>...) const noexcept -> bool
    {
      return (*this)(derivable<DerivableTag>{}) && (*this)(derivable<RemainingDerivableTags>{}...);
    }

    /**
     * Check whether this derivation clause is less than an other derivation clause
     *
     * A derivation clause is considered less than an other derivation clause iff. its set of derivables is a strict subset of
     * the set derivables of the other.
     */
    template<typename... OtherDerivableTags>
    auto constexpr operator<(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool
    {
      return (sizeof...(DerivableTags) < sizeof...(OtherDerivableTags)) && other(derivable<DerivableTags>{}...);
    }

    /**
     * Check whether this derivation clause is greater than an other derivation clause
     *
     * A derivation clause is considered greater than an other derivation clause iff. its set of derivables is a strict superset
     * of the set derivables of the other.
     */
    template<typename... OtherDerivableTags>
    auto constexpr operator>(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool
    {
      return other < *this;
    }

    /**
     * Check whether this derivation clause is equal to an other derivation clause
     *
     * Two derivation clauses are considered equal if both have the same set of derivables
     */
    template<typename... OtherDerivableTags>
    auto constexpr operator==(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool
    {
      return sizeof...(DerivableTags) == sizeof...(OtherDerivableTags) && other(derivable<DerivableTags>{}...);
    }

    /**
     * Check whether this derivation clause is not equal to an other derivation clause
     *
     * Two derivation clauses are considered not equal if neither has the same set of derivables as the other
     */
    template<typename... OtherDerivableTags>
    auto constexpr operator!=(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool
    {
      return !(*this == other);
    }

    /**
     * Check whether this derivation clause is less-than or equal to an other derivation clause
     *
     * @see nt::distinct::operator==
     * @see nt::distinct::operator<
     */
    template<typename... OtherDerivableTags>
    auto constexpr operator<=(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool
    {
      return *this < other || *this == other;
    }

    /**
     * Check whether this derivation clause is greater-than or equal to an other derivation clause
     *
     * @see nt::distinct::operator==
     * @see nt::distinct::operator<
     */
    template<typename... OtherDerivableTags>
    auto constexpr operator>=(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool
    {
      return *this > other || *this == other;
    }
  };

  /**
   * Create a new derivation clause with the given derivables
   */
  template<typename... DerivableTags>
  auto constexpr deriving(derivable<DerivableTags>... request) -> derivation_clause<DerivableTags...>
  {
    return {request...};
  }

}  // namespace nt

#endif