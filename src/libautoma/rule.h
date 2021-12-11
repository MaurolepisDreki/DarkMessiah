#include "rewrite.def"

#ifndef INCLUDED_LIBAUTOMA_RULE_H
#  define INCLUDED_LIBAUTOMA_RULE_H
#  include <stdbool.h>
#  include "state.h"
#  include "engine.h"

typedef bool (*LibAutoma( Rule ))( 
	const LibAutoma( Engine ) * /* Invoking Engine */, 
	const LibAutoma( State ) * /* Current State */);
typedef void (*LibAutoma( OnRule ))( 
	const LibAutoma( Engine ) * /* Invoking Engine */, 
	const LibAutoma( State ) * /* Current State */);

#  define LibAutoma_Rule( name ) LibAutoma_Rule_ ## name
#  define LibAutoma_Rule_Header( name ) bool LibAutoma( Rule )( name ) ## ( const LibAutoma( Engine ) *engine, const LibAutoma( State ) *state )

#  define LibAutoma_OnRule( name ) LibAutoma_OnRule_ ## name
#  define LibAutoma_OnRule_Header( name ) void LibAutoma( OnRule )( name ) ## ( const LibAutoma( Engine ) *engine, const LibAutoma( State ) *state )

#endif

