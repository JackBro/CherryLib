#pragma once

#include "CherryNotificationIcon.h"
#include "CherryButton.h"

// CFlyoutDlg ��ȭ �����Դϴ�.

class CFlyoutDlg : public CCherryNotificationIconFlyout
{
	DECLARE_DYNAMIC(CFlyoutDlg)

public:
	CFlyoutDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFlyoutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

	CButton m_button1;
	CCherryButton m_cherryButton;
public:
	virtual void OnDrawCherry(CCherryMemDC *pDC);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg void OnBnClickedButton1();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
