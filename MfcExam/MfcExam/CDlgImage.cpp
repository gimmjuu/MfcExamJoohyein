﻿// CDlgImage.cpp: 구현 파일
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
	m_pParent = pParent;
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
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	InitImage();

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

	DrawData(&dc);
}

void CDlgImage::DrawData(CDC* pDC)
{
	// 색상 설정
	CPen pen;
	pen.CreatePen(PS_SOLID, 5, RGB(0xff, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&pen);

	// 동일 위치에 원 그리기
	CRect rect;

	for (int i = 0; i < m_nDataCount; i++) {
		rect.SetRect(m_ptData[i], m_ptData[i]);
		rect.InflateRect(2, 2);
		pDC->Ellipse(rect);
	}

	pDC->SelectObject(pOldPen);
}

// CImage를 작성합니다.
void CDlgImage::InitImage()
{
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

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