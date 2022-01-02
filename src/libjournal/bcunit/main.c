/* [Local] Test Runner */
#include <BCUnit/BCUnit.h>
#include <BCUnit/Basic.h>
#include <stdlib.h>
#include <stdio.h>

__attribute__((constructor (101)))
void _JournalUnitTests_Init() {
	if( CU_initialize_registry() ) {
		fprintf( stderr, "FATAL: %s\n", CU_get_error_msg() );
		abort();
	}
}

__attribute__((destructor (101)))
void _JournalUnitTests_Term() {
	CU_cleanup_registry();
}

int main( int argc, char **argv ) {
	CU_basic_set_mode( CU_BRM_VERBOSE );
	if( CU_basic_run_tests() )
		printf( "%s\n", CU_get_error_msg() );
	return CU_get_error() ? EXIT_FAILURE : EXIT_SUCCESS;
}

