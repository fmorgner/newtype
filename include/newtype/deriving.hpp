#ifndef NEWTYPE_DERIVING_HPP
#define NEWTYPE_DERIVING_HPP

#include "newtype/derivable.hpp"
#include "newtype/derivation_clause.hpp"
#include "newtype/version.hpp"

#include <type_traits>

namespace nt
{

  /**
   * Create a new derivation clause with the given derivables
   */
  template<typename... DerivableTags>
  auto constexpr deriving(derivable<DerivableTags>... features) noexcept -> derivation_clause<DerivableTags...>
  {
    return {features...};
  }

}  // namespace nt

#endif