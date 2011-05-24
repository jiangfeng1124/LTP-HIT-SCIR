// IsSaveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wdCheck.h"
#include "IsSaveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIsSaveDlg dialog


CIsSaveDlg::CIsSaveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIsSaveDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIsSaveDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CIsSaveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIsSaveDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIsSaveDlg, CDialog)
	//{{AFX_MSG_MAP(CIsSaveDlg)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIsSaveDlg message handlers


