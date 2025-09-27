FILE(GLOB PUBLIC_HEADERS "${CMAKE_SOURCE_DIR}/headers/net_core/*.h")
FILE(GLOB HEADERS "./*.h")
FILE(GLOB SRC "./*.cpp")

add_library(net_core ${PUBLIC_HEADERS} ${HEADERS} ${SRC})

target_link_libraries(net_core core)