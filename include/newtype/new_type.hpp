#ifndef NEWTYPE_NEW_TYPE_HPP
#define NEWTYPE_NEW_TYPE_HPP

#include "newtype/derivable.hpp"
#include "newtype/deriving.hpp"
#include "newtype/impl/new_type_iterator_types.hpp"
#include "newtype/impl/new_type_storage.hpp"
#include "newtype/impl/type_traits_extensions.hpp"
#include "newtype/version.hpp"

#include <functional>
#include <istream>
#include <ostream>
#include <type_traits>

namespace nt
{

  template<typename BaseType, typename TagType, auto DerivationClause = deriving()>
  class new_type
      : impl::new_type_move_assignment<BaseType, TagType>
      , public impl::new_type_iterator_types<BaseType, DerivationClause(nt::Iterable)>
  {
    static_assert(!std::is_reference_v<BaseType>, "The base type must not be a reference type");
    static_assert(!std::is_void_v<std::remove_cv_t<BaseType>>, "The base type must not be possibly cv-qualified void");

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV, typename CharType, typename StreamTraits>
    auto friend operator>>(std::basic_istream<CharType, StreamTraits> &, new_type<BaseTypeT, TagTypeT, DerivationClauseV> &) noexcept(
        impl::is_nothrow_input_streamable_v<std::basic_istream<CharType, StreamTraits>, BaseTypeT>)
        -> std::enable_if_t<DerivationClauseV(nt::Read) && impl::is_input_streamable_v<std::basic_istream<CharType, StreamTraits>, BaseTypeT>,
                            std::basic_istream<CharType, StreamTraits>> &;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend
    operator+=(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & lhs,
               new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & rhs) noexcept(impl::is_nothrow_add_assignable_v<BaseTypeT>)
        -> std::enable_if_t<DerivationClauseV(nt::Arithmetic) && impl::is_add_assignable_v<BaseTypeT>,
                            new_type<BaseTypeT, TagTypeT, DerivationClauseV> &>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend
    operator-=(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & lhs,
               new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & rhs) noexcept(impl::is_nothrow_subtract_assignable_v<BaseTypeT>)
        -> std::enable_if_t<DerivationClauseV(nt::Arithmetic) && impl::is_subtract_assignable_v<BaseTypeT>,
                            new_type<BaseTypeT, TagTypeT, DerivationClauseV> &>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend
    operator*=(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & lhs,
               new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & rhs) noexcept(impl::is_nothrow_multiply_assignable_v<BaseTypeT>)
        -> std::enable_if_t<DerivationClauseV(nt::Arithmetic) && impl::is_multiply_assignable_v<BaseTypeT>,
                            new_type<BaseTypeT, TagTypeT, DerivationClauseV> &>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend
    operator/=(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & lhs,
               new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & rhs) noexcept(impl::is_nothrow_divide_assignable_v<BaseTypeT>)
        -> std::enable_if_t<DerivationClauseV(nt::Arithmetic) && impl::is_divide_assignable_v<BaseTypeT>,
                            new_type<BaseTypeT, TagTypeT, DerivationClauseV> &>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend begin(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & obj)
        -> std::enable_if_t<DerivationClauseV(nt::Iterable) && impl::has_free_begin_v<BaseTypeT>,
                            typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::iterator>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend begin(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj)
        -> std::enable_if_t<DerivationClauseV(nt::Iterable) && impl::has_free_begin_v<BaseTypeT const>,
                            typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_iterator>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend cbegin(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj)
        -> std::enable_if_t<DerivationClauseV(nt::Iterable) && impl::has_free_cbegin_v<BaseTypeT const>,
                            typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_iterator>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend rbegin(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & obj)
        -> std::enable_if_t<DerivationClauseV(nt::Iterable) && impl::has_free_rbegin_v<BaseTypeT>,
                            typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::reverse_iterator>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend rbegin(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj)
        -> std::enable_if_t<DerivationClauseV(nt::Iterable) && impl::has_free_rbegin_v<BaseTypeT const>,
                            typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_reverse_iterator>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend crbegin(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj)
        -> std::enable_if_t<DerivationClauseV(nt::Iterable) && impl::has_free_crbegin_v<BaseTypeT const>,
                            typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_reverse_iterator>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend end(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & obj)
        -> std::enable_if_t<DerivationClauseV(nt::Iterable) && impl::has_free_end_v<BaseTypeT>,
                            typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::iterator>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend end(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj)
        -> std::enable_if_t<DerivationClauseV(nt::Iterable) && impl::has_free_end_v<BaseTypeT const>,
                            typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_iterator>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend cend(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj)
        -> std::enable_if_t<DerivationClauseV(nt::Iterable) && impl::has_free_cend_v<BaseTypeT const>,
                            typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_iterator>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend rend(new_type<BaseTypeT, TagTypeT, DerivationClauseV> & obj)
        -> std::enable_if_t<DerivationClauseV(nt::Iterable) && impl::has_free_rend_v<BaseTypeT>,
                            typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::reverse_iterator>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend rend(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj)
        -> std::enable_if_t<DerivationClauseV(nt::Iterable) && impl::has_free_rend_v<BaseTypeT const>,
                            typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_reverse_iterator>;

    template<typename BaseTypeT, typename TagTypeT, auto DerivationClauseV>
    auto constexpr friend crend(new_type<BaseTypeT, TagTypeT, DerivationClauseV> const & obj)
        -> std::enable_if_t<DerivationClauseV(nt::Iterable) && impl::has_free_crend_v<BaseTypeT const>,
                            typename new_type<BaseTypeT, TagTypeT, DerivationClauseV>::const_reverse_iterator>;

    using super = impl::new_type_move_assignment<BaseType, TagType>;

  public:
    using base_type = BaseType;
    using tag_type = TagType;
    using derivation_clause_type = decltype(DerivationClause);

    auto constexpr static derivation_clause = DerivationClause;

    using super::super;

    constexpr new_type() noexcept(std::is_nothrow_default_constructible_v<BaseType>) = default;
    constexpr new_type(new_type const &) noexcept(std::is_nothrow_copy_constructible_v<BaseType>) = default;
    constexpr new_type(new_type &&) noexcept(std::is_nothrow_move_constructible_v<BaseType>) = default;

    auto constexpr operator=(new_type const &) noexcept(std::is_nothrow_copy_assignable_v<BaseType>) -> new_type & = default;
    auto constexpr operator=(new_type &&) noexcept(std::is_nothrow_move_assignable_v<BaseType>) -> new_type & = default;

    auto constexpr decay() const noexcept(std::is_nothrow_copy_constructible_v<BaseType>) -> BaseType
    {
      return this->m_value;
    }

    template<typename NewType = new_type, std::enable_if_t<NewType::derivation_clause(nt::ImplicitConversion)> * = nullptr>
    constexpr operator base_type() const noexcept(std::is_nothrow_copy_constructible_v<base_type>)
    {
      return decay();
    }

    template<typename NewType = new_type, std::enable_if_t<!NewType::derivation_clause(nt::ImplicitConversion)> * = nullptr>
    explicit constexpr operator base_type() const noexcept(std::is_nothrow_copy_constructible_v<base_type>)
    {
      return decay();
    }

    template<typename NewType = new_type>
    auto constexpr operator-> () noexcept -> std::enable_if_t<NewType::derivation_clause(nt::Indirection), BaseType *>
    {
      return std::addressof(this->m_value);
    }

    template<typename NewType = new_type>
    auto constexpr operator-> () const noexcept -> std::enable_if_t<NewType::derivation_clause(nt::Indirection), BaseType const *>
    {
      return std::addressof(this->m_value);
    }

    template<typename NewType = new_type, std::enable_if_t<NewType::derivation_clause(nt::Iterable)> * = nullptr>
    auto constexpr begin()
        -> std::enable_if_t<NewType::derivation_clause(nt::Iterable) && impl::has_member_begin_v<BaseType>, typename NewType::iterator>
    {
      return this->m_value.begin();
    }

    template<typename NewType = new_type>
    auto constexpr begin() const -> std::enable_if_t<NewType::derivation_clause(nt::Iterable) && impl::has_member_begin_v<BaseType const>,
                                                     typename NewType::const_iterator>
    {
      return this->m_value.begin();
    }

    template<typename NewType = new_type>
    auto constexpr cbegin() const -> std::enable_if_t<NewType::derivation_clause(nt::Iterable) && impl::has_member_cbegin_v<BaseType const>,
                                                      typename NewType::const_iterator>
    {
      return this->m_value.cbegin();
    }

    template<typename NewType = new_type, std::enable_if_t<NewType::derivation_clause(nt::Iterable)> * = nullptr>
    auto constexpr rbegin()
        -> std::enable_if_t<NewType::derivation_clause(nt::Iterable) && impl::has_member_rbegin_v<BaseType>, typename NewType::reverse_iterator>
    {
      return this->m_value.rbegin();
    }

    template<typename NewType = new_type>
    auto constexpr rbegin() const -> std::enable_if_t<NewType::derivation_clause(nt::Iterable) && impl::has_member_rbegin_v<BaseType const>,
                                                      typename NewType::const_reverse_iterator>
    {
      return this->m_value.rbegin();
    }

    template<typename NewType = new_type>
    auto constexpr crbegin() const -> std::enable_if_t<NewType::derivation_clause(nt::Iterable) && impl::has_member_crbegin_v<BaseType const>,
                                                       typename NewType::const_reverse_iterator>
    {
      return this->m_value.crbegin();
    }

    template<typename NewType = new_type, std::enable_if_t<NewType::derivation_clause(nt::Iterable)> * = nullptr>
    auto constexpr end()
        -> std::enable_if_t<NewType::derivation_clause(nt::Iterable) && impl::has_member_end_v<BaseType>, typename NewType::iterator>
    {
      return this->m_value.end();
    }

    template<typename NewType = new_type>
    auto constexpr end() const -> std::enable_if_t<NewType::derivation_clause(nt::Iterable) && impl::has_member_end_v<BaseType const>,
                                                   typename NewType::const_iterator>
    {
      return this->m_value.end();
    }

    template<typename NewType = new_type>
    auto constexpr cend() const -> std::enable_if_t<NewType::derivation_clause(nt::Iterable) && impl::has_member_cend_v<BaseType const>,
                                                    typename NewType::const_iterator>
    {
      return this->m_value.cend();
    }

    template<typename NewType = new_type, std::enable_if_t<NewType::derivation_clause(nt::Iterable)> * = nullptr>
    auto constexpr rend()
        -> std::enable_if_t<NewType::derivation_clause(nt::Iterable) && impl::has_member_rend_v<BaseType>, typename NewType::reverse_iterator>
    {
      return this->m_value.rend();
    }

    template<typename NewType = new_type>
    auto constexpr rend() const -> std::enable_if_t<NewType::derivation_clause(nt::Iterable) && impl::has_member_rend_v<BaseType const>,
                                                    typename NewType::const_reverse_iterator>
    {
      return this->m_value.rend();
    }

    template<typename NewType = new_type>
    auto constexpr crend() const -> std::enable_if_t<NewType::derivation_clause(nt::Iterable) && impl::has_member_crend_v<BaseType const>,
                                                     typename NewType::const_reverse_iterator>
    {
      return this->m_value.crend();
    }
  };

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator==(new_type<BaseType, TagType, DerivationClause> const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_equality_comparable_v<BaseType>)
      -> std::enable_if_t<impl::is_equality_comparable_v<BaseType>, bool>
  {
    return lhs.decay() == rhs.decay();
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator==(new_type<BaseType, TagType, DerivationClause> const & lhs,
                            BaseType const & rhs) noexcept(impl::is_nothrow_equality_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::EqBase) && impl::is_equality_comparable_v<BaseType>, bool>
  {
    return lhs.decay() == rhs;
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator==(BaseType const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_equality_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::EqBase) && impl::is_equality_comparable_v<BaseType>, bool>
  {
    return lhs == rhs.decay();
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator!=(new_type<BaseType, TagType, DerivationClause> const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_inequality_comparable_v<BaseType>)
      -> std::enable_if_t<impl::is_inequality_comparable_v<BaseType>, bool>
  {
    return lhs.decay() != rhs.decay();
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator!=(new_type<BaseType, TagType, DerivationClause> const & lhs,
                            BaseType const & rhs) noexcept(impl::is_nothrow_inequality_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::EqBase) && impl::is_inequality_comparable_v<BaseType>, bool>
  {
    return lhs.decay() != rhs;
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator!=(BaseType const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_inequality_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::EqBase) && impl::is_inequality_comparable_v<BaseType>, bool>
  {
    return lhs != rhs.decay();
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator<(new_type<BaseType, TagType, DerivationClause> const & lhs,
            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_less_than_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Relational) && impl::is_less_than_comparable_v<BaseType>, bool>
  {
    return lhs.decay() < rhs.decay();
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator>(new_type<BaseType, TagType, DerivationClause> const & lhs,
            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_greater_than_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Relational) && impl::is_greater_than_comparable_v<BaseType>, bool>
  {
    return lhs.decay() > rhs.decay();
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator<=(new_type<BaseType, TagType, DerivationClause> const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_less_than_equal_to_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Relational) && impl::is_less_than_equal_to_comparable_v<BaseType>, bool>
  {
    return lhs.decay() <= rhs.decay();
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator>=(new_type<BaseType, TagType, DerivationClause> const & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_greater_than_equal_to_comparable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Relational) && impl::is_greater_than_equal_to_comparable_v<BaseType>, bool>
  {
    return lhs.decay() >= rhs.decay();
  }

  template<typename BaseType, typename TagType, auto DerivationClause, typename CharType, typename StreamTraits>
  auto operator<<(std::basic_ostream<CharType, StreamTraits> & output, new_type<BaseType, TagType, DerivationClause> const & source) noexcept(
      impl::is_nothrow_output_streamable_v<std::basic_ostream<CharType, StreamTraits>, BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Show) && impl::is_output_streamable_v<std::basic_ostream<CharType, StreamTraits>, BaseType>,
                          std::basic_ostream<CharType, StreamTraits>> &
  {
    return output << source.decay();
  }

  template<typename BaseType, typename TagType, auto DerivationClause, typename CharType, typename StreamTraits>
  auto operator>>(std::basic_istream<CharType, StreamTraits> & input, new_type<BaseType, TagType, DerivationClause> & target) noexcept(
      impl::is_nothrow_input_streamable_v<std::basic_istream<CharType, StreamTraits>, BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Read) && impl::is_input_streamable_v<std::basic_istream<CharType, StreamTraits>, BaseType>,
                          std::basic_istream<CharType, StreamTraits>> &
  {
    return input >> target.m_value;
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator+(new_type<BaseType, TagType, DerivationClause> const & lhs, new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(
      impl::is_nothrow_addable_v<BaseType> && std::is_nothrow_copy_constructible_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Arithmetic) && impl::is_addable_v<BaseType>, new_type<BaseType, TagType, DerivationClause>>
  {
    return {lhs.decay() + rhs.decay()};
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator+=(new_type<BaseType, TagType, DerivationClause> & lhs,
                            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_add_assignable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Arithmetic) && impl::is_add_assignable_v<BaseType>,
                          new_type<BaseType, TagType, DerivationClause> &>
  {
    lhs.m_value += rhs.m_value;
    return lhs;
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator-(new_type<BaseType, TagType, DerivationClause> const & lhs, new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(
      impl::is_nothrow_subtractable_v<BaseType> && std::is_nothrow_copy_constructible_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Arithmetic) && impl::is_subtractable_v<BaseType>, new_type<BaseType, TagType, DerivationClause>>
  {
    return {lhs.decay() - rhs.decay()};
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator-=(new_type<BaseType, TagType, DerivationClause> & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_subtract_assignable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Arithmetic) && impl::is_subtract_assignable_v<BaseType>,
                          new_type<BaseType, TagType, DerivationClause> &>
  {
    lhs.m_value -= rhs.m_value;
    return lhs;
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator*(new_type<BaseType, TagType, DerivationClause> const & lhs, new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(
      impl::is_nothrow_multipliable_v<BaseType> && std::is_nothrow_copy_constructible_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Arithmetic) && impl::is_multipliable_v<BaseType>, new_type<BaseType, TagType, DerivationClause>>
  {
    return {lhs.decay() * rhs.decay()};
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator*=(new_type<BaseType, TagType, DerivationClause> & lhs,
             new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_multiply_assignable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Arithmetic) && impl::is_multiply_assignable_v<BaseType>,
                          new_type<BaseType, TagType, DerivationClause> &>
  {
    lhs.m_value *= rhs.m_value;
    return lhs;
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr
  operator/(new_type<BaseType, TagType, DerivationClause> const & lhs, new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(
      impl::is_nothrow_dividable_v<BaseType> && std::is_nothrow_copy_constructible_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Arithmetic) && impl::is_dividable_v<BaseType>, new_type<BaseType, TagType, DerivationClause>>
  {
    return {lhs.decay() / rhs.decay()};
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr operator/=(new_type<BaseType, TagType, DerivationClause> & lhs,
                            new_type<BaseType, TagType, DerivationClause> const & rhs) noexcept(impl::is_nothrow_divide_assignable_v<BaseType>)
      -> std::enable_if_t<DerivationClause(nt::Arithmetic) && impl::is_divide_assignable_v<BaseType>,
                          new_type<BaseType, TagType, DerivationClause> &>
  {
    lhs.m_value /= rhs.m_value;
    return lhs;
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr begin(new_type<BaseType, TagType, DerivationClause> & obj)
      -> std::enable_if_t<DerivationClause(nt::Iterable) && impl::has_free_begin_v<BaseType>,
                          typename new_type<BaseType, TagType, DerivationClause>::iterator>
  {
    return begin(obj.m_value);
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr begin(new_type<BaseType, TagType, DerivationClause> const & obj)
      -> std::enable_if_t<DerivationClause(nt::Iterable) && impl::has_free_begin_v<BaseType const>,
                          typename new_type<BaseType, TagType, DerivationClause>::const_iterator>
  {
    return begin(obj.m_value);
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr cbegin(new_type<BaseType, TagType, DerivationClause> const & obj)
      -> std::enable_if_t<DerivationClause(nt::Iterable) && impl::has_free_cbegin_v<BaseType const>,
                          typename new_type<BaseType, TagType, DerivationClause>::const_iterator>
  {
    return cbegin(obj.m_value);
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr rbegin(new_type<BaseType, TagType, DerivationClause> & obj)
      -> std::enable_if_t<DerivationClause(nt::Iterable) && impl::has_free_rbegin_v<BaseType>,
                          typename new_type<BaseType, TagType, DerivationClause>::reverse_iterator>
  {
    return rbegin(obj.m_value);
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr rbegin(new_type<BaseType, TagType, DerivationClause> const & obj)
      -> std::enable_if_t<DerivationClause(nt::Iterable) && impl::has_free_rbegin_v<BaseType const>,
                          typename new_type<BaseType, TagType, DerivationClause>::const_reverse_iterator>
  {
    return rbegin(obj.m_value);
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr crbegin(new_type<BaseType, TagType, DerivationClause> const & obj)
      -> std::enable_if_t<DerivationClause(nt::Iterable) && impl::has_free_crbegin_v<BaseType const>,
                          typename new_type<BaseType, TagType, DerivationClause>::const_reverse_iterator>
  {
    return crbegin(obj.m_value);
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr end(new_type<BaseType, TagType, DerivationClause> & obj)
      -> std::enable_if_t<DerivationClause(nt::Iterable) && impl::has_free_end_v<BaseType>,
                          typename new_type<BaseType, TagType, DerivationClause>::iterator>
  {
    return end(obj.m_value);
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr end(new_type<BaseType, TagType, DerivationClause> const & obj)
      -> std::enable_if_t<DerivationClause(nt::Iterable) && impl::has_free_end_v<BaseType const>,
                          typename new_type<BaseType, TagType, DerivationClause>::const_iterator>
  {
    return end(obj.m_value);
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr cend(new_type<BaseType, TagType, DerivationClause> const & obj)
      -> std::enable_if_t<DerivationClause(nt::Iterable) && impl::has_free_cend_v<BaseType const>,
                          typename new_type<BaseType, TagType, DerivationClause>::const_iterator>
  {
    return cend(obj.m_value);
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr rend(new_type<BaseType, TagType, DerivationClause> & obj)
      -> std::enable_if_t<DerivationClause(nt::Iterable) && impl::has_free_rend_v<BaseType>,
                          typename new_type<BaseType, TagType, DerivationClause>::reverse_iterator>
  {
    return rend(obj.m_value);
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr rend(new_type<BaseType, TagType, DerivationClause> const & obj)
      -> std::enable_if_t<DerivationClause(nt::Iterable) && impl::has_free_rend_v<BaseType const>,
                          typename new_type<BaseType, TagType, DerivationClause>::const_reverse_iterator>
  {
    return rend(obj.m_value);
  }

  template<typename BaseType, typename TagType, auto DerivationClause>
  auto constexpr crend(new_type<BaseType, TagType, DerivationClause> const & obj)
      -> std::enable_if_t<DerivationClause(nt::Iterable) && impl::has_free_crend_v<BaseType const>,
                          typename new_type<BaseType, TagType, DerivationClause>::const_reverse_iterator>
  {
    return crend(obj.m_value);
  }

}  // namespace nt

namespace std
{
  template<typename BaseType, typename TagType, auto DerivationClause>
  struct hash<nt::new_type<BaseType, TagType, DerivationClause>>
  {
    template<typename BaseTypeT = BaseType, auto DerivationClauseV = DerivationClause>
    auto constexpr operator()(nt::new_type<BaseType, TagType, DerivationClause> const & object,
                              std::enable_if_t<DerivationClauseV(nt::Hash) && nt::impl::is_hashable_v<BaseTypeT>> * = nullptr) const
        -> std::size_t
    {
      return std::hash<BaseType>{}(object.decay());
    }
  };
}  // namespace std

#endif
