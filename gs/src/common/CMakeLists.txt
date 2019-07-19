# 设置静态库名
SET(LIB_NAME common)
# 源文件
AUX_SOURCE_DIRECTORY(. SRC)
# 生成静态态库
ADD_LIBRARY(${LIB_NAME} ${SRC})
# 依赖库
TARGET_LINK_LIBRARIES(${LIB_NAME}
 mysqlclient
)