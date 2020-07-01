#pragma once
#include "InterfaceTestDlg.h"

// CReversiField

class CInterfaceTestDlg;

class CReversiField : public CWnd
{
	DECLARE_DYNAMIC(CReversiField)

public:
	CReversiField();
	virtual ~CReversiField();

protected:
	DECLARE_MESSAGE_MAP()
private:
	bool RegisterClass();
public:
	afx_msg void OnPaint();

public:
	// Установка размера игрового поля
	void SetFieldSize(int size);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

private:
	void GetFieldPosition(CPoint point, int& xpos, int& ypos);
	//int** fields;
	
public:
	afx_msg void OnDestroy();
private:
//	int GetRectFromField(int row, int col);
	CRect GetRectFromField(int row, int col);
public:
	void DrawBlackCell(CPaintDC& dc, CRect rect);
private:
	void DrawWhiteCell(CPaintDC& dc, CRect rect);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	int nSelectedX;
	int nSelectedY;
	CInterfaceTestDlg* gameParent;
	bool bHasLegalMovesComputedForThisTurn = false;
	bool bGameInProgress = false;
	bool bHasLegalMoves = false;
	void HighlightSelection(CPaintDC& dc);
	bool CheckEndCondition();
public:
	afx_msg void OnMouseLeave();
	void SetGameParent(CInterfaceTestDlg* p);
	void SetGameInProgress(bool inProgress);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


