from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.build import check_min_cppstd


class NewtypeConan(ConanFile):
    name = "newtype"
    version = "2.0.0"
    license = "BSD-3-Clause"
    description = "A library of types and functions to create strong type aliases"
    url = "https://github.com/fmorgner/newtype"

    settings = ("os", "arch", "compiler", "build_type")

    scm = {
        "type": "git",
        "url": "auto",
        "revision": "auto"
    }

    options = {
        "enable_docs": [False, True],
    }

    default_options = {
        "enable_docs": False,
    }

    generators = [
        "CMakeDeps"
    ]

    exports_sources = [
        "source/*",
        "test_package/*",
        "LICENSE",
    ]

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

    def build_requirements(self):
        self.tool_requires("cmake/[~3.25]")
        self.tool_requires("ninja/[~1.11]")
        self.test_requires("catch2/[~3.3]")

    def generate(self):
        toolchain = CMakeToolchain(self)
        toolchain.variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = True
        toolchain.variables["PROJECT_VERSION"] = self.version
        toolchain.variables["PROJECT_DESCRIPTION"] = self.description
        toolchain.generate()

    def layout(self):
        cmake_layout(self, generator="Ninja Multi-Config", src_folder="source")

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_id(self):
        self.info.clear()

    def package_info(self):
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []

    def validate(self):
        check_min_cppstd(self, 20)
