#include <BCUnit/Automated.h>
#include <stdlib.h>
#include <stdio.h>

int main( int argc, char **argv ) {
	CU_set_output_filename( "JournalTest" );
	CU_list_tests_to_file();
	CU_automated_run_tests();
	if( CU_get_error() )
		printf( "%s\n", CU_get_error_msg() );
	return  CU_get_error() ? EXIT_FAILURE : EXIT_SUCCESS;
}

