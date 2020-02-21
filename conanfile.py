import re

from conans import ConanFile, CMake
from conans.tools import load


def read_project_property(property):
    try:
        cmake_lists = load("CMakeLists.txt")
        value = re.search(r"project\(.*{} \"(.*?)\"".format(property), cmake_lists, re.S).group(1)
        return value.strip()
    except:
        return None


class NewtypeConan(ConanFile):
    name = "newtype"
    scm = {
        "type": "git",
        "url": "https://github.com/fmorgner/newtype.git",
        "revision": "auto",
    }
    settings = ("compiler",)
    version = read_project_property("VERSION")
    license = "BSD-3-Clause"
    url = "https://github.com/fmorgner/newtype"
    description = read_project_property("DESCRIPTION")
    generators = "cmake"
    build_requires = (
        "CUTE/2.2.6@fmorgner/stable",
        "lyra/1.2.0"
    )
    
    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_TESTING"] = True
        cmake.definitions["RUN_TESTS_AFTER_BUILD"] = True
        cmake.configure()
        return cmake

    def configure(self):
        del self.settings.compiler.libcxx

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
        cmake.test()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        if self.settings.compiler in ["gcc"]:
            self.cpp_info.cxxflags.append("-std=c++2a")