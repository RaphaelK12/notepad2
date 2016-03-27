// Lexer for Python.

#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "ILexer.h"
#include "Scintilla.h"
#include "SciLexer.h"

#include "WordList.h"
#include "CharacterSet.h"
#include "LexAccessor.h"
#include "Accessor.h"
#include "StyleContext.h"
#include "LexerModule.h"

#ifdef SCI_NAMESPACE
using namespace Scintilla;
#endif

#define		LEX_PY		32	// Python
#define		LEX_BOO		55	// Boo

/*static const char *const pythonWordListDesc[] = {
	"Keywords",
	"Type Keywords",
	"Built-in Constants",
	"Decorator",
	"Build-in Functions",
	"Attribute",
	"object Method"
	"global class",
	0
};*/

#define PY_DEF_CLASS 1
#define PY_DEF_FUNC	2
#define PY_DEF_ENUM	3	// Boo

static inline bool IsPyStringPrefix(int ch) {
    return ch == 'r' || ch == 'u' || ch == 'b' || ch == 'R' || ch == 'U' || ch == 'B';
}
static inline bool IsPyTripleStyle(int style) {
	return style == SCE_PY_TRIPLE_STRING1 || style == SCE_PY_TRIPLE_STRING2
		|| style == SCE_PY_TRIPLE_BYTES1 || style == SCE_PY_TRIPLE_BYTES2;
}
static inline bool IsPyStringStyle(int style) {
	return style == SCE_PY_STRING1 || style == SCE_PY_STRING2
		|| style == SCE_PY_BYTES1 || style == SCE_PY_BYTES2
		|| style == SCE_PY_RAW_STRING1 || style == SCE_PY_RAW_STRING2
		|| style == SCE_PY_RAW_BYTES1 || style == SCE_PY_RAW_BYTES2;
}
static void ColourisePyDoc(Sci_PositionU startPos, Sci_Position length, int initStyle, WordList *keywordLists[], Accessor &styler) {
	WordList &keywords = *keywordLists[0];
	WordList &keywords2 = *keywordLists[1];
	WordList &keywords_const = *keywordLists[2];
	//WordList &keywords4 = *keywordLists[3];
	WordList &keywords_func = *keywordLists[4];
	WordList &keywords_attr = *keywordLists[5];
	WordList &keywords_objm = *keywordLists[6];
	WordList &keywords_class = *keywordLists[7];

	int defType = 0;
	bool continuationLine = false;

	//const int lexType = styler.GetPropertyInt("lexer.lang.type", LEX_PY);
	StyleContext sc(startPos, length, initStyle, styler);

	for (; sc.More(); sc.Forward()) {
		if (sc.atLineStart) {
			if (IsPyTripleStyle(sc.state) || IsPyStringStyle(sc.state)) {
				sc.SetState(sc.state);
			}
			defType = 0;
		}

		// Determine if the current state should terminate.
		switch (sc.state) {
		case SCE_PY_OPERATOR:
			sc.SetState(SCE_PY_DEFAULT);
			break;
		case SCE_PY_NUMBER:
			if (!iswordstart(sc.ch)) {
				if ((sc.ch == '+' || sc.ch == '-') && (sc.chPrev == 'e' || sc.chPrev == 'E')) {
					sc.Forward();
				} else if (sc.ch == '.' && sc.chNext != '.') {
					sc.ForwardSetState(SCE_PY_DEFAULT);
				} else {
					sc.SetState(SCE_PY_DEFAULT);
				}
			}
			break;
		case SCE_PY_IDENTIFIER:
_label_identifier:
			if (!iswordstart(sc.ch)) {
				char s[128];
				sc.GetCurrent(s, sizeof(s));
				if (keywords.InList(s)) {
					sc.ChangeState(SCE_PY_WORD);
					if (strcmp(s, "def") == 0)
						defType = PY_DEF_FUNC;
					else if (strcmp(s, "class") == 0 || strcmp(s, "raise") == 0 || strcmp(s, "except") == 0)
						defType = PY_DEF_CLASS;
					//else if (strcmp(s, "enum") == 0)
					//	defType = PY_DEF_ENUM;
				} else if (keywords2.InList(s)) {
					sc.ChangeState(SCE_PY_WORD2);
				} else if (keywords_const.InList(s)) {
					sc.ChangeState(SCE_PY_BUILDIN_CONST);
				} else if (keywords_func.InListAbbreviated(s, '(')) {
					sc.ChangeState(SCE_PY_BUILDIN_FUNC);
				} else if (keywords_attr.InList(s)) {
					sc.ChangeState(SCE_PY_ATTR);
				} else if (keywords_objm.InList(s)) {
					sc.ChangeState(SCE_PY_OBJ_FUNC);
				} else if (defType == PY_DEF_CLASS) {
					defType = 0;
					sc.ChangeState(SCE_PY_CLASSNAME);
				} else if (defType == PY_DEF_FUNC) {
					defType = 0;
					sc.ChangeState(SCE_PY_DEFNAME);
				} else if (keywords_class.InList(s)) {
					defType = 0;
					sc.ChangeState(SCE_PY_CLASSNAME);
				} else if (LexGetNextChar(sc.currentPos, styler) == '(') {
					sc.ChangeState(SCE_PY_FUNCTION);
				}
				sc.SetState(SCE_PY_DEFAULT);
			}
			break;
		case SCE_PY_DECORATOR:
			if (!iswordchar(sc.ch))
				sc.SetState(SCE_PY_DEFAULT);
			break;

		case SCE_PY_COMMENTLINE:
			if (sc.atLineStart) {
				sc.SetState(SCE_PY_DEFAULT);
			}
			break;

		case SCE_PY_STRING1:
		case SCE_PY_BYTES1:
		case SCE_PY_RAW_STRING1:
		case SCE_PY_RAW_BYTES1:
			if (sc.atLineStart&& !continuationLine) {
				sc.SetState(SCE_PY_DEFAULT);
			} else if (sc.ch == '\\' && (sc.chNext == '\\' || sc.chNext == '\"' || sc.chNext == '\'')) {
				sc.Forward();
			} else if (sc.ch == '\'') {
				sc.ForwardSetState(SCE_PY_DEFAULT);
			}
			break;
		case SCE_PY_STRING2:
		case SCE_PY_BYTES2:
		case SCE_PY_RAW_STRING2:
		case SCE_PY_RAW_BYTES2:
			if (sc.atLineStart && !continuationLine) {
				sc.SetState(SCE_PY_DEFAULT);
			} else if (sc.ch == '\\' && (sc.chNext == '\\' || sc.chNext == '\"' || sc.chNext == '\'')) {
				sc.Forward();
			} else if (sc.ch == '\"') {
				sc.ForwardSetState(SCE_PY_DEFAULT);
			}
			break;
		case SCE_PY_TRIPLE_STRING1:
		case SCE_PY_TRIPLE_BYTES1:
			if (sc.ch == '\\') {
				sc.Forward();
			} else if (sc.Match("\'\'\'")) {
				sc.Forward(2);
				sc.ForwardSetState(SCE_PY_DEFAULT);
			}
			break;
		case SCE_PY_TRIPLE_STRING2:
		case SCE_PY_TRIPLE_BYTES2:
			if (sc.ch == '\\') {
				sc.Forward();
			} else if (sc.Match("\"\"\"")) {
				sc.Forward(2);
				sc.ForwardSetState(SCE_PY_DEFAULT);
			}
			break;
		}

		// Determine if a new state should be entered.
		if (sc.state == SCE_PY_DEFAULT) {
			if (sc.ch == '#') {
				sc.SetState(SCE_PY_COMMENTLINE);
			} else if (sc.Match("\'\'\'")) {
				sc.SetState(SCE_PY_TRIPLE_STRING1);
				sc.Forward(2);
			} else if (sc.Match("\"\"\"")) {
				sc.SetState(SCE_PY_TRIPLE_STRING2);
				sc.Forward(2);
			} else if (sc.ch == '\'') {
				sc.SetState(SCE_PY_STRING1);
			} else if (sc.ch == '\"') {
				sc.SetState(SCE_PY_STRING2);
			} else if (IsADigit(sc.ch) || (sc.ch == '.' && IsADigit(sc.chNext))) {
				sc.SetState(SCE_PY_NUMBER);
			} else if (IsPyStringPrefix(sc.ch)) {
				int offset = 0;
				bool is_raw = (sc.ch == 'r' || sc.ch == 'R');
				bool is_bytes = (sc.ch == 'b' || sc.ch == 'B');
				if (sc.chNext == '\"' || sc.chNext == '\'') {
					offset = 1;
				} else if (IsPyStringPrefix(sc.chNext) && (sc.GetRelative(2) == '\"' || sc.GetRelative(2) == '\'')) {
					offset = 2;
					is_bytes = !is_bytes && (sc.chNext == 'b' || sc.chNext == 'B');
					is_raw = !is_raw && (sc.chNext == 'r' || sc.chNext == 'R');
				}
				if (!offset) {
					sc.SetState(SCE_PY_IDENTIFIER);
				} else {
					sc.Forward(offset);
					if (sc.Match("\'\'\'")) {
						sc.ChangeState(is_bytes ? SCE_PY_TRIPLE_BYTES1 : SCE_PY_TRIPLE_STRING1);
						sc.Forward(2);
					} else if (sc.Match("\"\"\"")) {
						sc.ChangeState(is_bytes ? SCE_PY_TRIPLE_BYTES2 : SCE_PY_TRIPLE_STRING2);
						sc.Forward(2);
					} else if (sc.ch == '\'') {
						sc.ChangeState(is_raw ? (is_bytes ? SCE_PY_RAW_BYTES1 : SCE_PY_RAW_STRING1) : (is_bytes ? SCE_PY_BYTES1 : SCE_PY_STRING1));
					} else if (sc.ch == '\"') {
						sc.ChangeState(is_raw ? (is_bytes ? SCE_PY_RAW_BYTES2 : SCE_PY_RAW_STRING2) : (is_bytes ? SCE_PY_BYTES2 : SCE_PY_STRING2));
					}
				}
			} else if (iswordstart(sc.ch)) {
				sc.SetState(SCE_PY_IDENTIFIER);
			} else if (sc.ch == '@') {
				if (iswordstart(sc.chNext))
					sc.SetState(SCE_PY_OPERATOR);
				 else
					sc.SetState(SCE_PY_DECORATOR);
			} else if (isoperator(static_cast<char>(sc.ch)) || sc.ch == '`') {
				sc.SetState(SCE_PY_OPERATOR);
				if (defType > 0 && (sc.ch == '(' || sc.ch == ':'))
					defType = 0;
			}
		}

		// Handle line continuation generically.
		if (sc.ch == '\\') {
			if (sc.chNext == '\n' || sc.chNext == '\r') {
				sc.Forward();
				if (sc.ch == '\r' && sc.chNext == '\n') {
					sc.Forward();
				}
				continuationLine = true;
				continue;
			}
		}
		continuationLine = false;
	}

	if (sc.state == SCE_PY_IDENTIFIER)
		goto _label_identifier;

	sc.Complete();
}

#define IsCommentLine(line)		IsLexCommentLine(line, styler, MultiStyle(SCE_PY_COMMENTLINE, SCE_PY_COMMENTBLOCK))

static inline bool IsQuoteLine(Sci_Position line, Accessor &styler) {
	int style = styler.StyleAt(styler.LineStart(line));
	return IsPyTripleStyle(style);
}


static void FoldPyDoc(Sci_PositionU startPos, Sci_Position length, int, WordList *[], Accessor &styler) {
	if (styler.GetPropertyInt("fold") == 0)
		return;
	const Sci_Position maxPos = startPos + length;
	const Sci_Position maxLines = (maxPos == styler.Length()) ? styler.GetLine(maxPos) : styler.GetLine(maxPos - 1);	// Requested last line
	const Sci_Position docLines = styler.GetLine(styler.Length());	// Available last line

	// property fold.quotes.python
	//	This option enables folding multi-line quoted strings when using the Python lexer.
	const bool foldQuotes = styler.GetPropertyInt("fold.quotes.python", 1) != 0;

	const bool foldCompact = styler.GetPropertyInt("fold.compact") != 0;

	// Backtrack to previous non-blank line so we can determine indent level
	// for any white space lines (needed esp. within triple quoted strings)
	// and so we can fix any preceding fold level (which is why we go back
	// at least one line in all cases)
	int spaceFlags = 0;
	Sci_Position lineCurrent = styler.GetLine(startPos);
	int indentCurrent = Accessor::LexIndentAmount(styler, lineCurrent, &spaceFlags, NULL);
	while (lineCurrent > 0) {
		lineCurrent--;
		indentCurrent = Accessor::LexIndentAmount(styler, lineCurrent, &spaceFlags, NULL);
		if (!(indentCurrent & SC_FOLDLEVELWHITEFLAG) && (!IsCommentLine(lineCurrent)) &&
			(!IsQuoteLine(lineCurrent, styler)))
			break;
	}
	int indentCurrentLevel = indentCurrent & SC_FOLDLEVELNUMBERMASK;

	// Set up initial loop state
	startPos = styler.LineStart(lineCurrent);
	int prev_state = SCE_PY_DEFAULT & 31;
	if (lineCurrent >= 1)
		prev_state = styler.StyleAt(startPos - 1) & 31;
	int prevQuote = foldQuotes && (
		prev_state == SCE_PY_TRIPLE_STRING1 || prev_state == SCE_PY_TRIPLE_STRING2 ||
		prev_state == SCE_PY_TRIPLE_BYTES1 || prev_state == SCE_PY_TRIPLE_BYTES2);

	// Process all characters to end of requested range or end of any triple quote
	//that hangs over the end of the range.  Cap processing in all cases
	// to end of document (in case of unclosed quote at end).
	while ((lineCurrent <= docLines) && ((lineCurrent <= maxLines) || prevQuote)) {

		// Gather info
		int lev = indentCurrent;
		int lineNext = lineCurrent + 1;
		int indentNext = indentCurrent;
		int quote = false;
		if (lineNext <= docLines) {
			// Information about next line is only available if not at end of document
			indentNext = Accessor::LexIndentAmount(styler, lineNext, &spaceFlags, NULL);
			Sci_Position lookAtPos = (styler.LineStart(lineNext) == styler.Length()) ? styler.Length() - 1 : styler.LineStart(lineNext);
			int style = styler.StyleAt(lookAtPos) & 31;
			quote = foldQuotes && (
				style == SCE_PY_TRIPLE_STRING1 || style == SCE_PY_TRIPLE_STRING2 ||
				style == SCE_PY_TRIPLE_BYTES1 || style == SCE_PY_TRIPLE_BYTES2);
		}
		const int quote_start = (quote && !prevQuote);
		const int quote_continue = (quote && prevQuote);
		if (!quote || !prevQuote)
			indentCurrentLevel = indentCurrent & SC_FOLDLEVELNUMBERMASK;
		if (quote)
			indentNext = indentCurrentLevel;
		if (indentNext & SC_FOLDLEVELWHITEFLAG)
			indentNext = SC_FOLDLEVELWHITEFLAG | indentCurrentLevel;

		if (quote_start) {
			// Place fold point at start of triple quoted string
			lev |= SC_FOLDLEVELHEADERFLAG;
		} else if (quote_continue || prevQuote) {
			// Add level to rest of lines in the string
			lev = lev + 1;
		}

		// Skip past any blank lines for next indent level info; we skip also
		// comments (all comments, not just those starting in column 0)
		// which effectively folds them into surrounding code rather
		// than screwing up folding.

		while (!quote && (lineNext < docLines) && ((indentNext & SC_FOLDLEVELWHITEFLAG) ||
			(lineNext <= docLines && IsCommentLine(lineNext)))) {
			lineNext++;
			indentNext = Accessor::LexIndentAmount(styler, lineNext, &spaceFlags, NULL);
		}

		const int levelAfterComments = indentNext & SC_FOLDLEVELNUMBERMASK;
		const int levelBeforeComments = Maximum(indentCurrentLevel,levelAfterComments);

		// Now set all the indent levels on the lines we skipped
		// Do this from end to start.  Once we encounter one line
		// which is indented more than the line after the end of
		// the comment-block, use the level of the block before

		int skipLine = lineNext;
		int skipLevel = levelAfterComments;

		while (--skipLine > lineCurrent) {
			int skipLineIndent = Accessor::LexIndentAmount(styler, skipLine, &spaceFlags, NULL);

			if (foldCompact) {
				if ((skipLineIndent & SC_FOLDLEVELNUMBERMASK) > levelAfterComments)
					skipLevel = levelBeforeComments;

				int whiteFlag = skipLineIndent & SC_FOLDLEVELWHITEFLAG;

				styler.SetLevel(skipLine, skipLevel | whiteFlag);
			} else {
				if ((skipLineIndent & SC_FOLDLEVELNUMBERMASK) > levelAfterComments &&
					!(skipLineIndent & SC_FOLDLEVELWHITEFLAG) &&
					!IsCommentLine(skipLine))
					skipLevel = levelBeforeComments;

				styler.SetLevel(skipLine, skipLevel);
			}
		}

		// Set fold header on non-quote line
		if (!quote && !(indentCurrent & SC_FOLDLEVELWHITEFLAG)) {
			if ((indentCurrent & SC_FOLDLEVELNUMBERMASK) < (indentNext & SC_FOLDLEVELNUMBERMASK))
				lev |= SC_FOLDLEVELHEADERFLAG;
		}

		// Keep track of triple quote state of previous line
		prevQuote = quote;

		// Set fold level for this line and move to next line
		styler.SetLevel(lineCurrent, foldCompact ? lev : lev & ~SC_FOLDLEVELWHITEFLAG);
		indentCurrent = indentNext;
		lineCurrent = lineNext;
	}

	// NOTE: Cannot set level of last line here because indentCurrent doesn't have
	// header flag set; the loop above is crafted to take care of this case!
	//styler.SetLevel(lineCurrent, indentCurrent);
}

LexerModule lmPython(SCLEX_PYTHON, ColourisePyDoc, "python", FoldPyDoc);

