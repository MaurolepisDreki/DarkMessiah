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

/* Test Cyclic Shift */
void _JournalUnitTests_ELF64_SingleShift_Cycle() {
	ELF64_Hash hash = 0x0F00000000000000;
	const ELF64_Hash result = 0x00000000000000F0;
	const char data = '\0';

	#ifdef NDBUG
	CU_FAIL( "`Journal_ELF64_digest_char' is an inline function; use `Debug' compile mode." );
	#else
	_Journal_ELF64_digest_char( &hash, data );
	CU_ASSERT_EQUAL( hash, result );
	#endif
}

__attribute__((constructor (102)))
void _JournalUnitTests_RegisterSuite_ELF64() {
	CU_pSuite suite;
	CU_pTest test;

	suite = CU_add_suite( "[LibJournal] ELF64 SingleShift", NULL, NULL );
	test = CU_add_test( suite, "Returns Hash Address", &_JournalUnitTests_ELF64_SingleShift_Return );
	test = CU_add_test( suite, "First Byte Verbatim", &_JournalUnitTests_ELF64_SingleShift_FirstShift );
	test = CU_add_test( suite, "Left Cyclic Shift", &_JournalUnitTests_ELF64_SingleShift_Cycle );
	#ifdef NDEBUG
	CU_set_suite_active( suite, CU_FALSE );
	#endif
}

