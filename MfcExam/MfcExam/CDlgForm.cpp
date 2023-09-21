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
	m_operator.Empty();
}

CDlgForm::~CDlgForm()
{
}

void CDlgForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgForm, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_CLR, &CDlgForm::OnBnClickedBtnClr)
	ON_BN_CLICKED(IDC_BTN_DEL, &CDlgForm::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_DOT, &CDlgForm::OnBnClickedBtnDot)
	ON_COMMAND_RANGE(IDC_BTN_NUM0, IDC_BTN_NUM9, CDlgForm::OnBnClickedBtnNum)
	ON_COMMAND_RANGE(IDC_BTN_ENT, IDC_BTN_DIV, CDlgForm::OnBnClickedBtnOp)
	ON_BN_CLICKED(IDC_BTN_ENT, &CDlgForm::OnBnClickedBtnEnt)
END_MESSAGE_MAP()


// CDlgForm 메시지 처리기


BOOL CDlgForm::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// Edit Control Font Size 변경
	CFont font;
	font.CreatePointFont(180, _T("Verdana"));
	GetDlgItem(IDC_EDIT_NUM)->SetFont(&font);
	font.Detach();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


HBRUSH CDlgForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	// STATIC TEXT 글자 색상 변경
	if (pWnd->GetDlgCtrlID() == IDC_PREV_VALUE) {
		pDC->SetTextColor(RGB(150, 150, 150));
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


// Clear 버튼 클릭 시 전체 내용을 초기화합니다.
void CDlgForm::OnBnClickedBtnClr()
{
	ClearControlText();
	m_isProcessed = 0;
	m_operator.Empty();
}


// 입력 컨트롤 텍스트를 초기화합니다.
void CDlgForm::ClearControlText()
{
	SetDlgItemText(IDC_EDIT_NUM, _T(""));
	SetDlgItemText(IDC_PREV_VALUE, _T(""));
}


// Del 버튼 클릭 시 Edit Control의 텍스트를 한 글자씩 삭제합니다.
void CDlgForm::OnBnClickedBtnDel()
{
	CString nEditText;
	GetDlgItemText(IDC_EDIT_NUM, nEditText);

	int length = nEditText.GetLength();

	if (length >= 1)	nEditText.Delete(length - 1);

	SetDlgItemText(IDC_EDIT_NUM, nEditText);
}


// . 버튼 클릭 시 Edit Control Text에 소수점을 추가합니다.
void CDlgForm::OnBnClickedBtnDot()
{
	CString nEditText;
	GetDlgItemText(IDC_EDIT_NUM, nEditText);

	if (nEditText.Find('.') < 0 && nEditText != "") {
		nEditText += _T('.');
		SetDlgItemText(IDC_EDIT_NUM, nEditText);
	}
	else
	{
		AfxMessageBox(_T("Invalid input value."));
	}
}


// 숫자 버튼 클릭 시 Edit Control Text에 해당 숫자를 추가합니다.
void CDlgForm::OnBnClickedBtnNum(UINT uiID)
{
	if (m_isProcessed == 1) {
		SetDlgItemText(IDC_EDIT_NUM, _T(""));
		m_isProcessed = 0;
	}
	else if (m_isProcessed == -1) {
		CString nEditText;
		GetDlgItemText(IDC_EDIT_NUM, nEditText);
		SetDlgItemText(IDC_PREV_VALUE, nEditText);
		SetDlgItemText(IDC_EDIT_NUM, _T(""));
		m_isProcessed = 2;
	}

	CString nNum;
	GetDlgItemText(uiID, nNum);

	CString nEditText;
	GetDlgItemText(IDC_EDIT_NUM, nEditText);

	if (nEditText == "") {
		nEditText = nNum;
	}
	else {
		nEditText += nNum;
	}

	SetDlgItemText(IDC_EDIT_NUM, nEditText);
}

// +-*/= 연산 기호 버튼 클릭 시 Edit Control Text에 해당 연산을 추가합니다.
void CDlgForm::OnBnClickedBtnOp(UINT uiID)
{
	if (m_isProcessed == 2)	SetDlgItemText(IDC_PREV_VALUE, _T(""));

	CString nPrevStr;
	GetDlgItemText(IDC_PREV_VALUE, nPrevStr);

	CString nEditText;
	GetDlgItemText(IDC_EDIT_NUM, nEditText);

	if (nPrevStr == "" && nEditText == "")	return;

	CString nOperator;
	GetDlgItemText(uiID, nOperator);

	SetDlgItemText(IDC_PREV_VALUE, nPrevStr + m_operator + nEditText);
	m_operator = nOperator;
	m_isProcessed = 1;

	if (uiID == IDC_BTN_ENT) {
		m_operator.Empty();
		OnBnClickedBtnEnt();
	}
}


// = 기호 버튼 클릭 시 Edit Control Text에 대한 연산을 수행합니다.
void CDlgForm::OnBnClickedBtnEnt()
{
	CString nFormula;
	GetDlgItemText(IDC_PREV_VALUE, nFormula);

	double nRet = ParseCStringtoValue(nFormula);
	
	if (nRet != NULL) {
		SetDlgItemText(IDC_EDIT_NUM, RstripDoublebyZero(nRet));
		m_isProcessed = -1;
	}
	else {
		AfxMessageBox(_T("Invalid input error : 분모는 0이 될 수 없습니다."));
		ClearControlText();
	}
}


// double을 string으로 변환하여 소수점 아래 0을 trim합니다.
CString CDlgForm::RstripDoublebyZero(double nTarget)
{
	CString nRet;
	string nStr = to_string(nTarget);
	size_t nDot = nStr.find('.');

	if (nDot != string::npos) {
		nStr.erase(nStr.find_last_not_of('0') + 1, string::npos);

		if (nStr.back() == '.') {
			nStr.pop_back();
		}
	}

	nRet = nStr.c_str();
	return nRet;
}
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

int main() {
	double myDouble = 3.14000; // 예제로 사용할 double 값

	// double 값을 문자열로 변환
	std::string str = std::to_string(myDouble);

	// 소수점 아래의 0 제거
	size_t dotPos = str.find('.');
	if (dotPos != std::string::npos) {
		str.erase(str.find_last_not_of('0') + 1, std::string::npos);
		if (str.back() == '.') {
			str.pop_back(); // 소수점 이후에 모든 0을 제거한 경우, 소수점도 제거
		}
	}

	// 결과 출력
	std::cout << str << std::endl;

	return 0;
}



// CString에서 수와 연산 기호를 분리하여 연산을 수행합니다.
double CDlgForm::ParseCStringtoValue(CString nTargetString)
{
	double nRet = 0.0;
	stack<double> nNumStack;
	stack<CString> nOpStack;
	int nLength = nTargetString.GetLength();
	CString nTarget;

	for (int i = 0; i < nLength; i++) {
		CString c = nTargetString.Mid(i, 1);

		// c가 기호가 아닐 때,
		if (c != "＋" && c != "－" && c != "×" && c != "÷") {
			nTarget += c;

			if (i == nLength - 1) {
				double x = nNumStack.top();
				nNumStack.pop();
				CString op = nOpStack.top();
				nOpStack.pop();

				double nTemp = CalculateValue(x, op, _wtof(nTarget));
				if (nTemp == NULL)	return NULL;

				nNumStack.push(nTemp);
			}
		}
		else {
			// c가 기호가 일 때,
			nNumStack.push(_wtof(nTarget));
			nTarget.Empty();

			if (nOpStack.empty()) {
				// 스택이 비어있으면 스택을 채웁니다.
				nOpStack.push(c);
			}
			else {
				// 스택이 차있으면 우선순위를 확인합니다.
				CString op = nOpStack.top();
				
				if (op == "×" || op == "÷") {
					double y = nNumStack.top();
					nNumStack.pop();
					double x = nNumStack.top();
					nNumStack.pop();
					
					double nTemp = CalculateValue(x, op, y);
					if (nTemp == NULL)	return NULL;

					nNumStack.push(nTemp);

					nOpStack.pop();
				}

				nOpStack.push(c);
			}
		}
	}

	while (!nOpStack.empty())
	{
		double y = nNumStack.top();
		nNumStack.pop();
		double x = nNumStack.top();
		nNumStack.pop();
		CString op = nOpStack.top();
		nOpStack.pop();

		double nTemp = CalculateValue(x, op, y);
		if (nTemp == NULL)	return NULL;

		nNumStack.push(nTemp);
	}

	nRet = nNumStack.top();
	nNumStack.pop();

	return nRet;
}

// 두 항을 연산하여 결과값을 반환합니다.
double CDlgForm::CalculateValue(double a, CString op, double b)
{
	cout << "CalculateValue : " << a << string(CT2CA(op)) << b << endl;
	double nRet = 0.0;

	if (op == "×") {
		nRet = a * b;
	}
	if (op == "÷") {
		if (b == 0)	nRet = NULL;
		else		nRet = a / b;
	}
	if (op == "＋") {
		nRet = a + b;
	}
	if (op == "－") {
		nRet = a - b;
	}
	cout << "Ret : " << nRet << endl;

	return nRet;
}
