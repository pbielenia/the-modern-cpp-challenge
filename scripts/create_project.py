#!/usr/bin/env python3
import sys
import os
from pathlib import Path


class ProjectCreator(object):
    def __init__(self, number, title, class_name):
        self.number = number
        self.title = title
        self.class_name = class_name
        self.project_path = self.__generate_project_path()
        self.__include_dir_path = self.__generate_include_dir_path()
        self.__source_dir_path = self.__generate_source_dir_path()
        self.__header_path = self.__generate_header_path()
        self.__source_path = self.__generate_source_path()

    def __generate_project_path(self):
        return os.getcwd() + '/src/' + str(self.number).zfill(3) + '-' + self.title

    def __generate_include_dir_path(self):
        return self.project_path + '/include/' + self.title

    def __generate_source_dir_path(self):
        return self.project_path + '/src'

    def __generate_header_path(self):
        return self.__include_dir_path + '/' + self.class_name + '.hpp'

    def __generate_source_path(self):
        return self.__source_dir_path + '/' + self.class_name + '.cpp'

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

    def create_directories(self):
        print("Creating directories:\n\t{}\n\t{}".format(
              self.__include_dir_path, self.__source_dir_path))
        Path(self.__include_dir_path).mkdir(parents=True, exist_ok=True)
        Path(self.__source_dir_path).mkdir(parents=True, exist_ok=True)

    def create_files(self):
        print("Creating files:\n\t{}\n\t{}".format(
              self.__header_path, self.__source_path))
        self.__create_header_file()
        self.__create_source_file()


creator = ProjectCreator(sys.argv[1], sys.argv[2], sys.argv[3])
creator.create_directories()
creator.create_files()

# get user input as arguments
# create:
#   [ ] src/<number>-<project_name>/include/<project_name>/<project_name>.hpp
#   [ ] src/<number>-<project_name>/src/<project_name>.cpp
#   [ ] src/<number>-<project_name>/CMakeLists.txt
#   [ ] tests/<number>-<project_name>/unit_tests.cpp
#   [ ] tests/<number>-<project_name>/CMakeLists.txt
#   [ ] record in the src/CMakeLists.txt
#   [ ] record in the tests/CMakeLists.txt
