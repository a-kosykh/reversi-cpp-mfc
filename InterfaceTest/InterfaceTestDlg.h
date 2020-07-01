
// InterfaceTestDlg.h : ���� ���������
//

#pragma once


#include "ReversiBoard.h"
#include "ReversiPlayer.h"
#include "ReversiHumanPlayer.h"
#include "ReversiComputerPlayer.h"
#include "ReversiField.h"
#include "afxwin.h"


class CReversiField;

// ���������� ���� CInterfaceTestDlg
class CInterfaceTestDlg : public CDialogEx
{
// ��������
public:
	CInterfaceTestDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INTERFACETEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;
	CReversiField rField;
	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	void CreateBoard(int size);
	void CreatePlayer1(CString name, int type);
	void CreatePlayer2(CString name, int type);

	ReversiBoard* GetBoard();
	ReversiPlayer* GetPlayer();

private:
	ReversiBoard* board;
	ReversiPlayer* player1;
	ReversiPlayer* player2;
	ReversiPlayer* currentPlayer;
	bool bGameInProgress = false;


	void UpdateName();
	void CleanUp();
public:
	afx_msg void OnDestroy();
	void SetGameInProgress(bool inProgress);
	CButton mStartStopButton;
	CString strPlayerTurn;
	void TogglePlayer();
};
