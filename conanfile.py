from conans import ConanFile, CMake

class NewtypeConan(ConanFile):
    name = "newtype"
    scm = {
        "type": "git",
        "url": "https://github.com/fmorgner/newtype.git",
        "revision": "auto",
    }
    version = "0.0.1"
    license = "BSD-3-Clause"
    url = "https://github.com/fmorgner/newtype"
    description = "A library of types and functions to create strong type aliases"
    generators = "cmake"
    requires = (
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
