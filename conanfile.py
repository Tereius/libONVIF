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
    requires = "Qt/[>=5.4 <6.0]@tereius/stable"
    settings = {"os": ["Windows", "Linux", "Android", "Macos"], "compiler": None, "build_type": None, "arch": None}
    options = {"shared": [True, False], "openssl": [True, False]}
    default_options = "shared=True", "openssl=True"
    generators = "cmake"
    exports = "info.json"
    exports_sources = "*"

    def requirements(self):
        if self.options.openssl:
            self.requires("OpenSSL/1.1.1b@tereius/stable")
            self.options["OpenSSL"].shared = True
            self.options["OpenSSL"].no_zlib = True

    def build_requirements(self):
        if self.settings.os == 'Android':
            self.build_requires("android-ndk/r17b@tereius/stable")
            self.build_requires_options["android-ndk"].makeStandalone=False
            if tools.os_info.is_windows == 'Windows':
                self.build_requires("msys2/20161025@tereius/stable")

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
