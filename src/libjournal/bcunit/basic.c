#include <BCUnit/Basic.h>
#include <stdlib.h>
#include <stdio.h>

int main( int argc, char **argv ) {
	CU_basic_set_mode( CU_BRM_VERBOSE );
	if( CU_basic_run_tests() )
		printf( "%s\n", CU_get_error_msg() );
	return CU_get_error() ? EXIT_FAILURE : EXIT_SUCCESS;
}

