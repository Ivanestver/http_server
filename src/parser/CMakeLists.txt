FILE(GLOB PUBLIC_HEADERS "${CMAKE_SOURCE_DIR}/headers/parser/*.h")
FILE(GLOB HEADERS "./*.h")
FILE(GLOB SRC "./*.cpp")

add_library(parser ${PUBLIC_HEADERS} ${HEADERS} ${SRC})

target_link_libraries(parser net_core message)