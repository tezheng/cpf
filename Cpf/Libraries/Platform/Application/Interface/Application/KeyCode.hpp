//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	enum class KeyCode : int32_t
	{
		eUnknown = 0,
		eReturn = '\r',
		eEscape = '\033',
		eBackspace = '\b',
		eTab = '\t',
		eSpace = ' ',
		eExclamation = '!',
		eDoubleQuote = '\"',
		eHash = '#',
		ePercent = '%',
		eDollar = '$',
		eAmpersand = '&',
		eSingleQuote = '\'',
		eLeftParen = '(',
		eRightParen = ')',
		eAsterisk = '*',
		ePlus = '+',
		eComma = ',',
		eMinus = '-',
		ePeriod = '.',
		eSlash = '/',
		eLeftBracket = '[',
		eRightBracket = ']',

		e0 = '0',
		e1 = '1',
		e2 = '2',
		e3 = '3',
		e4 = '4',
		e5 = '5',
		e6 = '6',
		e7 = '7',
		e8 = '8',
		e9 = '9',

		eColor = ':',
		eSemicolon = ';',
		eLess = '<',
		eEquals = '=',
		eGreater = '>',
		eQuestion = '?',
		eAt = '@',

		eBackslash = '\\',
		eCaret = '^',
		eUnderscore = '_',
		eBackQuote = '`',
		eA = 'a',
		eB = 'b',
		eC = 'c',
		eD = 'd',
		eE = 'e',
		eF = 'f',
		eG = 'g',
		eH = 'h',
		eI = 'i',
		eJ = 'j',
		eK = 'k',
		eL = 'l',
		eM = 'm',
		eN = 'n',
		eO = 'o',
		eP = 'p',
		eQ = 'q',
		eR = 'r',
		eS = 's',
		eT = 't',
		eU = 'u',
		eV = 'v',
		eW = 'w',
		eX = 'x',
		eY = 'y',
		eZ = 'z',

		eF1 = (1 << 30) | 58,
		eF2 = (1 << 30) | 59,
		eF3 = (1 << 30) | 60,
		eF4 = (1 << 30) | 61,
		eF5 = (1 << 30) | 62,
		eF6 = (1 << 30) | 63,
		eF7 = (1 << 30) | 64,
		eF8 = (1 << 30) | 65,
		eF9 = (1 << 30) | 66,
		eF10 = (1 << 30) | 67,
		eF11 = (1 << 30) | 68,
		eF12 = (1 << 30) | 69,
	};
}