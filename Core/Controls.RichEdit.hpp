#pragma once
#include "Controls.Control.hpp"
#include <Richedit.h>
#include <RichOle.h>

namespace Controls
{
	class RichEdit : public Control
	{
	public:
		//Constants
		constexpr static inline auto ClassName = MSFTEDIT_CLASS;

		enum class Styles
		{
			DisableNoScroll = ES_DISABLENOSCROLL,
			NoCallOleInit = ES_EX_NOCALLOLEINIT,
			NoIME = ES_NOIME,
			NoOleDragDrop = ES_NOOLEDRAGDROP,
			SaveSel = ES_SAVESEL,
			SelectionBar = ES_SELECTIONBAR,
			SelfIME = ES_SELFIME,
			Sunken = ES_SUNKEN,
			Verttical = ES_VERTICAL,
			AutoHScroll = ES_AUTOHSCROLL,
			AutoVScroll = ES_AUTOVSCROLL,
			Center = ES_CENTER,
			Left = ES_LEFT,
			MultiLine = ES_MULTILINE,
			NoHideSel = ES_NOHIDESEL,
			Number = ES_NUMBER,
			Password = ES_PASSWORD,
			ReadOnly = ES_READONLY,
			Right = ES_RIGHT,
			WantReturn = ES_WANTRETURN
		};
		
		RichEdit(HWND parent, int x, int y, int width, int height, DWORD style)
		{
			m_hwnd = CreateWindowEx(
				0,
				ClassName,
				L"",
				style | WS_VISIBLE | WS_CHILD,
				x, y, width, height,
				parent,
				NULL,
				GetModuleHandle(NULL),
				NULL
			);
		}

		enum class DetectionKind
		{
			DisableMixedLGC = AURL_DISABLEMIXEDLGC,
			EnableDriveLetters = AURL_ENABLEDRIVELETTERS,
			EnableEAUrls = AURL_ENABLEEAURLS,
			EnableEmailAddr = AURL_ENABLEEAURLS,
			EnableTelNo = AURL_ENABLETELNO,
			EnableUrl = AURL_ENABLEURL
		};

		auto autoUrlDetect(DetectionKind kind, LPCTSTR schemes = nullptr)
		{
			return sendMessage(EM_AUTOURLDETECT, static_cast<WPARAM>(kind), reinterpret_cast<LPARAM>(schemes));
		}

		auto callAutoCorrectProc(WCHAR character)
		{
			return sendMessage(EM_CALLAUTOCORRECTPROC, character, 0);
		}

		bool canPaste(UINT clipboardFormat)
		{
			return sendMessage(EM_CANPASTE, clipboardFormat, 0);
		}

		bool canRedo()
		{
			return sendMessage(EM_CANREDO, 0, 0);
		}

		bool displayBand(RECT area)
		{
			return sendMessage(EM_DISPLAYBAND, 0, reinterpret_cast<LPARAM>(&area));
		}

		void exGetSel(CHARRANGE& range)
		{
			sendMessage(EM_EXGETSEL, 0, reinterpret_cast<LPARAM>(&range));
		}

		void exLimitText(int textLimit)
		{
			sendMessage(EM_EXLIMITTEXT, 0, textLimit);
		}

		int lineFromChar(int charIndex)
		{
			sendMessage(EM_EXLINEFROMCHAR, 0, charIndex);
		}

		CHARRANGE exSetSel(CHARRANGE selectionRange)
		{
			return *reinterpret_cast<CHARRANGE*>(sendMessage(EM_EXSETSEL, 0, reinterpret_cast<LPARAM>(&selectionRange)));
		}

		enum class FindTextOperation
		{
			Down = FR_DOWN,
			MatchAlefHamza = FR_MATCHALEFHAMZA,
			MatchDiac = FR_MATCHDIAC,
			MatchKashida = FR_MATCHKASHIDA,
			//MatchWidth = FR_MATCHWIDTH,
			WholeWord = FR_WHOLEWORD
		};
		
		int findText(FindTextOperation op, FINDTEXT const& info)
		{
			return sendMessage(EM_FINDTEXT, static_cast<WPARAM>(op), reinterpret_cast<LPARAM>(&info));
		}

		int findTextEx(FindTextOperation op, FINDTEXTEX const& info)
		{
			return sendMessage(EM_FINDTEXTEX, static_cast<WPARAM>(op), reinterpret_cast<LPARAM>(&info));
		}
		
		enum class FindWordBreakOperation
		{
			Classify = WB_CLASSIFY,
			IsDelimiter = WB_ISDELIMITER,
			Left = WB_LEFT,
			LeftBreak = WB_LEFTBREAK,
			MoveWordLeft = WB_MOVEWORDLEFT,
			MoveWordRight = WB_MOVEWORDRIGHT,
			Right = WB_RIGHT,
			RightBreak = WB_RIGHTBREAK
		};
		
		int findWordBreak(FindWordBreakOperation op, int charIndex)
		{
			return sendMessage(EM_FINDWORDBREAK, static_cast<WPARAM>(op), charIndex);
		}

		int formatRage(bool needRender, FORMATRANGE const& info)
		{
			return sendMessage(EM_FORMATRANGE, needRender, reinterpret_cast<LPARAM>(&info));
		}

		AutoCorrectProc getAutoCorrectProc()
		{
			return reinterpret_cast<AutoCorrectProc>(sendMessage(EM_GETAUTOCORRECTPROC, 0, 0));
		}

		bool getAutoUrlDetect()
		{
			return sendMessage(EM_GETAUTOURLDETECT, 0, 0);
		}

		void getBiDiOptions(BIDIOPTIONS& options)
		{
			sendMessage(EM_GETBIDIOPTIONS, 0, reinterpret_cast<LPARAM>(&options));
		}

		enum class CharFormatKind
		{
			Default = SCF_DEFAULT,
			Selection = SCF_SELECTION
		};

		DWORD getCharFormat(CharFormatKind kind, CHARFORMAT& format)
		{
			return sendMessage(EM_GETCHARFORMAT, static_cast<WPARAM>(kind), reinterpret_cast<LPARAM>(&format));
		}
		
		//?
		auto getTCTFModeBias()
		{
			return sendMessage(EM_GETCTFMODEBIAS, 0, 0);
		}

		bool getTCTFOpenStatus()
		{
			return sendMessage(EM_GETCTFOPENSTATUS, 0, 0);
		}

		DWORD getEditStyle()
		{
			return sendMessage(EM_GETEDITSTYLE, 0, 0);
		}

		DWORD getEditStyleEx()
		{
			return sendMessage(EM_GETEDITSTYLEEX, 0, 0);
		}

		enum class EllipsisMode
		{
			None = ELLIPSIS_NONE,
			End = ELLIPSIS_END,
			Word = ELLIPSIS_WORD
		};

		bool getEllipsisMode(DWORD& style)
		{
			return sendMessage(EM_GETELLIPSISMODE, 0, reinterpret_cast<LPARAM>(&style));
		}

		bool setEllipsisMode(DWORD style)
		{
			return sendMessage(EM_SETELLIPSISMODE, 0, style);
		}

		bool getEllipsisState()
		{
			return sendMessage(EM_GETELLIPSISSTATE, 0, 0);
		}

		//?
		auto getEventMask()
		{
			return sendMessage(EM_GETEVENTMASK, 0, 0);
		}

		void getHyphenateInfo(HYPHENATEINFO& info)
		{
			sendMessage(EM_GETHYPHENATEINFO, reinterpret_cast<WPARAM>(&info), 0);
		}
		
		void setHyphenateInfo(HYPHENATEINFO& info)
		{
			sendMessage(EM_SETHYPHENATEINFO, reinterpret_cast<WPARAM>(&info), 0);
		}

		enum class IMECompositionMode
		{
			NotOpen = ICM_NOTOPEN,
			Level2 = ICM_LEVEL2,
			Level2_5 = ICM_LEVEL2_5,
			Level3 = ICM_LEVEL3,
			Level2_SUI = ICM_LEVEL2_SUI
		};

		IMECompositionMode getIMECompositionMode()
		{
			return static_cast<IMECompositionMode>(sendMessage(EM_GETIMECOMPMODE, 0, 0));
		}

		int GetIMECompText(IMECOMPTEXT& imeCompText, LPTSTR buffer)
		{
			return sendMessage(EM_GETIMECOMPTEXT, reinterpret_cast<WPARAM>(&imeCompText), reinterpret_cast<LPARAM>(buffer));
		}

		enum class IMEModeBias
		{
			PluralClause = IMF_SMODE_PLAURALCLAUSE,
			None = IMF_SMODE_NONE
		};

		int getIMEModeBias()
		{
			return sendMessage(EM_GETIMEMODEBIAS, 0, 0);
		}

		IMEModeBias setIMEModeBias(IMEModeBias bias)
		{
			return static_cast<IMEModeBias>(sendMessage(EM_SETIMEMODEBIAS, static_cast<LPARAM>(bias), static_cast<LPARAM>(bias)));
		}

		enum class IMEProperty
		{
			
		};

		enum class LangOptions
		{
			
		};

		//?
		auto getLangOptions()
		{
			return sendMessage(EM_GETLANGOPTIONS, 0, 0);
		}

		void setLangOptions(DWORD options)
		{
			sendMessage(EM_SETLANGOPTIONS, 0, options);
		}


		bool getOLEInterface(IRichEditOle& ptr)
		{
			return sendMessage(EM_GETOLEINTERFACE, 0, reinterpret_cast<LPARAM>(&ptr));
		}

		//?
		auto getOptions()
		{
			return sendMessage(EM_GETOPTIONS, 0, 0);
		}

		//?
		auto setOptions(WPARAM op, LPARAM value)
		{
			return sendMessage(EM_SETOPTIONS, op, value);
		}

		enum class PageRotate
		{
			Rotate_0 = EPR_0,
			Rotate_90 = EPR_90,
			Rotate_180 = EPR_180,
			Rotate_270 = EPR_270,
			Se = EPR_SE
		};
		
		PageRotate getPageRotate()
		{
			return static_cast<PageRotate>(sendMessage(EM_GETPAGEROTATE, 0, 0));
		}

		PageRotate setPageRotate(PageRotate pageRotate)
		{
			return static_cast<PageRotate>(sendMessage(EM_SETPAGEROTATE, static_cast<WPARAM>(pageRotate), 0));
		}
		
		DWORD getParaFormat(PARAFORMAT& format)
		{
			return sendMessage(EM_GETPARAFORMAT, 0, reinterpret_cast<LPARAM>(&format));
		}

		bool setParaFormat(PARAFORMAT& format)
		{
			return sendMessage(EM_SETPARAFORMAT, 0, reinterpret_cast<LPARAM>(&format));
		}

		UNDONAMEID getRedoName()
		{
			return static_cast<UNDONAMEID>(sendMessage(EM_GETREDONAME, 0, 0));
		}

		void getScrollPos(POINT& pos)
		{
			sendMessage(EM_GETSCROLLPOS, 0, reinterpret_cast<LPARAM>(&pos));
		}
		
		int getSelText(LPTSTR buffer)
		{
			return sendMessage(EM_GETSELTEXT, 0, reinterpret_cast<LPARAM>(buffer));
		}

		//?
		auto getStoryType()
		{
			return sendMessage(EM_GETSTORYTYPE, 0, 0);
		}
		//?
		auto setStoryType(WPARAM storyIndex, LPARAM newStoryType)
		{
			return sendMessage(EM_SETSTORYTYPE, storyIndex, newStoryType);
		}

		auto getTableParams(TABLEROWPARMS* tableRowParams, TABLECELLPARMS* tableCellParams)
		{
			return sendMessage(EM_GETTABLEPARMS, reinterpret_cast<WPARAM>(tableRowParams), reinterpret_cast<LPARAM>(tableCellParams));
		}

		auto setTableParams(TABLEROWPARMS* tableRowParams, TABLECELLPARMS* tableCellParams)
		{
			return sendMessage(EM_SETTABLEPARMS, reinterpret_cast<WPARAM>(tableRowParams), reinterpret_cast<LPARAM>(tableCellParams));
		}

		int getTextEx(GETTEXTEX& info, LPTSTR buffer)
		{
			return sendMessage(EM_GETTEXTEX, reinterpret_cast<WPARAM>(&info), reinterpret_cast<LPARAM>(buffer));
		}

		int getTextLengthEx(GETTEXTLENGTHEX& info)
		{
			return sendMessage(EM_GETTEXTLENGTHEX, reinterpret_cast<WPARAM>(&info), 0);
		}

		enum class TextMode
		{
			PlainText = TM_PLAINTEXT,
			RichText = TM_RICHTEXT,
			SingleLevelUndo = TM_SINGLELEVELUNDO,
			MultiLevelUndo = TM_MULTILEVELUNDO,
			SingleCodePage = TM_SINGLECODEPAGE,
			MultiCodePage = TM_MULTICODEPAGE
		};

		DWORD getTextMode()
		{
			return sendMessage(EM_GETTEXTMODE, 0, 0);
		}

		bool setTextMode(TextMode textMode)
		{
			return sendMessage(EM_SETTEXTMODE, static_cast<WPARAM>(textMode), 0);
		}

		int getTextRange(TEXTRANGE& info)
		{
			return sendMessage(EM_GETTEXTRANGE, 0, reinterpret_cast<LPARAM>(&info));
		}

		//?
		auto getTouchOptions(WPARAM touchOptions)
		{
			return sendMessage(EM_GETTOUCHOPTIONS, touchOptions, 0);
		}

		//?
		void setTouchOptions(WPARAM touchOptions, bool enableTouchSelectionHandler)
		{
			sendMessage(EM_SETTOUCHOPTIONS, touchOptions, enableTouchSelectionHandler);
		}


		//?
		auto getTypographyOptions()
		{
			return sendMessage(EM_GETTYPOGRAPHYOPTIONS, 0, 0);
		}

		//?
		bool setTypographyOptions(WPARAM options, LPARAM mask)
		{
			return sendMessage(EM_SETTYPOGRAPHYOPTIONS, options, mask);
		}

		bool setUIAName(LPCTSTR name)
		{
			return sendMessage(EM_SETUIANAME, 0, reinterpret_cast<LPARAM>(name));
		}

		int setUndoLimit(int limit)
		{
			return sendMessage(EM_SETUNDOLIMIT, limit, 0);
		}

		EDITWORDBREAKPROCEX setWordBreakProcEx(EDITWORDBREAKPROCEX newWordBreakProc)
		{
			return reinterpret_cast<EDITWORDBREAKPROCEX>(sendMessage(EM_SETWORDBREAKPROCEX, 0, reinterpret_cast<LPARAM>(newWordBreakProc)));
		}

		UNDONAMEID getUndoName()
		{
			return static_cast<UNDONAMEID>(sendMessage(EM_GETUNDONAME, 0, 0));
		}

		EDITWORDBREAKPROCEX getWordBreakProcEx()
		{
			return reinterpret_cast<EDITWORDBREAKPROCEX>(sendMessage(EM_GETWORDBREAKPROCEX, 0, 0));
		}

		bool getZoom(int& numerator, int& denominator)
		{
			return sendMessage(EM_GETZOOM, reinterpret_cast<WPARAM>(&numerator), reinterpret_cast<LPARAM>(&denominator));
		}

		void hideSelection(bool hide)
		{
			sendMessage(EM_HIDESELECTION, hide, 0);
		}

		auto insertImage(RICHEDIT_IMAGE_PARAMETERS& info)
		{
			return sendMessage(EM_INSERTIMAGE, 0, reinterpret_cast<LPARAM>(&info));
		}

		auto insertTable(TABLEROWPARMS& tableRowParams, TABLECELLPARMS& tableCellParams)
		{
			return sendMessage(EM_INSERTTABLE, reinterpret_cast<WPARAM>(&tableRowParams), reinterpret_cast<LPARAM>(&tableCellParams));
		}

		bool isIME()
		{
			return sendMessage(EM_ISIME, 0, 0);
		}

		void pasteSpecial(UINT clipboardFormat, REPASTESPECIAL* info)
		{
			sendMessage(EM_PASTESPECIAL, clipboardFormat, reinterpret_cast<LPARAM>(info));
		}

		void reconversion()
		{
			sendMessage(EM_RECONVERSION, 0, 0);
		}
		
		bool redo()
		{
			return sendMessage(EM_REDO, 0, 0);
		}

		void requestResize()
		{
			sendMessage(EM_REQUESTRESIZE, 0, 0);
		}

		enum class Selection
		{
			Text = SEL_TEXT,
			Object = SEL_OBJECT,
			MultiChar = SEL_MULTICHAR,
			MultiObject = SEL_MULTIOBJECT,
		};

		Selection SelectionType()
		{
			return static_cast<Selection>(sendMessage(EM_SELECTIONTYPE, 0, 0));
		}

		bool setAutoCorrectProc(AutoCorrectProc callback)
		{
			return sendMessage(EM_SETAUTOCORRECTPROC, reinterpret_cast<WPARAM>(callback), 0);
		}

		void setBiDiOptions(BIDIOPTIONS& options)
		{
			sendMessage(EM_SETBIDIOPTIONS, 0, reinterpret_cast<LPARAM>(&options));
		}

		COLORREF setBkgndColor(bool useSystemColor, COLORREF color)
		{
			return *reinterpret_cast<COLORREF*>(sendMessage(EM_SETBKGNDCOLOR, useSystemColor, *reinterpret_cast<LPARAM*>(reinterpret_cast<DWORD*>(&color))));
		}

		enum class CharFormat
		{
			All = SCF_ALL,
			AssociateFont = SCF_ASSOCIATEFONT,
			AssociateFont2 = SCF_ASSOCIATEFONT2,
			CharRepFromLCID = SCF_CHARREPFROMLCID,
			Default = SCF_DEFAULT,
			DontSetDefault = SPF_DONTSETDEFAULT,
			NoKbUpdate = SCF_NOKBUPDATE,
			Selection = SCF_SELECTION,
			SetDefault = SPF_SETDEFAULT,
			SmartFont = SCF_SMARTFONT,
			UseUIRules = SCF_USEUIRULES,
			Word = SCF_WORD,
		};
		
		bool setCharFormat(CharFormat format, CHARFORMAT& info)
		{
			sendMessage(EM_SETCHARFORMAT, static_cast<WPARAM>(format), reinterpret_cast<LPARAM>(&info));
		}

		enum class CTFModeBias
		{
			Default = CTFMODEBIAS_DEFAULT,
			FileName = CTFMODEBIAS_FILENAME,
			Name = CTFMODEBIAS_NAME,
			Reading = CTFMODEBIAS_READING,
			DateTime = CTFMODEBIAS_DATETIME,
			Conversation = CTFMODEBIAS_CONVERSATION,
			Numeric = CTFMODEBIAS_NUMERIC,
			Hiragana = CTFMODEBIAS_HIRAGANA,
			Katakana = CTFMODEBIAS_KATAKANA,
			Hangul = CTFMODEBIAS_HANGUL,
			HalfWidthKatakana = CTFMODEBIAS_HALFWIDTHKATAKANA,
			FullWidthAlphaNumeric = CTFMODEBIAS_FULLWIDTHALPHANUMERIC,
			HalfWidthAlphaNumeric = CTFMODEBIAS_HALFWIDTHALPHANUMERIC,
		};
		CTFModeBias setCTFModeBias(CTFModeBias bias)
		{
			return static_cast<CTFModeBias>(sendMessage(EM_SETCTFMODEBIAS, static_cast<WPARAM>(bias), 0));
		}

		bool setCTFOpenStatus(bool turnOn)
		{
			return sendMessage(EM_SETCTFOPENSTATUS, turnOn, 0);
		}
		
		enum class EditStyle
		{
			BeepOnMaxText = SES_BEEPONMAXTEXT,
			BiDi = SES_BIDI,
			CTFAllowEmbed = SES_CTFALLOWEMBED,
			CTFAllowProofing = SES_CTFALLOWPROOFING,
			CTFAllowSmartTag = SES_CTFALLOWSMARTTAG,
			CTFNoLock = SES_CTFNOLOCK,
			DefaultLatinLiga = SES_DEFAULTLATINLIGA,
			DraftMode = SES_DRAFTMODE,
			Emulate10 = SES_EMULATE10,
			EmulateSysEdit = SES_EMULATESYSEDIT,
			ExtendBackColor = SES_EXTENDBACKCOLOR,
			HideGridLines = SES_HIDEGRIDLINES,
			HyperlinkTooltips = SES_HYPERLINKTOOLTIPS,
			LogicalCaret = SES_LOGICALCARET,
			Lowercase = SES_LOWERCASE,
			MultiSelect = SES_MULTISELECT,
			NoEALineHeightAdjust = SES_NOEALINEHEIGHTADJUST,
			NoFocusLinkNotify = SES_NOFOCUSLINKNOTIFY,
			NoIME = SES_NOIME,
			NoInputSequenceCHK = SES_NOINPUTSEQUENCECHK,
			ScrollOnKillFocus = SES_SCROLLONKILLFOCUS,
			SmartDragDrop = SES_SMARTDRAGDROP,
			WordDragDrop = SES_WORDDRAGDROP,
			UpperCase = SES_UPPERCASE,
			UseAIMM = SES_USEAIMM,
			UseAtFont = SES_USEATFONT,
			UseCTF = SES_USECTF,
			XLTCRCRLFToCR = SES_XLTCRCRLFTOCR,
		};

		enum class EditStyleEx
		{
			HandleFriendlyURL = SES_EX_HANDLEFRIENDLYURL,
			MultiTouch = SES_EX_MULTITOUCH,
			NoAcetateSelection = SES_EX_NOACETATESELECTION, //?
			NoMath = SES_EX_NOMATH,
			NoTable = SES_EX_NOTABLE,
			UseSingleLine = SES_EX_USESINGLELINE,
			HideTempFormat = SES_EX_HIDETEMPFORMAT,
			UseMouseWPARAM = SES_EX_USEMOUSEWPARAM,
		};
		
		
		auto setEditStyle(DWORD styles, DWORD mask)
		{
			return sendMessage(EM_SETEDITSTYLE, styles, mask);
		}

		auto setEditStyleEx(DWORD exStyles, DWORD mask)
		{
			return sendMessage(EM_SETEDITSTYLEEX, exStyles, mask);
		}

		enum class Events
		{
			Change = ENM_CHANGE,
			ClipFormat = ENM_CLIPFORMAT,
			CoorectText = ENM_CORRECTTEXT,
			DragDropDone = ENM_DRAGDROPDONE,
			DropFiles = ENM_DROPFILES,
			IMEChange = ENM_IMECHANGE,
			KeyEvents = ENM_KEYEVENTS,
			Link = ENM_LINK,
			LowFiRTF = ENM_LOWFIRTF,
			MouseEvents = ENM_MOUSEEVENTS,
			ObjectPositions = ENM_OBJECTPOSITIONS,
			ParagraphExpanded = ENM_PARAGRAPHEXPANDED,
			Protected = ENM_PROTECTED,
			RequestResize = ENM_REQUESTRESIZE,
			Scroll = ENM_SCROLL,
			ScrollEvents = ENM_SCROLLEVENTS,
			SelChange = ENM_SELCHANGE,
			Update = ENM_UPDATE,
		};

		DWORD setEventMask(DWORD mask)
		{
			return sendMessage(EM_SETEVENTMASK, 0, mask);
		}

		bool setFontSize(short fontSizeDelta)
		{
			return sendMessage(EM_SETFONTSIZE, fontSizeDelta, 0);
		}

		bool setIMEColor(COMPCOLOR& info)
		{
			return sendMessage(EM_SETIMECOLOR, 0, reinterpret_cast<LPARAM>(&info));
		}

		//?
		bool setIMEOptions(WPARAM wparam, LPARAM lparam)
		{
			return sendMessage(EM_SETIMEOPTIONS, wparam, lparam);
		}

		bool setOLECallback(IRichEditOleCallback& pointer)
		{
			return sendMessage(EM_SETOLECALLBACK, 0, reinterpret_cast<LPARAM>(&pointer));
		}

		//?
		void setPalette(WPARAM paletteHandle)
		{
			sendMessage(EM_SETPALETTE, paletteHandle, 0);
		}

		enum class PunctuationType
		{
			Leading = PC_LEADING,
			Following = PC_FOLLOWING,
			Delimiter = PC_DELIMITER,
			Overflow = PC_OVERFLOW
		};

		bool setPunctuation(PunctuationType punctuationType, PUNCTUATION& info)
		{
			return sendMessage(EM_SETPUNCTUATION, static_cast<WPARAM>(punctuationType), reinterpret_cast<LPARAM>(&info));
		}

		void setScrollPos(POINT p)
		{
			sendMessage(EM_SETSCROLLPOS, 0, reinterpret_cast<LPARAM>(&p));
		}

		bool setTargetDevice(HDC targetDevice, int lineWidth)
		{
			return sendMessage(EM_SETTARGETDEVICE, reinterpret_cast<WPARAM>(targetDevice), lineWidth);
		}

		int setTextEx(SETTEXTEX& info, LPTSTR text)
		{
			return sendMessage(EM_SETTEXTEX, reinterpret_cast<WPARAM>(&info), reinterpret_cast<LPARAM>(text));
		}

		bool setZoom(int numerator, int deminator)
		{
			return sendMessage(EM_SETZOOM, numerator, deminator);
		}

		enum class ScrollbarType
		{
			Horizontal = SB_HORZ,
			Vertical = SB_VERT
		};

		void showScrollBar(ScrollbarType scrollbarType, bool show)
		{
			sendMessage(EM_SHOWSCROLLBAR, static_cast<WPARAM>(scrollbarType), show);
		}

		void stopGroupTyping()
		{
			sendMessage(EM_STOPGROUPTYPING, 0, 0);
		}

		enum class StreamFormaat
		{
			RTF = SF_RTF,
			RTFNoObjs = SF_RTFNOOBJS,
			Text = SF_TEXT,
			Textized = SF_TEXTIZED,
			PlainRTF = SFF_PLAINRTF,
			Selection = SFF_SELECTION,
			Unicode = SF_UNICODE,
			
		};

		int streamIn(DWORD streamFormat, EDITSTREAM& info)
		{
			return sendMessage(EM_STREAMIN, streamFormat, reinterpret_cast<LPARAM>(&info));
		}

		int streamOut(DWORD streamFormat, EDITSTREAM& info)
		{
			return sendMessage(EM_STREAMOUT, streamFormat, reinterpret_cast<LPARAM>(&info));
		}
	};
}