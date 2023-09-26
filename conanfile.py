#!/usr/bin/env python
# -*- coding: utf-8 -*-

import json, os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain
from conan.tools.files import copy
from conan.tools.build import cross_building
from conan.tools.env import VirtualBuildEnv

required_conan_version = ">=2.0"


class LibonvifConan(ConanFile):
    jsonInfo = json.load(open("info.json", 'r'))
    # ---Package reference---
    name = jsonInfo["projectName"]
    version = "%u.%u.%u" % (jsonInfo["version"]["major"], jsonInfo["version"]["minor"], jsonInfo["version"]["patch"])
    user = jsonInfo["domain"]
    channel = "%s" % ("snapshot" if jsonInfo["version"]["snapshot"] else "stable")
    # ---Metadata---
    description = jsonInfo["projectDescription"]
    license = jsonInfo["license"]
    author = jsonInfo["vendor"]
    topics = jsonInfo["topics"]
    homepage = jsonInfo["homepage"]
    url = jsonInfo["repository"]
    # ---Requirements---
    requires = ["qt/[~6.5]@%s/stable" % user]
    tool_requires = ["cmake/3.21.7", "ninja/1.11.1", "qt_app_base/[~1]@%s/snapshot" % user]
    # ---Sources---
    exports = ["info.json", "LICENSE"]
    exports_sources = ["info.json", "src/*", "doc/*", "CMake/*", "CMakeLists.txt"]
    # ---Binary model---
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "openssl": [True, False]}
    default_options = {"shared": True,
                       "openssl": False,
                       "qt/*:qtbase": True}
    # ---Build---
    generators = []
    # ---Folders---
    no_copy_source = False

    def requirements(self):
        if self.options.openssl:
            self.requires("openssl/1.1.1l@tereius/stable")
            self.options["openssl"].shared = True

    def generate(self):
        ms = VirtualBuildEnv(self)
        tc = CMakeToolchain(self, generator="Ninja")
        tc.variables["ENABLE_SSL"] = self.options.openssl
        tc.generate()
        ms.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.builddirs = ['cmake']
        self.cpp_info.defines = ['WITH_SELF_PIPE', 'WITH_DOM']
        if self.options.openssl:
            self.cpp_info.defines = ['WITH_OPENSSL']
