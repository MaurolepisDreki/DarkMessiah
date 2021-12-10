#include "rewrite.def"

#ifdef INCLUDED_LIBAUTOMA_STATE_H

/* Pre-Load Symbol Wrapper */
#  ifndef LibAutoma_State
#    define LibAutoma_State struct _( LibAutoma( State ) )
LibAutoma( State );
#  endif

#else
#  define INCLUDED_LIBAUTOMA_STATE_H

/* Replace Symbol Wrapper with Symbol (typedef) */
#  ifdef LibAutoma_State
#    undef LibAutoma_State
#  endif

/* IDs 0-255 reserved for read bytes */
typedef struct _( LibAutoma( State ) ) {
	unsigned int ID;
	struct _( LibAutoma( State ) ) *Prev;
	unsigned int Refs;
	void *Data;
	void (*OnDel)( void * /* Data */ );
} LibAutoma( State );

/* Function Identity Wrapper */
#  define LibAutoma_State( routine ) LibAutoma_State_ ## routine
#  define _LibAutoma_State( routine ) _LibAutoma_State_ ## routine

LibAutoma( State ) *LibAutoma( State )( Create )( 
	unsigned int /* new state */, 
	const LibAutoma( State ) * /* previous state */, 
	void * /* new data */,
	void (* /* data cleaner */)(void * /* data */ );

void _( LibAutoma( State )( Destroy ) )(
	LibAutoma( State ) ** /* target state */ );

void LibAutoma( State )( Acquire )(
	const LibAutoma( State ) * /* target state */ );

void LibAutoma( State )( Drop )(
	LibAutoma( State ) * /* target state */ );

const void *LibAutoma( State )( GetData )(
	const LibAutoma( State ) * /* target state */ );

unsigned int *LibAutoma( State )( GetID )(
	const LibAutoma( State ) * /* target state */ );

LibAutoma( State ) *LibAutoma( State )( GetPrev )(
	const LibAutoma( State ) * /* target state */ );

#endif

