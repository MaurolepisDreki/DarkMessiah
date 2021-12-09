#include "rewrite.def"

#ifdef INCLUDED_LIBAUTOMA_STATE_H
/* Pre-Load Symbol Wrapper */
#  define LibAutoma_State struct _( LibAutoma( State ) )
LibAutoma( State );

#else
#  define INCLUDED_LIBAUTOMA_STATE_H

/* Replace Symbol Wrapper with Symbol (typedef) */
#  ifdef LibAutoma_State
#    undef LibAutoma_State
#  endif

struct _( LibAutoma( State ) ) {
	unsigned int ID;
	struct _( LibAutoma( State ) ) *Prev;
	unsigned int Refs;
	void *Data;
	void (*OnDel)( void * /* Data */ );
};

typedef struct _( LibAutoma( State ) ) LibAutoma( State );

/* Function Identity Wrapper */
#  define LibAutoma_State( routine ) LibAutoma_State_ ## routine
#  define _LibAutoma_State( routine ) _LibAutoma_State_ ## routine

LibAutoma( State ) *LibAutoma( State )( New )( 
	unsigned int /* new state */, 
	const LibAutoma( State ) * /* previous state */ = NULL, 
	void * /* new data */ = NULL,
	void (* /* data cleaner */)(void * /* data */ ) = NULL);

void _( LibAutoma( State )( Del ) )(
	LibAutoma( State ) ** /* target state */ );

void LibAutoma( State )( Accuire )(
	const LibAutoma( State ) * /* target state */ );

void LibAutoma( State )( Drop )(
	LibAutoma( State ) * /* target state */ );

inline const void *LibAutoma( State )( GetData )(
	const LibAutoma( State ) * /* target state */ );

inline unsigned int *LibAutoma( State )( GetID )(
	const LibAutoma( State ) * /* target state */ );

inline LibAutoma( State ) *LibAutoma( State )( GetPrev )(
	const LibAutoma( State ) * /* target state */ );

#endif

