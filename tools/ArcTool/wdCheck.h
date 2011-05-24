// wdCheck.h : main header file for the WDCHECK application
//

#if !defined(AFX_WDCHECK_H__D23FCDCE_DB89_4197_96B3_2F8B68666AAB__INCLUDED_)
#define AFX_WDCHECK_H__D23FCDCE_DB89_4197_96B3_2F8B68666AAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWdCheckApp:
// See wdCheck.cpp for the implementation of this class
//

class CWdCheckApp : public CWinApp
{
public:
	CWdCheckApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWdCheckApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWdCheckApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WDCHECK_H__D23FCDCE_DB89_4197_96B3_2F8B68666AAB__INCLUDED_)
