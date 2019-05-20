/******************************************************************************
*
*
* Notepad2
*
* SciCall.h
*   Inline wrappers for Scintilla API calls, arranged in the order and grouping
*   in which they appear in the Scintilla documentation.
*
* The use of these inline wrapper functions with declared types will ensure
* that we get the benefit of the compiler's type checking.
*
* Actual type for `int` based on SciTE's ScintillaCall.h.
*
*
******************************************************************************/

#ifndef NOTEPAD2_SCICALL_H_
#define NOTEPAD2_SCICALL_H_
#include "compiler.h"
#include "Scintilla.h"

#if defined(__cplusplus) && !NP2_FORCE_COMPILE_C_AS_CPP
extern "C" HANDLE g_hScintilla;
#else
extern HANDLE g_hScintilla;
#endif

NP2_inline void InitScintillaHandle(HWND hwnd) {
	g_hScintilla = (HANDLE)SendMessage(hwnd, SCI_GETDIRECTPOINTER, 0, 0);
}

#if defined(__cplusplus)
extern "C"
#endif
LRESULT WINAPI Scintilla_DirectFunction(HANDLE handle, UINT msg, WPARAM wParam, LPARAM lParam);
#define SciCall(m, w, l)	Scintilla_DirectFunction(g_hScintilla, (m), (w), (l))

typedef Sci_Position Sci_Line;

NP2_inline Sci_Position min_pos(Sci_Position x, Sci_Position y) {
	return (x < y) ? x : y;
}

NP2_inline Sci_Position max_pos(Sci_Position x, Sci_Position y) {
	return (x > y) ? x : y;
}

// Text retrieval and modification

NP2_inline Sci_Position SciCall_GetText(Sci_Position length, char *text) {
	return SciCall(SCI_GETTEXT, length, (LPARAM)text);
}

NP2_inline void SciCall_SetSavePoint(void) {
	SciCall(SCI_SETSAVEPOINT, 0, 0);
}

NP2_inline Sci_Position SciCall_GetLine(Sci_Line line, char *text) {
	return SciCall(SCI_GETLINE, line, (LPARAM)text);
}

NP2_inline void SciCall_ReplaceSel(const char *text) {
	SciCall(SCI_REPLACESEL, 0, (LPARAM)text);
}

NP2_inline void SciCall_SetReadOnly(BOOL readOnly) {
	SciCall(SCI_SETREADONLY, readOnly, 0);
}

NP2_inline BOOL SciCall_GetReadOnly(void) {
	return (BOOL)SciCall(SCI_GETREADONLY, 0, 0);
}

NP2_inline Sci_Position SciCall_GetTextRange(struct Sci_TextRange *tr) {
	return SciCall(SCI_GETTEXTRANGE, 0, (LPARAM)tr);
}

NP2_inline void SciCall_AddText(Sci_Position length, const char *text) {
	SciCall(SCI_ADDTEXT, length, (LPARAM)text);
}

NP2_inline void SciCall_AppendText(Sci_Position length, const char *text) {
	SciCall(SCI_APPENDTEXT, length, (LPARAM)text);
}

NP2_inline void SciCall_InsertText(Sci_Position pos, const char *text) {
	SciCall(SCI_INSERTTEXT, pos, (LPARAM)text);
}

NP2_inline void SciCall_ClearAll(void) {
	SciCall(SCI_CLEARALL, 0, 0);
}

NP2_inline void SciCall_ClearDocumentStyle(void) {
	SciCall(SCI_CLEARDOCUMENTSTYLE, 0, 0);
}

NP2_inline int SciCall_GetCharAt(Sci_Position position) {
	return (int)SciCall(SCI_GETCHARAT, position, 0);
}

NP2_inline int SciCall_GetStyleAt(Sci_Position position) {
	return (int)SciCall(SCI_GETSTYLEAT, position, 0);
}

// Searching and replacing

// Overtype

NP2_inline BOOL SciCall_GetOvertype(void) {
	return (BOOL)SciCall(SCI_GETOVERTYPE, 0, 0);
}

// Cut, copy and paste

NP2_inline void SciCall_Cut(BOOL asBinary) {
	SciCall(SCI_CUT, asBinary, 0);
}

NP2_inline void SciCall_Copy(BOOL asBinary) {
	SciCall(SCI_COPY, asBinary, 0);
}

NP2_inline void SciCall_Paste(BOOL asBinary) {
	SciCall(SCI_PASTE, asBinary, 0);
}

NP2_inline void SciCall_Clear(void) {
	SciCall(SCI_CLEAR, 0, 0);
}

NP2_inline BOOL SciCall_CanPaste(void) {
	return (BOOL)SciCall(SCI_CANPASTE, 0, 0);
}

NP2_inline void SciCall_CopyRange(Sci_Position start, Sci_Position end) {
	SciCall(SCI_COPYRANGE, start, end);
}

NP2_inline void SciCall_SetPasteConvertEndings(BOOL convert) {
	SciCall(SCI_SETPASTECONVERTENDINGS, convert, 0);
}

// Undo and Redo

NP2_inline void SciCall_Undo(void) {
	SciCall(SCI_UNDO, 0, 0);
}

NP2_inline BOOL SciCall_CanUndo(void) {
	return (BOOL)SciCall(SCI_CANUNDO, 0, 0);
}

NP2_inline void SciCall_EmptyUndoBuffer(void) {
	SciCall(SCI_EMPTYUNDOBUFFER, 0, 0);
}

NP2_inline void SciCall_Redo(void) {
	SciCall(SCI_REDO, 0, 0);
}

NP2_inline BOOL SciCall_CanRedo(void) {
	return (BOOL)SciCall(SCI_CANREDO, 0, 0);
}

NP2_inline void SciCall_SetUndoCollection(BOOL collectUndo) {
	SciCall(SCI_SETUNDOCOLLECTION, collectUndo, 0);
}

NP2_inline void SciCall_BeginUndoAction(void) {
	SciCall(SCI_BEGINUNDOACTION, 0, 0);
}

NP2_inline void SciCall_EndUndoAction(void) {
	SciCall(SCI_ENDUNDOACTION, 0, 0);
}

// Selection and information

NP2_inline Sci_Position SciCall_GetLength(void) {
	return SciCall(SCI_GETLENGTH, 0, 0);
}

NP2_inline Sci_Line SciCall_GetLineCount(void) {
	return SciCall(SCI_GETLINECOUNT, 0, 0);
}

NP2_inline void SciCall_SetSel(Sci_Position anchor, Sci_Position caret) {
	SciCall(SCI_SETSEL, anchor, caret);
}

NP2_inline void SciCall_DocumentStart(void) {
	SciCall(SCI_DOCUMENTSTART, 0, 0);
}

NP2_inline void SciCall_DocumentEnd(void) {
	SciCall(SCI_DOCUMENTEND, 0, 0);
}

NP2_inline void SciCall_GotoPos(Sci_Position caret) {
	SciCall(SCI_GOTOPOS, caret, 0);
}

NP2_inline void SciCall_GotoLine(Sci_Line line) {
	SciCall(SCI_GOTOLINE, line, 0);
}

NP2_inline void SciCall_SetCurrentPos(Sci_Position caret) {
	SciCall(SCI_SETCURRENTPOS, caret, 0);
}

NP2_inline Sci_Position SciCall_GetCurrentPos(void) {
	return SciCall(SCI_GETCURRENTPOS, 0, 0);
}

NP2_inline void SciCall_SetAnchor(Sci_Position anchor) {
	SciCall(SCI_SETANCHOR, anchor, 0);
}

NP2_inline Sci_Position SciCall_GetAnchor(void) {
	return SciCall(SCI_GETANCHOR, 0, 0);
}

NP2_inline Sci_Position SciCall_PositionBefore(Sci_Position position) {
	return SciCall(SCI_POSITIONBEFORE, position, 0);
}

NP2_inline Sci_Position SciCall_PositionAfter(Sci_Position position) {
	return SciCall(SCI_POSITIONAFTER, position, 0);
}

NP2_inline Sci_Position SciCall_GetColumn(Sci_Position position) {
	return SciCall(SCI_GETCOLUMN, position, 0);
}

NP2_inline Sci_Line SciCall_LineFromPosition(Sci_Position position) {
	return SciCall(SCI_LINEFROMPOSITION, position, 0);
}

NP2_inline Sci_Position SciCall_PositionFromLine(Sci_Line line) {
	return SciCall(SCI_POSITIONFROMLINE, line, 0);
}

NP2_inline int SciCall_GetCharacterAndWidth(Sci_Position position, Sci_Position *width) {
	return (int)SciCall(SCI_GETCHARACTERANDWIDTH, position, (LPARAM)width);
}

NP2_inline int SciCall_GetCharacterAt(Sci_Position position) {
	return (int)SciCall(SCI_GETCHARACTERANDWIDTH, position, 0);
}

NP2_inline BOOL SciCall_IsAutoCompletionWordCharacter(int ch) {
	return (BOOL)SciCall(SCI_ISAUTOCOMPLETIONWORDCHARACTER, ch, 0);
}

NP2_inline Sci_Position SciCall_WordStartPosition(Sci_Position position, BOOL onlyWordCharacters) {
	return SciCall(SCI_WORDSTARTPOSITION, position, onlyWordCharacters);
}

NP2_inline Sci_Position SciCall_WordEndPosition(Sci_Position position, BOOL onlyWordCharacters) {
	return SciCall(SCI_WORDENDPOSITION, position, onlyWordCharacters);
}

NP2_inline Sci_Position SciCall_GetLineEndPosition(Sci_Line line) {
	return SciCall(SCI_GETLINEENDPOSITION, line, 0);
}

NP2_inline Sci_Position SciCall_GetLineLength(Sci_Line line) {
	return SciCall(SCI_LINELENGTH, line, 0);
}

NP2_inline Sci_Position SciCall_GetSelTextLength(void) {
	return SciCall(SCI_GETSELTEXT, 0, 0);
}

NP2_inline Sci_Position SciCall_GetSelText(char *buffer) {
	return SciCall(SCI_GETSELTEXT, 0, (LPARAM)buffer);
}

NP2_inline Sci_Position SciCall_CountCharacters(Sci_Position start, Sci_Position end) {
	return SciCall(SCI_COUNTCHARACTERS, start, end);
}

NP2_inline Sci_Position SciCall_GetSelectionStart(void) {
	return SciCall(SCI_GETSELECTIONSTART, 0, 0);
}

NP2_inline Sci_Position SciCall_GetSelectionEnd(void) {
	return SciCall(SCI_GETSELECTIONEND, 0, 0);
}

NP2_inline Sci_Line EditGetSelectedLineCount(void) {
	const Sci_Line iLineStart = SciCall_LineFromPosition(SciCall_GetSelectionStart());
	const Sci_Line iLineEnd = SciCall_LineFromPosition(SciCall_GetSelectionEnd());
	return iLineEnd - iLineStart + 1;
}

NP2_inline int SciCall_GetSelectionMode(void) {
	return (int)SciCall(SCI_GETSELECTIONMODE, 0, 0);
}

NP2_inline BOOL SciCall_IsRectangleSelection(void) {
	return SciCall(SCI_GETSELECTIONMODE, 0, 0) == SC_SEL_RECTANGLE;
}

NP2_inline BOOL SciCall_IsSelectionEmpty(void) {
	return (BOOL)SciCall(SCI_GETSELECTIONEMPTY, 0, 0);
}

NP2_inline Sci_Position SciCall_FindText(int searchFlags, struct Sci_TextToFind *ft) {
	return SciCall(SCI_FINDTEXT, searchFlags, (LPARAM)ft);
}

NP2_inline void SciCall_SetTargetRange(Sci_Position start, Sci_Position end) {
	SciCall(SCI_SETTARGETRANGE, start, end);
}

NP2_inline void SciCall_SetSearchFlags(int searchFlags) {
	SciCall(SCI_SETSEARCHFLAGS, searchFlags, 0);
}

NP2_inline Sci_Position SciCall_SearchInTarget(Sci_Position length, const char *text) {
	return SciCall(SCI_SEARCHINTARGET, length, (LPARAM)text);
}

// White space

NP2_inline void SciCall_SetViewWS(int viewWS) {
	SciCall(SCI_SETVIEWWS, viewWS, 0);
}

NP2_inline void SciCall_SetWhitespaceFore(BOOL useSetting, COLORREF fore) {
	SciCall(SCI_SETWHITESPACEFORE, useSetting, fore);
}

NP2_inline void SciCall_SetWhitespaceBack(BOOL useSetting, COLORREF back) {
	SciCall(SCI_SETWHITESPACEBACK, useSetting, back);
}

NP2_inline void SciCall_SetWhitespaceSize(int size) {
	SciCall(SCI_SETWHITESPACESIZE, size, 0);
}

NP2_inline void SciCall_SetExtraAscent(int extraAscent) {
	SciCall(SCI_SETEXTRAASCENT, extraAscent, 0);
}

NP2_inline void SciCall_SetExtraDescent(int extraDescent) {
	SciCall(SCI_SETEXTRADESCENT, extraDescent, 0);
}

// Cursor

NP2_inline void SciCall_SetCursor(int cursorType) {
	SciCall(SCI_SETCURSOR, cursorType, 0);
}

NP2_inline void BeginWaitCursor(void) {
	SciCall_SetCursor(SC_CURSORWAIT);
}

NP2_inline void EndWaitCursor(void) {
	POINT pt;
	SciCall_SetCursor(SC_CURSORNORMAL);
	GetCursorPos(&pt);
	SetCursorPos(pt.x, pt.y);
}

// Caret

NP2_inline void SciCall_SetCaretFore(COLORREF fore) {
	SciCall(SCI_SETCARETFORE, fore, 0);
}

NP2_inline void SciCall_SetCaretStyle(int caretStyle) {
	SciCall(SCI_SETCARETSTYLE, caretStyle, 0);
}

NP2_inline void SciCall_SetCaretWidth(int pixelWidth) {
	SciCall(SCI_SETCARETWIDTH, pixelWidth, 0);
}

NP2_inline void SciCall_SetCaretPeriod(int periodMilliseconds) {
	SciCall(SCI_SETCARETPERIOD, periodMilliseconds, 0);
}

NP2_inline void SciCall_SetCaretLineVisible(BOOL show) {
	SciCall(SCI_SETCARETLINEVISIBLE, show, 0);
}

NP2_inline void SciCall_SetCaretLineVisibleAlways(BOOL alwaysVisible) {
	SciCall(SCI_SETCARETLINEVISIBLEALWAYS, alwaysVisible, 0);
}

NP2_inline void SciCall_SetCaretLineBack(COLORREF back) {
	SciCall(SCI_SETCARETLINEBACK, back, 0);
}

NP2_inline void SciCall_SetCaretLineBackAlpha(int alpha) {
	SciCall(SCI_SETCARETLINEBACKALPHA, alpha, 0);
}

NP2_inline void SciCall_SetCaretLineFrame(int width) {
	SciCall(SCI_SETCARETLINEFRAME, width, 0);
}

NP2_inline void SciCall_ScrollCaret(void) {
	SciCall(SCI_SCROLLCARET, 0, 0);
}

NP2_inline void SciCall_ChooseCaretX(void) {
	SciCall(SCI_CHOOSECARETX, 0, 0);
}

NP2_inline void SciCall_SetXCaretPolicy(int caretPolicy, int caretSlop) {
	SciCall(SCI_SETXCARETPOLICY, caretPolicy, caretSlop);
}

NP2_inline void SciCall_SetYCaretPolicy(int caretPolicy, int caretSlop) {
	SciCall(SCI_SETYCARETPOLICY, caretPolicy, caretSlop);
}

NP2_inline void SciCall_SetCaretSticky(int useCaretStickyBehaviour) {
	SciCall(SCI_SETCARETSTICKY, useCaretStickyBehaviour, 0);
}

// Selection

NP2_inline void SciCall_SetSelFore(BOOL useSetting, COLORREF fore) {
	SciCall(SCI_SETSELFORE, useSetting, fore);
}

NP2_inline void SciCall_SetSelBack(BOOL useSetting, COLORREF back) {
	SciCall(SCI_SETSELBACK, useSetting, back);
}

NP2_inline void SciCall_SetSelAlpha(int alpha) {
	SciCall(SCI_SETSELALPHA, alpha, 0);
}

NP2_inline void SciCall_SetSelEOLFilled(BOOL filled) {
	SciCall(SCI_SETSELEOLFILLED, filled, 0);
}

NP2_inline void SciCall_SetMultipleSelection(BOOL multipleSelection) {
	SciCall(SCI_SETMULTIPLESELECTION, multipleSelection, 0);
}

NP2_inline void SciCall_SetAdditionalSelectionTyping(BOOL additionalSelectionTyping) {
	SciCall(SCI_SETADDITIONALSELECTIONTYPING, additionalSelectionTyping, 0);
}

NP2_inline void SciCall_SetVirtualSpaceOptions(int virtualSpaceOptions) {
	SciCall(SCI_SETVIRTUALSPACEOPTIONS, virtualSpaceOptions, 0);
}

NP2_inline void SciCall_SetAdditionalSelFore(COLORREF fore) {
	SciCall(SCI_SETADDITIONALSELFORE, fore, 0);
}

NP2_inline void SciCall_SetAdditionalSelBack(COLORREF back) {
	SciCall(SCI_SETADDITIONALSELBACK, back, 0);
}

NP2_inline void SciCall_SetAdditionalSelAlpha(int alpha) {
	SciCall(SCI_SETADDITIONALSELALPHA, alpha, 0);
}

NP2_inline void SciCall_SetAdditionalCaretFore(COLORREF fore) {
	SciCall(SCI_SETADDITIONALCARETFORE, fore, 0);
}

NP2_inline void SciCall_SetAdditionalCaretsBlink(BOOL additionalCaretsBlink) {
	SciCall(SCI_SETADDITIONALCARETSBLINK, additionalCaretsBlink, 0);
}

NP2_inline void SciCall_SetAdditionalCaretsVisible(BOOL additionalCaretsVisible) {
	SciCall(SCI_SETADDITIONALCARETSVISIBLE, additionalCaretsVisible, 0);
}

// Line endings

NP2_inline void SciCall_SetEOLMode(int eolMode) {
	SciCall(SCI_SETEOLMODE, eolMode, 0);
}

NP2_inline int SciCall_GetEOLMode(void) {
	return (int)SciCall(SCI_GETEOLMODE, 0, 0);
}

NP2_inline void SciCall_ConvertEOLs(int eolMode) {
	SciCall(SCI_CONVERTEOLS, eolMode, 0);
}

NP2_inline void SciCall_SetViewEOL(BOOL visible) {
	SciCall(SCI_SETVIEWEOL, visible, 0);
}

// Styling

NP2_inline Sci_Position SciCall_GetEndStyled(void) {
	return SciCall(SCI_GETENDSTYLED, 0, 0);
}

NP2_inline void SciCall_SetIdleStyling(int idleStyling) {
	SciCall(SCI_SETIDLESTYLING, idleStyling, 0);
}

// Style definition

NP2_inline void SciCall_StyleResetDefault(void) {
	SciCall(SCI_STYLERESETDEFAULT, 0, 0);
}

NP2_inline void SciCall_StyleClearAll(void) {
	SciCall(SCI_STYLECLEARALL, 0, 0);
}

NP2_inline void SciCall_StyleSetFont(int style, const char *fontName) {
	SciCall(SCI_STYLESETFONT, style, (LPARAM)fontName);
}

NP2_inline void SciCall_StyleSetSizeFractional(int style, int sizeHundredthPoints) {
	SciCall(SCI_STYLESETSIZEFRACTIONAL, style, sizeHundredthPoints);
}

NP2_inline void SciCall_StyleSetWeight(int style, int weight) {
	SciCall(SCI_STYLESETWEIGHT, style, weight);
}

NP2_inline void SciCall_StyleSetItalic(int style, BOOL italic) {
	SciCall(SCI_STYLESETITALIC, style, italic);
}

NP2_inline void SciCall_StyleSetUnderline(int style, BOOL underline) {
	SciCall(SCI_STYLESETUNDERLINE, style, underline);
}

NP2_inline void SciCall_StyleSetStrike(int style, BOOL strike) {
	SciCall(SCI_STYLESETSTRIKE, style, strike);
}

NP2_inline void SciCall_StyleSetFore(int style, COLORREF fore) {
	SciCall(SCI_STYLESETFORE, style, fore);
}

NP2_inline COLORREF SciCall_StyleGetFore(int style) {
	return (COLORREF)SciCall(SCI_STYLEGETFORE, style, 0);
}

NP2_inline void SciCall_StyleSetBack(int style, COLORREF back) {
	SciCall(SCI_STYLESETBACK, style, back);
}

NP2_inline COLORREF SciCall_StyleGetBack(int style) {
	return (COLORREF)SciCall(SCI_STYLEGETBACK, style, 0);
}

NP2_inline void SciCall_StyleSetEOLFilled(int style, BOOL eolFilled) {
	SciCall(SCI_STYLESETEOLFILLED, style, eolFilled);
}

NP2_inline void SciCall_StyleSetCharacterSet(int style, int characterSet) {
	SciCall(SCI_STYLESETCHARACTERSET, style, characterSet);
}

NP2_inline void SciCall_StyleSetCase(int style, int caseVisible) {
	SciCall(SCI_STYLESETCASE, style, caseVisible);
}

// Margins

NP2_inline void SciCall_SetMarginType(int margin, int marginType) {
	SciCall(SCI_SETMARGINTYPEN, margin, marginType);
}

NP2_inline void SciCall_SetMarginWidth(int margin, int pixelWidth) {
	SciCall(SCI_SETMARGINWIDTHN, margin, pixelWidth);
}

NP2_inline int SciCall_GetMarginWidth(int margin) {
	return (int)SciCall(SCI_GETMARGINWIDTHN, margin, 0);
}

NP2_inline int SciCall_TextWidth(int style, const char *text) {
	return (int)SciCall(SCI_TEXTWIDTH, style, (LPARAM)text);
}

NP2_inline void SciCall_SetMarginMask(int margin, int mask) {
	SciCall(SCI_SETMARGINMASKN, margin, mask);
}

NP2_inline void SciCall_SetMarginSensitive(int margin, BOOL sensitive) {
	SciCall(SCI_SETMARGINSENSITIVEN, margin, sensitive);
}

NP2_inline void SciCall_SetFoldMarginColour(BOOL useSetting, COLORREF back) {
	SciCall(SCI_SETFOLDMARGINCOLOUR, useSetting, back);
}

NP2_inline void SciCall_SetFoldMarginHiColour(BOOL useSetting, COLORREF fore) {
	SciCall(SCI_SETFOLDMARGINHICOLOUR, useSetting, fore);
}

NP2_inline void SciCall_SetMarginOptions(int marginOptions) {
	SciCall(SCI_SETMARGINOPTIONS, marginOptions, 0);
}

// Other settings

NP2_inline void SciCall_SetCodePage(UINT codePage) {
	SciCall(SCI_SETCODEPAGE, codePage, 0);
}

NP2_inline UINT SciCall_GetCodePage(void) {
	return (UINT)SciCall(SCI_GETCODEPAGE, 0, 0);
}

NP2_inline void SciCall_SetBufferedDraw(BOOL buffered) {
	SciCall(SCI_SETBUFFEREDDRAW, buffered, 0);
}

NP2_inline void SciCall_SetTechnology(int technology) {
	SciCall(SCI_SETTECHNOLOGY, technology, 0);
}

NP2_inline int SciCall_GetTechnology(void) {
	return (int)SciCall(SCI_GETTECHNOLOGY, 0, 0);
}

NP2_inline void SciCall_SetBidirectional(int bidirectional) {
	SciCall(SCI_SETBIDIRECTIONAL, bidirectional, 0);
}

NP2_inline int SciCall_GetBidirectional(void) {
	return (int)SciCall(SCI_GETBIDIRECTIONAL, 0, 0);
}

NP2_inline void SciCall_SetFontQuality(int fontQuality) {
	SciCall(SCI_SETFONTQUALITY, fontQuality, 0);
}

NP2_inline void SciCall_SetFontLocale(const char *localeName) {
	SciCall(SCI_SETFONTLOCALE, 0, (LPARAM)localeName);
}

NP2_inline void SciCall_SetIMEInteraction(int imeInteraction) {
	SciCall(SCI_SETIMEINTERACTION, imeInteraction, 0);
}

NP2_inline void SciCall_SetInlineIMEUseBlockCaret(BOOL useBlockCaret) {
	SciCall(SCI_SETINLINEIMEUSEBLOCKCARET, useBlockCaret, 0);
}

// Tabs and Indentation Guides

NP2_inline void SciCall_SetTabWidth(int tabWidth) {
	SciCall(SCI_SETTABWIDTH, tabWidth, 0);
}

NP2_inline int SciCall_GetTabWidth(void) {
	return (int)SciCall(SCI_GETTABWIDTH, 0, 0);
}

NP2_inline void SciCall_SetUseTabs(BOOL useTabs) {
	SciCall(SCI_SETUSETABS, useTabs, 0);
}

NP2_inline void SciCall_SetIndent(int indentSize) {
	SciCall(SCI_SETINDENT, indentSize, 0);
}

NP2_inline void SciCall_SetTabIndents(BOOL tabIndents) {
	SciCall(SCI_SETTABINDENTS, tabIndents, 0);
}

NP2_inline void SciCall_SetBackSpaceUnIndents(BOOL bsUnIndents) {
	SciCall(SCI_SETBACKSPACEUNINDENTS, bsUnIndents, 0);
}

NP2_inline void SciCall_SetLineIndentation(Sci_Line line, int indentation) {
	SciCall(SCI_SETLINEINDENTATION, line, indentation);
}

NP2_inline int SciCall_GetLineIndentation(Sci_Line line) {
	return (int)SciCall(SCI_GETLINEINDENTATION, line, 0);
}

NP2_inline Sci_Position SciCall_GetLineIndentPosition(Sci_Line line) {
	return SciCall(SCI_GETLINEINDENTPOSITION, line, 0);
}

NP2_inline void SciCall_SetIndentationGuides(int indentView) {
	SciCall(SCI_SETINDENTATIONGUIDES, indentView, 0);
}

NP2_inline int SciCall_GetIndentationGuides(void) {
	return (int)SciCall(SCI_GETINDENTATIONGUIDES, 0, 0);
}

// Markers

NP2_inline void SciCall_MarkerDefine(int markerNumber, int markerSymbol) {
	SciCall(SCI_MARKERDEFINE, markerNumber, markerSymbol);
}

NP2_inline void SciCall_MarkerDefinePixmap(int markerNumber, const char *pixmap) {
	SciCall(SCI_MARKERDEFINEPIXMAP, markerNumber, (LPARAM)pixmap);
}

NP2_inline int SciCall_MarkerSymbolDefined(int markerNumber) {
	return (int)SciCall(SCI_MARKERSYMBOLDEFINED, markerNumber, 0);
}

NP2_inline void SciCall_MarkerSetFore(int markerNumber, COLORREF fore) {
	SciCall(SCI_MARKERSETFORE, markerNumber, fore);
}

NP2_inline void SciCall_MarkerSetBack(int markerNumber, COLORREF back) {
	SciCall(SCI_MARKERSETBACK, markerNumber, back);
}

NP2_inline void SciCall_MarkerSetAlpha(int markerNumber, int alpha) {
	SciCall(SCI_MARKERSETALPHA, markerNumber, alpha);
}

NP2_inline void SciCall_MarkerEnableHighlight(BOOL enabled) {
	SciCall(SCI_MARKERENABLEHIGHLIGHT, enabled, 0);
}

// Indicators

NP2_inline void SciCall_IndicSetStyle(int indicator, int indicatorStyle) {
	SciCall(SCI_INDICSETSTYLE, indicator, indicatorStyle);
}

NP2_inline void SciCall_IndicSetFore(int indicator, COLORREF fore) {
	SciCall(SCI_INDICSETFORE, indicator, fore);
}

NP2_inline void SciCall_IndicSetAlpha(int indicator, int alpha) {
	SciCall(SCI_INDICSETALPHA, indicator, alpha);
}

NP2_inline void SciCall_SetIndicatorCurrent(int indicator) {
	SciCall(SCI_SETINDICATORCURRENT, indicator, 0);
}

NP2_inline void SciCall_IndicatorClearRange(Sci_Position start, Sci_Position length) {
	SciCall(SCI_INDICATORCLEARRANGE, start, length);
}

NP2_inline void SciCall_IndicatorFillRange(Sci_Position start, Sci_Position length) {
	SciCall(SCI_INDICATORFILLRANGE, start, length);
}

// Printing

NP2_inline Sci_Position SciCall_FormatRange(BOOL draw, struct Sci_RangeToFormat *fr) {
	return SciCall(SCI_FORMATRANGE, draw, (LPARAM)fr);
}

NP2_inline void SciCall_SetPrintMagnification(int magnification) {
	SciCall(SCI_SETPRINTMAGNIFICATION, magnification, 0);
}

NP2_inline void SciCall_SetPrintColourMode(int mode) {
	SciCall(SCI_SETPRINTCOLOURMODE, mode, 0);
}

// Folding

NP2_inline BOOL SciCall_GetLineVisible(Sci_Line line) {
	return (BOOL)SciCall(SCI_GETLINEVISIBLE, line, 0);
}

NP2_inline int SciCall_GetFoldLevel(Sci_Line line) {
	return (int)SciCall(SCI_GETFOLDLEVEL, line, 0);
}

NP2_inline void SciCall_SetFoldFlags(Sci_Line flags) {
	SciCall(SCI_SETFOLDFLAGS, flags, 0);
}

NP2_inline Sci_Line SciCall_GetLastChild(Sci_Line line) {
	return SciCall(SCI_GETLASTCHILD, line, -1);
}

NP2_inline Sci_Line SciCall_GetFoldParent(Sci_Line line) {
	return SciCall(SCI_GETFOLDPARENT, line, 0);
}

NP2_inline BOOL SciCall_GetFoldExpanded(Sci_Line line) {
	return (BOOL)SciCall(SCI_GETFOLDEXPANDED, line, 0);
}

NP2_inline void SciCall_ToggleFold(Sci_Line line) {
	SciCall(SCI_TOGGLEFOLD, line, 0);
}

NP2_inline void SciCall_ToggleFoldShowText(Sci_Line line, const char *text) {
	SciCall(SCI_TOGGLEFOLDSHOWTEXT, line, (LPARAM)text);
}

NP2_inline void SciCall_SetDefaultFoldDisplayText(const char *text) {
	SciCall(SCI_SETDEFAULTFOLDDISPLAYTEXT, 0, (LPARAM)text);
}

NP2_inline void SciCall_FoldDisplayTextSetStyle(int style) {
	SciCall(SCI_FOLDDISPLAYTEXTSETSTYLE, style, 0);
}

NP2_inline void SciCall_EnsureVisible(Sci_Line line) {
	SciCall(SCI_ENSUREVISIBLE, line, 0);
}

// Line wrapping

NP2_inline void SciCall_SetWrapMode(int wrapMode) {
	SciCall(SCI_SETWRAPMODE, wrapMode, 0);
}

NP2_inline void SciCall_SetWrapVisualFlags(int wrapVisualFlags) {
	SciCall(SCI_SETWRAPVISUALFLAGS, wrapVisualFlags, 0);
}

NP2_inline void SciCall_SetWrapVisualFlagsLocation(int wrapVisualFlagsLocation) {
	SciCall(SCI_SETWRAPVISUALFLAGSLOCATION, wrapVisualFlagsLocation, 0);
}

NP2_inline void SciCall_SetWrapIndentMode(int wrapIndentMode) {
	SciCall(SCI_SETWRAPINDENTMODE, wrapIndentMode, 0);
}

NP2_inline void SciCall_SetWrapStartIndent(int indent) {
	SciCall(SCI_SETWRAPSTARTINDENT, indent, 0);
}

NP2_inline void SciCall_SetLayoutCache(int cacheMode) {
	SciCall(SCI_SETLAYOUTCACHE, cacheMode, 0);
}

NP2_inline void SciCall_LinesSplit(int pixelWidth) {
	SciCall(SCI_LINESSPLIT, pixelWidth, 0);
}

NP2_inline void SciCall_LinesJoin(void) {
	SciCall(SCI_LINESJOIN, 0, 0);
}

// Zooming

NP2_inline void SciCall_SetZoom(int percent) {
	SciCall(SCI_SETZOOM, percent, 0);
}

NP2_inline int SciCall_GetZoom(void) {
	return (int)SciCall(SCI_GETZOOM, 0, 0);
}

NP2_inline void SciCall_ZoomIn(void) {
	SciCall(SCI_ZOOMIN, 0, 0);
}

NP2_inline void SciCall_ZoomOut(void) {
	SciCall(SCI_ZOOMOUT, 0, 0);
}

// Long lines

NP2_inline void SciCall_SetEdgeMode(int edgeMode) {
	SciCall(SCI_SETEDGEMODE, edgeMode, 0);
}

NP2_inline int SciCall_GetEdgeMode(void) {
	return (int)SciCall(SCI_GETEDGEMODE, 0, 0);
}

NP2_inline void SciCall_SetEdgeColumn(int column) {
	SciCall(SCI_SETEDGECOLUMN, column, 0);
}

NP2_inline void SciCall_SetEdgeColour(COLORREF edgeColour) {
	SciCall(SCI_SETEDGECOLOUR, edgeColour, 0);
}

// Lexer

NP2_inline void SciCall_SetLexer(int lexer) {
	SciCall(SCI_SETLEXER, lexer, 0);
}

NP2_inline void SciCall_Colourise(Sci_Position start, Sci_Position end) {
	SciCall(SCI_COLOURISE, start, end);
}

NP2_inline void SciCall_SetProperty(const char *key, const char *value) {
	SciCall(SCI_SETPROPERTY, (WPARAM)key, (LPARAM)value);
}

NP2_inline void SciCall_SetKeywords(int keywordSet, const char *keywords) {
	SciCall(SCI_SETKEYWORDS, keywordSet, (LPARAM)keywords);
}

#endif // NOTEPAD2_SCICALL_H_

// End of SciCall.h
