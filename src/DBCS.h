// Scintilla source code edit control
/** @file DBCS.h
 ** Functions to handle DBCS double byte encodings like Shift-JIS.
 **/
// Copyright 2017 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#ifndef DBCS_H
#define DBCS_H

namespace Scintilla::Internal {

constexpr int cp932 = 932;
constexpr int cp936 = 936;
constexpr int cp949 = 949;
constexpr int cp950 = 950;
constexpr int cp1361 = 1361;

constexpr bool IsDBCSCodePage(int codePage) noexcept {
	return codePage == cp932
	       || codePage == cp936
	       || codePage == cp949
	       || codePage == cp950
	       || codePage == cp1361;
}

bool DBCSIsLeadByte(int codePage, char ch) noexcept;
bool IsDBCSValidSingleByte(int codePage, int ch) noexcept;

}

#endif
