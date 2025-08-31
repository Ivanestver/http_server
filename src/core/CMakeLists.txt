FILE(GLOB HEADERS "${CMAKE_SOURCE_DIR}/headers/core/*.h")
FILE(GLOB SRC "./*.cpp")

add_library(core ${HEADERS} ${SRC})