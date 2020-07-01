
// InterfaceTestDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "InterfaceTest.h"
#include "InterfaceTestDlg.h"
#include "afxdialogex.h"
#include "СStartupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно CInterfaceTestDlg



CInterfaceTestDlg::CInterfaceTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INTERFACETEST_DIALOG, pParent)
	, strPlayerTurn(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	board = nullptr;
	player1 = nullptr;
	player2 = nullptr;
	currentPlayer = nullptr;
}

void CInterfaceTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REVERSIFIELD, rField);
	DDX_Control(pDX, IDC_BUTTON2, mStartStopButton);
	DDX_Text(pDX, IDC_STATIC1, strPlayerTurn);
}

BEGIN_MESSAGE_MAP(CInterfaceTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CInterfaceTestDlg::OnBnClickedButton2)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// обработчики сообщений CInterfaceTestDlg

BOOL CInterfaceTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	rField.SetGameParent(this);


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CInterfaceTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CInterfaceTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CInterfaceTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CInterfaceTestDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	if (bGameInProgress) {
		CleanUp();
		this->SetGameInProgress(false);
		this->Invalidate();
	}
	else {
		СStartupDlg sdlg;
		sdlg.SetDlgParent(this);
		int nRes = sdlg.DoModal();

		if (nRes == IDOK) {
			currentPlayer = player1;
			this->SetGameInProgress(true);
			this->UpdateName();
			this->Invalidate();
		}
	}
}

void CInterfaceTestDlg::CreateBoard(int size)
{
	this->board = new ReversiBoard(size);

}

void CInterfaceTestDlg::CreatePlayer1(CString name, int type)
{
	if (type == 0)
		this->player1 = new ReversiHumanPlayer();
	else
		this->player1 = new ReversiComputerPlayer();

	player1->setupPlayer(name, CELL_BLACK);
	player1->setBoard(this->board);
}

void CInterfaceTestDlg::CreatePlayer2(CString name, int type)
{
	if (type == 0)
		this->player2 = new ReversiHumanPlayer();
	else
		this->player2 = new ReversiComputerPlayer();

	player2->setupPlayer(name, CELL_WHITE);
	player2->setBoard(this->board);
}

ReversiBoard * CInterfaceTestDlg::GetBoard()
{
	return board;
}

ReversiPlayer * CInterfaceTestDlg::GetPlayer()
{
	return currentPlayer;
}

void CInterfaceTestDlg::UpdateName()
{
	CString str;
	str.Format(L"Ход игрока: %s", currentPlayer->GetName());
	strPlayerTurn = str;
	UpdateData(FALSE);
}

void CInterfaceTestDlg::CleanUp()
{
	if (player1 != nullptr) {
		delete player1;
		player1 = nullptr;
	}
	if (player2 != nullptr) {
		delete player2;
		player2 = nullptr;
	}
	if (board != nullptr) {
		delete board;
		board = nullptr;
	}
	currentPlayer = nullptr;
}


void CInterfaceTestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	CleanUp();
	// TODO: Add your message handler code here
}

void CInterfaceTestDlg::SetGameInProgress(bool inProgress)
{
	this->bGameInProgress = inProgress;
	this->rField.SetGameInProgress(inProgress);
	if (inProgress) {
		mStartStopButton.SetWindowTextW(L"Остановить");
	}
	else {
		mStartStopButton.SetWindowTextW(L"Запустить");
		CleanUp();
	}
}

void CInterfaceTestDlg::TogglePlayer()
{
	if (currentPlayer != player1)
		currentPlayer = player1;
	else
		currentPlayer = player2;

	UpdateName();
}
