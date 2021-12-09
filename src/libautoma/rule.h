#ifndef INCLUDED_LIBAUTOMA_RULE_H
#  define INLCUDED_LIBAUTOMA_RULE_H
#  include <stdbool.h>
#  include "rewrite.def"
#  include "state.h"
#  include "engine.h"

typedef bool (*f_libautoma_rule)( const LibAutoma_Engine*, const LibAutoma_State* );
typedef void (*f_libautoma_onrule)( const LibAutoma_Engine*, const LibAutoma_State* );

#  define LibAutoma_Rule( name ) LibAutoma( Rule ) # _ # name
#  define LibAutoma_Rule_Header( name ) bool LibAutoma_Rule( name ) # ( const LibAutoma_Engine* engine, const LibAutoma_State* state )

#  define LibAutoma_OnRule( name ) LibAutoma( OnRule ) # _ # name
#  define LibAutoma_OnRule_Header( name ) void LibAutoma_OnRule( name ) # ( const LibAutoma_Engine* engine, const LibAutoma_State* state )

#endif

