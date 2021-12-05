cmake_minimum_required( VERSION 3.22 )

project( DarkMessiah
	VERSION 2021.339
	DESCRIPTION "Full-Service Web Site featuring Privacy, Security, and Liberty"
)

find_package( PkgConfig )

add_subdirectory( src build )

