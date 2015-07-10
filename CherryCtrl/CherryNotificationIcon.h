#pragma once

#include "CherryException.h"
#include <vector>

using namespace std;

///////////////////////////////////////////////////////////////////////////
///
/// \class    CherryNotificationIcon
/// \brief    Ʈ���� ������ ����
/// \author   ogoons
/// \date     2013-09-05
/// \remark   
/// \section  
///
///////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CCherryNotificationIcon : public CWnd // CWnd is for timer
{
	DECLARE_DYNAMIC(CCherryNotificationIcon)

// Constructors
public:
	CCherryNotificationIcon();
	CCherryNotificationIcon(HICON hIcon, LPCTSTR lpszToolTip, UINT nContextMenuID, UINT nCallbackMessage, CWnd *pParentWnd, UINT nID = 0);
	CHERRY_RET Create(HICON hIcon, LPCTSTR lpszToolTip, UINT nContextMenuID, UINT nCallbackMessage, CWnd *pParentWnd, UINT nID = 0);

// Attributes
public:
	NOTIFYICONDATA		m_notifyIconData;			// NOTIFYICONDATA ����ü

	CWnd				*m_pParentWnd;				// �θ� ������
	HICON				m_hIcon;					// �⺻ ������
	vector<HICON>		m_hIconList;				// ������ ����Ʈ

	int					m_nAddedID;					// �ߺ� ���̵� ó����
	UINT				m_nContextMenuID;			// Context Menu �� ���̵�
	UINT_PTR			m_nTimerID;					// ���ϸ��̼ǿ� Ÿ�̸� ���̵� (Ÿ�̸� ���� ����)
	UINT				m_nCount;					// ���ϸ��̼ǿ� Ÿ�̸� ī��Ʈ
	const size_t		m_notifyIconDataSize;		// NOTIFYICONDATA ����ü ������ ���� (�� ���� �ʱ�ȭ)

	// Flags
	const BOOL			m_bWinXPOrLater;			// Win2k �̻�����
	BOOL				m_bEnabled;					// Create ����
	BOOL				m_bAdded;					// Add ����
	BOOL				m_bVisible;					// Ʈ���̿� �������� �ִ� ���� ����
	
	// Context Menu
	UINT				m_nContextMenuDefaultItem;	// Default �޴� ����
	BOOL				m_bContextMenuDefaultByPos;	// Default �޴��� pos�� �� ������ T/F F�̸� m_nContextMenuDefaultItem�� ���

	static const UINT m_nTaskbarCreatedMessage;

// Operations
public:
	CHERRY_RET	AddIcon();
	HICON		GetIcon() const;						// ���� ȭ�鿡 ǥ�õǴ� ������ ��������
	HICON		GetDefaultIcon() const;					// ���ϸ��̼����� ǥ�õǴ� ������ �ܿ� �⺻���� ������ ������ ��������
	HICON		GetIconFromList(INT_PTR nPos) const;	// �� ���� ���ϸ��̼� ������ ��������
	CHERRY_RET	SetIcon(HICON hIcon);
	CHERRY_RET	SetIcon(LPCTSTR lpszIconPath);
	CHERRY_RET	SetIcon(UINT nID);
	CHERRY_RET	SetIconFromList(UINT nPos);
	CHERRY_RET	RemoveIcon();
	CHERRY_RET	ShowIcon();
	CHERRY_RET	HideIcon();
	CHERRY_RET	SetFocus();
	CHERRY_RET	Destroy();

	// NOTIFYICONDATA
	NOTIFYICONDATA*					GetNotifyIconData();

	// Menu
	CHERRY_RET	SetContextMenu(UINT nContextMenuID);
	void		GetContextMenuDefaultItem(UINT &nItem, BOOL &bByPos);
	CHERRY_RET	SetContextMenuDefaultItem(UINT nItem, BOOL bByPos = FALSE);

	// Status
	BOOL		IsVisible() const;	// �������� �������� �ִ� ��
	BOOL		IsEnabled() const;	// ������(��ü) ���� ����

	// ToolTip
	CString		GetToolTipText() const;
	CHERRY_RET	SetToolTipText(LPCTSTR lpszToolTip);

	// Callback Message
	UINT		GetCallbackMessage() const;
	DWORD		SetCallbackMessage(UINT nCallbackMessage);

	// Animation
	CHERRY_RET	StartAnimation(UINT nElapse);
	CHERRY_RET	StepAnimation();
	CHERRY_RET	PauseAnimation();
	CHERRY_RET	StopAnimation();
	CHERRY_RET	SetIconList(UINT nFirstIconID, UINT nLastIconID);

	// Balloon
	CHERRY_RET	ShowBalloon(LPCTSTR lpszText, LPCTSTR lpszTitle, DWORD dwIcon);
	CHERRY_RET	ShowBalloon(LPCTSTR lpszText, LPCTSTR lpszTitle, DWORD dwIcon, UINT nTimeout, HICON hBalloonIcon);

	// Flyout
	//DWORD	ShowFlyout(CCherryNotificationIconFlyout *pFlyout, UINT nWidth, UINT nHeight);
	//void							HideFlyout();
	//CWnd							*GetFlyout();
	//CRect							GetFlyoutRect(UINT nWidth, UINT nHeight);

protected:
	void	Initialize();
	size_t	GetNotifyIconDataSize() const;		// NOTIFYICONDATA ����ü�� ����� �����´�.

// Overridables
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

// Implementation
public:
	virtual ~CCherryNotificationIcon();

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void		OnTimer(UINT_PTR nIDEvent);
	LRESULT				OnNotificationIcon(WPARAM wParam, LPARAM lParam);
	LRESULT				OnTaskbarCreated(WPARAM wParam, LPARAM lParam);
};

#include "CherryDialog.h"

///////////////////////////////////////////////////////////////////////////
///
/// \class		CCherryNotificationIconFlyout
/// \brief		Ʈ���� ������ �ʿ��� ���ƿ��� Window
/// \author		ogoons
/// \date		2013-10-04
/// \remark		
/// \section	
///
///////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CCherryNotificationIconFlyout : public CCherryDialog
{
	DECLARE_DYNAMIC(CCherryNotificationIconFlyout)

// Constructors
public:
	CCherryNotificationIconFlyout();
	CCherryNotificationIconFlyout(UINT nIDTemplate, CWnd *pParent);
	CHERRY_RET Create(CCherryNotificationIcon* pNotificationIcon, UINT nWidth, UINT nHeight);
	
// Attributes
protected:

// Operations
	CRect GetAnchorRect(CCherryNotificationIcon *pNotificationIcon, UINT nWidth, UINT nHeight);
	CRect GetAnchorRect(NOTIFYICONDATA *pNotifyIconData, UINT nWidth, UINT nHeight);

// Overridables
protected:
	virtual BOOL OnInitDialog();
	virtual BOOL OnCreateCherry();
	virtual void OnDrawCherry(CCherryMemDC *pDC);

// Implementation
public:
	virtual ~CCherryNotificationIconFlyout();

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnKillFocus(CWnd *pNewWnd);
	virtual void PostNcDestroy();
};