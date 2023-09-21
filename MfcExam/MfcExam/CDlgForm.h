#pragma once
#include "afxdialogex.h"


// CDlgForm 대화 상자

class CDlgForm : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgForm)

public:
	CDlgForm(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgForm();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgForm };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
