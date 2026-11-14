// Scintilla source code edit control
/** @file CharacterType.cxx
 ** Tests for character type and case-insensitive comparisons.
 **/
// Copyright 1998-2010 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#include <cstdlib>
#include <cassert>

#include "CharacterType.h"

using namespace Scintilla::Internal;

namespace Scintilla::Internal {

int CompareCaseInsensitive(const char *a, const char *b) noexcept {
	while (*a && *b) {
		if (*a != *b) {
			const char upperA = MakeUpperCase(*a);
			const char upperB = MakeUpperCase(*b);
			if (upperA != upperB)
				return upperA - upperB;
		}
		a++;
		b++;
	}
	// Either *a or *b is nul
	return *a - *b;
}

int CompareNCaseInsensitive(const char *a, const char *b, size_t len) noexcept {
	while (*a && *b && len) {
		if (*a != *b) {
			const char upperA = MakeUpperCase(*a);
			const char upperB = MakeUpperCase(*b);
			if (upperA != upperB)
				return upperA - upperB;
		}
		a++;
		b++;
		len--;
	}
	if (len == 0)
		return 0;
	else
		// Either *a or *b is nul
		return *a - *b;
}

// Return -1 on failure
constexpr int ValueFromHex(const char ch) noexcept {
	constexpr int decimal = 10;
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	if (ch >= 'A' && ch <= 'F')
		return ch - 'A' + decimal;
	if (ch >= 'a' && ch <= 'f')
		return ch - 'a' + decimal;
	return -1;
}

// Return -1 on failure
int ValueFromHexPair(const char *cp) noexcept {
	constexpr int hexBase = 16;
	if (const int hex0 = ValueFromHex(cp[0]); hex0 >= 0) {
		if (const int hex1 = ValueFromHex(cp[1]); hex1 >= 0) {
			return (hex0 * hexBase) + hex1;
		}
	}
	return -1;
}

// Return 0 on failure
int ByteFromHexPair(const char *cp) noexcept {
	const int value = ValueFromHexPair(cp);
	return (value < 0) ? 0 : value;
}

}
