add_library( automa SHARED
	engine.c
#	state.c
)

install( TARGETS automa 
	DESTINATION "${DM_INSTALL_LIB}"
)

