#ifndef __TYPESET_H__
#define __TYPESET_H__

// size_t
#include <stddef.h>
// uint8_t
#include <stdint.h>

/// The first character represented in the typeset.
extern const char TYPESET_FIRST_CHAR;
/// The last character represented in the typeset.
extern const char TYPESET_LAST_CHAR;
/// A list of column offsets per character.
extern const size_t TYPESET_OFFSETS[];
/// An 8 pixel tall bitmap of the typeset. Every byte is a column in the bitmap.
extern const uint8_t TYPESET_BITMAP[];

#endif