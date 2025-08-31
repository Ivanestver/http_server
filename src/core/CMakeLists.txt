FILE(GLOB HEADERS "${CMAKE_SOURCE_DIR}/headers/core/*.h")
FILE(GLOB SRC "./*.cpp")

add_compile_definitions(CORE_EXPORTS)

add_library(core ${HEADERS} ${SRC})