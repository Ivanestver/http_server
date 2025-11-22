macro(define_library)
    set(oneValueArgs TARGET)
    cmake_parse_arguments(arg
        "${options}" "${oneValueArgs}" "${multiValueArgs}"
        ${ARGN}
    )

	FILE(GLOB PUBLIC_HEADERS "${CMAKE_SOURCE_DIR}/headers/${arg_TARGET}/*.h")
	FILE(GLOB HEADERS "./*.h")
	FILE(GLOB SOURCES "./*.cpp")

    string(TOUPPER "${arg_TARGET}" TARGET_UPPER)
	set(TARGET_EXPORTS "${TARGET_UPPER}_EXPORTS")
	add_library(${arg_TARGET} SHARED ${PUBLIC_HEADERS} ${HEADERS} ${SOURCES})
    target_compile_definitions(${arg_TARGET} PRIVATE ${TARGET_EXPORTS})

    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/export_decl.h" "
#pragma once

#if defined(_WIN32)
	#ifdef ${TARGET_EXPORTS}
		#define ${TARGET_UPPER} __declspec(dllexport)
	#else
		#define ${TARGET_UPPER} __declspec(dllimport)
	#endif
#else // Linux and other platforms
	#define ${TARGET_UPPER} __attribute__((visibility(\"default\")))
#endif"
    )
	target_include_directories(${arg_TARGET} PUBLIC
		${CMAKE_BINARY_DIR}/src
	)

	set_target_properties(${arg_TARGET} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
		ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
	)
endmacro()
