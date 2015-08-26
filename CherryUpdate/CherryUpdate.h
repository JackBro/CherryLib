#pragma once

//#define USE_MFC_CLASS
//#define INCLUDE_FILE_SIZE_INFO

#include "afxinet.h"
#include "wininet.h"
#pragma comment(lib, "wininet.lib")

#include "sensapi.h"
#pragma comment(lib, "sensapi.lib")

#include <vector>
using namespace std;

#include "tinyxml2.h"
#ifdef _DEBUG
#pragma comment(lib, "TinyXML2D.lib")
#else
#pragma comment(lib, "TinyXML2.lib")
#endif
using namespace tinyxml2;

#include "CherryException.h"

///////////////////////////////////////////////////////////////////////////
///
/// \class		CCherryUpdate
/// \brief		���̺� ������Ʈ �Ŵ��� Ŭ����
/// \author		ogoons
/// \date		2014-05-19
///
/// \remark		Win32 / MFC ���� �� ������ ���еǸ� 
///             ��� USE_MFC_CLASS define�� ����ϸ� MFC Ŭ������ �����
///             ���̺� ������Ʈ dll ���尡 �����ϴ�.
///             �ӵ��� ������ ũ�Ƿ� Win32 ���� ���带 ��õ�Ѵ�.
///
/// \warning	- �ѱ� �̸����� �� ������ �ٿ�ε� �� �� ����.
///				- ������ ���� �ʼ�	
///				- TinyXML2 ���̺귯�� �ʿ�
/// \section	
///
///////////////////////////////////////////////////////////////////////////

#ifdef USE_MFC_CLASS
class AFX_EXT_CLASS CCherryUpdate : public CInternetSession
#else
class AFX_EXT_CLASS CCherryUpdate
#endif
{
// Constructors
public:
	CCherryUpdate();
	BOOL Open(
		LPCTSTR lpszAgent,
		LPCTSTR lpszClientVersion,
		LPCTSTR lpszRootUrl,
		LPCTSTR lpszUpdateProfileXml,
		LPCTSTR lpszPatchTargetPath,
		BOOL bUseUtf8 = TRUE);							// ������Ʈ�� �ʿ��� ������ ��� �޸𸮿� �ε��ϰ� ������Ʈ �غ� ����

// Attributes
protected:
#ifndef USE_MFC_CLASS
	HINTERNET m_hSession;
#endif

#ifdef INCLUDE_FILE_SIZE_INFO
	// ���� ����Ʈ�� ���� ����ü
	typedef struct _FILE_ATTR
	{
		CString		strFile;
		LONGLONG	llSize;
	} FILE_ATTR, *PFILE_ATTR;
#endif

	// ������Ʈ �������� ���� xml���� ������ �����͸� ���� ����ü
	typedef struct _UPDATE_PROFILE
	{
		//vector<CString> packageFileVector;

#ifdef INCLUDE_FILE_SIZE_INFO
		vector<FILE_ATTR> fileUrlVector;
#else
		vector<CString> fileUrlVector;
#endif
		CString			strNewVerion;
		CString			strRootUrl;
		BOOL			bPackageUpdate;
		CString			strRunPackageFilePath;
		ULONGLONG		llFileTotalSize;

		void Initialize()
		{
			fileUrlVector.clear();
			strNewVerion.Empty();
			strRootUrl.Empty();
			bPackageUpdate = TRUE;
			strRunPackageFilePath.Empty();
			llFileTotalSize = 0;
		}
	} UPDATE_PROFILE, *PUPDATE_PROFILE;

	UPDATE_PROFILE m_updateProfile;

	CString		m_strAgent;
	CString		m_strClientVersion;
	CString		m_strPatchTargetPath;

	CWinThread	*m_pUpdateProcessThread;
	BOOL		m_bStarted;
	BOOL		m_bRunPackage;
	ULONGLONG	m_llReceivedSize; // ������� �ٿ�ε� ���� ������ ���

	// Callback
	void (*m_pDownloadStatusCallback)(ULONGLONG, ULONGLONG, void *);
	void (*m_pDownloadCompleteCallback)(BOOL, BOOL, void *);
	void (*m_pPatchCompleteCallback)(BOOL, BOOL, void *);

	void *m_pDownloadStatusUserData;
	void *m_pDownloadCompleteUserData;
	void *m_pPatchCompleteUserData;

// Operations
public:
	BOOL		IsOpen() const;																									// Internet session�� ���� open�Ǿ ������Ʈ�� ������ ��������
	BOOL		IsStarted() const;																								// ������Ʈ ���� ����
	BOOL		CheckNewVersion(LPCTSTR lpszCurrentVersion);																	// �� ���� ���� ����
	CHERRY_RET	OpenUpdateProfile(LPCTSTR lpszRootUrl, LPCTSTR lpszUpdateProfileXml, BOOL bUseUtf8 = TRUE);						// ������Ʈ ���� ���� ����(�ٿ�ε�, �Ľ�, �޸� �ε�)

	BOOL		StartUpdate();																									// ������Ʈ ����
	BOOL		StopUpdate();																									// ������Ʈ �ߴ�

	BOOL		DownloadFile(_In_ LPCTSTR lpszUrl, _In_ LPCTSTR lpszDownloadPath, _Out_ CString &strReceivedFullPath);			// ���� �ٿ�ε�
	BOOL		SendHttpRequest(_In_ LPCTSTR lpszUrl, _In_ BOOL bPost, _In_ LPCTSTR lpszPostData, _Out_ CString &strResponse);	// ������ �������� ��û ������

	ULONGLONG	GetTotalReceiveFileSize();																						// ���� ������ �� ������ �������� (Open�� �������� �� ����)
	void		EnableRunPackage(BOOL bRun = TRUE);																				// ��Ű�� ������Ʈ �� ��Ű�� ������ ����/����� ����

	// Set callback
	void		SetDownloadStatusCallback(LPVOID lpCallbackFunc, void *pUserData);												// �ٿ�ε� ���� ���� ��ȭ �� ȣ��
	void		SetDownloadCompleteCallback(LPVOID lpCallbackFunc, void *pUserData);											// �ٿ�ε� �Ϸ� �� ȣ��
	void		SetPatchCompleteCallback(LPVOID lpCallbackFunc, void *pUserData);												// �ٿ�ε� �� ������ �ش� ���丮�� ���� �Ϸ� �� ȣ��

	// Utilities
	static BOOL		IsInternetConnected();																						// ���ͳ� ���� ����
	static BOOL		GetFileVersion(_In_ LPCTSTR lpszFilePath, _Out_ CString &strVersion);										// ������ ���� ��������		
	static BOOL		GetFileSize(_In_ LPCTSTR lpszFilePath, _Out_ LONGLONG &llFileSize);											// ������ ������ ��������
	static BOOL		ExecuteProcess(_In_ LPCTSTR lpszPath, _In_ LPCTSTR lpszParam = NULL, _In_ BOOL bWaitProcess = FALSE);		// ���μ��� ����															// ���� ����
	static int		CompareVersion(LPCTSTR lpszCurrentVersion, LPCTSTR lpszNewVersion);											// ���� ��
	static void		CreateDirectoryAndParent(LPTSTR lpszPath);																	// ���丮 ����(path �� ���� ���丮�� ���ٸ� ���� ����)
	static BOOL		DeleteDirectoryAndChild(LPCTSTR lpszPath);																	// ���丮 ����(���� ���丮, ���� ��� ����)
	static CString	ConvertUtf8ToUnicode(_In_ LPCWSTR lpszUtf8);																// UTF-8 -> Unicode(UTF-8 LE)
	void			UrlEncode(char *output, char *input);																		// ���� ��� �� ��

#ifdef USE_MFC_CLASS
	virtual void	Close();
#else
	BOOL			Close();																									// ���� �ݱ�
#endif

protected:
	void			Initialize();																								// �ʱ�ȭ
	CString			GetIncomingPath();																							// �ٿ�ε�� ������ �ӽ� ����� ���丮 ��� ��������

	void			ParseFileNode(BOOL bPackageNode, XMLNode *pFileListNode, LPCTSTR lpszRootUrl, BOOL bUseUtf8);				// ���� ����Ʈ ��带 �Ľ��Ͽ� �����´�. (���ο����� ���)

	// Thread
	static UINT		UpdateProcessThread(LPVOID lpParam);																		// ���� �ٿ�ε忡�� ��������� ��� ������Ʈ ���� ������ (Worker thread)

// Implementation
public:
	virtual ~CCherryUpdate();
};