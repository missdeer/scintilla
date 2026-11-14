/** @file testCharacterType.cxx
 ** Unit Tests for Scintilla internal data structures
 **/

#include <cstring>

#include <string_view>
#include <vector>
#include <optional>
#include <algorithm>
#include <memory>
#include <ostream>
#include <iostream>

#include "Debugging.h"

#include "CharacterType.h"

#include "catch.hpp"

using namespace Scintilla::Internal;

// Test CharacterType.

TEST_CASE("CharacterTypeTest") {

	SECTION("ValueFromHexPair") {
		REQUIRE(ValueFromHexPair("1a") == 0x1a);
		REQUIRE(ValueFromHexPair("1A") == 0x1a);
		REQUIRE(ValueFromHexPair("1A3") == 0x1a);
		REQUIRE(ValueFromHexPair("1X") == -1);
		REQUIRE(ValueFromHexPair("1") == -1);
		REQUIRE(ValueFromHexPair("") == -1);
	}

	SECTION("ByteFromHexPair") {
		REQUIRE(ByteFromHexPair("1a") == 0x1a);
		REQUIRE(ByteFromHexPair("1A") == 0x1a);
		REQUIRE(ByteFromHexPair("1A3") == 0x1a);
		REQUIRE(ByteFromHexPair("1X") == 0);
		REQUIRE(ByteFromHexPair("1") == 0);
		REQUIRE(ByteFromHexPair("") == 0);
	}

}
