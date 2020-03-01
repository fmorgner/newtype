import os
from conans import ConanFile, CMake


class NewtypeTestConan(ConanFile):
    settings = None
    requires = "newtype/[~=1.0]@fmorgner/stable"
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        os.chdir("bin")
        self.run(".%stest_package" % os.sep)