
SET(THIRDPARTY ../third_party)

INCLUDE_DIRECTORIES(common)
INCLUDE_DIRECTORIES(network)
INCLUDE_DIRECTORIES(${THIRDPARTY}/libevent-2.1.8-stable/include)
INCLUDE_DIRECTORIES(${THIRDPARTY}/yaml-cpp/include)

# 找到当前所有源文件并赋值
AUX_SOURCE_DIRECTORY(common COMMON_SRC)
AUX_SOURCE_DIRECTORY(network NETWORK_SRC)
AUX_SOURCE_DIRECTORY(. SRC)

ADD_EXECUTABLE(xlogic_gs ${COMMON_SRC} ${NETWORK_SRC} ${SRC})

target_link_libraries(
 libevent.a
)

