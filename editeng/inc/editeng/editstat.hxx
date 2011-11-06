/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



#ifndef _EDITSTAT_HXX
#define _EDITSTAT_HXX

#include <tools/string.hxx>
#include <i18npool/lang.h>

#define EE_CNTRL_USECHARATTRIBS		0x00000001	// Verwendung harter ZeichenAttr.
#define EE_CNTRL_USEPARAATTRIBS		0x00000002	// Verwendung von AbsatzAttr.
#define EE_CNTRL_CRSRLEFTPARA		0x00000004	// Cursor ist in einen anderen Absatz gewandert
#define EE_CNTRL_DOIDLEFORMAT		0x00000008	// Idle-Formatierung
#define EE_CNTRL_PASTESPECIAL		0x00000010	// Allow PasteSpecial
#define EE_CNTRL_AUTOINDENTING		0x00000020	// Automatisches einruecken
#define EE_CNTRL_UNDOATTRIBS		0x00000040	// Undo fuer Attribute....
#define EE_CNTRL_ONECHARPERLINE		0x00000080	// Ein Zeichen pro Zeile
#define EE_CNTRL_NOCOLORS			0x00000100	// Engine: Keine Farben
#define EE_CNTRL_OUTLINER			0x00000200	// Sonderbehandlung Outliner/Gliederungsmodus
#define EE_CNTRL_OUTLINER2			0x00000400	// Sonderbehandlung Outliner/Seite
#define EE_CNTRL_ALLOWBIGOBJS		0x00000800	// PortionInfo in Textobjekten
#define EE_CNTRL_ONLINESPELLING		0x00001000	// Waehrend des editieren Spelling
#define EE_CNTRL_STRETCHING			0x00002000	// Stretch-Modus
#define EE_CNTRL_MARKFIELDS			0x00004000	// Felder farblich hinterlegen
#define EE_CNTRL_URLSFXEXECUTE		0x00008000	// !!!OLD!!!: SFX-URL-Execute.
#define EE_CNTRL_RESTOREFONT		0x00010000	// Font im OutDev restaurieren
#define EE_CNTRL_RTFSTYLESHEETS		0x00020000	// Stylesheets bei Import verwenden
//#define EE_CNTRL_NOREDLINES            0x00040000  // Keine RedLines bei OnlineSpellError     /* removed #i91949 */
#define EE_CNTRL_AUTOCORRECT		0x00080000	// AutoKorrektur
#define EE_CNTRL_AUTOCOMPLETE		0x00100000	// AutoComplete
#define EE_CNTRL_AUTOPAGESIZEX		0x00200000	// Papierbreite an Text anpassen
#define EE_CNTRL_AUTOPAGESIZEY		0x00400000	// Papierhoehe an Text anpassen
#define EE_CNTRL_AUTOPAGESIZE		(EE_CNTRL_AUTOPAGESIZEX|EE_CNTRL_AUTOPAGESIZEY)
#define EE_CNTRL_TABINDENTING		0x00800000	// Einruecken mit Tab
#define EE_CNTRL_FORMAT100			0x01000000	// Immer nach 100% formatieren
#define EE_CNTRL_ULSPACESUMMATION	0x02000000	// MS Compat: SA und SB aufsummieren, nicht maximalwert
#define EE_CNTRL_ULSPACEFIRSTPARA	0x04000000	// MS Compat: SB auch beim ersten Absatz auswerten

#define EV_CNTRL_AUTOSCROLL			0x00000001	// Autom. Scrollen horiz.
#define EV_CNTRL_BIGSCROLL			0x00000002	// Weiter Scrollen, als nur zum Cursor
#define EV_CNTRL_ENABLEPASTE		0x00000004	// Paste erlauben
#define EV_CNTRL_SINGLELINEPASTE	0x00000008	// View: Paste in Eingabezeile...
#define EV_CNTRL_OVERWRITE			0x00000010	// Ueberschreibmodus
#define EV_CNTRL_INVONEMORE			0x00000020	// Ein Pixel mehr invalidieren
#define EV_CNTRL_AUTOSIZEX			0x00000040	// Automatisch an Textbreite anpassen
#define EV_CNTRL_AUTOSIZEY			0x00000080	// Automatisch an Texthoehe anpassen
#define EV_CNTRL_AUTOSIZE			(EV_CNTRL_AUTOSIZEX|EV_CNTRL_AUTOSIZEY)

#define EE_STAT_HSCROLL				0x00000001
#define EE_STAT_VSCROLL				0x00000002
#define EE_STAT_CURSOROUT			0x00000004
#define EE_STAT_CRSRMOVEFAIL		0x00000008
#define EE_STAT_CRSRLEFTPARA		0x00000010
#define EE_STAT_TEXTWIDTHCHANGED	0x00000020
#define EE_STAT_TEXTHEIGHTCHANGED	0x00000040
#define EE_STAT_WRONGWORDCHANGED	0x00000080
// #define EE_STAT_MODIFIED			0x00000100

// Nur fuer Update:
#define EE_CNTRL_AUTOCENTER		EE_CNTRL_AUTOPAGESIZE
#define EE_STAT_GROWY			EE_STAT_TEXTHEIGHTCHANGED

/*
	EE_STAT_CRSRLEFTPARA zur Zeit bei Cursorbewegungen und Return.
*/

inline void SetFlags( sal_uLong& rBits, const sal_uInt32 nMask, sal_Bool bOn )
{
	if ( bOn )
		rBits |= nMask;
	else
		rBits &= ~nMask;
}

class EditStatus
{
protected:
	sal_uLong	nStatusBits;
	sal_uLong	nControlBits;
	sal_uInt16	nPrevPara;					// fuer EE_STAT_CRSRLEFTPARA

public:
			EditStatus()				{ nStatusBits = 0; nControlBits = 0; nPrevPara = 0xFFFF; }

	void	Clear() 					{ nStatusBits = 0; }
	void	SetControlBits( sal_uLong nMask, sal_Bool bOn )
				{ SetFlags( nControlBits, nMask, bOn ); }

	sal_uLong	GetStatusWord() const		{ return nStatusBits; }
	sal_uLong&	GetStatusWord() 			{ return nStatusBits; }

	sal_uLong	GetControlWord() const		{ return nControlBits; }
	sal_uLong&	GetControlWord() 			{ return nControlBits; }

	sal_uInt16	GetPrevParagraph() const	{ return nPrevPara; }
	sal_uInt16&	GetPrevParagraph() 			{ return nPrevPara; }
};

#define SPELLCMD_IGNOREWORD			0x0001
#define SPELLCMD_STARTSPELLDLG		0x0002
#define SPELLCMD_ADDTODICTIONARY	0x0003
#define SPELLCMD_WORDLANGUAGE   	0x0004
#define SPELLCMD_PARALANGUAGE	    0x0005

struct SpellCallbackInfo
{
	sal_uInt16		    nCommand;
	String		    aWord;
    LanguageType    eLanguage;

	SpellCallbackInfo( sal_uInt16 nCMD, const String& rWord )
	: aWord( rWord )
	{
		nCommand = nCMD;
        eLanguage = LANGUAGE_DONTKNOW;
	}

    SpellCallbackInfo( sal_uInt16 nCMD, LanguageType eLang )
	{
		nCommand = nCMD;
        eLanguage = eLang;
	}
};

#endif // _EDITSTAT_HXX

