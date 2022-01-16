/* Local ELF Algorithm Implimentation in 64-bits */
#include "journal.h"
#include <limits.h>
#include <stddef.h>
#include <string.h>

/* Digest one char into ELF64; return `hashref' */
#ifdef NDEBUG
inline
#endif
ELF64_Hash *_Journal_ELF64_digest_char( ELF64_Hash *restrict hashref, const char data ) {
	static const size_t hashlen = sizeof( ELF64_Hash ) * CHAR_BIT;
	static const ELF64_Hash lastnib = ((ELF64_Hash) 0xF) << hashlen - 4;
	ELF64_Hash buffer;

	*hashref = ( *hashref << 4 ) + data;
	if( buffer = *hashref & lastnib )
		*hashref ^= buffer >> hashlen - 8;
	*hashref &= ~buffer;

	return hashref;
}

/* Digest an array of arbitrary bytes into ELF64; return `hashref' */
ELF64_Hash *_Journal_ELF64_digest( ELF64_Hash *restrict hashref, const void *restrict data, const size_t len ) {
	for( int indx = 0; indx < len; indx++ )
		_Journal_ELF64_digest_char( hashref, *((char *)data + indx) );

	return hashref;
}

/* MAIN INTERFACE: Create an ELF64 hash from a C-String */
ELF64_Hash _Journal_ELF64( const char *restrict cstr ) {
	ELF64_Hash output = 0;
	_Journal_ELF64_digest( &output, cstr, strlen( cstr ) );
	return output;
}

