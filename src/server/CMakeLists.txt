FILE(GLOB PUBLIC_HEADERS "${CMAKE_SOURCE_DIR}/headers/server/*.h")
FILE(GLOB HEADERS "./*.h")
FILE(GLOB SRC "./*.cpp")

add_library(server ${PUBLIC_HEADERS} ${HEADERS} ${SRC})

target_link_libraries(server INTERFACE parser net_core message)