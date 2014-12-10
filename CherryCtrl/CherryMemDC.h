#pragma once

#include "CherryException.h"

///////////////////////////////////////////////////////////////////////////
///
/// \class		CCherryMemDC
/// \brief		Memory DC Ŭ���� (Double buffering)\n
///				CherryX ���� ����ϴ� Memory DC�� �� Ŭ������ ����Ѵ�.
/// \author		����ö
/// \date		2012-11-09
/// \remark		
/// \section	
///
///////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CCherryMemDC : public CDC
{
// Constructors
public:
	CCherryMemDC(CDC *pDC, BOOL bDrawOut = TRUE);
	CCherryMemDC(CDC *pDC, CRect &rect, BOOL bDrawOut = TRUE);
	
// Attributes
private:
	CDC			*m_pDC;
	CBitmap		m_bitmap;
	CBitmap		*m_pOldBitmap;

	CRect		m_rect;
	BOOL		m_bMemDC;
	BOOL		m_bDrawOut;

// Operations
public:
	BOOL Draw(CDC *pDC);
	void EnableDrawOut(BOOL bDrawOut = TRUE);

	CCherryMemDC *operator->();	 
	operator CCherryMemDC *();

protected:
	void Initialize(CDC *pDC, const CRect *pRect, BOOL bDrawOut);

// Implementation
public:
	virtual ~CCherryMemDC();
};
