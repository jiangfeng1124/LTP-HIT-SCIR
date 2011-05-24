#if !defined(AFX_SENTENCEVIEW_H__6C32755B_7F56_4CB1_8D97_8EEF68AB5680__INCLUDED_)
#define AFX_SENTENCEVIEW_H__6C32755B_7F56_4CB1_8D97_8EEF68AB5680__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SentenceView.h : header file
//
#include "WordArray.h"
#include "PairArray.h"
#define LEFT 0
/////////////////////////////////////////////////////////////////////////////
// CSentenceView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CSentenceView : public CFormView
{
private:
	void ConvertData();
	void Initiatate();
	bool MatchDistance(int nLeftNum,int nRightNum,int m_nDistance1,int m_nDistance2);
	CString Match(CString m_strWord1,CString m_strPOS1,CString m_strDirection,CString m_strWord2,CString m_strPOS2,CString m_strRelation,int m_nDistance1,int m_nDistance2,CPairArray& pairarray, CWordsArray& wordsarray);
	bool IsPair(CString strPOS1, CString strPOS2, CString strWord1, CString strWord2, 
		CPairArray& pairarray, CWordsArray& wordarray);
	bool IsLeft(CString strPOS1, CString strWord1, 
		CPairArray& pairarray, CWordsArray& wordarray);
	bool IsRight(CString strPOS1, CString strWord1, 
		CPairArray& pairarray, CWordsArray& wordarray);
protected:
	CSentenceView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSentenceView)

// Form Data
public:
	//{{AFX_DATA(CSentenceView)
	enum { IDD = IDD_FORMVIEW };
	CListBox	m_lbMatchedPair;
	CListBox	m_lbDistance;
	CListBox	m_lbDirection;
	CListBox	m_lbResult;
	CEdit	m_editSentence;
	CString	m_strPOS1;
	CString	m_strPOS2;
	CString	m_strWord1;
	CString	m_strWord2;
	int		m_nCount;
	CString	m_strRelation;
	//}}AFX_DATA

// Attributes
public:

	CString m_strDirection;
	int m_nDistance1;
	int m_nDistance2;
	CString	m_strMatchedPair;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSentenceView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSentenceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSentenceView)
	afx_msg void OnSearch();
	afx_msg void OnDblclkResult();
	afx_msg void OnReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENTENCEVIEW_H__6C32755B_7F56_4CB1_8D97_8EEF68AB5680__INCLUDED_)
