// Scintilla source code edit control
/** @file Style.cxx
 ** Defines the font and colour style for a class of text.
 **/
// Copyright 1998-2001 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#include <cstdint>

#include <stdexcept>
#include <utility>
#include <compare>
#include <string_view>
#include <vector>
#include <optional>
#include <memory>

#include "ScintillaTypes.h"

#include "Debugging.h"
#include "Geometry.h"
#include "Platform.h"

#include "Style.h"

using namespace Scintilla;
using namespace Scintilla::Internal;

namespace {

// noexcept Platform::DefaultFontSize
int DefaultFontSize() noexcept {
	try {
		return Platform::DefaultFontSize();
	} catch (...) {
		// Should never happen
		return Style::sensibleFontSize;
	}
}

}

Style::Style(const char *fontName_) noexcept :
	FontSpecification(fontName_, DefaultFontSize() * FontSizeMultiplier) {
}

void Style::Copy(std::shared_ptr<Font> font_, const FontMeasurements &fm_) noexcept {
	font = std::move(font_);
	static_cast<FontMeasurements &>(*this) = fm_;
}
