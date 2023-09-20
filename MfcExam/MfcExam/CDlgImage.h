﻿#pragma once
#include "afxdialogex.h"


// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();

	CImage m_Image;
	CWnd* m_pParent;
	int m_nDataCount = 0;
	CPoint m_ptData[100];

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgImage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	void DrawData(CDC* pDC);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitImage();
	afx_msg void OnPaint();
};