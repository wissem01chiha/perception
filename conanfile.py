from conan import ConanFile
from conan.tools.cmake import CMakeToolchain


class CompressorRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def requirements(self):
        self.requires("fmt/10.2.1")
        self.requires("gtest/1.14.0")
        self.requires("cxxopts/3.2.0")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = False
        tc.generate()
        