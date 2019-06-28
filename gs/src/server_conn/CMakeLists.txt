# 服务器名
SET(EXEC_NAME server_conn)
# 第三方路径
SET(THIRDPARTY ../../third_party)
# 头文件包含目录
INCLUDE_DIRECTORIES(../common)
INCLUDE_DIRECTORIES(../network)
INCLUDE_DIRECTORIES(${THIRDPARTY}/libevent-2.1.8-stable/include)
INCLUDE_DIRECTORIES(${THIRDPARTY}/yaml-cpp/include)
# 指定库路径
LINK_DIRECTORIES(${THIRDPARTY}/lib
 ../../lib
)
# 源文件赋值给SRV_SRC
AUX_SOURCE_DIRECTORY(. SRV_SRC)
# 生成可执行文件
ADD_EXECUTABLE(${EXEC_NAME} ${SRV_SRC})

# 链接指定库，目前只链接静态库
TARGET_LINK_LIBRARIES(${EXEC_NAME}
 libcommon.a
 libnetwork.a
 event
 pthread
)
