#pragma once

#include "CherryFont.h"

///////////////////////////////////////////////////////////////////////////
///
/// \class		CCherryFontByStatus
/// \brief		4���� ���� Font ���� Ŭ����\n
///				CCherryButton, CCherryCheckBox, CCherryLinkCtrl �� ���콺 �޽����� �޾� ó���Ǵ�\n
///				��Ʈ�ѵ��� ���ڿ� ó���� ����ϴ� Super Ŭ�����̴�.
/// \author		ogoons
/// \date		2013-04-06
/// \remark		
/// \section	
///
///////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CCherryFontByStatus
{
// Constructors
public:
	CCherryFontByStatus();

// Attributes
protected:
	CCherryFont		*m_pCurrentFont;
	CCherryFont		m_normalFont;
	CCherryFont		m_hoverFont;
	CCherryFont		m_downFont;
	CCherryFont		m_disableFont;

// Operations
public:
	// ��� ���� ��Ʈ�� �����Ѵ�.(Disable Į��� �⺻ �׷��� ����)
	void SetCherryFont(LPCTSTR lpszFontName, float fFontSize, Color fontColor, DWORD dwFontStyle);
	BOOL SetCherryFont(CCherryFont *pCherryFont);

	// ���º� ��Ʈ ����
	void SetFontByStatus(CCherryFont *pNormalFont, CCherryFont *pHoverFont, CCherryFont *pDownFont, CCherryFont *pDisableFont);
	
	// Normal ��Ʈ ����
	void SetNormalFont(LPCTSTR lpszFontName, float fFontSize, Color fontColor, DWORD dwFontStyle);
	BOOL SetNormalFont(CCherryFont *pNormalFont);
	void SetNormalFontName(LPCTSTR lpszFontName);
	void SetNormalFontSize(float fFontSize);
	void SetNormalFontColor(Color fontColor);
	void SetNormalFontStyle(DWORD dwFontStyle);

	// Hover ��Ʈ ����
	void SetHoverFont(LPCTSTR lpszFontName, float fFontSize, Color fontColor, DWORD dwFontStyle);
	BOOL SetHoverFont(CCherryFont *pHoverFont);
	void SetHoverFontName(LPCTSTR lpszFontName);
	void SetHoverFontSize(float fFontSize);
	void SetHoverFontColor(Color fontColor);
	void SetHoverFontStyle(DWORD dwFontStyle);

	// Down ��Ʈ ����
	void SetDownFont(LPCTSTR lpszFontName, float fFontSize, Color fontColor, DWORD dwFontStyle);
	BOOL SetDownFont(CCherryFont *pDownFont);
	void SetDownFontName(LPCTSTR lpszFontName);
	void SetDownFontSize(float fFontSize);
	void SetDownFontColor(Color fontColor);
	void SetDownFontStyle(DWORD dwFontStyle);

	// Disable ��Ʈ ����
	void SetDisableFont(LPCTSTR lpszFontName, float fFontSize, Color fontColor, DWORD dwFontStyle);
	BOOL SetDisableFont(CCherryFont *pDisableFont);
	void SetDisableFontName(LPCTSTR lpszFontName);
	void SetDisableFontSize(float fFontSize);
	void SetDisableFontColor(Color fontColor);
	void SetDisableFontStyle(DWORD dwFontStyle);

	void GetFontByStatus(CCherryFont &normalFont, CCherryFont &hoverFont, CCherryFont &downFont, CCherryFont &disableFont) const;

protected:
	CCherryFont	*GetNormalFont();
	CCherryFont	*GetHoverFont();
	CCherryFont	*GetDownFont();
	CCherryFont	*GetDisableFont();

	void SetCurrentFont(CCherryFont *pStatusFont);
	CCherryFont	*GetCurrentFont() const;

// Implementation
public:
	virtual ~CCherryFontByStatus();
};
