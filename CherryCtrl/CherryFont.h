#pragma once

#include "CherryException.h"

using namespace Gdiplus;

#define DEFAULT_FONT_NAME		_T("Segoe UI")
#define DEFAULT_FONT_SIZE		12
#define DEFAULT_ORG_FONT_SIZE	15
#define DEFAULT_FONT_STYLE		FontStyleRegular
#define DEFAULT_UNIT_PIXEL		UnitPixel
#define DEFAULT_FONT_COLOR		Color(0, 0, 0)			// black
#define DEFAULT_SHADOW_COLOR	Color(160, 160, 160);	// gray
#define DEFAULT_FONT_ALIGN		StringAlignmentCenter

///////////////////////////////////////////////////////////////////////////
///
/// \class		CCherryFont
/// \brief		CherryX ���� ����ϴ� ��� ���ڿ��� �� Ŭ������ ����Ͽ� ǥ���ϵ��� �Ѵ�.\n
///				Base Ŭ���� ����.
/// \author		����ö
/// \date		2012-11-09
/// \remark		
/// \section	
///
///////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CCherryFont
{
public:
	// ��Ÿ�� ����
	enum STYLE
	{
		STYLE_DEFAULT = 0x0000,	// �⺻��
		STYLE_LEFT = 0x0000,	// �·� ����
		STYLE_TOP = 0x0001,	// ���� ����
		STYLE_RIGHT = 0x0002,	// ��� ����
		STYLE_BOTTOM = 0x0004,	// �Ʒ��� ����
		STYLE_CENTER = 0x0008,	// ���� ��� ����
		STYLE_VCENTER = 0x0010,	// ���� ��� ����

		STYLE_BOLD = 0x0020,	// ���ϰ�
		STYLE_ITALIC = 0x0040,	// �����
		STYLE_UNDERLINE = 0x0080,	// ���� �߱�
		STYLE_STRIKEOUT = 0x0100,	// ��Ҽ�
		STYLE_NOWRAP = 0x0200,	// �ٹٲ� �� ��
	};

// Constructors
public:
	CCherryFont();
	CCherryFont(LPCTSTR lpszFontName, float fFontSize, Color fontColor, DWORD dwFontStyle);
	CCherryFont(const CCherryFont &cherryFont);

// Attributes
protected:
	// Text
	CString			m_strFontName;
	Color			m_fontColor;
	float			m_fFontSize;
	DWORD			m_dwFontStyle;
	CRect			m_offsetRect;				// OffsetText() ���ÿ�

// 	// Shadow
// 	BOOL			m_bEnableShadow;
// 	Color			m_shadowColor;
// 	int				m_nOffsetTextLeft;
// 	int				m_nOffsetTextTop;

// Operations
public:
	// Text Style
	void			SetCherryFont(LPCTSTR lpszFontName, float fFontSize, Color fontColor, DWORD dwFontStyle);
	BOOL			SetCherryFont(CCherryFont *pCherryFont);
	void			SetFontName(LPCTSTR lpszFontName);
	void			SetFontSize(float fFontSize);
	void			SetFontColor(Color fontColor);
	void			SetFontStyle(DWORD dwFontStyle);
	CRect			MeasureString(Graphics *pGraphics, LPCTSTR lpszString);

	CString			GetFontName();
	float			GetFontSize();
	Color			GetFontColor();
	DWORD			GetFontStyle();
	
	void			DrawText(Graphics *pGraphics, LPCTSTR lpszText, const CRect &rect);

// Implementation
public:
	virtual ~CCherryFont();
};
