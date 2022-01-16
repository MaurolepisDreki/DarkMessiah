#include "journal.h"
#include <BCUnit/BCUnit.h>
#include <string.h>

/* Private Function Declarations From LibJournal */
#ifndef NDEBUG
ELF64_Hash *_Journal_ELF64_digest_char( ELF64_Hash *restrict, const char );
#endif
ELF64_Hash *_Journal_ELF64_digest( ELF64_Hash *restrict, const void *restrict, const size_t );

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

	#ifdef NDEBUG
	CU_FAIL( "`_Journal_ELF64_digest_char' is an inline function; use `Debug' compile mode." );
	#else
	_Journal_ELF64_digest_char( &hash, data );
	CU_ASSERT_EQUAL( hash, result );
	#endif
}

/* Test Data Chain */
void _JournalUnitTests_ELF64_SingleShift_Chain() {
	ELF64_Hash hash = 0;
	
	#ifdef NDEBUG
	CU_FAIL( "`_Journal_ELF64_digest_char' is an inline function; use `Debug' compiler mode." );
	#else
	_Journal_ELF64_digest_char( &hash, 'M' );
	CU_ASSERT_EQUAL( hash, 0x000000000000004D );

	_Journal_ELF64_digest_char( &hash, 'a' );
	CU_ASSERT_EQUAL( hash, 0x0000000000000531 );

	_Journal_ELF64_digest_char( &hash, 'u' );
	CU_ASSERT_EQUAL( hash, 0x0000000000005385 );

	_Journal_ELF64_digest_char( &hash, 'r' );
	CU_ASSERT_EQUAL( hash, 0x00000000000538C2 );

	_Journal_ELF64_digest_char( &hash, 'o' );
	CU_ASSERT_EQUAL( hash, 0x0000000000538C8F );

	_Journal_ELF64_digest_char( &hash, 'l' );
	CU_ASSERT_EQUAL( hash, 0x000000000538C95C );

	_Journal_ELF64_digest_char( &hash, 'e' );
	CU_ASSERT_EQUAL( hash, 0x00000000538C9625 );

	_Journal_ELF64_digest_char( &hash, 'p' );
	CU_ASSERT_EQUAL( hash, 0x0000000538C962C0 );

	_Journal_ELF64_digest_char( &hash, 'i' );
	CU_ASSERT_EQUAL( hash, 0x000000538C962C69 );

	_Journal_ELF64_digest_char( &hash, 's' );
	CU_ASSERT_EQUAL( hash, 0x00000538C962C703 );

	_Journal_ELF64_digest_char( &hash, ' ' );
	CU_ASSERT_EQUAL( hash, 0x0000538C962C7050 );

	_Journal_ELF64_digest_char( &hash, 'D' );
	CU_ASSERT_EQUAL( hash, 0x000538C962C70544 );

	_Journal_ELF64_digest_char( &hash, 'r' );
	CU_ASSERT_EQUAL( hash, 0x00538C962C7054B2 );

	_Journal_ELF64_digest_char( &hash, 'e' );
	CU_ASSERT_EQUAL( hash, 0x0538C962C7054B85 );

	_Journal_ELF64_digest_char( &hash, 'k' );
	CU_ASSERT_EQUAL( hash, 0x038C962C7054B8EB );

	_Journal_ELF64_digest_char( &hash, 'i' );
	CU_ASSERT_EQUAL( hash, 0x08C962C7054B8F29 );

	_Journal_ELF64_digest_char( &hash, '\'' );
	CU_ASSERT_EQUAL( hash, 0x0C962C7054B8F237 );

	_Journal_ELF64_digest_char( &hash, 's' );
	CU_ASSERT_EQUAL( hash, 0x0962C7054B8F2323 );

	_Journal_ELF64_digest_char( &hash, ' ' );
	CU_ASSERT_EQUAL( hash, 0x062C7054B8F232C0 );

	_Journal_ELF64_digest_char( &hash, 'D' );
	CU_ASSERT_EQUAL( hash, 0x02C7054B8F232C24 );

	_Journal_ELF64_digest_char( &hash, 'a' );
	CU_ASSERT_EQUAL( hash, 0x0C7054B8F232C281 );

	_Journal_ELF64_digest_char( &hash, 'r' );
	CU_ASSERT_EQUAL( hash, 0x07054B8F232C2842 );

	_Journal_ELF64_digest_char( &hash, 'k' );
	CU_ASSERT_EQUAL( hash, 0x0054B8F232C284FB );

	_Journal_ELF64_digest_char( &hash, ' ' );
	CU_ASSERT_EQUAL( hash, 0x054B8F232C284FD0 );

	_Journal_ELF64_digest_char( &hash, 'M' );
	CU_ASSERT_EQUAL( hash, 0x04B8F232C284FD1D );

	_Journal_ELF64_digest_char( &hash, 'e' );
	CU_ASSERT_EQUAL( hash, 0x0B8F232C284FD275 );

	_Journal_ELF64_digest_char( &hash, 's' );
	CU_ASSERT_EQUAL( hash, 0x08F232C284FD2773 );

	_Journal_ELF64_digest_char( &hash, 's' );
	CU_ASSERT_EQUAL( hash, 0x0F232C284FD27723 );

	_Journal_ELF64_digest_char( &hash, 'i' );
	CU_ASSERT_EQUAL( hash, 0x0232C284FD277269 );

	_Journal_ELF64_digest_char( &hash, 'a' );
	CU_ASSERT_EQUAL( hash, 0x032C284FD27726D1 );

	_Journal_ELF64_digest_char( &hash, 'h' );
	CU_ASSERT_EQUAL( hash, 0x02C284FD27726D48 );
	#endif
}

void _JournalUnitTests_ELF64_MultiShift_Return() {
	ELF64_Hash hash = 0;
	CU_ASSERT_PTR_EQUAL( _Journal_ELF64_digest( &hash, "", 0 ), &hash );
}

void _JournalUnitTests_ELF64_MultiShift_SingleByte() {
	ELF64_Hash hash = 0;
	const char *str2 = "D";
	
	_Journal_ELF64_digest( &hash, "M", 1 );
	CU_ASSERT_EQUAL( hash, 0x000000000000004D );

	hash = 0;
	_Journal_ELF64_digest( &hash, str2, strlen( str2 ) );
	CU_ASSERT_EQUAL( hash, 0x0000000000000044 );
}

void _JournalUnitTests_ELF64_MultiShift_LCS() {
	ELF64_Hash hash = 0x0F00000000000000;

	_Journal_ELF64_digest( &hash, "", 1 );
	CU_ASSERT_EQUAL( hash, 0x00000000000000F0 );

	hash = 0x0F00000000000008;
	_Journal_ELF64_digest( &hash, "", 1 );
	CU_ASSERT_EQUAL( hash, 0x0000000000000070 );
}

void _JournalUnitTests_ELF64_MultiShift_Basic() {
	ELF64_Hash hash = 0;
	const char *str1 = "Maurolepis Dreki's Dark Messiah";
	
	_Journal_ELF64_digest( &hash, str1, strlen( str1 ) );
	CU_ASSERT_EQUAL( hash, 0x02C284FD27726D48 );
}

void _JournalUnitTests_ELF64_Interface_Empty() {
	CU_ASSERT_EQUAL( _Journal_ELF64( "" ), 0x0000000000000000 );
}

void _JournalUnitTests_ELF64_Interface_Hashes() {
	CU_ASSERT_EQUAL( _Journal_ELF64( "Maurolepis Dreki's Dark Messiah" ), 0x02C284FD27726D48 );
}

__attribute__((constructor (102)))
void _JournalUnitTests_RegisterSuite_ELF64() {
	CU_pSuite suite;
	CU_pTest test;

	suite = CU_add_suite( "[LibJournal] ELF64 SingleShift", NULL, NULL );
	test = CU_add_test( suite, "Returns Hash Address", &_JournalUnitTests_ELF64_SingleShift_Return );
	test = CU_add_test( suite, "First Byte Verbatim", &_JournalUnitTests_ELF64_SingleShift_FirstShift );
	test = CU_add_test( suite, "Left Cyclic Shift", &_JournalUnitTests_ELF64_SingleShift_Cycle );
	test = CU_add_test( suite, "Hash Data Chain", &_JournalUnitTests_ELF64_SingleShift_Chain );
	#ifdef NDEBUG
	CU_set_suite_active( suite, CU_FALSE );
	#endif

	suite = CU_add_suite( "[LibJournal] ELF64 MultiShift", NULL, NULL );
	test = CU_add_test( suite, "Returns Hash Address", &_JournalUnitTests_ELF64_MultiShift_Return );
	test = CU_add_test( suite, "Single Byte Verbatim", &_JournalUnitTests_ELF64_MultiShift_SingleByte );
	test = CU_add_test( suite, "Overflow Wrapping", &_JournalUnitTests_ELF64_MultiShift_LCS );
	test = CU_add_test( suite, "Basic Digest", &_JournalUnitTests_ELF64_MultiShift_Basic );

	suite = CU_add_suite( "[LibJournal] ELF64 Interface", NULL, NULL );
	test = CU_add_test( suite, "Empty String", &_JournalUnitTests_ELF64_Interface_Empty );
	test = CU_add_test( suite, "Basic Hashes", &_JournalUnitTests_ELF64_Interface_Hashes );
}

