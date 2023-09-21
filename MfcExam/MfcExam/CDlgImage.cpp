// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "MfcExam.h"
#include "MfcExamDlg.h"
#include "afxdialogex.h"
#include "CDlgImage.h"


// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgImage, pParent)
{
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_WM_PAINT()
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	InitImage(640, 480, 8);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	// 이미지를 화면에 출력합니다.
	if (m_Image) {
		m_Image.Draw(dc, 0, 0);
	}
}

// CImage에 원과 마커를 그립니다.
void CDlgImage::DrawCircle(int aX, int aY, int nRadius)
{
	CPaintDC dc(this);
	CDC* pDC = &dc;
	
	// 흰색 배경 그리기
	CRect nBg(-1, -1, 640, 480);
	pDC->Rectangle(nBg);

	// 보더 색상 설정
	CPen pen(PS_SOLID, 2, COLOR_YELLOW);
	CPen* pOldPen = pDC->SelectObject(&pen);

	// 원 그리기
	CRect rect(aX, aY, aX + nRadius * 2, aY + nRadius * 2);
	pDC->Ellipse(rect);

	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	DrawCenterMarker(pDC, aX + nRadius, aY + nRadius);
}

// 원의 중심을 나타내는 크로스헤드 마커를 그립니다.
void CDlgImage::DrawCenterMarker(CDC* pDC, int nCenterX, int nCenterY)
{
	int nTh = 4;

	CPen pen(PS_SOLID, 1, RGB(0x00, 0x00, 0x00));
	CPen* pOldPen = pDC->SelectObject(&pen);

	pDC->MoveTo(nCenterX - nTh, nCenterY);
	pDC->LineTo(nCenterX + nTh + 1, nCenterY);
	pDC->MoveTo(nCenterX, nCenterY - nTh);
	pDC->LineTo(nCenterX, nCenterY + nTh + 1);

	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}

// CImage를 작성합니다.
void CDlgImage::InitImage(int nWidth, int nHeight, int nBpp)
{
	const int kRgb = 256;

	m_Image.Create(nWidth, -nHeight, nBpp);

	if (nBpp == 8) {
		static RGBQUAD rgb[kRgb];

		for (int i = 0; i < kRgb; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}

		m_Image.SetColorTable(0, kRgb, rgb);
	}

	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);
}
