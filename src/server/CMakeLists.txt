DEFINE_LIBRARY(
	TARGET server
)

target_link_libraries(server parser net_core)