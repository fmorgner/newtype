import re

from conans import ConanFile, CMake
from conans.tools import load


def get_version():
    try:
        content = load("CMakeLists.txt")
        version = re.search("project\(\"newtype\"\s*VERSION \"(.*)\"", content).group(1)
        return version.strip()
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
    version = get_version()
    license = "BSD-3-Clause"
    url = "https://github.com/fmorgner/newtype"
    description = "A library of types and functions to create strong type aliases"
    generators = "cmake"
    build_requires = (
        "CUTE/2.2.6@fmorgner/stable",
        "lyra/1.2.0"
    )
    
    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_TESTING"] = True
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
        cmake.test()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        if self.settings.compiler in ["gcc", "clang"]:
            self.cpp_info.cxxflags = "-std=c++20"