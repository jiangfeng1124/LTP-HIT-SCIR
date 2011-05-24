#if !defined(AFX_GODIALOG_H__3B505785_9A71_440D_A2DB_FA84F46053CD__INCLUDED_)
#define AFX_GODIALOG_H__3B505785_9A71_440D_A2DB_FA84F46053CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// goDialog.h : header file
#include "WdCheckView.h"

/////////////////////////////////////////////////////////////////////////////
// CgoDialog dialog

class CgoDialog : public CDialog
{
// Construction
public:
	CgoDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CgoDialog)
	enum { IDD = 130};//IDD_GO };
	unsigned	m_numsen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CgoDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CgoDialog)

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GODIALOG_H__3B505785_9A71_440D_A2DB_FA84F46053CD__INCLUDED_)
