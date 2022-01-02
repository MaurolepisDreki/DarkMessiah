/* Local ELF Algorithm Implimentation in 64-bits */
#include "journal.h"
#include <limits.h>
#include <stddef.h>

/* Digest one char into ELF64; return `hashref' */
#ifdef NDEBUG
inline
#endif
ELF64_Hash *_Journal_ELF64_digest_char( ELF64_Hash *restrict hashref, const char data ) {
	const size_t hashlen = sizeof( ELF64_Hash ) * CHAR_BIT;
	const ELF64_Hash lastnib = ((ELF64_Hash) 0xF) << hashlen - 4;
	ELF64_Hash buffer;

	*hashref = ( *hashref << 4 ) + data;
	if( buffer = *hashref & lastnib )
		*hashref ^= buffer >> hashlen - 8;
	*hashref &= ~buffer;

	return hashref;
}

