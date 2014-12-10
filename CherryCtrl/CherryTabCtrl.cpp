#include "stdafx.h"
#include "CherryTabCtrl.h"

IMPLEMENT_DYNAMIC(CCherryTabCtrl, CCherryWnd)

CCherryTabCtrl::CCherryTabCtrl()
{
	m_pHeadTab = NULL;
	m_dwCherryStyle = 0;
	m_nTabGap = 0;
	m_nCtrlIDCount = 0;
}

CCherryTabCtrl::~CCherryTabCtrl()
{
	for (vector<CCherryRadioButton *>::iterator it = m_tabVector.begin(); it != m_tabVector.end(); ++it)
	{
		((CCherryRadioButton *)*it)->DestroyWindow();
		delete (CCherryRadioButton *)*it;
	}
	
	/*
	// ������ ������ ����
	vector<CCherryWnd *> *pPageVector = GetPageVector();

	dwSize = pPageVector->size();

	for (vector<CCherryWnd *>::iterator it = pPageVector->begin(); it != pPageVector->end(); ++it)
	{
		(CCherryWnd *)
		//((CCherryWnd *)*it)->DestroyWindow();
		//delete (CCherryWnd *)*it;
	}
	*/
}

BEGIN_MESSAGE_MAP(CCherryTabCtrl, CCherryWnd)
	ON_WM_SIZE()
END_MESSAGE_MAP()

CHERRY_RET CCherryTabCtrl::Create(LPCTSTR lpszTabImagePath, DWORD dwCherryStyle, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID)
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (!CCherryWnd::Create(NULL, NULL, dwStyle, rect, pParentWnd, nID))
			throw CCherryException::ERROR_TABCTRL_CREATE_FAIL;

		ModifyCherryStyle(0, dwCherryStyle);

		m_lpszTabImagePath = lpszTabImagePath;

		m_nCtrlIDCount = nID;
	}
	catch (const CHERRY_RET &errorRet)
	{
		return errorRet;
	}

	return cherryRet;
}

void CCherryTabCtrl::OnDrawCherry(CCherryMemDC *pDC)
{
}

CHERRY_RET CCherryTabCtrl::AddPage(CCherryWnd *pWnd)
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (!GetSafeHwnd())
			throw CCherryException::ERROR_TABCTRL_NOT_CREATED;

		if (pWnd == NULL || !pWnd->GetSafeHwnd())
			throw CCherryException::ERROR_TABCTRL_CREATE_FAIL;

		// ĸ���� �����쿡�� ��������
		CString strCaption;
		pWnd->GetWindowText(strCaption);
		pWnd->SetParent(this);

		// ��ư �Ҵ�
		CCherryRadioButton *pTab = new CCherryRadioButton();
		if ((cherryRet = pTab->Create(
			strCaption, 
			m_lpszTabImagePath,
			CCherryRadioButton::STYLE_AUTORESIZE |
			CCherryRadioButton::STYLE_AUTOCHECKBOX |
			CCherryRadioButton::STYLE_BUTTONTYPE,
			m_pHeadTab, 
			WS_CHILD | WS_VISIBLE, 
			CRect(), 
			this, 
			++m_nCtrlIDCount)) != CCherryException::ERROR_CHERRY_SUCCESS) // �� ���� �� ��Ʈ�� ���̵� ������ ���� ����ó�� �ʿ�
			throw cherryRet;

		// �� ��ư �⺻ ��Ÿ�� ����
		pTab->SetNormalFontStyle(CCherryFont::STYLE_CENTER | CCherryFont::STYLE_VCENTER);
		pTab->SetHoverFontStyle(CCherryFont::STYLE_CENTER | CCherryFont::STYLE_VCENTER);
		pTab->SetDownFontStyle(CCherryFont::STYLE_CENTER | CCherryFont::STYLE_VCENTER);
		pTab->SetDisableFontStyle(CCherryFont::STYLE_CENTER | CCherryFont::STYLE_VCENTER);

		if (m_pHeadTab == NULL)	// ù ��° ��ư�� ���� �Ҵ�
		{
			m_pHeadTab = pTab;
			m_pHeadTab->SetCheck(CCherryRadioButton::STATUS_CHECKED); // ù ��° ��ư ����Ʈ üũ

			if (!pWnd->IsWindowVisible())
				pWnd->ShowWindow(SW_SHOW);
		}
		else
		{
			pWnd->ShowWindow(SW_HIDE);
		}

		m_tabVector.push_back(pTab);
		m_pageVector.push_back(pWnd);

		ResizeWindow();
	}
	catch (const CHERRY_RET &errorRet)
	{
		return errorRet;
	}

	return cherryRet;
}

void CCherryTabCtrl::ResizeWindow()
{
	CRect clientRect;
	GetClientRect(clientRect);

	DWORD dwCount = (DWORD)m_tabVector.size();

	for (vector<CCherryRadioButton *>::iterator it = m_tabVector.begin(); it != m_tabVector.end(); ++it)
	{
		DWORD dwPos = it - m_tabVector.begin();
		CRect buttonRect;
		((CCherryRadioButton *)*it)->GetClientRect(buttonRect);

		int nLeft = 0, nTop = 0;
		int nWidth = 0, nHeight = buttonRect.Height();
		int nWidthGap = 0, nHeightGap = 0;

		switch (GetCherryStyle())
		{
		case STYLE_TAB_TOP:
			nWidthGap = m_nTabGap;
			nWidth = clientRect.Width() / dwCount;
			nLeft = nWidth * dwPos;
			break;
		case STYLE_TAB_BOTTOM:
			nWidthGap = m_nTabGap;
			nWidth = clientRect.Width() / dwCount;
			nLeft = nWidth * dwPos;
			nTop = clientRect.bottom - nHeight;
			break;
		case STYLE_TAB_LEFT:
			nHeightGap = m_nTabGap;
			nHeight = clientRect.Height() / dwCount;
			nTop = nHeight * dwPos;
			nWidth = buttonRect.Width();
			break;
		case STYLE_TAB_RIGHT:
			nHeightGap = m_nTabGap;
			nLeft = clientRect.Width() - buttonRect.Width();
			nHeight = clientRect.Height() / dwCount;
			nTop = nHeight * dwPos;
			nWidth = buttonRect.Width();
			break;
		default:
			ASSERT(0);
			break;
		}

		((CCherryRadioButton *)*it)->MoveWindow(nLeft, nTop, nWidth - nWidthGap, nHeight - nHeightGap);
	}

	if (m_pHeadTab)
	{
		CRect buttonRect;
		m_pHeadTab->GetClientRect(buttonRect);

		CRect pageRect;
		switch (GetCherryStyle())
		{
		case STYLE_TAB_TOP:
			pageRect.SetRect(0, buttonRect.Height(), clientRect.Width(), clientRect.Height());
			break;
		case STYLE_TAB_BOTTOM:
			pageRect.SetRect(0, 0, clientRect.Width(), clientRect.Height() - buttonRect.Height());
			break;
		case STYLE_TAB_LEFT:
			pageRect.SetRect(buttonRect.Width(), 0, clientRect.Width(), clientRect.Height());
			break;
		case STYLE_TAB_RIGHT:
			pageRect.SetRect(0, 0, clientRect.Width() - buttonRect.Width(), clientRect.Height());
			break;
		default:
			ASSERT(0);
			break;
		}

		for (vector<CCherryWnd *>::iterator it = m_pageVector.begin(); it != m_pageVector.end(); ++it)
			((CCherryWnd *)*it)->MoveWindow(pageRect);
	}
}

DWORD CCherryTabCtrl::GetCurPage()
{
	for (vector<CCherryRadioButton *>::iterator it = m_tabVector.begin(); it != m_tabVector.end(); ++it)
	{
		DWORD dwPos = it - m_tabVector.begin();
		if (((CCherryRadioButton *)*it)->GetCheck() == CCherryRadioButton::STATUS_CHECKED)
			return dwPos;
	}

	return 0;
}

void CCherryTabCtrl::SetCurPage(DWORD dwIndex)
{
	if (m_tabVector.empty() || m_tabVector.size() < dwIndex)
		return;

	// �� ��ư üũ
	m_tabVector.at(dwIndex)->SetCheck(CCherryRadioButton::STATUS_CHECKED);
	
	// �ش� ������ ���̱�
	for (vector<CCherryWnd *>::iterator it = m_pageVector.begin(); it != m_pageVector.end(); ++it)
	{
		DWORD dwPos = it - m_pageVector.begin();
		if (dwIndex == dwPos)
		{
			((CCherryWnd *)*it)->ShowWindow(SW_SHOW);

			continue;
		}

		((CCherryWnd *)*it)->ShowWindow(SW_HIDE);
	}

	// ���� �ʿ�
	GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(dwIndex, WM_CHERRY_TABCTRL_PAGE_CHANGED), (LPARAM)GetSafeHwnd());
}

DWORD CCherryTabCtrl::GetCherryStyle() const	
{
	return m_dwCherryStyle;
}

void CCherryTabCtrl::ModifyCherryStyle(DWORD dwRemove, DWORD dwAdd)
{
	m_dwCherryStyle &= ~dwRemove;
	m_dwCherryStyle |= dwAdd;
}

void CCherryTabCtrl::SetTabGap(UINT nGap)
{
	m_nTabGap = nGap;
	ResizeWindow();
}

vector<CCherryRadioButton *> *CCherryTabCtrl::GetTabVector()
{
	return &m_tabVector;
}

vector<CCherryWnd *> *CCherryTabCtrl::GetPageVector()
{
	return &m_pageVector;
}

CCherryRadioButton *CCherryTabCtrl::GetTab(UINT nIndex) const
{
	if (m_tabVector.empty())
		return NULL;

	return m_tabVector.at(nIndex);
}

CCherryWnd *CCherryTabCtrl::GetPage(UINT nIndex) const
{
	if (m_pageVector.empty())
		return NULL;

	return m_pageVector.at(nIndex);
}

DWORD CCherryTabCtrl::GetPageCount() const
{
	return (DWORD)m_pageVector.size();
}

void CCherryTabCtrl::OnSize(UINT nType, int cx, int cy)
{
	CCherryWnd::OnSize(nType, cx, cy);

	ResizeWindow();
}

LRESULT CCherryTabCtrl::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED)
	{
		UINT nCtrlID = LOWORD(wParam);
		for (vector<CCherryRadioButton *>::iterator it = m_tabVector.begin(); it != m_tabVector.end(); ++it)
		{
			if (((CCherryRadioButton *)*it)->GetSafeHwnd())
			{
				if (((CCherryRadioButton *)*it)->GetDlgCtrlID() == nCtrlID)
				{
					DWORD dwPos = it - m_tabVector.begin();
					SetCurPage(dwPos);
				}
			}
		}
	}

	return CCherryWnd::DefWindowProc(message, wParam, lParam);
}

DWORD CCherryTabCtrl::DeleteTabPage(DWORD dwIndex)
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (m_pageVector.empty() || (m_pageVector.size() - 1) < dwIndex)
			throw CCherryException::ERROR_TABCTRL_OUT_OF_BOUND;

		// �� ����
		vector<CCherryRadioButton *>::iterator it = m_tabVector.begin() + dwIndex;
		((CCherryRadioButton *)*it)->DestroyWindow();
		delete (CCherryRadioButton *)*it;
		m_tabVector.erase(it);

		// ������ ����
		m_pageVector.at(dwIndex)->DestroyWindow();
		m_pageVector.erase(m_pageVector.begin() + dwIndex);

		// �� �׷쿡�� �׷��� ���� ����
		if (m_pageVector.empty())
			m_pHeadTab = NULL;
		else
			m_pHeadTab = (CCherryRadioButton *)*m_tabVector.begin();

		// ���������� üũ�� �� �������� ����
		SetCurPage(GetCurPage());

		ResizeWindow();
	}
	catch (const CHERRY_RET &errorRet)
	{
		return errorRet;
	}

	return cherryRet;
}

DWORD CCherryTabCtrl::DeleteTabPageAll()
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (!GetSafeHwnd())
			throw CCherryException::ERROR_TABCTRL_NOT_CREATED;

		for (vector<CCherryRadioButton *>::iterator it = m_tabVector.begin(); it != m_tabVector.end(); ++it)
		{
			// ��ư ����
			((CCherryRadioButton *)*it)->DestroyWindow();
			delete (CCherryRadioButton *)*it;
		}

		m_tabVector.clear();

		for (vector<CCherryWnd *>::iterator it = m_pageVector.begin(); it != m_pageVector.end(); ++it)
		{
			// ������ ����
			((CCherryWnd *)*it)->DestroyWindow();
		}

		m_pageVector.clear();

		m_pHeadTab = NULL;

		ResizeWindow();
	}
	catch (const CHERRY_RET &errorRet)
	{
		return errorRet;
	}

	return cherryRet;
}
