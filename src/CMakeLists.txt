pkg_check_modules( FCGI REQUIRED fcgi )
pkg_check_modules( BCUNIT bcunit ) #< Required for testing

add_subdirectory( libautoma )
add_subdirectory( libjournal )

add_executable( dm.fcgi 
	main.c
)
target_link_libraries( dm.fcgi
	${FCGI_LIBRARIES}
)
install( TARGETS dm.fcgi
	DESTINATION "${DM_INSTALL_BIN}"
)

