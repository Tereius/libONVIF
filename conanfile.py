#!/usr/bin/env python
# -*- coding: utf-8 -*-


import json, os
from conans import ConanFile, CMake, tools


class LibonvifConan(ConanFile):
    jsonInfo = json.loads(tools.load("info.json"))
    name = jsonInfo["projectName"]
    version = "%u.%u.%u" % (jsonInfo["version"]["major"], jsonInfo["version"]["minor"], jsonInfo["version"]["patch"])
    license = jsonInfo["license"]
    url = jsonInfo["repository"]
    description = jsonInfo["projectDescription"]
    author = jsonInfo["vendor"]
    homepage = jsonInfo["repository"]
    requires = "Qt/[>=5.4]@tereius/stable"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "openssl": [True, False]}
    default_options = "shared=True", "openssl=False"
    generators = "cmake"
    build_policy = "missing"
    exports = "info.json"
    exports_sources = "*"

    def requirements(self):
        if self.options.openssl:
            self.requires("OpenSSL/1.1.0g@conan/stable")

    def source(self):
        # This small hack might be useful to guarantee proper /MT /MD linkage
        # in MSVC if the packaged project doesn't have variables to set it
        # properly
        tools.replace_in_file("CMakeLists.txt", "### CONAN_BEACON ###",
'''include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()''')

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.install()

    def package_info(self):
        self.cpp_info.builddirs = ['cmake']
