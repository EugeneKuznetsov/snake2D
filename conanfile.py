import re

from conans import ConanFile, CMake, tools
from pathlib import Path

required_conan_version = ">=1.45.0"

class Snake2D(ConanFile):
    name = "snake2D"
    author = "Eugene Kuznetsov"
    license = "MIT"
    description = "2D snake game powered by GameDevKit"
    url = "git@github.com:EugeneKuznetsov/snake2D.git"
    scm = {"type": "git", "url": "auto", "revision": "auto"}
    default_user = "gamedev"
    default_channel = "stable"
    generators = "cmake_find_package"
    settings = "os", "compiler", "arch", "build_type"
    tool_requires = "cmake/[>3.20.x]", "ninja/[^1.11.x]", "gtest/[~1.11.x]"
    requires = "gamedevkit/[^1.x]@gamedev/stable"

    def __init__(self, output, runner, display_name="", user=None, channel=None):
        super().__init__(output, runner, display_name=display_name, user=user, channel=channel)
        self.version = self.read_version()

    def read_version(self):
        cmakelists_txt = Path(self.recipe_folder) / "CMakeLists.txt"
        if cmakelists_txt.exists():
            content = tools.load(cmakelists_txt)
            version_regex = "project[\S\s]*VERSION[\S\s](\d+\.\d+\.\d+)"
            return re.findall(version_regex, content, re.MULTILINE)[0]
        return None

    def build(self):
        if self.should_build is True:
            self.cmake.build()
        if self.should_test is True:
            self.cmake.test(output_on_failure=True)

    @property
    def cmake(self):
        if not hasattr(self, "_cmake"):
            cmake_modules = [self.source_folder + "/cmake", self.build_folder]
            self._cmake = CMake(self, generator="Ninja")
            self._cmake.definitions["CMAKE_MODULE_PATH"] = ";".join([f.replace("\\", "/") for f in cmake_modules])
            self._cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = True
            if self.should_configure is True:
                self._cmake.configure()
        return self._cmake
