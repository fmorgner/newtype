import os
from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout


class NewtypeTestConan(ConanFile):
    settings = ("os", "arch", "compiler", "build_type")
    requires = "newtype/[~2.0]"
    generators = "CMakeDeps", "CMakeToolchain"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        os.chdir(self.build_folder)
        self.run(".%sTestPackage" % os.sep)

    def layout(self):
        cmake_layout(self, generator="Ninja Multi-Config")
