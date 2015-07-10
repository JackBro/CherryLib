#pragma once

#include "CherryMemDC.h"
#include "CherryImage.h"

///////////////////////////////////////////////////////////////////////////
///
/// \class		CCherryDialog (Abstract Class)
/// \brief		Cherry Control�� ��ġ ������ Based ���̾�α�,
/// \author		ogoons
/// \date		2013-09-05
/// \remark		
/// \section	
///
///////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CCherryDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCherryDialog)

	// ��ư ���� ����
	enum STATUS
	{
		STATUS_NORMAL,
		STATUS_HOVER,
		STATUS_DOWN,
		STATUS_DISABLE,
		STATUS_MAX_COUNT
	};

// Constructors
public:
	CCherryDialog();
	CCherryDialog(UINT nIDTemplate, CWnd *pParent);
	

// Attributes
protected:
	// Icon
	CCherryImage m_iconImage;

	// System buttons
	CCherryImage m_sysHelpButtonImage[STATUS_MAX_COUNT];
	CCherryImage m_sysMinButtonImage[STATUS_MAX_COUNT];
	CCherryImage m_sysMaxButtonImage[STATUS_MAX_COUNT];
	CCherryImage m_sysCloseButtonImage[STATUS_MAX_COUNT];

// Operations
public:
	CHERRY_RET SetSystemButtonImage(LPCTSTR lpszMinButtonImagePath, LPCTSTR lpszMaxButtonImagePath, LPCTSTR lpszCloseButtonImagePath);

protected:
	// ��� �׸��� �۾��� ���⼭ �Ѵ�. (OnPaint �������̵� ����)
	virtual void OnDrawCherry(CCherryMemDC *pDC) = 0; // �ڽ� Ŭ�������� �����ϵ��� �Ѵ�.

	// ��� CherryCtrl ���� ���⼭ �����Ѵ�.
	virtual BOOL OnCreateCherry();	
	
// Overridables
	virtual BOOL OnInitDialog();

// Implementation
public:
	virtual ~CCherryDialog();

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	
	virtual void OnDrawSystemButton(CCherryMemDC *pDC);

	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnNcMouseLeave();
	virtual void PreSubclassWindow();
};
