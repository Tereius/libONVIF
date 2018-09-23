#!/usr/bin/env python
# -*- coding: utf-8 -*-


import json, os
from conans import ConanFile, CMake, tools, AutoToolsBuildEnvironment


class LibonvifConan(ConanFile):
    jsonInfo = json.loads(tools.load("info.json"))
    name = jsonInfo["projectName"]
    version = "%u.%u.%u%s" % (jsonInfo["version"]["major"], jsonInfo["version"]["minor"], jsonInfo["version"]["patch"], "-SNAPSHOT" if jsonInfo["version"]["snapshot"] else "")
    license = jsonInfo["license"]
    url = jsonInfo["repository"]
    description = jsonInfo["projectDescription"]
    author = jsonInfo["vendor"]
    homepage = jsonInfo["repository"]
    requires = "Qt/[>=5.4]@tereius/stable"
    settings = "os", "compiler", "build_type", "arch", "os_build", "arch_build"
    options = {"shared": [True, False], "openssl": [True, False]}
    default_options = "shared=True", "openssl=True", "OpenSSL:shared=True"
    generators = "cmake"
    exports = "info.json"
    exports_sources = "*"

    def requirements(self):
        if self.options.openssl:
            self.requires("OpenSSL/1.1.0g@conan/stable")

    def build_requirements(self):
        if self.settings.os == 'Android':
            self.build_requires("android-ndk/r17b@tereius/stable")
            if self.settings.os_build == 'Windows':
                self.build_requires("msys2/20161025@tereius/stable")

    def build(self):
        tools.replace_in_file(os.path.join(self.build_folder, "CMakeLists.txt"), "### CONAN_BEACON ###", 'include(%s)\n%s' % (os.path.join(self.install_folder, "conanbuildinfo.cmake").replace("\\", "/"), "conan_basic_setup()"), strict=False)
        if self.settings.os == 'Android':
            autotools = AutoToolsBuildEnvironment(self, win_bash=True)
            environment = autotools.vars
            #environment["CC"] = self.deps_env_info['android-ndk'].CC
            #environment["CXX"] = self.deps_env_info['android-ndk'].CXX
            while tools.environment_append(autotools.vars):
                self.run("whereis cmake", win_bash=True)
                cmake = CMake(self, generator="Unix Makefiles")
                self.run('cmake "%s" %s -DCMAKE_C_COMPILER=%s -DCMAKE_CXX_COMPILER=%s' % (self.source_folder, cmake.command_line, tools.unix_path(self.deps_env_info['android-ndk'].CC), tools.unix_path(self.deps_env_info['android-ndk'].CXX)), win_bash=True)
                #cmake.configure(defs = {"CMAKE_MAKE_PROGRAM": tools.unix_path(os.path.join(self.deps_env_info['msys2'].MSYS_BIN, "make.exe")), "CMAKE_C_COMPILER": tools.unix_path(self.deps_env_info['android-ndk'].CC), "CMAKE_CXX_COMPILER": tools.unix_path(self.deps_env_info['android-ndk'].CXX)})
                #cmake.build()
                #cmake.install()
        else:
            cmake = CMake(self)
            cmake.configure()
            cmake.build()
            cmake.install()

    def package_info(self):
        self.cpp_info.builddirs = ['cmake']
        if self.options.openssl:
            self.cpp_info.defines = ['WITH_OPENSSL']
