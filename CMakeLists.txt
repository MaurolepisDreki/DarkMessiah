cmake_minimum_required( VERSION 3.22 )

project( DarkMessiah
	VERSION 2021.339
	DESCRIPTION "Full-Service Web Site featuring Privacy, Security, and Liberty"
)

find_package( PkgConfig )

add_subdirectory( src build )

# Add Uninstall Target
configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
	@ONLY
)

ADD_CUSTOM_TARGET( uninstall
	"${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
)

