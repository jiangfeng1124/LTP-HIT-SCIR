     // ArcView.h : interface of the CArcView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARCVIEW_H__07E6E4E6_0295_4A83_A8A6_61B07580EA38__INCLUDED_)
#define AFX_ARCVIEW_H__07E6E4E6_0295_4A83_A8A6_61B07580EA38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define SCROLLHIGH 1500
#define POSITION_X 150
#define POSITION_Y SCROLLHIGH-150
#define ALLPHRASE 8

class CWdCheckDoc;
#include "Pair.h"
#include "wdCheckView.h"
#include "Relation.h"

const int g_nWeigth = 40;//40;

class CArcView : public CScrollView
{
private:
	CPoint m_pointTopLeft;
	
protected: // create from serialization only
	CArcView();
	DECLARE_DYNCREATE(CArcView)

// Attributes
public:
	CWdCheckDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArcView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CArcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
//	void InitRelation();
//	vector <string> vecRelation;
//	string vecRelation[100];
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CArcView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
//	CString DependencyRelation(string lefttag,string righttag,int leftnum,int rightnum);
//	void DependencyRelation(CRelation relation);
	void ChangeRelation(CPoint point);
	void DeleteArc(CPoint point);
	void DisplayMenu(CPoint point);
	void DrawText(CDC* pDC);
	void DrawArc(CDC* pDC);

	CPair m_pair;
	vector < CRelation > m_vecRelation;
	int	m_ScrollHigh;
	int m_ScrollWidth;
	int m_nLeftBound;
	int m_nRightBound;
	int menuID;
	vector <CRect> m_vecRect;
 	CString PhraseArray[ALLPHRASE];
	BOOL bDowned;//是否在拉动
	BOOL bUped;//
	CPoint ptCurrent,ptLast;//按下位置

public:
	int m_nCountClick;
	int m_nRightClick;

};

#ifndef _DEBUG  // debug version in ArcView.cpp
inline CWdCheckDoc* CArcView::GetDocument()
   { return (CWdCheckDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARCVIEW_H__07E6E4E6_0295_4A83_A8A6_61B07580EA38__INCLUDED_)
