# CMakeList.txt: проект CMake для HTTPServer; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/headers)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (HTTPServer "main.cpp")

target_link_libraries(HTTPServer PUBLIC server)

# And to your executable's CMakeLists.txt
set_target_properties(HTTPServer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
