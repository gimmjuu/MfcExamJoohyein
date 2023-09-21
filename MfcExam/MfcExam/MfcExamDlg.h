
// MfcExamDlg.h: 헤더 파일
//
#include "CDlgImage.h"	// Add custom class header : 작성한 클래스를 참조합니다.
#include "CDlgForm.h"

#pragma once
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 

#define IMAGE_WIDTH		640
#define IMAGE_HEIGHT	480

// CMfcExamDlg 대화 상자
class CMfcExamDlg : public CDialogEx
{
// 생성입니다.
public:
	CMfcExamDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CDlgImage* m_pDlgImage;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCEXAM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnCircle();
	void SetTextCenterInfo(int nX, int nY);
	void SetTextOtherInfo(CString nStr);
	void ClearDlgImage();
	afx_msg void OnBnClickedBtnClr();
	afx_msg void OnBnClickedBtnCalculator();
};
