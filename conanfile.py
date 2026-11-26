# *****************************************************************************
# Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/     *
#                                                                             *
# This program and the accompanying materials are made available under the    *
# terms of the Eclipse Public License 2.0 which is available at               *
# http://www.eclipse.org/legal/epl-2.0                                        *
#                                                                             *
# SPDX-License-Identifier: EPL-2.0                                            *
# *****************************************************************************/

import os
import re

from conan import ConanFile
from conan.tools.build import can_run
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.env import VirtualRunEnv
from conan.tools.files import copy, load


class KeyplePluginStubCppLibConan(ConanFile):
    name = "keyple-plugin-stub-cpp-lib"
    license = "EPL-2.0"
    author = "Calypso Networks Association <https://calypsonet.org/>"
    url = "https://github.com/eclipse-keyple/keyple-plugin-stub-cpp-lib"
    homepage = "https://keyple.org/apis/plugin-layer/stub-plugin/"
    description = "C++ implementation of the Eclipse Keyple stub (test) plugin"
    topics = ("keyple", "calypso")

    package_type = "library"
    settings = "os", "arch", "compiler", "build_type"

    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "with_tests": [True, False]
    }

    default_options = {
        "shared": True,
        "fPIC": True,
        "with_tests": False
    }

    exports_sources = [
        "include/*",
        "src/*",
        "CMakeLists.txt",
        "LICENSE",
        "NOTICE.md"
    ]

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def set_version(self):
        cmake_lists = load(self, os.path.join(self.recipe_folder, "CMakeLists.txt"))
        match = re.search(r"VERSION\s+(\d+\.\d+\.\d+)", cmake_lists)
        self.version = match.group(1)

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        self.requires("keyple-common-cpp-api/[~2.0.2]", transitive_headers=True)
        self.requires("keyple-plugin-cpp-api/[~2.3.2]", transitive_headers=True)
        self.requires("keyple-util-cpp-lib/[~2.4.1]", transitive_headers=True)
        # Not referenced by any public header today, but the CMake target
        # intentionally links it (see src/main/CMakeLists.txt), so downstream
        # consumers of Keyple::Plugin::Stub get it too.
        self.requires("keypop-reader-cpp-api/[~2.1.0]")

    def build_requirements(self):
        if self.options.with_tests:
            # 1.12.1 is the last GoogleTest release still compiling as C++11,
            # matching this project's CMAKE_CXX_STANDARD.
            self.test_requires("gtest/1.12.1")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["LIBRARY_TYPE"] = "SHARED" if self.options.shared else "STATIC"
        tc.variables["BUILD_TESTING"] = bool(self.options.with_tests)
        tc.generate()
        CMakeDeps(self).generate()
        if self.options.with_tests:
            VirtualRunEnv(self).generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if self.options.with_tests and can_run(self):
            bin_dir = os.path.join(self.build_folder, "bin")
            if self.settings.os == "Windows":
                bin_dir = os.path.join(bin_dir, str(self.settings.build_type))
            bin_name = "keyplepluginstubcpplib_ut.exe" if self.settings.os == "Windows" else "keyplepluginstubcpplib_ut"
            self.run(os.path.join(bin_dir, bin_name), env="conanrun")

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["keyplepluginstubcpplib"]
        self.cpp_info.set_property("cmake_file_name", "keyple-plugin-stub-cpp-lib")
        self.cpp_info.set_property("cmake_target_name", "Keyple::Plugin::Stub")

    def package_id(self):
        self.info.options.rm_safe("with_tests")
