#ifndef INCLUDED_JOURNAL_H
#  define INCLUDED_JOURNAL_h
#  include <stdarg.h>
#  include <stdint.h>
#  include <stdio.h>

/* Internal Name Hasher
 *  RETURN: ELF64 Hash of `cstr'
 *  cstr: C-String to hash
 */
typedef uint64_t ELF64_Hash;
ELF64_Hash _Journal_ELF64( char *str );

/* Internal Logging Levels */
typedef uint8_t Journal_Level;
#  define Journal_Level_INHERIT 0x80
#  define Journal_Level_TRACE   0x40
#  define Journal_Level_DEBUG   0x20
#  define Journal_Level_STATUS  0x10
#  define Journal_Level_NOTICE  0x08
#  define Journal_Level_WARNING 0x04
#  define Journal_Level_ERROR   0x02
#  define Journal_Level_FATAL   0x01
#  define Journal_Level_NONE    0x00
const char *Journal_Level_GetName( const Journal_Level );

/* Internal Unit Registry Schema Objects */
typedef struct _Journal_Unit {
	struct _Journal_Unit *parent;
	ELF64_Hash hash;
	char *string;
	Journal_Level level;
} Journal_Unit;

typedef struct _Journal_Unit_ListNode {
	struct _Journal_Unit_ListNode *next;
	struct _Journal_Unit *unit;
} Journal_Unit_ListNode;

typedef struct _Journal_Unit_MapNode {
	struct _Journal_Unit_MapNode *next;
	struct _Journal_Unit_ListNode *list;
} Journal_Unit_MapNode;

/* Get/Create Internal Reference for Component (by given name)
 *  RETURN: reference to LibJournal_Unit from register
 *  cstr: Unit Name as C-String
 *  parent: Reference to parent Unit
 */
const Journal_Unit *Journal_GetUnit( const char *cstr, const Journal_Unit *parent );

/* Get/Create Interal Reference for Component (by given name)
 *   A wrapper for LibJournal_GetUnit
 *  RETURN: reference to LibJournal_Unit from register
 *  cstr: Unit Name as C-String
 *  ...: Continuing Unit Names as C-Strings
 */
const Journal_Unit *Journal_GetUnit_Full( const char *cstr, ... );

/* Set Logger Level for Unit 
 *  unit: Reference to Unit
 *  level: Journaling Level of Unit
 */
void Journal_Unit_SetLevel( const Journal_Unit *unit, const Journal_Level level );

/* Internal File Registry Schema Objects */
typedef struct _Journal_FILE_Node {
	char *path;
	ELF64_Hash hash;
	FILE *file;
} Journal_FILE_NODE;

/* Set Files to Log */

/* Print Message to Log from Unit */
int Journal_Write( const Journal_Unit *unit, const Journal_Level level, const char *message, ...);

/* Print Wrappers */

#endif

