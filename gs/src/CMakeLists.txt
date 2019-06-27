
# cmake版本要求
cmake_minimum_required(VERSION 2.8.9)
# 项目名
PROJECT(xlogic_gs)
# 编译选项
SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -g -DDEBUG ")
SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -g -O3 -DNDEBUG ")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++11 -g -DDEBUG -Wall -Wno-reorder -Wno-unused-variable -Wno-unused-function -fexceptions -Wno-unused-result -ldl")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -std=c++11 -g -O3 -DNDEBUG -Wall -Wno-reorder -Wno-unused-variable -Wno-unused-function -fexceptions -Wno-unused-result -ldl")
# 生成可执行文件路径
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}../../bin)
# 生成库路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}../../lib)

ADD_SUBDIRECTORY(common)
ADD_SUBDIRECTORY(network)
# 服务器
ADD_SUBDIRECTORY(service_conn)
