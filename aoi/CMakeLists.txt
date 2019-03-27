cmake_minimum_required(VERSION 2.8.9)
# 工程名
PROJECT(xlogic)

SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -g -DDEBUG ")
SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -g -O3 -DNDEBUG ")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++11 -g -DDEBUG -Wall -Wno-reorder -Wno-unused-variable -Wno-unused-function -fexceptions -Wno-unused-result -ldl")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -std=c++11 -g -O3 -DNDEBUG -Wall -Wno-reorder -Wno-unused-variable -Wno-unused-function -fexceptions -Wno-unused-result -ldl")

# 编译模式
SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_BUILD_TYPE Release)

# 找到当前所有源文件并赋值
AUX_SOURCE_DIRECTORY(. SRV_SRC)

# 生成可执行文件
ADD_EXECUTABLE(test_aol ${SRV_SRC})
