=======
newtype
=======

The `newtype` library provides types and functions to facilitate the creation of strong type aliases.

|c++20| |license| |docs| |travis| |btc|

Usage
=====

The code block below demonstrates the basic usage and features of `newtype`. For a more details description of the library, as well as a full API documentation, please `read the docs <https://newtype.rtfd.io>`_ (also available as a `PDF file <https://readthedocs.org/projects/newtype/downloads/pdf/latest/>`_).

.. code-block:: c++
   
   #include <newtype/derivable.hpp>
   #include <newtype/deriving.hpp>
   #include <newtype/new_type.hpp>
   
   #include <iostream>
   
   using Width = nt::new_type<unsigned int, struct width_tag, deriving(nt::Read)>;
   using Height = nt::new_type<unsigned int, struct height_tag, deriving(nt::Read)>;
   using Area = nt::new_type<unsigned int, struct area_tag, deriving(nt::Show)>;
   
   struct Rectangle
   {
     constexpr Rectangle(Width w, Height h)
         : width{w}
         , height{h}
     {
     }
   
     auto constexpr area() const noexcept -> Area
     {
       return {width.decay() * height.decay()};
     }
   
   private:
     Width width;
     Height height;
   };
   
   int main()
   {
     auto width = Width{};
     auto height = Height{};
   
     std::cin >> width >> height;
   
     auto rect = Rectangle{width, height};
   
     std::cout << rect.area() << '\n';
   }

Requirements
============

This library uses features of C++20 and thus requires a modern compiler.
All development was done on GCC 9.2.
This is a header-only library, and thus no compilation is need if you want to use it in your project.
If you want to run the sanity-checks/unit-test, you will need at least CMake 3.9.0.
If you want to build to documentation, you will need either a local installation of sphinx, or alternatively `pipenv`.
A `Pipfile` is provided in the directory `docs` within the source root.

.. |c++20| image:: https://img.shields.io/badge/c%2B%2B-20-orange
   :alt: C++20
   :target: https://en.wikipedia.org/wiki/C%2B%2B20

.. |license| image:: https://img.shields.io/github/license/fmorgner/newtype
   :alt: GitHub license
   :target: https://github.com/fmorgner/newtype/blob/master/LICENSE
   
.. |docs| image:: https://readthedocs.org/projects/newtype/badge/?version=latest
   :target: https://newtype.readthedocs.io/?badge=latest
   :alt: Documentation Status
   
.. |btc| image:: https://img.shields.io/badge/Support-BTC-yellow
   :alt: Support the project with Bitcoin
   :target: bitcoin:14NhzUxmcXaXwLQQcj5UhDvSuxA6hmGkkg?label=Donation%20to%20%27fmorgner%2Fnew_type%27&message=Thanks%20for%20your%20work%20on%20%27fmorgner%2Fnewtype%27

.. |travis| image:: https://travis-ci.org/fmorgner/newtype.svg?branch=master
   :target: https://travis-ci.org/fmorgner/newtype

.. |conan| image:: https://api.bintray.com/packages/fmorgner/conan-public/newtype%3A_/images/download.svg
   :alt: Download the latest version on conan
   :target: https://bintray.com/fmorgner/conan-public/newtype%3A_/_latestVersion