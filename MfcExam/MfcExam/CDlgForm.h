#pragma once
#include "afxdialogex.h"
#include <iostream>
#include <string>
#include <stack>
using namespace std;


// CDlgForm 대화 상자

class CDlgForm : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgForm)

public:
	CDlgForm(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgForm();

	CString m_operator;
	int m_isProcessed = 0;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgForm };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	void ClearControlText();

public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnClr();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnDot();
	void OnBnClickedBtnNum(UINT uiID);
	afx_msg void OnBnClickedBtnOp(UINT uiID);
	void OnBnClickedBtnEnt();
	double ParseCStringtoValue(CString nTargetString);
	double CalculateValue(double a, CString op, double b);
	CString RstripDoublebyZero(double nTarget);
};
