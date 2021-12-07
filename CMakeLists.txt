cmake_minimum_required( VERSION 3.22 )

project( DarkMessiah
	VERSION 2021.339
	DESCRIPTION "Full-Service Web Site featuring Privacy, Security, and Liberty"
	LANGUAGES C
)

# Installation Directory Configurations (CGI)
set( WEBROOT "/srv/" CACHE PATH "Web Application Super-Directory" )
set( DM_INSTALL_DIR "${WEBROOT}/${CMAKE_PROJECT_NAME}/" )
set( DM_INSTALL_BIN "${DM_INSTALL_DIR}bin/" )
set( DM_INSTALL_LIB "${DM_INSTALL_DIR}lib/" )

find_package( UnixCommands REQUIRED )
find_package( PkgConfig )

add_subdirectory( src build )
add_subdirectory( data build/data )

# Add Uninstall Target
configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
	@ONLY
)

ADD_CUSTOM_TARGET( uninstall
	"${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
)

