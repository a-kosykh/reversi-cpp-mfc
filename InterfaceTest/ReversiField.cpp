// ReversiField.cpp : implementation file
//

#include "stdafx.h"
#include "InterfaceTest.h"
#include "InterfaceTestDlg.h"
#include "ReversiField.h"

#define REVERSIFIELD_CLASSNAME L"ReversiField"
#define FIELDNUMBERSPACE 20
#define OFFSET 2
#define TIMER_ID 101

// CReversiField

IMPLEMENT_DYNAMIC(CReversiField, CWnd)

CReversiField::CReversiField()
{
	gameParent = nullptr;
	this->RegisterClass();

	nSelectedX = -1;
	nSelectedY = -1;
}

CReversiField::~CReversiField()
{
}


BEGIN_MESSAGE_MAP(CReversiField, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CReversiField message handlers




bool CReversiField::RegisterClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, REVERSIFIELD_CLASSNAME, &wndcls))) {
		wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
		wndcls.hInstance = hInst;
		wndcls.hIcon = NULL;
		wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = REVERSIFIELD_CLASSNAME;

		if (!AfxRegisterClass(&wndcls)) {
			AfxThrowResourceException();
			return FALSE;
		}
	}
	return TRUE;
}


void CReversiField::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages

	if (this->gameParent == nullptr || this->gameParent->GetBoard() == nullptr)
		return;

	CRect rect;
	GetClientRect(&rect);

	int fieldSize = this->gameParent->GetBoard()->GetBoardSize();
	
	CPen ourPen;
	HGDIOBJ oldPen;
	ourPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

	oldPen = dc.SelectObject(ourPen);

	int hPartSize = (rect.right - FIELDNUMBERSPACE) / fieldSize;
	int wPartSize = (rect.bottom - FIELDNUMBERSPACE) / fieldSize;

	this->HighlightSelection(dc);

	for (int i = 0; i < fieldSize + 1; ++i) {
		dc.MoveTo(FIELDNUMBERSPACE + i * hPartSize, FIELDNUMBERSPACE);
		dc.LineTo(FIELDNUMBERSPACE + i * hPartSize, rect.bottom);
		dc.MoveTo(FIELDNUMBERSPACE , i * wPartSize + FIELDNUMBERSPACE);
		dc.LineTo(rect.right, i * wPartSize + FIELDNUMBERSPACE);
	}

	dc.SetTextColor(RGB(255, 0, 0));
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextAlign(TA_TOP | TA_LEFT);

	for (int i = 0; i < fieldSize; ++i) {
		CString str;
		str.Format(L"%d", i);
		dc.TextOutW(0, FIELDNUMBERSPACE / 2 + wPartSize / 2 + i * wPartSize, str);
		dc.TextOutW(FIELDNUMBERSPACE / 2 + hPartSize / 2 + i * hPartSize, 0, str);
	}

	for (int i = 0; i < fieldSize; ++i) {
		for (int j = 0; j < fieldSize; ++j) {
			if (this->gameParent->GetBoard()->GetCell(i, j).type == CELL_BLACK) {
				this->DrawBlackCell(dc, this->GetRectFromField(i, j));
			}
			if (this->gameParent->GetBoard()->GetCell(i, j).type == CELL_WHITE) {
				this->DrawWhiteCell(dc, this->GetRectFromField(i, j));
			}
		}
	}
	

	dc.SelectObject(oldPen);
	ourPen.DeleteObject();
}


void CReversiField::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (bGameInProgress && this->gameParent->GetPlayer()->IsHuman()) {
		if (this->gameParent == nullptr || this->gameParent->GetBoard() == nullptr)
			return;
		
		bool bMoveMade = false;

		if (!bHasLegalMovesComputedForThisTurn) {
			bHasLegalMoves = this->gameParent->GetBoard()->hasLegalMoves(this->gameParent->GetPlayer()->GetType());
			bHasLegalMovesComputedForThisTurn = true;
		}

		if (!bHasLegalMoves) {

		}

		if (bHasLegalMoves) {
			int x, y;
			GetFieldPosition(point, x, y);
			if (x < 0 || y < 0) {
				return;
			}
			bMoveMade = this->gameParent->GetPlayer()->MakeMove(y, x);
		}
		if (this->CheckEndCondition()) {
			this->SetGameInProgress(false);
			bHasLegalMovesComputedForThisTurn = false;
			bHasLegalMoves = false;
			this->gameParent->Invalidate();
		}
		else {
			if (bMoveMade || (bHasLegalMovesComputedForThisTurn && !bHasLegalMoves)) {
				bHasLegalMovesComputedForThisTurn = false;
				bHasLegalMoves = false;
				this->gameParent->TogglePlayer();
				this->Invalidate();
			}
			this->Invalidate();
		}

	}
	
	CWnd::OnLButtonDown(nFlags, point);
}

bool CReversiField::CheckEndCondition()
{
	
	if (this->gameParent->GetBoard()->checkEndCondition()){
		KillTimer(TIMER_ID);
		this->bGameInProgress = false;
		if (this->gameParent->GetBoard()->GetWinner() == 0) {
			CString str;
			str.Format(L"Ничья");
			AfxMessageBox(str);
		}
		if (this->gameParent->GetBoard()->GetWinner() == 1) {
			CString str;
			str.Format(L"Черные фишки победили");
			AfxMessageBox(str);
		}
		if (this->gameParent->GetBoard()->GetWinner() == 2) {
			CString str;
			str.Format(L"Белые фишки победили");
			AfxMessageBox(str);
		}
		this->gameParent->SetGameInProgress(false);
		return true;
	}
	return false;
}

void CReversiField::GetFieldPosition(CPoint point, int& xpos, int& ypos)
{
	if (this->gameParent == nullptr || this->gameParent->GetBoard() == nullptr)
		return;
	
	int fieldSize = this->gameParent->GetBoard()->GetBoardSize();

	CRect rect;
	GetClientRect(&rect);
	int hPartSize = (rect.right - FIELDNUMBERSPACE) / fieldSize;
	int wPartSize = (rect.bottom - FIELDNUMBERSPACE) / fieldSize;

	for (int i = 0; i < fieldSize; ++i) {
		if ((point.x > FIELDNUMBERSPACE + i * hPartSize) && (point.x < FIELDNUMBERSPACE + (i + 1) * hPartSize)) {
			ypos = i;
		}
		if ((point.y > FIELDNUMBERSPACE + i * wPartSize) && (point.y < FIELDNUMBERSPACE + (i + 1) * wPartSize)) {
			xpos = i;
		}
	}
}


void CReversiField::OnDestroy()
{
	CWnd::OnDestroy();
	// TODO: Add your message handler code here
}





//int CReversiField::GetRectFromField(int row, int col)
//{
//	return 0;
//}


CRect CReversiField::GetRectFromField(int row, int col)
{
	if (this->gameParent == nullptr || this->gameParent->GetBoard() == nullptr)
		return CRect(0, 0, 0, 0);

	int fieldSize = this->gameParent->GetBoard()->GetBoardSize();
	
	CRect rect;
	CRect rectWnd;
	GetClientRect(&rectWnd);
	int hPartSize = (rectWnd.right - FIELDNUMBERSPACE) / fieldSize;
	int wPartSize = (rectWnd.bottom - FIELDNUMBERSPACE) / fieldSize;

	rect.left = FIELDNUMBERSPACE + row * hPartSize + 1;
	rect.top = FIELDNUMBERSPACE + col * wPartSize + 1;
	rect.right = FIELDNUMBERSPACE + (row+1) * hPartSize - 1;
	rect.bottom = FIELDNUMBERSPACE + (col+1) * wPartSize - 1;

	return rect;
}


void CReversiField::DrawBlackCell(CPaintDC& dc, CRect rect)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));
	HGDIOBJ oldBrush = dc.SelectObject(brush);

	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HGDIOBJ oldPen = dc.SelectObject(pen);

	Ellipse(dc, rect.left + 2, rect.top + 2, rect.right - 2, rect.bottom - 2);
	
	dc.SelectObject(oldPen);
	pen.DeleteObject();

	dc.SelectObject(oldBrush);
	brush.DeleteObject();

}


void CReversiField::DrawWhiteCell(CPaintDC& dc, CRect rect)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	HGDIOBJ oldBrush = dc.SelectObject(brush);

	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HGDIOBJ oldPen = dc.SelectObject(pen);

	Ellipse(dc, rect.left + 2, rect.top + 2, rect.right - 2, rect.bottom - 2);

	dc.SelectObject(oldPen);
	pen.DeleteObject();

	dc.SelectObject(oldBrush);
	brush.DeleteObject();
}


void CReversiField::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int x, y;
	GetFieldPosition(point, x, y);
	if (nSelectedX != x || nSelectedY != y) {
		nSelectedX = x;
		nSelectedY = y;
		this->Invalidate();
	}
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.hwndTrack = this->m_hWnd;
	tme.dwFlags = TME_LEAVE;
	tme.dwHoverTime = HOVER_DEFAULT;
	CWnd::OnMouseMove(nFlags, point);
}


void CReversiField::HighlightSelection(CPaintDC& dc)
{
	if ((nSelectedX < 0) || (nSelectedY < 0))
		return;

	CRect rect = GetRectFromField(nSelectedY, nSelectedX);
	CBrush brush;
	brush.CreateSolidBrush(RGB(125, 249, 255));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Rectangle(rect);
	dc.SelectObject(oldBrush);
	brush.DeleteObject();

}


void CReversiField::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default
	nSelectedX = -1;
	nSelectedY = -1;
	this->Invalidate();
	CWnd::OnMouseLeave();
}

void CReversiField::SetGameParent(CInterfaceTestDlg * p)
{
	this->gameParent = p;
}

void CReversiField::SetGameInProgress(bool inProgress)
{
	if (bGameInProgress != inProgress) {
		this->bGameInProgress = inProgress;
		this->gameParent->SetGameInProgress(inProgress);
		if (inProgress)
			SetTimer(TIMER_ID, 1000, NULL);
	}
}


void CReversiField::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (bGameInProgress && (!this->gameParent->GetPlayer()->IsHuman())) {
		if (this->gameParent == nullptr || this->gameParent->GetBoard() == nullptr)
			return;

		bool bMoveMade = false;

		if (!bHasLegalMovesComputedForThisTurn) {
			bHasLegalMoves = this->gameParent->GetBoard()->hasLegalMoves(this->gameParent->GetPlayer()->GetType());
			bHasLegalMovesComputedForThisTurn = true;
		}

		if (!bHasLegalMoves) {

		}

		if (bHasLegalMoves) {
			bMoveMade = this->gameParent->GetPlayer()->MakeMove(0, 0);
		}
		if (this->CheckEndCondition()) {
			this->SetGameInProgress(false);
			bHasLegalMovesComputedForThisTurn = false;
			this->gameParent->Invalidate();
		}
		else {
			if (bMoveMade || (bHasLegalMovesComputedForThisTurn && !bHasLegalMoves)) {
				bHasLegalMovesComputedForThisTurn = false;
				bHasLegalMoves = false;
				this->gameParent->TogglePlayer();
				this->Invalidate();
			}
			this->Invalidate();
		}

	}
	CWnd::OnTimer(nIDEvent);
}
