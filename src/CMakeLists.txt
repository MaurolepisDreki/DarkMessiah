pkg_check_modules( FCGI REQUIRED fcgi )

add_executable( dmcgi 
	main.c
)
target_link_libraries( dmcgi
	${FCGI_LIBRARIES}
)
install( TARGETS dmcgi
	DESTINATION "${DM_INSTALL_BIN}"
)

