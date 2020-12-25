# CMakeList.txt: leet_code_cmake 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("leet_code_cmake")

include_directories( ${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

# 将源代码添加到此项目的可执行文件。
add_executable (leet_code_cmake ${SRC_LIST})

# TODO: 如有需要，请添加测试并安装目标。
