// CDlgForm.cpp: 구현 파일
//

#include "pch.h"
#include "MfcExam.h"
#include "afxdialogex.h"
#include "CDlgForm.h"


// CDlgForm 대화 상자

IMPLEMENT_DYNAMIC(CDlgForm, CDialogEx)

CDlgForm::CDlgForm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgForm, pParent)
{

}

CDlgForm::~CDlgForm()
{
}

void CDlgForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgForm, CDialogEx)
END_MESSAGE_MAP()


// CDlgForm 메시지 처리기
