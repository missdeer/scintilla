/** @file testSelection.cxx
 ** Unit Tests for Scintilla internal data structures
 **/

#include <cstdint>

#include <stdexcept>
#include <string_view>
#include <vector>

#include "Debugging.h"

#include "Position.h"
#include "Selection.h"

#include "catch.hpp"

using namespace Scintilla;
using namespace Scintilla::Internal;

// Test Selection.

namespace {

constexpr SelectionPosition invalid;
constexpr SelectionPosition zero(0);
constexpr SelectionRange rangeInvalid;
constexpr SelectionRange rangeZero(0);

}

TEST_CASE("SelectionPosition") {

	SECTION("SelectionPosition") {
		SelectionPosition sel;
		REQUIRE(sel.Position() == Sci::invalidPosition);
		REQUIRE(sel.VirtualSpace() == 0);
		REQUIRE(!sel.IsValid());
		REQUIRE(sel.VirtualSpace() == 0);

		REQUIRE(sel == invalid);
		REQUIRE(sel != zero);
		sel.Reset();
		REQUIRE(sel != invalid);
		REQUIRE(sel == zero);
	}

	SECTION("Comparison") {
		constexpr SelectionPosition sel(2,3);
		REQUIRE(sel > invalid);
		REQUIRE(sel > zero);
		REQUIRE(sel >= zero);
		REQUIRE(zero < sel);
		REQUIRE(zero <= sel);

		SelectionPosition virtuous(0, 4);
		REQUIRE(virtuous > zero);
		REQUIRE(virtuous >= zero);
		REQUIRE(zero < virtuous);
		REQUIRE(zero <= virtuous);

		REQUIRE(virtuous.Position() == 0);
		REQUIRE(virtuous.VirtualSpace() == 4);

		virtuous.SetPosition(1);	// Also resets virtualSpace
		REQUIRE(virtuous.Position() == 1);
		REQUIRE(virtuous.VirtualSpace() == 0);
		virtuous.SetVirtualSpace(3);	// Does not reset position
		REQUIRE(virtuous.Position() == 1);
		REQUIRE(virtuous.VirtualSpace() == 3);
	}

	SECTION("Add") {
		SelectionPosition sel(2,3);
		sel.Add(1);
		REQUIRE(sel.Position() == 3);
		REQUIRE(sel.VirtualSpace() == 3);
		sel.AddVirtualSpace(2);
		REQUIRE(sel.Position() == 3);
		REQUIRE(sel.VirtualSpace() == 5);
	}

	SECTION("MoveForInsertDelete") {
		// There are multiple details implemented in MoveForInsertDelete that are supposed to
		// move selections in a way that appears to be natural to a user.

		SelectionPosition sel(2,3);
		sel.MoveForInsertDelete(true, 0,1, false);
		REQUIRE(sel == SelectionPosition(3,3));

		// Converts a virtual space to real space
		sel.MoveForInsertDelete(true, 3,1, false);
		REQUIRE(sel == SelectionPosition(4,2));

		// Deletion at position clears virtual space
		sel.MoveForInsertDelete(false, 4,1, false);
		REQUIRE(sel == SelectionPosition(4,0));

		sel.MoveForInsertDelete(false, 3,1, false);
		REQUIRE(sel == SelectionPosition(3,0));

		// Insert at position with and without move for equal
		sel.MoveForInsertDelete(true, 3, 1, false);
		REQUIRE(sel == SelectionPosition(3, 0));
		sel.MoveForInsertDelete(true, 3, 1, true);
		REQUIRE(sel == SelectionPosition(4, 0));

		// Deletion over the position moves to start of deletion
		sel.MoveForInsertDelete(false, 2, 5, false);
		REQUIRE(sel == SelectionPosition(2, 0));
	}

}

TEST_CASE("SelectionSegment") {

	SECTION("SelectionSegment") {
		SelectionSegment ss;
		REQUIRE(ss.start == invalid);
		REQUIRE(ss.end == invalid);
	}

}

TEST_CASE("SelectionRange") {

	SECTION("SelectionRange") {
		SelectionRange sr;
		REQUIRE(sr.anchor == invalid);
		REQUIRE(sr.caret == invalid);
	}

}

TEST_CASE("Selection") {

	SECTION("Selection") {
		Selection sel;
		
		REQUIRE(sel.selType == Selection::SelTypes::stream);
		REQUIRE(!sel.IsRectangular());
		REQUIRE(sel.Count() == 1);
		REQUIRE(sel.Main() == 0);

		REQUIRE(sel.Range(0) == rangeZero);
		REQUIRE(sel.RangeMain() == rangeZero);
		REQUIRE(sel.Rectangular() == rangeInvalid);
		REQUIRE(sel.Empty());
	}

}
