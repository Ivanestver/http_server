FILE(GLOB HEADERS "${CMAKE_SOURCE_DIR}/headers/message/*.h")
FILE(GLOB SRC "./*.cpp")

add_library(message ${HEADERS} ${SRC})