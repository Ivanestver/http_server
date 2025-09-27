FILE(GLOB PUBLIC_HEADERS "${CMAKE_SOURCE_DIR}/headers/message/*.h")
FILE(GLOB HEADERS "./*.h")
FILE(GLOB SRC "./*.cpp")

add_library(message ${PUBLIC_HEADERS} ${HEADERS} ${SRC})