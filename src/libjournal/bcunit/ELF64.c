#include "journal.h"
#include <BCUnit/BCUnit.h>

/* Private Function Declarations From LibJournal */
#ifndef NDEBUG
ELF64_Hash *_Journal_ELF64_digest_char( ELF64_Hash *restrict, const char );
#endif

/* Test Digest Returns input hash reference */
void _JournalUnitTests_ELF64_SingleShift_Return() {
	ELF64_Hash hash = 0;
	const char data = 'D';

	#ifdef NDEBUG
	CU_FAIL( "`_Journal_ELF64_digest_char' is an inline function; use `Debug' compile mode." );
	#else
	CU_ASSERT_PTR_EQUAL( _Journal_ELF64_digest_char( &hash, data ), &hash );
	#endif
}

/* Test First [non-null] Data Read */
void _JournalUnitTests_ELF64_SingleShift_FirstShift() {
	ELF64_Hash hash = 0;
	const char data = 'M';

	#ifdef NDEBUG
	CU_FAIL( "`_Journal_ELF64_digest_char' is an inline function; use `Debug' compile mode." );
	#else
	_Journal_ELF64_digest_char( &hash, data );
	CU_ASSERT_EQUAL( (char)hash, data );
	#endif
}	

__attribute__((constructor (102)))
void _JournalUnitTests_RegisterSuite_ELF64() {
	CU_pSuite suite;
	CU_pTest test;

	suite = CU_add_suite( "[LibJournal] ELF64 SingleShift", NULL, NULL );
	test = CU_add_test( suite, "Returns Hash", &_JournalUnitTests_ELF64_SingleShift_Return );
	test = CU_add_test( suite, "First Shift Unchanged", &_JournalUnitTests_ELF64_SingleShift_FirstShift );
	#ifdef NDEBUG
	CU_set_suite_active( suite, CU_FALSE );
	#endif
}

