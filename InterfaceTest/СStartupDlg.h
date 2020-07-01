#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "InterfaceTestDlg.h"

// �StartupDlg dialog

class �StartupDlg : public CDialogEx
{
	DECLARE_DYNAMIC(�StartupDlg)

public:
	�StartupDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~�StartupDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STARTDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CEdit mSizeEdit;
public:
	CString strSizeEdit;
	CSpinButtonCtrl mSizeSpin;
private:
	CString strPlayerName1;
	CString strPlayerName2;
	CComboBox mTypePlayer1;
	CComboBox mTypePlayer2;

	CInterfaceTestDlg* dlgParent;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedStartbutton();
	void SetDlgParent(CInterfaceTestDlg* p);
};
