#pragma once


// CFlyoutDlg2 ��ȭ �����Դϴ�.

class CFlyoutDlg2 : public CDialog
{
	DECLARE_DYNAMIC(CFlyoutDlg2)

public:
	CFlyoutDlg2(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFlyoutDlg2();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
