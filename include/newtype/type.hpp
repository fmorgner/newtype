#ifndef NEWTYPE_TYPE_HPP
#define NEWTYPE_TYPE_HPP

namespace nt
{

  /**
   * A convenience type to make values out of types
   *
   * @tparam Type The type to wrap
   * @since 1.0.0
   */
  template<typename Type>
  struct type final
  {
  };

  /**
   * A value to represent a type
   *
   * @tparam The type to represent
   * @since 1.0.0
   */
  template<typename Type>
  auto constexpr type_v = type<Type>{};

}  // namespace nt

#endif