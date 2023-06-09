#ifndef NEWTYPE_IMPL_NEW_TYPE_STORAGE_HPP
#define NEWTYPE_IMPL_NEW_TYPE_STORAGE_HPP

#include <type_traits>
#include <utility>

namespace nt::impl
{

  template<typename BaseType, typename TagType>
  struct new_type_storage
  {
    constexpr new_type_storage() noexcept(std::is_nothrow_default_constructible_v<BaseType>)
        : m_value{}
    {
    }

    constexpr new_type_storage(BaseType const & value)
        : m_value{value}
    {
    }

    constexpr new_type_storage(BaseType && value)
        : m_value{std::move(value)}
    {
    }

    BaseType m_value;
  };

  template<typename BaseType, typename TagType, bool = std::is_default_constructible_v<BaseType>>
  struct new_type_constructor : new_type_storage<BaseType, TagType>
  {
    using new_type_storage<BaseType, TagType>::new_type_storage;
  };

  template<typename BaseType, typename TagType>
  struct new_type_constructor<BaseType, TagType, false> : new_type_storage<BaseType, TagType>
  {
    using new_type_storage<BaseType, TagType>::new_type_storage;

    constexpr new_type_constructor() = delete;
  };

  template<typename BaseType, typename TagType, bool = std::is_copy_constructible_v<BaseType>>
  struct new_type_copy_constructor : new_type_constructor<BaseType, TagType>
  {
    using new_type_constructor<BaseType, TagType>::new_type_constructor;

    constexpr new_type_copy_constructor(new_type_copy_constructor const &) = default;
    constexpr new_type_copy_constructor(new_type_copy_constructor &&) = default;
    auto constexpr operator=(new_type_copy_constructor &) -> new_type_copy_constructor & = default;
    auto constexpr operator=(new_type_copy_constructor &&) -> new_type_copy_constructor & = default;
  };

  template<typename BaseType, typename TagType>
  struct new_type_copy_constructor<BaseType, TagType, false> : new_type_constructor<BaseType, TagType>
  {
    using new_type_constructor<BaseType, TagType>::new_type_constructor;

    constexpr new_type_copy_constructor(new_type_copy_constructor const &) = delete;
    constexpr new_type_copy_constructor(new_type_copy_constructor &&) = default;
    constexpr new_type_copy_constructor(BaseType const &) = delete;
    auto constexpr operator=(new_type_copy_constructor &) -> new_type_copy_constructor & = default;
    auto constexpr operator=(new_type_copy_constructor &&) -> new_type_copy_constructor & = default;
  };

  template<typename BaseType, typename TagType, bool = std::is_move_constructible_v<BaseType>>
  struct new_type_move_constructor : new_type_copy_constructor<BaseType, TagType>
  {
    using new_type_copy_constructor<BaseType, TagType>::new_type_copy_constructor;

    constexpr new_type_move_constructor(new_type_move_constructor const &) = default;
    constexpr new_type_move_constructor(new_type_move_constructor &&) = default;
    auto constexpr operator=(new_type_move_constructor &) -> new_type_move_constructor & = default;
    auto constexpr operator=(new_type_move_constructor &&) -> new_type_move_constructor & = default;
  };

  template<typename BaseType, typename TagType>
  struct new_type_move_constructor<BaseType, TagType, false> : new_type_copy_constructor<BaseType, TagType>
  {
    using new_type_copy_constructor<BaseType, TagType>::new_type_copy_constructor;

    constexpr new_type_move_constructor(new_type_move_constructor const &) = default;
    constexpr new_type_move_constructor(new_type_move_constructor &&) = delete;
    constexpr new_type_move_constructor(BaseType &&) = delete;
    auto constexpr operator=(new_type_move_constructor &) -> new_type_move_constructor & = default;
    auto constexpr operator=(new_type_move_constructor &&) -> new_type_move_constructor & = default;
  };

  template<typename BaseType, typename TagType, bool = std::is_copy_assignable_v<BaseType>>
  struct new_type_copy_assignment : new_type_move_constructor<BaseType, TagType>
  {
    using new_type_move_constructor<BaseType, TagType>::new_type_move_constructor;

    constexpr new_type_copy_assignment(new_type_copy_assignment const &) = default;
    constexpr new_type_copy_assignment(new_type_copy_assignment &&) = default;
    auto constexpr operator=(new_type_copy_assignment &) -> new_type_copy_assignment & = default;
    auto constexpr operator=(new_type_copy_assignment &&) -> new_type_copy_assignment & = default;
  };

  template<typename BaseType, typename TagType>
  struct new_type_copy_assignment<BaseType, TagType, false> : new_type_move_constructor<BaseType, TagType>
  {
    using new_type_move_constructor<BaseType, TagType>::new_type_move_constructor;

    constexpr new_type_copy_assignment(new_type_copy_assignment const &) = default;
    constexpr new_type_copy_assignment(new_type_copy_assignment &&) = default;
    auto constexpr operator=(new_type_copy_assignment &) -> new_type_copy_assignment & = default;
    auto constexpr operator=(new_type_copy_assignment &&) -> new_type_copy_assignment & = delete;
  };

  template<typename BaseType, typename TagType, bool = std::is_move_assignable_v<BaseType>>
  struct new_type_move_assignment : new_type_copy_assignment<BaseType, TagType>
  {
    using new_type_copy_assignment<BaseType, TagType>::new_type_copy_assignment;

    constexpr new_type_move_assignment(new_type_move_assignment const &) = default;
    constexpr new_type_move_assignment(new_type_move_assignment &&) = default;
    auto constexpr operator=(new_type_move_assignment &) -> new_type_move_assignment & = default;
    auto constexpr operator=(new_type_move_assignment &&) -> new_type_move_assignment & = default;
  };

  template<typename BaseType, typename TagType>
  struct new_type_move_assignment<BaseType, TagType, false> : new_type_copy_assignment<BaseType, TagType>
  {
    using new_type_copy_assignment<BaseType, TagType>::new_type_copy_assignment;

    constexpr new_type_move_assignment(new_type_move_assignment const &) = default;
    constexpr new_type_move_assignment(new_type_move_assignment &&) = default;
    auto constexpr operator=(new_type_move_assignment &) -> new_type_move_assignment & = default;
    auto constexpr operator=(new_type_move_assignment &&) -> new_type_move_assignment & = delete;
  };

}  // namespace nt::impl

#endif
