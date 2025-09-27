FILE(GLOB PUBLIC_HEADERS "${CMAKE_SOURCE_DIR}/headers/core/*.h")
FILE(GLOB HEADERS "./*.h")
FILE(GLOB SRC "./*.cpp")

add_library(core ${PUBLIC_HEADERS} ${HEADERS} ${SRC})