#!/usr/bin/env python
# -*- coding: utf-8 -*-


import json
from conans import ConanFile, CMake, tools


class LibonvifConan(ConanFile):
    jsonInfo = json.loads(tools.load("info.json"))
    name = jsonInfo["projectName"]
    version = "%u.%u.%u%s" % (jsonInfo["version"]["major"], jsonInfo["version"]["minor"], jsonInfo["version"]["patch"], "-SNAPSHOT" if jsonInfo["version"]["snapshot"] else "")
    license = jsonInfo["license"]
    url = jsonInfo["repository"]
    description = jsonInfo["projectDescription"]
    author = jsonInfo["vendor"]
    homepage = jsonInfo["repository"]
    requires = "Qt/[5.12]@tereius/stable"
    settings = {"os": ["Windows", "Linux", "Android", "Macos"], "compiler": None, "build_type": None, "arch": None}
    options = {"shared": [True, False], "openssl": [True, False]}
    default_options = "shared=True", "openssl=True"
    generators = "cmake"
    exports = "info.json"
    exports_sources = "*"
    default_user = "tereius"
    default_channel = "stable"

    def requirements(self):
        if self.options.openssl:
            self.requires("openssl/1.1.1i")
            self.options["openssl"].shared = True

    def build(self):
        if self.settings.os == 'Android':
            cmake = CMake(self, generator="Unix Makefiles")
        else:
            cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.install()

    def package_info(self):
        self.cpp_info.builddirs = ['cmake']
        if self.options.openssl:
            self.cpp_info.defines = ['WITH_OPENSSL']
