#pragma once

#include "CherryDialog.h"

///////////////////////////////////////////////////////////////////////////
///
/// \class		CCherryNotificationDialog
/// \brief		
/// \author		����ö
/// \date		2013-10-04
/// \remark		OnCreate �κ��� �������� �ʿ��� ����
/// \section	
///
///////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CCherryNotificationDialog : public CCherryDialog
{
	DECLARE_DYNAMIC(CCherryNotificationDialog)

// Constructors
public:
	CCherryNotificationDialog();
	virtual CHERRY_RET Create(
		DWORD dwStyle, 
		UINT nWidth,
		UINT nHeight,
		CWnd *pParentWnd, 
		UINT nID, 
		UINT nDurationSec = 0);						// 0�� ��� ����
	
// Attributes
protected:
	const BOOL	m_bWinXPOrLater;

	BOOL		m_bFadeInTurn;
	int			m_nFadeCount;
	int			m_nDurationSec;
	int			m_nDurationSecCount;

	UINT_PTR	m_nFadingTimerRet;
	UINT_PTR	m_nDurationTimerRet;

// Operations
public:
	BOOL	FadeInWindow(USHORT nStep = 10);		// ���� �������ϰ�
	BOOL	FadeOutWindow(USHORT nStep = 10);		// ���� �����ϰ�
	BOOL	IsFadeInWindowTurn() const;				// ����ȭ, ������ȭ ���� ����

protected:
	void	Initialize();
	CRect	GetAnchorRect(UINT nWidth, UINT nHeight);

// Overridables
protected:
	virtual void	OnDrawCherry(CCherryMemDC *pDC);

// Implementation
public:
	virtual ~CCherryNotificationDialog();

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnTimer(UINT_PTR nIDEvent);	
	virtual void	PostNcDestroy();	
};


///////////////////////////////////////////////////////////////////////////
///
/// \class		CCherryNotificationPopup
/// \brief		
/// \author		����ö
/// \date		2013-10-04
/// \remark		
/// \section	
///
///////////////////////////////////////////////////////////////////////////
/*
typedef struct NOTIFICATION_DIALOG_POINT
{
	int nRow;
	int nCol;
	int nCount;
} NOTIFICATION_DIALOG_POINT;

class AFX_EXT_CLASS CCherryNotificationPopup
{
// Constructors
public:
	CCherryNotificationPopup();
	CCherryNotificationPopup(CCherryNotificationDialog *pNotificationDialog, UINT nWidth, UINT nHeight);
	DWORD Create(CCherryNotificationDialog *pNotificationDialog, UINT nWidth, UINT nHeight);
	virtual ~CCherryNotificationPopup();

// Attributes
protected:
	vector<CCherryNotificationDialog *> m_notificationDialogVector;
	UINT m_nWidth;
	UINT m_nHeight;

	CPoint m_dialogPoint;
	UINT m_nCount;


	CCherryNotificationDialog *m_pNotificationDialog;

// Operations
public:
	BOOL PopupNotificationDialog();
	void Destroy();

protected:
	void Initialize();
	CRect GetAnchorRect();
		
// Overridables
	
// Implementation

};
*/