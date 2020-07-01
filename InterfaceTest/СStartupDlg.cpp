// �StartupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InterfaceTest.h"
#include "�StartupDlg.h"
#include "afxdialogex.h"


// �StartupDlg dialog

IMPLEMENT_DYNAMIC(�StartupDlg, CDialogEx)

�StartupDlg::�StartupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STARTDIALOG, pParent)
	, strSizeEdit(_T(""))
	, strPlayerName1(_T(""))
	, strPlayerName2(_T(""))
{

}

�StartupDlg::~�StartupDlg()
{
}

void �StartupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mSizeEdit);
	DDX_Text(pDX, IDC_EDIT1, strSizeEdit);
	DDX_Control(pDX, IDC_SPIN1, mSizeSpin);
	DDX_Text(pDX, IDC_EDITNAMEPLAYER1, strPlayerName1);
	DDX_Text(pDX, IDC_EDITNAMEPLAYER2, strPlayerName2);
	DDX_Control(pDX, IDC_COMBOTYPEPLAYER1, mTypePlayer1);
	DDX_Control(pDX, IDC_COMBOTYPEPLAYER2, mTypePlayer2);
}


BEGIN_MESSAGE_MAP(�StartupDlg, CDialogEx)
	ON_BN_CLICKED(ID_STARTBUTTON, &�StartupDlg::OnBnClickedStartbutton)
END_MESSAGE_MAP()


// �StartupDlg message handlers


BOOL �StartupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	mSizeSpin.SetBuddy(&mSizeEdit);
	mSizeSpin.SetRange(4, 10);
	mSizeSpin.SetPos(3);

	mTypePlayer1.SetCurSel(0);
	mTypePlayer2.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void �StartupDlg::OnBnClickedStartbutton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if ((strPlayerName1 == L"") || strPlayerName2 == L"") {
		AfxMessageBox(L"��� ������ �� ����� ���� ������");
		return;
	}

	if (_ttoi(strSizeEdit) % 2 == 1) {
		AfxMessageBox(L"������ ���� ������ ���� ������");
		return;
	}

	dlgParent->CreateBoard(_ttoi(strSizeEdit));
	dlgParent->CreatePlayer1(strPlayerName1, mTypePlayer1.GetCurSel());
	dlgParent->CreatePlayer2(strPlayerName2, mTypePlayer2.GetCurSel());

	this->EndDialog(IDOK);
}

void �StartupDlg::SetDlgParent(CInterfaceTestDlg * p)
{
	this->dlgParent = p;
}
