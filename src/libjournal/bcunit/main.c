/* Core Functions of the Test Collection */
#include <BCUnit/BCUnit.h>
#include <stdlib.h>
#include <stdio.h>

/* Test Registration List */
void _JournalUnitTests_RegisterSuite_ELF64();

__attribute__((constructor (101)))
void _JournalUnitTests_Init() {
	if( CU_initialize_registry() ) {
		fprintf( stderr, "FATAL: %s\n", CU_get_error_msg() );
		abort();
	}

	_JournalUnitTests_RegisterSuite_ELF64();
}

__attribute__((destructor (101)))
void _JournalUnitTests_Term() {
	CU_cleanup_registry();
}

