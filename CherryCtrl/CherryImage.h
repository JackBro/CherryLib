#pragma once

#include "CherryException.h"

using namespace Gdiplus;

///////////////////////////////////////////////////////////////////////////
///
/// \class		CCherryFont
/// \brief		�̹��� ���� Ŭ����\n
///				CherryX ���� ����ϴ� ��� �̹����� �� Ŭ������ ����Ͽ� ǥ���ϵ��� �Ѵ�.\n
///				���� ����ϱ� ���� ����Ͽ� ����ϴ� ���� and �߻� Ŭ���� ������ �����ִ�.
/// \author		ogoons
/// \date		2012-11-09
/// \remark		
/// \section	
///
///////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CCherryImage
{
// Constructors
public:
	CCherryImage();
	CCherryImage(LPCTSTR lpszImagePath, BOOL bUseCachedImage = FALSE);
	CCherryImage(Bitmap *pBitmap, BOOL bUseCachedImage = FALSE);
	CCherryImage(Bitmap *pBitmap, int nLeft, int nTop, int nWidth, int nHeight, BOOL bUseCachedImage = FALSE);
	CCherryImage(Bitmap *pBitmap, Rect rect, BOOL bUseCachedImage = FALSE);
	CCherryImage(const CCherryImage &image);

// Attributes
protected:
	Bitmap			*m_pBitmap;
	
	CachedBitmap	*m_pCachedBitmap;
	CRect			m_cachedBitmapRect;
	
	BOOL			m_bUseCachedImage;

	static CString	m_strDefaultImagePath;
// Operations
public:
	// �̹����� �ε� �Ǿ�����
	BOOL			IsLoadedImage() const;
	
	// Bitmap ��ü �����͸� ������
	Bitmap			*GetBitmap() const;
	
	// ��ü �̹��� ����� ������
	CSize			GetSize() const;
	
	// ���� ũ�⸦ ������
	UINT			GetWidth() const;
	
	// ���� ũ�⸦ ������
	UINT			GetHeight() const;

	// ������ ���� ���� ������
	Status			GetBitmapLastStatus() const;

	// ĳ�õ� �̹��� ���
	void									UseCachedImage(BOOL bUse = TRUE);

	// �̹��� �о����
	CHERRY_RET		LoadImage(LPCTSTR lpszImagePath, BOOL bUseCachedImage = FALSE);
	CHERRY_RET		LoadImage(Bitmap *pBitmap, BOOL bUseCachedImage = FALSE);
	CHERRY_RET		LoadImage(Bitmap *pBitmap, int nLeft, int nTop, int nWidth, int nHeight, BOOL bUseCachedImage);
	CHERRY_RET		LoadImage(Bitmap *pBitmap, Rect rect, BOOL bUseCachedImage = FALSE);
	CHERRY_RET		LoadImageFromResourceID(LPCTSTR lpszResourceType, UINT nResourceID, BOOL bUseCachedImage = FALSE);

	// ����� ��ϵ� �̹��� �׸���
	CHERRY_RET		DrawImage(Graphics *pGraphics, int nLeft, int nTop, UINT nAlphaBlendRatio = 100);
	CHERRY_RET		DrawImage(Graphics *pGraphics, int nLeft, int nTop, int nRight, int nBottom, UINT nAlphaBlendRatio = 100);
	CHERRY_RET		DrawImage(Graphics *pGraphics, CRect rect, UINT nAlphaBlendRatio = 100);

	//// Ȯ�볪 ��ҵ� �̹��� �׸���(��� �� ��)
	//BOOL			DrawRatioImage(Graphics *pGraphics, int nLeft, int nTop, UINT nRatio, UINT nAlphaBlendRatio = 100);	
	//BOOL			DrawRatioImage(Graphics *pGraphics, CPoint point, UINT nRatio, UINT nAlphaBlendRatio = 100);
	//

	// 3x3 ���� �����Ͽ� Ȯ�� �׸���(�ܰ��� ���� ������)
	CHERRY_RET		DrawStretchImage3x3(Graphics *pGraphics, int nLeft, int nTop, int nRight, int nBottom, UINT nAlphaBlendRatio = 100);
	CHERRY_RET		DrawStretchImage3x3(Graphics *pGraphics, CRect rect, UINT nAlphaBlendRatio = 100);

	// ����� �Ҵ�� Bitmap ��ü ����
	BOOL									RemoveImage();
	
	// ����� �Ҵ�� ĳ�õ� Bitmap ��ü ����
	BOOL									RemoveCachedImage();

	static void		SetDefaultImagePath(LPCTSTR lpszPath);
	

protected:
	// �ߺ��Ǵ� ������ �ϳ��� ��� Ŭ���� ���ο����� ����ϴ� �̹��� Draw �Լ�
	Status			MakeImage(Graphics *pGraphics, Rect rect, UINT nAlphaBlendRatio);
	Status			MakeStretchImage3x3(Graphics *pGraphics, Rect rect, UINT nAlphaBlendRatio);

	// �̹��� �Ӽ��� ���� ȿ��
	Status			CaculatedAlphaBlendAttributes(_In_ UINT nAlphaBlendRatio, _Out_ ImageAttributes &imageAttributes);

	// ĳ�õ� �̹����� ������Ʈ
	Status			UpdateCachedImage(Graphics *pGraphics, CRect rect, UINT nAlphaBlendRatio, BOOL bUseDrawStretch3x3 = FALSE);

// Implementation
public:
	virtual	~CCherryImage();
};