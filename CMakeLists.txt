# CMakeList.txt: проект CMake для HTTPServer; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: Disable compiler-specific extensions if not desired
set(CMAKE_CXX_EXTENSIONS OFF)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("HTTPServer")

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/headers)

add_compile_definitions(CORE_EXPORTS)

add_subdirectory("src/core")
add_subdirectory("src/net_core")
add_subdirectory("src/message")
add_subdirectory("src/parser")
add_subdirectory("src/main")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET HTTPServer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
