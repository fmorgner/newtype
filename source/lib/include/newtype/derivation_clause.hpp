#ifndef NEWTYPE_DERIVATION_CLAUSE_HPP
#define NEWTYPE_DERIVATION_CLAUSE_HPP

#include "newtype/derivable.hpp"
#include "newtype/version.hpp"

#include <type_traits>

namespace nt
{

  template<typename... DerivableTags>
  struct derivation_clause
  {
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

  template<typename DerivationClause, auto Feature>
  concept contains = requires(DerivationClause clause) { requires clause(Feature); };

}  // namespace nt

#endif