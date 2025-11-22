define_library(
	TARGET net_core
	SRC
		${PUBLIC_HEADERS}
		${HEADERS}
		${SRC}
)

target_link_libraries(net_core PRIVATE core)
