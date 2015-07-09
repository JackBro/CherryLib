#pragma once

#include "CherryMemDC.h"

// CCherryWnd

class AFX_EXT_CLASS CCherryWnd : public CWnd
{
	DECLARE_DYNAMIC(CCherryWnd)

// Constructors
public:
	CCherryWnd();

// Attributes
protected:
	CCherryMemDC *m_pBackMemDC;
	BOOL m_bShowed;

// Operations
public:
	void SetBackground(CDC *pDC);

// Implementation
public:
	virtual ~CCherryWnd();

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnPaint();

	// ��� �׸��� �۾��� ���⼭ �Ѵ�. (OnPaint �������̵� ����)
	virtual void OnDrawCherry(CCherryMemDC *pDC) = 0; // �ڽ� Ŭ�������� �����ϵ��� �Ѵ�.

	// OnCreate ������ ��Ʈ���� �����ϴ� �۾��� ���� ��� ���, �����Ͽ� ����Ѵ�. OnInitDialog() �Լ��� �����.
	virtual void OnLoad();
};


