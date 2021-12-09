add_library( automa SHARED
	engine.c
)

install( automa 
	DESTINATION "${DM_INSTALL_LIB}"
)

