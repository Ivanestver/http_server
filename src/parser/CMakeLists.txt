FILE(GLOB HEADERS "${CMAKE_SOURCE_DIR}/headers/parser/*.h")
FILE(GLOB SRC "./*.cpp")

add_library(parser ${HEADERS} ${SRC})