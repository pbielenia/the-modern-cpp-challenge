#!/usr/bin/env python3
import sys
import os
from pathlib import Path


class ProjectCreator(object):
    def __init__(self, number, title, class_name):
        self.number = number
        self.title = title
        self.class_name = class_name

        self.__include_dir_name = 'include'
        self.__source_dir_name = 'src'
        self.__tests_dir_name = 'tests'
        self.__header_name = self.class_name + '.hpp'
        self.__source_name = self.class_name + '.cpp'
        self.__unit_tests_name = 'unit_tests.cpp'

        self.full_name = self.__generate_full_name()
        self.project_path = self.__generate_project_path()

        self.__include_dir_path = self.__generate_include_dir_path()
        self.__source_dir_path = self.__generate_source_dir_path()
        self.__unit_tests_dir_path = self.__generate_unit_tests_dir_path()

        self.__header_path = self.__include_dir_path + self.__header_name
        self.__source_path = self.__source_dir_path + self.__source_name

    def __generate_full_name(self):
        return str(self.number).zfill(3) + '-' + self.title

    def __generate_project_path(self):
        return os.getcwd() + '/' + self.__source_dir_name + '/' + self.full_name + '/'

    def __generate_include_dir_path(self):
        return self.project_path + self.__include_dir_name + '/' + self.title + '/'

    def __generate_source_dir_path(self):
        return self.project_path + self.__source_dir_name + '/'

    def __generate_unit_tests_dir_path(self):
        return os.getcwd() + '/' + self.__tests_dir_name + '/' + self.full_name + '/'

    def __create_header_file(self):
        header = open(self.__header_path, 'w+')
        header.write("#pragma once\n"
                     "\n"
                     "class " + self.class_name + " {\n"
                     "public:\n"
                     "\t//\n"
                     "private:\n"
                     "\t//\n"
                     "};\n")
        header.close()

    def __create_source_file(self):
        source = open(self.__source_path, 'w+')
        source.write("#include \"" + self.title + '/' + self.class_name + ".hpp\"\n"
                     "\n")
        source.close()

    def __create_cmakelists_file(self):
        source = open(self.project_path + '/CMakeLists.txt', 'w+')
        source.write("cmake_minimum_required(VERSION 3.17)\n\n"
                     "set(target_name " + self.full_name + ")\n\n"
                     "add_library(${target_name} STATIC " + self.__source_dir_name + "/" +
                     self.__source_name + ")\n"
                     "target_include_directories(${target_name}\n"
                     "PUBLIC\n"
                     "\t$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/" +
                     self.__include_dir_name + ">\n"
                     "PRIVATE\n"
                     "\t$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/" + self.__include_dir_name + "/" +
                     self.title + ">\n"
                     ")\n\n"
                     "target_compile_options(${target_name}\n"
                     "PRIVATE\n"
                     "\t-Wall -Wextra -pedantic -Werror\n"
                     ")\n"
                     )
        source.close()

    def __create_unit_tests_cmakelists_file(self):
        cmakelists = open(self.__unit_tests_dir_path + '/CMakeLists.txt', 'w+')
        cmakelists.write("cmake_minimum_required(VERSION 3.17)\n\n"
                         "include(GoogleTest)\n\n"
                         "set(target_name " + self.full_name + "_tests)\n"
                         "add_executable(${target_name} " +
                         self.__unit_tests_name + ")\n"
                         "target_compile_features(${target_name} PRIVATE cxx_std_17)\n"
                         "target_link_libraries(${target_name}\n"
                         "PRIVATE\n"
                         "\tgtest\n"
                         "\tgtest_main\n"
                         "\tgmock\n"
                         "\t" + self.full_name + "\n"
                         ")\n\n"
                         "gtest_discover_tests(${target_name} TEST_PREFIX " +
                         self.number + ": )\n"
                         )

        cmakelists.close()

    def __create_unit_tests_file(self):
        path = self.__unit_tests_dir_path + self.__unit_tests_name
        unit_tests = open(path, 'w+')
        unit_tests.write("#include \"" + self.title + "/" +
                         self.__header_name + "\"\n\n"
                         "#include <gmock/gmock.h>\n\n"
                         "using namespace testing;\n\n"
                         "TEST(" + self.class_name + ", ExampleTest)\n"
                         "{\n"
                         "\tauto example = " + self.class_name + "();\n"
                         "}\n")
        unit_tests.close()

    def create_directories(self):
        print("Creating directories:\n\t{}\n\t{}\n\t{}".format(
              self.__include_dir_path, self.__source_dir_path, self.__unit_tests_dir_path))
        Path(self.__include_dir_path).mkdir(parents=True, exist_ok=True)
        Path(self.__source_dir_path).mkdir(parents=True, exist_ok=True)
        Path(self.__unit_tests_dir_path).mkdir(parents=True, exist_ok=True)

    def create_files(self):
        print("Creating files:\n\t{}\n\t{}".format(
              self.__header_path, self.__source_path))
        self.__create_header_file()
        self.__create_source_file()
        self.__create_cmakelists_file()
        self.__create_unit_tests_cmakelists_file()
        self.__create_unit_tests_file()

    def register_project(self):
        self.__register_sources()
        self.__register_tests()

    def __register_sources(self):
        f = open(self.__source_dir_name + "/CMakeLists.txt", "a")
        f.write("add_subdirectory(" + self.full_name + ")\n")
        f.close()

    def __register_tests(self):
        f = open(self.__tests_dir_name + "/CMakeLists.txt", "a")
        f.write("add_subdirectory(" + self.full_name + ")\n")
        f.close()


creator = ProjectCreator(sys.argv[1], sys.argv[2], sys.argv[3])
creator.create_directories()
creator.create_files()
creator.register_project()
