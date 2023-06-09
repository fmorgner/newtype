#ifndef NEWTYPE_DERIVABLE_HPP
#define NEWTYPE_DERIVABLE_HPP

namespace nt
{

  template<typename DerivableTag>
  struct derivable final
  {
    using tag_type = DerivableTag;
  };

  inline namespace derivables
  {

    auto constexpr Arithmetic = derivable<struct arithmetic_tag>{};
    auto constexpr EqBase = derivable<struct eq_base_tag>{};
    auto constexpr Hash = derivable<struct hash_tag>{};
    auto constexpr ImplicitConversion = derivable<struct implicit_conversion_tag>{};
    auto constexpr Indirection = derivable<struct indirection_tag>{};
    auto constexpr Iterable = derivable<struct iterable_tag>{};
    auto constexpr Read = derivable<struct read_tag>{};
    auto constexpr Relational = derivable<struct relational_tag>{};
    auto constexpr Show = derivable<struct show_tag>{};

  }  // namespace derivables

}  // namespace nt

#endif