#include "rewrite.def"

#ifdef INCLUDED_LIBAUTOMA_ENGINE_H

/* Pre-Load Symbol Wrapper */
#  ifndef LibAutoma_Engine
#    define LibAutoma_Engine struct _( LibAutoma( Engine ) )
LibAutoma( Engine );
#  endif

#else
#  define INCLUDED_LIBAUTOMA_ENGINE_H
#  include <stdbool.h>
#  include <stdio.h>
#  include "state.h"
#  include "rule.h"

/* Relplace Symbol Wrapper */
#  ifdef LibAutoma_Engine
#    undef LibAutoma_Engine
#  endif

typedef struct _( LibAutoma( StateNode ) ) {
	LibAutoma( State ) *Ref;
	struct _( LibAutoma( StateNode ) ) *Next;
} LibAutoma( StateNode );

typedef struct _( LibAutoma( RuleNode ) ) {
	LibAutoma( Rule ) Rule;
	LibAutoma( OnRule ) Action;
	struct _( LibAutoma( RuleNode ) ) *Next;
} LibAutoma( RuleNode );

typedef struct _( LibAutoma( SourceNode ) ) {
	char Type;
	union {
		struct { char *orig; char *pos; size_t len; } cstr;
		FILE *file;
	} Source;
	struct _( LibAutoma( SourceNode ) ) *Next;
} LibAutoma( SourceNode );

typedef struct _( LibAutoma( Engine ) ) {
	LibAutoma( StateNode ) *ActiveState;
	LibAutoma( StateNode ) *FinalState;
	LibAutoma( RuleNode ) *RuleChain;
	LibAutoma( SourceNode ) *SourceStack;
	bool Run;
} LibAutoma( Engine );
	
/* Function Identity Wrappers */	
#  define LibAutoma_StateNode( routine ) LibAutoma_StateNode_ ## routine
#  define _LibAutoma_StateNode( routine ) _LibAutoma_StateNode_ ## routine
#  define LibAutoma_RuleNode( routine ) LibAutoma_RuleNode_ ## routine
#  define _LibAutoma_RuleNode( routine ) _LibAutoma_RuleNode_ ## routine
#  define LibAutoma_SourceNode( routine ) LibAutoma_SourceNode_ ## routine
#  define _LibAutoma_SourceNode( routine ) _LibAutoma_SourceNode_ ## routine
#  define LibAutoma_Engine( routine ) LibAutoma_Engine_ ## routine
#  define _LibAutoma_Engine( routine ) _LibAutoma_Engine_ ## routine

/* Source Types */
#  define LibAutoma_SourceType( ID ) LibAutoma_SourceType_ ## ID
#  define LibAutoma_SourceType_STRING 's'
#  define LibAutoma_SourceType_FILE 'f'

/* MEMO: Ideally use to build FILO chains */
LibAutoma( StateNode ) *LibAutoma( StateNode )( Create )( 
	LibAutoma( State ) * /* Referenced State */,
	LibAutoma( StateNode ) * /* Next StateNode */);

/* MEMO: Effectivly performs `StateNode = StateNode->Next` without leaking memory */
void LibAutoma( StateNode )( Destroy )(
	LibAutoma( StateNode ) ** /* Target StateNode */);

/* WARN: NewStateNode != OldStateNode && NewStateNode->Next == OldStateNode->Next */
LibAutoma( StateNode ) *LibAutoma( StateNode )( Copy )( 
	LibAutoma( StateNode ) * /* Target StateNode */);

/* NOTE: Copies entire chain */
LibAutoma( StateNode ) *LibAutoma( StateNode )( CopyChain )(
	LibAutoma( StateNode ) * /* First StateNode */);

LibAutoma( State ) *LibAutoma( StateNode )( GetState )(
	const LibAutoma( StateNode ) * /* Target StateNode */);

LibAutoma( StateNode ) *LibAutoma( StateNode )( GetNext )(
	const LibAutoma( StateNode ) * /* Target StateNode */);

long LibAutoma( StateNode )( Count )(
	LibAutoma( StateNode ) * /* Target StateNode */);


/* MEMO: Ideally use to create FILO chains */
LibAutoma( RuleNode ) *LibAutoma( RuleNode )( Create )(
	LibAutoma( Rule ) * /* Target Rule */,
	LibAutoma( OnRule ) * /* Target Action */,
	LibAutoma( RuleNode ) * /* Next RuleNode */);

/* MEMO: As above, performs `RuleNode = RuleNode->Next` */
void LibAutoma( RuleNode )( Destroy )(
	LibAutoma( RuleNode ) ** /* Target RuleNode */ );

/* WARN: NewRuleNode != OldRuleNode && NewRuleNode->Next == OldRuleNode->Next */
LibAutoma( RuleNode ) *LibAutoma( RuleNode )( Copy )(
	LibAutoma( RuleNode ) * /* Target RuleNode */);

/* NOTE: Copies entire chain */
LibAutoma( RuleNode ) *LibAutoma( RuleNode )( CopyChain )(
	LibAutoma( RuleNode ) * /* First RuleNode */);

bool LibAutoma( RuleNode )( Exec )( 
	LibAutoma( RuleNode ) * /* Rule Being Invoked */,
	LibAutoma( Engine ) * /* Calling Engine */,
	const LibAutoma( State ) * /* Current State */);


bool LibAutoma( SourceNode )( PushString )(
	LibAutoma( SourceNode ) ** /* Source Stack */,
	const char * /* Byte Array */,
	const size_t /* Array Length */); /*< Returns True on Success */

bool LibAutoma( SourceNode )( PushFile )(
	LibAutoma( SourceNode ) ** /* Source Stack */,
	const char * /* File Path */); /*< Returns True on Success */

void LibAutoma( SourceNode )( PopNode )(
	LibAutoma( SourceNode ) ** /* Source Stack */);

bool LibAutoma( SourceNode )( IsGood )(
	LibAutoma( SourceNode ) ** /* Source Stack */);

unsigned char LibAutoma( SourceNode )( GetChar )(
	LibAutoma( SourceNode ) ** /* Source Stack */);


void LibAutoma( Engine )( Init )( LibAutoma( Engine ) * /* Target Engine */ );
void LibAutoma( Engine )( ReInit )( LibAutoma( Engine ) * /* Target Engine */ );
void LibAutoma( Engine )( AddActiveState )( 
	LibAutoma( Engine ) * /* Target Engine */, 
	LibAutoma( State )  * /* Target State */);
void LibAutoma( Engine )( ClearActiveStates )( LibAutoma( Engine ) * /* Target Engine */ );
void LibAutoma( Engine )( AddRule )( LibAutoma( Engine ) * /* Target Engine */, 
	LibAutoma( Rule ) * /* Rule Function */,
	LibAutoma( OnRule ) * /* Action Routine */);
void LibAutoma( Engine )( ClearRules )( LibAutoma( Engine ) * /* Target Engine */ );

void LibAutoma( Engine )( AddFinalState )(
	LibAutoma( Engine ) * /* Target Engine */,
	LibAutoma( State ) * /* Target State */);
LibAutoma( State ) *LibAutoma( Engine )( GetFinalState )(
	LibAutoma( Engine ) * /* Target Engine */);
long LibAutoma( Engine )( PopFinalState )( 
	LibAutoma( Engine ) * /* Target Engine */); /*< Returns the number of final states remaining */
long LibAutoma( Engine )( DelFinalState )(
	LibAutoma( Engine ) * /* Target Enigne */,
	const LibAutoma( State ) * /* Target State */); 
/*^^ Delets all instances of Target State in Engine->FinalState list; 
 *    Returns the number of final states remaining */
void LibAutoma( Engine )( ClearFinalStates )(
	LibAutoma( Engine ) * /* Target Engine */);

bool LibAutoma( Engine )( ReadString )( LibAutoma( Engine ) * /* Target Engine */, const char * /* Byte Array */, const size_t /* Array Length */);
bool LibAutoma( Engine )( ReadFile )( LibAutoma( Engine ) * /* Target Engine */, const char * /* File Path */ );
bool LibAutoma( Engine )( NextChar )( LibAutoma( Engine ) * /* Target Engine */ ); /*< Returns True on success */
void LibAutoma( Engine )( Exec )( LibAutoma( Engine ) * /* Target Engine */ );
/*^ Execution Continues as long as there is data to read and active states available */
void LibAutoma( Engine )( Stop )( LibAutoma( Engine ) * /* Target Engine */ ); /* Stop Engine durring Exec */

#endif

