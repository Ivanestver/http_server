FILE(GLOB HEADERS "${CMAKE_SOURCE_DIR}/headers/net_core/*.h")
FILE(GLOB SRC "./*.cpp")

add_library(net_core ${HEADERS} ${SRC})

target_link_libraries(net_core core)