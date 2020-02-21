#ifndef NEWTYPE_IMPL_NEW_TYPE_ITERATOR_TYPES_HPP
#define NEWTYPE_IMPL_NEW_TYPE_ITERATOR_TYPES_HPP

#include "newtype/version.hpp"

#include <type_traits>

namespace nt::impl
{

  template<typename T, bool = false, typename = std::void_t<>>
  struct new_type_iterator
  {
  };

  template<typename T>
  struct new_type_iterator<T, true, std::void_t<typename T::iterator>>
  {
    using iterator = typename T::iterator;
  };

  template<typename T, bool = false, typename = std::void_t<>>
  struct new_type_const_iterator
  {
  };

  template<typename T>
  struct new_type_const_iterator<T, true, std::void_t<typename T::const_iterator>>
  {
    using const_iterator = typename T::const_iterator;
  };

  template<typename T, bool Enabled>
  struct new_type_iterator_types
      : new_type_iterator<T, Enabled>
      , new_type_const_iterator<T, Enabled>
  {
  };

}  // namespace nt::impl

#endif