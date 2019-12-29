#############
Documentation
#############

The ``newtype`` library provides types and functions to facilitate the creation of strong type aliases.

API
===

.. cpp:namespace-push:: nt

This section of the documentation describes the public API of the *new_type*.
It provides detailed descriptions of the types and functions designed to be used by applications.
Additionally, this section provides usage examples that demonstrate the use and properties of the public API.

Class template :cpp:class:`new_type`
------------------------------------

.. cpp:class:: template<typename BaseType, typename TagType, auto DerivationClause = deriving()> \
               new_type

   The class template :cpp:class:`new_type` is designed to allow the creation of new types based on existing types.
   Similarly to the Haskell :literal:`newtype`, this class template creates a new type that is layout equivalent to the underlying type.

   :tparam BaseType: The underlying type of the new strong alias
   :tparam TagType: A type uniquely identifying this string alias
   :tparam DerivationClause: A :cpp:class:`derivation_clause` listing all features that shall be automatically derived.


Usage
~~~~~

:ref:`new-type-usage-simple` below demonstrate the most basic usage of :cpp:class:`new_type`.
In it, :cpp:class:`new_type` is used to create a new strong alias :literal:`width` for :literal:`unsigned int`.

.. code-block:: c++
   :linenos:
   :name: new-type-usage-simple
   :caption: Creating a new strong alias for :literal:`unsigned int`

   #include <newtype/new_type.hpp>

   using width = nt::new_type<unsigned int, struct width_tag>;

The class template :cpp:class:`new_type` expects the desired underlying type as its first template argument, :literal:`unsigned int` in the example above.
As a second template argument, :cpp:class:`new_type` expects a tag- or phantom-type.
Neither the underlying type, nor the tag-type are is required to be complete.

The class template :cpp:class:`new_type` takes as a third template argument an instance of :cpp:class:`derivation_clause`.
Derivation clauses make it possible to let the implementation derive certain operations automatically.
For example, the derivation tag :cpp:var:`Arithmetic` enables automatic derivation of arithmetic operations for a given instance of :cpp:class:`new_type` (see :ref:`new-type-usage-deriving-arithmetic` below).

.. code-block:: c++
   :linenos:
   :name: new-type-usage-deriving-arithmetic
   :caption: Automatically deriving arithmetic operations

   #include <newtype/new_type.hpp>

   using width = nt::new_type<unsigned int, struct width_tag, deriving(nt::Arithmetic)>;

Synopsis
~~~~~~~~

.. code-block:: c++

   namespace nt
   {
     template<typename BaseType, typename TagType, auto DerivationClause = deriving()>
     class new_type
     {
     public:

       // Type aliases

       using base_type = BaseType;
       using tag_type = TagType;
       using derivation_clause_type = decltype(DerivationClause);

       // Derivation clause access

       auto constexpr static derivation_clause = DerivationClause;

       // Constructors

       constexpr          new_type() noexcept(std::is_nothrow_default_constructible_v<BaseType>) = /*see below*/;

       constexpr          new_type(new_type const &) noexcept(std::is_nothrow_copy_constructible_v<BaseType>) = /*see below*/;

       constexpr          new_type(new_type      &&) noexcept(std::is_nothrow_move_constructible_v<BaseType>) = /*see below*/;

       constexpr explicit new_type(BaseType const &) noexcept(std::is_nothrow_copy_constructible_v<BaseType>);

       constexpr explicit new_type(BaseType      &&) noexcept(std::is_nothrow_move_constructible_v<BaseType>);

       // Assignment operators

       auto constexpr operator=(new_type const &) noexcept(std::is_nothrow_copy_assignable_v<BaseType>) -> new_type & = /*see below*/

       auto constexpr operator=(new_type &&) noexcept(std::is_nothrow_move_assignable_v<BaseType>) -> new_type & = /*see below*/

       // Accessors

       auto constexpr decay() const noexcept -> BaseType;

       /* EXPLICIT: see below */ constexpr operator base_type() const noexcept(/*see below*/)

       // Indirection operators

       auto constexpr operator->()       noexcept -> std::enable_if_t<DerivationClause(nt::Indirection), BaseType       *>;

       auto constexpr operator->() const noexcept -> std::enable_if_t<DerivationClause(nt::Indirection), BaseType const *>;

     private:
       BaseType m_value; // exposition only
     };

     // Equality comparison operators

     template<typename BaseType,
              typename TagType,
              auto DerivationClause>
     auto constexpr operator==(new_type<BaseType, TagType, DerivationClause> const &,
                               new_type<BaseType, TagType, DerivationClause> const &) noexcept(/*see below*/)
                               -> bool;

     template<typename BaseType,
              typename TagType,
              auto DerivationClause>
     auto constexpr operator!=(new_type<BaseType, TagType, DerivationClause> const &,
                               new_type<BaseType, TagType, DerivationClause> const &) noexcept(/*see below*/)
                               -> bool;
     
     // Relational operators

     template<typename BaseType,
              typename TagType,
              auto DerivationClause>
     auto constexpr operator<(new_type<BaseType, TagType, DerivationClause> const &,
                              new_type<BaseType, TagType, DerivationClause> const &) noexcept(/*see below*/)
                              -> std::enable_if_t<DerivationClause(nt::Relational) && /*see below*/, bool>;

     template<typename BaseType,
              typename TagType,
              auto DerivationClause>
     auto constexpr operator>(new_type<BaseType, TagType, DerivationClause> const &,
                              new_type<BaseType, TagType, DerivationClause> const &) noexcept(/*see below*/)
                              -> std::enable_if_t<DerivationClause(nt::Relational) && /*see below*/, bool>;

     template<typename BaseType,
              typename TagType,
              auto DerivationClause>
     auto constexpr operator<=(new_type<BaseType, TagType, DerivationClause> const &,
                               new_type<BaseType, TagType, DerivationClause> const &) noexcept(/*see below*/)
                               -> std::enable_if_t<DerivationClause(nt::Relational) && /*see below*/, bool>;

     template<typename BaseType,
              typename TagType,
              auto DerivationClause>
     auto constexpr operator>=(new_type<BaseType, TagType, DerivationClause> const &,
                               new_type<BaseType, TagType, DerivationClause> const &) noexcept(/*see below*/)
                               -> std::enable_if_t<DerivationClause(nt::Relational) && /*see below*/, bool>;

    // Stream input/output operators

     template<typename BaseType,
              typename TagType,
              auto DerivationClause,
              typename CharType,
              typename StreamTraits>
     auto operator<<(std::basic_ostream<CharType, StreamTraits> &,
                     new_type<BaseType, TagType, DerivationClause> const &) noexcept(/*see below*/)
                     -> std::enable_if_t<DerivationClause(nt::Show) && /*see below*/, std::basic_ostream<CharType, StreamTraits>> &;

     template<typename BaseType,
              typename TagType,
              auto DerivationClause,
              typename CharType,
              typename StreamTraits>
     auto operator>>(std::basic_istream<CharType, StreamTraits> &,
                     new_type<BaseType, TagType, DerivationClause> &) noexcept(/*see below*/)
                     -> std::enable_if_t<DerivationClause(nt::Read) && /*see below*/, std::basic_istream<CharType, StreamTraits>> &;
   }

Member Type Aliases
~~~~~~~~~~~~~~~~~~~

Static Data Members
~~~~~~~~~~~~~~~~~~~

Special Member Functions
~~~~~~~~~~~~~~~~~~~~~~~~

Free Equality Comparison Operators
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Free Relational Operators
~~~~~~~~~~~~~~~~~~~~~~~~~

Free Stream Input/Ouput Operators
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Class template :cpp:class:`derivation_clause`
---------------------------------------------

.. cpp:class:: template<typename... DerivableTags> \
               derivation_clause

   Derivation clauses are used by :cpp:class:`new_type` to allow users to specify a set of automatically derived support functions.

   :tparam DerivableTags: A (possibly empty) list of derivation tags to mark automatically derived features

Synopsis
~~~~~~~~

.. code-block:: c++

   namespace nt
   {
     template<typename... DerivableTags>
     class derivation_clause
     {
     public:
       // Constructors

       constexpr derivation_clause(derivable<DerivableTags>...) noexcept;
   
       // Evaluation functions

       template<typename DerivableTag>
       auto constexpr operator()(derivable<DerivableTag>) const noexcept -> bool;
   
       template<typename DerivableTag, typename... RemainingDerivableTags>
       auto constexpr operator()(derivable<DerivableTag>, derivable<RemainingDerivableTags>...) const noexcept -> bool;

       // Equality comparison operators

       template<typename... OtherDerivableTags>
       auto constexpr operator==(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool;

       template<typename... OtherDerivableTags>
       auto constexpr operator!=(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool;

       // Relational operators

       template<typename... OtherDerivableTags>
       auto constexpr operator<(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool;
   
       template<typename... OtherDerivableTags>
       auto constexpr operator>(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool;
   
       template<typename... OtherDerivableTags>
       auto constexpr operator<=(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool;

       template<typename... OtherDerivableTags>
       auto constexpr operator>=(derivation_clause<OtherDerivableTags...> other) const noexcept -> bool;
     };
   }

Unit Tests
==========
