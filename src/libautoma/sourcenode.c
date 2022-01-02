#include "rewrite.def"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"

bool LibAutoma( SourceNode )( PushString )( LibAutoma( SourceNode ) **stack, const char *array, const size_t length ) {
	LibAutoma( SourceNode ) *newnode = (LibAutoma( SourceNode ) *) malloc( sizeof( LibAutoma( SourceNode ) ) );
	if( newnode == NULL ) {
		return false;
	}

	newnode->Type = LibAutoma( SourceType )( STRING );
	newnode->Source.cstr.orig = (char *) malloc( length );
	if( newnode->Source.cstr.orig == NULL ) {
		free( newnode );
		return false;
	}

	newnode->Source.cstr.pos = newnode->Source.cstr.orig;
	newnode->Source.cstr.len = length;

	newnode->Next = *stack;
	*stack = newnode;

	return true;
}

bool LibAutoma( SourceNode )( PushFile )( LibAutoma( SourceNode ) **stack, const char *path ) {
	LibAutoma( SourceNode ) *newnode = (LibAutoma( SourceNode ) *) malloc( sizeof( LibAutoma( SourceNode ) ) );
	if( newnode == NULL ) {
		return false;
	}

	newnode->Type = LibAutoma( SourceType )( FILE );
	newnode->Source.file = fopen( path, "r" );
	if( newnode->Source.file == NULL ) {
		free( newnode );
		return false;
	}

	newnode->Next = *stack;
	*stack = newnode;

	return true;
}

void LibAutoma( SourceNode )( PopNode )( LibAutoma( SourceNode ) **stack ) {
	LibAutoma( SourceNode ) *tmpnode = *stack;
	*stack = tmpnode->Next;
	if( tmpnode->Type == LibAutoma( SourceType )( STRING ) ) {
		free( tmpnode->Source.cstr.orig );
	} else {
		fclose( tmpnode->Source.file );
	}
	free( tmpnode );
}

bool LibAutoma( SourceNode )( IsGood )( LibAutoma( SourceNode ) **stack ) {
	if( *stack == NULL ) {
		return false;
	} else if( (*stack)->Type == LibAutoma( SourceType )( STRING ) ) {
		return (*stack)->Source.cstr.pos - (*stack)->Source.cstr.orig < (*stack)->Source.cstr.len;
	} else {
		/* Bump the read 1 char to detect EOF */
		fpos_t pos;
		int buff;
		fgetpos( (*stack)->Source.file, &pos );
		buff = fgetc( (*stack)->Source.file );
		if( buff != EOF )
			fsetpos( (*stack)->Source.file, &pos );

		return ferror( (*stack)->Source.file ) == 0 && feof( (*stack)->Source.file ) == 0;
	}
}

unsigned char LibAutoma( SourceNode )( GetChar )( LibAutoma( SourceNode ) **stack ) {
	char charbuff = '\0';

	/* Start Process in Good State if Possible */
	while( *stack != NULL && !LibAutoma( SourceNode )( IsGood )( stack ) )
		LibAutoma( SourceNode )( PopNode )( stack );

	if( LibAutoma( SourceNode )( IsGood )( stack ) ) {
		/* Get next char */
		if( (*stack)->Type == LibAutoma( SourceType )( STRING ) ) { 
			charbuff = *(*stack)->Source.cstr.pos++;		
		} else {
			charbuff = fgetc( (*stack)->Source.file );
		}

		/* End Process in Good State (if Possible ) */
		while( *stack != NULL && ! LibAutoma( SourceNode )( IsGood )( stack ) )
			LibAutoma( SourceNode )( PopNode )( stack );
	}

	return charbuff;
}

