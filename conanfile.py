import os
import json
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.scm import Git


class ExampleApp(ConanFile):
    name = "example_app"
    url = ""
    author = "Christian Gröling"
    copyright = "MIT"
    description = ""
    homepage = ""
    topics = ()
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = (
        "inc*",
        "src*",
        "CMakeLists.txt",
    )

    options = {
    }
    default_options = {
    }

    def requirements(self):
        # only require fmt, cxxopts, spdlog, gtest if not doxygen_only
        self.requires("fmt/10.2.1")
        self.requires("cxxopts/3.2.0")
        self.requires("spdlog/1.14.1")
 

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build_requirements(self):
        pass

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
