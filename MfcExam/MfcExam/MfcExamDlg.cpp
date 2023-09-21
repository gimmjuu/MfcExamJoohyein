
// MfcExamDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MfcExam.h"
#include "MfcExamDlg.h"
#include "afxdialogex.h"

#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMfcExamDlg 대화 상자



CMfcExamDlg::CMfcExamDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCEXAM_DIALOG, pParent)
{
	m_pDlgImage = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcExamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMfcExamDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_CIRCLE, &CMfcExamDlg::OnBnClickedBtnCircle)
	ON_BN_CLICKED(IDC_BTN_CLR, &CMfcExamDlg::OnBnClickedBtnClr)
	ON_BN_CLICKED(IDC_BTN_CALCULATOR, &CMfcExamDlg::OnBnClickedBtnCalculator)
END_MESSAGE_MAP()


// CMfcExamDlg 메시지 처리기

BOOL CMfcExamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, 1080, 600);

	CFont font1;
	font1.CreatePointFont(140, _T("Verdana"));
	GetDlgItem(IDC_RADIUS_TITLE)->SetFont(&font1);
	font1.Detach();

	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_CDlgImage, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(40, 40, IMAGE_WIDTH, IMAGE_HEIGHT);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMfcExamDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMfcExamDlg::OnPaint()
{
	if (IsIconic()) {
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMfcExamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMfcExamDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_pDlgImage)	delete m_pDlgImage;
}

// 사용자가 입력한 반지름을 가져와 CDlgImage 영역에 원을 출력합니다.
void CMfcExamDlg::OnBnClickedBtnCircle()
{
	CString nStr;
	GetDlgItemText(IDC_EDIT_RADIUS, nStr);
	int nRadius = _ttoi(nStr);

	if (nRadius < 9 || nRadius >= 240) {
		ClearDlgImage();
		SetTextOtherInfo(_T("잘못된 입력값입니다."));
		return;
	}

	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();

	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();

	int aX = rand() % (nWidth - nRadius * 2);
	int aY = rand() % (nHeight - nRadius * 2);

	m_pDlgImage->Invalidate();

	m_pDlgImage->DrawCircle(aX, aY, nRadius);
	SetTextCenterInfo(aX + nRadius, aY + nRadius);
}

// 무게 중심 좌표를 Static Text로 출력합니다.
void CMfcExamDlg::SetTextCenterInfo(int nX, int nY)
{
	CString nText;
	nText.Format(_T("현재 원의 무게 중심은 (%d, %d)에 위치합니다."), nX, nY);
	SetDlgItemText(IDC_STATIC_RESULT, nText);
}

// 현재 입력값에 대한 정보를 Static Text에 출력합니다.
void CMfcExamDlg::SetTextOtherInfo(CString nStr)
{
	SetDlgItemText(IDC_EDIT_RADIUS, _T(""));
	SetDlgItemText(IDC_STATIC_RESULT, nStr);
}

// CImage 영역을 흰색으로 초기화합니다.
void CMfcExamDlg::ClearDlgImage()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();

	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();

	memset(fm, 0xff, nWidth * nHeight);

	m_pDlgImage->Invalidate();
}

// Clear 버튼 클릭 시 화면과 텍스트를 모두 초기화합니다.
void CMfcExamDlg::OnBnClickedBtnClr()
{
	ClearDlgImage();
	SetTextOtherInfo(_T("현재 입력한 값이 없습니다."));
}


// CDlgForm을 모달창으로 출력합니다.
void CMfcExamDlg::OnBnClickedBtnCalculator()
{
	CDlgForm calculator;
	calculator.DoModal();
}
