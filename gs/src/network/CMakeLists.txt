
# 设置静态库名
SET(LIB_NAME network)

# 第三方库主目录
SET(THIRDPARTY ../../third_party)

# 头文件路径
INCLUDE_DIRECTORIES(../common)
INCLUDE_DIRECTORIES(${THIRDPARTY}/libevent-2.1.8-stable/include)

# 指定库路径
LINK_DIRECTORIES(${THIRDPARTY}/lib)

# 源文件
AUX_SOURCE_DIRECTORY(. SRC)

# 生成静态态库
ADD_LIBRARY(${LIB_NAME} ${SRC})

# 链接指定库，目前只链接静态库
TARGET_LINK_LIBRARIES(${LIB_NAME}
 libevent.a
 libevent_core.a
 libevent_extra.a
)
