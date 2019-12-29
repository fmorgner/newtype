.. cpp:namespace-push:: nt

#############
Documentation
#############

The ``newtype`` library provides types and functions to facilitate the creation of strong type aliases.

Example Usage
#############

:ref:`new-type-usage-basic` below demonstrates the basic usage of :cpp:class:`new_type`.
In it, :cpp:class:`new_type` is used to create thre new strong aliases :literal:`Width`, :literal:`Height`, and :literal:`Area` that all alias :literal:`unsigned int`.

.. literalinclude:: ../../examples/src/basic_usage.cpp
   :language: c++
   :linenos:
   :name: new-type-usage-basic 
   :caption: Basic usage of :cpp:class:`new_type`

However, using :cpp:class:`new_type` in this fashion seem quite cumbersome.
Starting from the bottom, :literal:`unsigned int` can normally be shifted on to any :cpp:class:`std::basic_ostream`, like :cpp:var:`std::cout` in this example.
Since printing values, among other things, is a common scenario, ``newtype`` provides facilities to support automatic derivation of supporting functions.

.. literalinclude:: ../../examples/src/basic_usage_with_show.cpp
   :language: c++
   :linenos:
   :name: new-type-usage-basic-show
   :caption: Improved usability using the :cpp:var:`Show` derivation tag

:ref:`new-type-usage-basic-show` demonstrates how the function template :cpp:func:`deriving` can be used to enable automatic derivation of the stream output operator for :literal:`Area`.
Similarly, it is possible to derive the stream input operators of :literal:`Width` and :literal:`Height`, as shown in :ref:`new-type-usage-basic-read` below.

.. literalinclude:: ../../examples/src/basic_usage_with_read.cpp
   :language: c++
   :linenos:
   :name: new-type-usage-basic-read
   :caption: Deriving input operations using the :cpp:var:`Read` derivation tag

API
###

This section of the documentation describes the public API of the *new_type*.
It provides detailed descriptions of the types and functions designed to be used by applications.
Additionally, this section provides usage examples that demonstrate the use and properties of the public API.

Header :literal:`<newtype/new_type.hpp>`
========================================

This header contains the definitions of the class template :cpp:class:`new_type` as well as a set of associated namespace-level functions.

Class template :cpp:class:`new_type`
------------------------------------

The class template :cpp:class:`new_type` is designed to allow the creation of new types based on existing types.
Similarly to the Haskell newtype, this class template creates a new type that is layout equivalent to the underlying type.

.. cpp:class:: template<typename BaseType, typename TagType, auto DerivationClause = deriving()> \
               new_type

   **Member Type Aliases**

   .. cpp:type:: base_type = BaseType

   .. cpp:type:: tag_type = TagType

   .. cpp:type:: derivation_clause_type = decltype(DerivationClause)

   **Static Data Members**

   .. cpp:var:: derivation_clause_type constexpr static derivation_clause = DerivationClause

   **Constructors**

   .. cpp:function:: constexpr new_type()

      **noexcept specification:** This constructor shall be noexcept iff. this :cpp:class:`new_type`'s :cpp:type:`base_type` is nothrow default-construtible.

      **default definition:** This constructor shall be defined as :literal:`= default` iff. this :cpp:class:`new_type`'s :cpp:type:`base_type` is default-construtible.
      Otherwise, this constructor shall be explicitely deleted.

   .. cpp:function:: constexpr new_type(new_type const &)

      **noexcept specification:**: This constructor shall be noexcept iff. this :cpp:class:`new_type`'s :cpp:type:`base_type` is nothrow copy-construtible.

      **default definition:** This constructor shall be defined as :literal:`= default` iff. this :cpp:class:`new_type`'s :cpp:type:`base_type` is copy-construtible.
      Otherwise, this constructor shall be explicitely deleted.

   .. cpp:function:: constexpr new_type(new_type &&)

      **noexcept specification:**: This constructor shall be noexcept iff. this :cpp:class:`new_type`'s :cpp:type:`base_type` is nothrow move-construtible.

      **default definition:** This constructor shall be defined as :literal:`= default` iff. this :cpp:class:`new_type`'s :cpp:type:`base_type` is move-construtible.
      Otherwise, this constructor shall be explicitely deleted.

   .. cpp:function:: constexpr new_type(BaseType &)

      **noexcept specification:** This constructor shall be noexcept iff. this :cpp:class:`new_type`'s :cpp:type:`base_type` is nothrow copy-construtible.

      **enablement:** This constructor shall be defined iff. this :cpp:class:`new_type`'s :cpp:type:`base_type` is copy-construtible.
      Otherwise, this constructor shall be explicitely deleted.

   .. cpp:function:: constexpr new_type(BaseType &&)

      **noexcept specification:** This constructor shall be noexcept iff. this :cpp:class:`new_type`'s :cpp:type:`base_type` is nothrow move-construtible.

      **enablement:** This constructor shall be defined iff. this :cpp:class:`new_type`'s :cpp:type:`base_type` is move-construtible.
      Otherwise, this constructor shall be explicitely deleted.

   **Assignment Operators**

   .. cpp:function:: constexpr new_type & operator=(new_type const &)

      **noexcept specification:** This assignment operator shall be noexcept iff. this :cpp:class:`new_type`'s :cpp:type:`base_type` is nothrow copy-assignable.

      **default definition:** This assignment operator shall be defined as :literal:`= default` iff. this :cpp:class:`new_type`'s :cpp:type:`base_type` is copy-assignable.
      Otherwise, this assignment operator shall be explicitely deleted.

   .. cpp:function:: constexpr new_type & operator=(new_type &&)

      **noexcept specification:** This assignment operator shall be noexcept iff. this :cpp:class:`new_type`'s :cpp:type:`base_type` is nothrow move-assignable.

      **default definition:** This assignment operator shall be defined as :literal:`= default` iff. this :cpp:class:`new_type`'s :cpp:type:`base_type` is move-assignable.
      Otherwise, this assignment operator shall be explicitely deleted.

   **Accessors**

   .. cpp:function:: constexpr BaseType decay() const

      **noexcept specification:** This member function shall be noexcept iff. this :cpp:class:`new_type`'s :cpp:type:`base_type` is nothrow copy-assignable.

   .. cpp:function:: constexpr operator BaseType() const

      **noexcept specification:** This conversion operator shall be noexcept iff. this :cpp:class:`new_type`'s :cpp:type:`base_type` is nothrow copy-assignable.

      **explicit specification:** This conversion operator shall be explicit unless this :cpp:class:`new_type`'s :cpp:var:`derivation_clause` contains :cpp:var:`ImplicitConversion`.

   **Member Access Trough Pointer**

   .. cpp:function:: constexpr BaseType operator->() noexcept

      **enablement:** This operator shall be available iff. this :cpp:class:`new_type`'s :cpp:var:`derivation_clause` contains :cpp:var:`Indirection`

   .. cpp:function:: constexpr BaseType const * operator->() const noexcept

      **enablement:** This operator shall be available iff. this :cpp:class:`new_type`'s :cpp:var:`derivation_clause` contains :cpp:var:`Indirection`

Namespace-level functions and function templates
------------------------------------------------

The functions and functions templates described in this section provide additional functionality for the class template :cpp:class:`new_type` that is not part of the class itself.

Equality Comparison Operators
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. cpp:function:: template<typename BaseType, \
                  typename TagType, \
                  auto DerivationClause> \
                  constexpr bool operator==(new_type<BaseType, TagType, DerivationClause> const &,\
                                            new_type<BaseType, TagType, DerivationClause> const &)

   **noexcept specification:** This conversion operator shall be noexcept iff. :cpp:type:`new_type<BaseType, TagType, DerivationClause>::base_type` is nothrow equals-comparable.

   **enablement:** This operator shall be available iff. :cpp:type:`new_type<BaseType, TagType, DerivationClause>::base_type` supports comparison using the operator :literal:`==`

.. cpp:function:: template<typename BaseType, \
                  typename TagType, \
                  auto DerivationClause> \
                  constexpr bool operator!=(new_type<BaseType, TagType, DerivationClause> const &,\
                                            new_type<BaseType, TagType, DerivationClause> const &)

   **noexcept specification:** This conversion operator shall be noexcept iff. :cpp:type:`new_type<BaseType, TagType, DerivationClause>::base_type` is nothrow not-equals-comparable.

   **enablement:** This operator shall be available iff. this :cpp:type:`new_type<BaseType, TagType, DerivationClause>::base_type` supports comparison using the operator :literal:`!=`

Relational Comparison Operators
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. cpp:function:: template<typename BaseType, \
                  typename TagType, \
                  auto DerivationClause> \
                  constexpr bool operator<(new_type<BaseType, TagType, DerivationClause> const &, \
                                           new_type<BaseType, TagType, DerivationClause> const &)

.. cpp:function:: template<typename BaseType, \
                  typename TagType, \
                  auto DerivationClause> \
                  constexpr bool operator>(new_type<BaseType, TagType, DerivationClause> const &, \
                                           new_type<BaseType, TagType, DerivationClause> const &)

.. cpp:function:: template<typename BaseType, \
                  typename TagType, \
                  auto DerivationClause> \
                  constexpr bool operator<=(new_type<BaseType, TagType, DerivationClause> const &, \
                                            new_type<BaseType, TagType, DerivationClause> const &)

.. cpp:function:: template<typename BaseType, \
                  typename TagType, \
                  auto DerivationClause> \
                  constexpr bool operator>=(new_type<BaseType, TagType, DerivationClause> const &, \
                                            new_type<BaseType, TagType, DerivationClause> const &)

Stream I/O Operators
~~~~~~~~~~~~~~~~~~~~

.. cpp:function:: template<typename BaseType, \
                  typename TagType, \
                  auto DerivationClause, \
                  typename CharType, \
                  typename StreamTraits> \
                  std::basic_ostream<CharType, StreamTraits> & operator<<(std::basic_ostream<CharType, StreamTraits> &, \
                                                                         new_type<BaseType, TagType, DerivationClause> const &)

.. cpp:function:: template<typename BaseType, \
                  typename TagType, \
                  auto DerivationClause, \
                  typename CharType, \
                  typename StreamTraits> \
                  std::basic_istream<CharType, StreamTraits> & operator>>(std::basic_istream<CharType, StreamTraits> &, \
                                                                         new_type<BaseType, TagType, DerivationClause> &)

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
