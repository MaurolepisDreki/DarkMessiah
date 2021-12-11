#include <stdlib.h>
#include "rewrite.def"
#include "engine.h"

void LibAutoma( Engine )( Init )( LibAutoma( Engine ) *engine ) {
	engine->ActiveState = NULL;
	engine->FinalState = NULL;
	engine->RuleChain = NULL;
	engine->SourceStack = NULL;
	engine->Run = false;
}

void LibAutoma( Engine )( ReInit )( LibAutoma( Engine ) *engine ) {
	LibAutoma( Engine )( Stop )( engine );
	LibAutoma( Engine )( ClearActiveStates )( engine );
	LibAutoma( Engine )( ClearFinalStates )( engine );
	LibAutoma( Engine )( ClearRules )( engine );

	while( engine->SourceStack != NULL ) 
		LibAutoma( SourceNode )( PopNode )( &engine->SourceStack );
}

void LibAutoma( Engine )( AddActiveState )( LibAutoma( Engine ) *engine, LibAutoma( State ) *state ) {
	engine->ActiveState = LibAutoma( StateNode )( Create )( state, engine->ActiveState );
}

void LibAutoma( Engine )( ClearActiveStates )( LibAutoma( Engine ) *engine ) {
	while( engine->ActiveState != NULL )
		LibAutoma( StateNode )( Destroy )( &engine->ActiveState );
}

void LibAutoma( Engine )( AddRule )( LibAutoma( Engine ) *engine, LibAutoma( Rule ) *rule, LibAutoma( OnRule ) *action ) {
	engine->RuleChain = LibAutoma( RuleNode )( Create )( rule, action, engine->RuleChain );
}

void LibAutoma( Engine )( ClearRules )( LibAutoma( Engine ) *engine ) {
	while( engine->RuleChain != NULL ) 
		LibAutoma( RuleNode )( Destroy )( &engine->RuleChain );
}
 
void LibAutoma( Engine )( AddFinalState )( LibAutoma( Engine ) *engine, LibAutoma( State ) *state ) {
	engine->FinalState = LibAutoma( StateNode )( Create )( state, engine->FinalState );
}

LibAutoma( State ) *LibAutoma( Engine )( GetFinalState )( LibAutoma( Engine ) *engine ) {
	return LibAutoma( StateNode )( GetState )( engine->FinalState );
}

long LibAutoma( Engine )( PopFinalState )( LibAutoma( Engine ) *engine ) {
	LibAutoma( StateNode )( Destroy )( &engine->FinalState );
	return LibAutoma( StateNode )( Count )( engine->FinalState );
}

long LibAutoma( Engine )( DelFinalState )( LibAutoma( Engine ) *engine, const LibAutoma( State ) *state ) {
	register LibAutoma( StateNode ) **metaptr;
	/*^^ Points to pointer links between nodes instead of the nodes themselves;  DO NOT FUCK THIS UP!! */

	metaptr = &engine->FinalState;
	while( *metaptr != NULL ) {
		if( LibAutoma( StateNode )( GetState )( *metaptr ) == state ) {
			LibAutoma( StateNode )( Destroy )( metaptr );
		} else {
			metaptr = &(*metaptr)->Next;
		}
	}

	return LibAutoma( StateNode )( Count )( engine->FinalState );
}

void LibAutoma( Engine )( ClearFinalStates )( LibAutoma( Engine ) *engine ) {
	while( engine->FinalState != NULL )
		LibAutoma( StateNode )( Destroy )( &engine->FinalState );
}

bool LibAutoma( Engine )( ReadString )( LibAutoma( Engine ) *engine, const char *str, const size_t len ){
	return LibAutoma( SourceNode )( PushString )( &engine->SourceStack, str, len );
}

bool LibAutoma( Engine )( ReadFile )( LibAutoma( Engine ) *engine, const char *path ){
	return LibAutoma( SourceNode )( PushFile )( &engine->SourceStack, path );
}

bool LibAutoma( Engine )( NextChar )( LibAutoma( Engine ) *engine ) {
	register unsigned int stateID;
	LibAutoma( StateNode ) *PrevState;

	while( engine->SourceStack != NULL && !LibAutoma( SourceNode )( IsGood )( &engine->SourceStack ) )
		LibAutoma( SourceNode )( PopNode )( &engine->SourceStack );

	if( engine->SourceStack != NULL ) {
		stateID = (unsigned int) LibAutoma( SourceNode )( GetChar )( &engine->SourceStack );
		
		/* First Char */
		if( engine->ActiveState == NULL ) {
			LibAutoma( Engine )( AddActiveState )( engine, 
				LibAutoma( State )( Create )( stateID, NULL, NULL, NULL ) );
		} else {
			PrevState = engine->ActiveState;
			engine->ActiveState = NULL;
			while( PrevState != NULL ) {
				LibAutoma( Engine )( AddActiveState )( engine, 
					LibAutoma( State )( Create )( stateID, 
						LibAutoma( StateNode )( GetState )( PrevState ), 
						NULL, NULL ) );
				LibAutoma( StateNode )( Destroy )( &PrevState );
			}
		}
		
		return true;
	} else return false;
}

void LibAutoma( Engine )( Exec )( LibAutoma( Engine ) *engine ) {
	if( engine->Run ) return;
	else engine->Run = true;

	LibAutoma( StateNode ) *PrevState = NULL;
	LibAutoma( StateNode ) *PauseState = NULL;
	LibAutoma( StateNode ) *tmpState;
	register LibAutoma( State ) *CurrentState;
	register LibAutoma( RuleNode ) *CurrentRule;
	register bool RulePass;

	/* Init Engine */
	if( engine->ActiveState == NULL && !LibAutoma( Engine )( NextChar )( engine ) ) {
		engine->Run = false;
		return;
	}

	/* Run Engine */
	while( engine->ActiveState != NULL && engine->Run ) {
		PrevState = engine->ActiveState;
		engine->ActiveState = NULL;
		while( PrevState != NULL  && engine->Run) {
			CurrentState = LibAutoma( StateNode )( GetState )( PrevState );
			RulePass = false;
			CurrentRule = engine->RuleChain;
			while( CurrentRule != NULL && engine->Run ) {
				RulePass |= LibAutoma( RuleNode )( Exec )( CurrentRule, engine, CurrentState );
				CurrentRule = CurrentRule->Next;
			}
 			if(!RulePass) {
				/* Preserve State via Pause 
				 *   At this point, no rules match this state, so pause until more data is available */
				tmpState = PrevState;
				PrevState = tmpState->Next;
				tmpState->Next = PauseState;
				PauseState = tmpState;
			} else {
				/* Drop State
				 *   If another state was meant to be attained, it was placed in Active|Final by a rule's action */
				LibAutoma( StateNode )( Destroy )( &PrevState );
			}
		}
		if( engine->ActiveState == NULL ) {
			/* No More Active States,
			 *   Unpause States and attempt to get more data */
			engine->ActiveState = PauseState;
			PauseState = NULL;
			engine->Run = LibAutoma( Engine )( NextChar );
		}
	}

	/* Cleanup
	 *   If Engine is Stopped Mid-Exec, unprocessed and waiting states will be lost as an end-state is assumed to be reached (good or bad end is irrelevent) */
	while( PrevState != NULL )
		LibAutoma( StateNode )( Destroy )( &PrevState );
	while( PauseState != NULL )
		LibAutoma( StateNode )( Destroy )( &PauseState );
	
	/*   If Engine stopped naturally, as a result of having no more active states (or data underflow), switch off */
	engine->Run = false;
}

void LibAutoma( Engine )( Stop )( LibAutoma( Engine ) *engine ) {
	/* Switch Engine off
    *   WARN: DATA LOSS IS A GAREENTEE.  MEMORY LEAK IS NOT. */
	engine->Run = false;
}

