#pragma once

#include "CherryWnd.h"
#include "CherryException.h"
#include "CherryImage.h"
#include "CherryMemDC.h"

///////////////////////////////////////////////////////////////////////////
///
/// \class		CCherryImageCtrl
/// \brief		�̹��� ��Ʈ�� Ŭ����
/// \author		����ö
/// \date		2013-07-10
/// \remark		
/// \section	
///
///////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CCherryImageCtrl : public CCherryWnd
{
	DECLARE_DYNAMIC(CCherryImageCtrl)

// Constructors
public:
	CCherryImageCtrl();
	virtual CHERRY_RET Create(
		LPCTSTR lpszImagePath,
		DWORD dwStyle,
		const RECT& rect, 
		CWnd* pParentWnd, 
		UINT nID);

// Attributes
protected:
	CCherryImage m_image;
	
// Operations
public:
	CHERRY_RET SetImage(LPCTSTR lpszImagePath, int nWidth, int nHeight);

// Implementation
public:
	virtual ~CCherryImageCtrl();
protected:
	DECLARE_MESSAGE_MAP()

	void OnDrawCherry(CCherryMemDC *pDC);

	afx_msg void OnPaint();
};


