from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, cmake_layout


class ConanPackage(ConanFile):
    name = "the-modern-cpp-challenge"
    version = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"
    requires = (
        "gtest/1.17.0",
    )
    tool_requires = "cmake/4.1.2"
    generators = "CMakeDeps", "CMakeToolchain"

    def layout(self):
        cmake_layout(self)