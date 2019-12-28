#ifndef NEWTYPE_DERIVING_HPP
#define NEWTYPE_DERIVING_HPP

#include "newtype/derivable.hpp"
#include "newtype/derivation_clause.hpp"

#include <type_traits>

namespace nt
{

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