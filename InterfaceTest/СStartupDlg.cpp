// ÑStartupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InterfaceTest.h"
#include "ÑStartupDlg.h"
#include "afxdialogex.h"


// ÑStartupDlg dialog

IMPLEMENT_DYNAMIC(ÑStartupDlg, CDialogEx)

ÑStartupDlg::ÑStartupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STARTDIALOG, pParent)
	, strSizeEdit(_T(""))
	, strPlayerName1(_T(""))
	, strPlayerName2(_T(""))
{

}

ÑStartupDlg::~ÑStartupDlg()
{
}

void ÑStartupDlg::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(ÑStartupDlg, CDialogEx)
	ON_BN_CLICKED(ID_STARTBUTTON, &ÑStartupDlg::OnBnClickedStartbutton)
END_MESSAGE_MAP()


// ÑStartupDlg message handlers


BOOL ÑStartupDlg::OnInitDialog()
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


void ÑStartupDlg::OnBnClickedStartbutton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if ((strPlayerName1 == L"") || strPlayerName2 == L"") {
		AfxMessageBox(L"Èìÿ èãğîêà íå ìîæåò áûòü ïóñòûì");
		return;
	}

	if (_ttoi(strSizeEdit) % 2 == 1) {
		AfxMessageBox(L"Ğàçìåğ ïîëÿ äîëæåí áûòü ÷åòíûé");
		return;
	}

	dlgParent->CreateBoard(_ttoi(strSizeEdit));
	dlgParent->CreatePlayer1(strPlayerName1, mTypePlayer1.GetCurSel());
	dlgParent->CreatePlayer2(strPlayerName2, mTypePlayer2.GetCurSel());

	this->EndDialog(IDOK);
}

void ÑStartupDlg::SetDlgParent(CInterfaceTestDlg * p)
{
	this->dlgParent = p;
}
